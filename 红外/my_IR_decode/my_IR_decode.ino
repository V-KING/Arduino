#define DEBUG  1

int dataTime[33]={0};	
int data[32]={0};
int flag_putTime=0;			//数据从什么时候开始放时间
int bitnum;				//是第几位的时间
int IRRECV_OK;				//红外接受完成的flag
unsigned char ircode[32]={0};		//我们的数据是8位的，用unsigned char 或者byte 
unsigned long prior_time;     		//记录上一次的时间					
unsigned long now_time;    		//记录现在的时间 
unsigned long count_100us;		//100us的计数器,就是100us加一次

void Interrupt_falling(){
    //now_time=millis();		//知道这里为什么不能用millis()吗？因为精度不够
    now_time = count_100us;  
    if(flag_putTime){			//第一次下降沿是不能算时间的。所以从第二次开始计算时间
	if(now_time - prior_time > 100){//只要NEC协议中13.5ms是在>10ms范围内的。所以这里大约计算
	    bitnum = 0;			//
	}
	dataTime[bitnum] = now_time - prior_time;//核心代码
	//Serial.println(dataTime[bitnum]);
	bitnum++;			//数组的下表要加1
	prior_time=now_time;		//重新给上一次的时间赋值

	if(bitnum == 33){		//如果接受数据到了33位了，我们就将下标归零,下次从头开始
	    bitnum = 0;			
	    flag_putTime = 0;		//接受完一帧数据后，就不能再放了。
	    IRRECV_OK = 1;		//接收完成了
	}
    }
    else{				//flag_putTime初始值是0，所以第一次是执行下面的
	prior_time = now_time;		//从这一刻开始，作为前一次的时间
	flag_putTime=1;			//flag_putTime=1，下次就是可以执行上面的语句了
	IRRECV_OK=0;			//没有头，也就是没有开始肯定是没有接受完成
    }
}

void parseTimeTo01(){
    int	 k=1;
    unsigned char value=0;
    for(int j=0; j<4; j++){
	for(int i=0; i<8; i++){
	    value >>= 1;
	    if( dataTime[k] > 18){
		value=value | 0x80;		
	    }
	    k++;
	}
	ircode[j]=value;
	value=0;
    }
#ifdef DEBUG
    Serial.print(ircode[0],HEX);
    Serial.print(ircode[1],HEX);
    Serial.print(ircode[2],HEX);
    Serial.print(ircode[3],HEX);
    Serial.print();
#endif
}

/* 
 * 将定时器中断设为1ms 
 */
void init_time()  
{  
  TCCR2A |= (1 <<WGM21) | (1 << WGM20);  //fast PWM模式
  TCCR2B |= (1 << CS22 );  			     //64分频
  TCCR2B &= ~((1 <<CS21) | (1 <<CS20));  //64分频
  TCCR2B &= ~((1 << WGM21 ) | (1 << WGM20));  
  ASSR |= ( 1 << AS2 );                  //时钟和晶振同步
  TIMSK2 |= ( 1 << TOIE2 ) | ( 0 << OCIE2B );//使能定时中断
  TCNT2 = 231;  							 //初始化技术寄存器的值
  sei();  								 //开总中断	
}  


/*
 * 定时器2溢出中断
 * */
ISR(TIMER2_OVF_vect)  
{  
  TCNT2 = 231;  							//重新填写定时器2计数器
  ++count_100us;  							//ms计数加1
}  



void setup(){
    Serial.begin(9600);
    init_time();  
    
    attachInterrupt(0,Interrupt_falling,FALLING);
    //prior_time=millis();
    prior_time = count_100us;
}



void loop(){
    if(IRRECV_OK){
	IRRECV_OK=0;
	parseTimeTo01();
    }
}
