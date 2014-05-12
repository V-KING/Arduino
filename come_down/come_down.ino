
/*
 * ====================================================
 *      Name: come_down.ino
 *   Version: 1.0
 *  Compiler: arduino-IDE
 *   Company: WWW.SOGWORKS.CN 
 * Functioin: a clock with arduino uno
 * =====================================================
 * */

/* 
 *数码管引脚号:(3462BS这一面对着你)
 *数码管上排：12 - 6
 *数码管下排：1  - 6 
 *
 * 数码管引脚号对应的 led段：
 * 数码管引脚 - arduino引脚
 * A-11            7
 * B-7             6
 * C-4             5
 * D-2             10
 * E-1             11
 * F-10            8
 * G-5             9
 * DP-3            4
 * DIG1-12         13
 * DIG2-9          12
 * DIG3-8          3 
 * DIG4-6          2 
 * */



//设置控制各段的数字IO 脚
int a=7;			//定义数字接口7 连接a 段数码管
int b=6;			// 定义数字接口6 连接b 段数码管
int c=5;			// 定义数字接口5 连接c 段数码管
int d=10;			// 定义数字接口10 连接d 段数码管
int e=11;			// 定义数字接口11 连接e 段数码管
int f=8;			// 定义数字接口8 连接f 段数码管
int g=9;			// 定义数字接口9 连接g 段数码管
int dp=4;			// 定义数字接口4 连接dp 段数码管
int bitn[4]={
	13,12,3,2};		//有四个数码管，从左到右它们的共阴极引脚分别接arduino的13,12,3,2引脚
/* 
 * 我们用的3462BS是共阳极的所以应该是,之前用的是共阴极的数码管
 * 所以可以只需要改动下面一行代码就可以了
 * 二极管正极--->
 *
 */
int high=LOW;					  //共阴极时high=HIGH；
int low=HIGH;					  //共阳极时low=LOW;
/* **时间用到的变量** */
int shi1=0;                       //小时的第一个数
int shi2=0;                       //小时的第二个数
int fen1=0;                       //小时的第一个数
int fen2=0;                       //小时的第二个数
/* **定时器用到的变量** */
byte miao=0;          		  //秒
byte fen=0;	          		  //分
byte shi=12;           		  //时
/* **串口相关变量** */           
int restBytes=0;				  //串口中剩下的字节数
/* **秒表相关变量** */
int buttonPP = A0;				  //play OR pause 按键
void digital_0(void)              //显示数字0
{
	unsigned char j;
	digitalWrite(a,high);
	digitalWrite(b,high);
	digitalWrite(c,high);
	digitalWrite(d,high);
	digitalWrite(e,high);
	digitalWrite(f,high);

	digitalWrite(g,low);
}
//显示数字1
void digital_1(void)             
{
	unsigned char j;
	digitalWrite(c,high);			//给数字接口5 引脚高电平，点亮c 段
	digitalWrite(b,high);			//点亮b 段
	for(j=7;j<=11;j++)			//熄灭其余段
		digitalWrite(j,low);
	digitalWrite(dp,low);			//熄灭小数点DP 段
}
//显示数字2
void digital_2(void) 			
{
	unsigned char j;
	digitalWrite(b,high);
	digitalWrite(a,high);
	for(j=9;j<=11;j++)
		digitalWrite(j,high);
	digitalWrite(dp,low);
	digitalWrite(c,low);
	digitalWrite(f,low);
}
//显示数字3
void digital_3(void) 			
{
	unsigned char j;
	digitalWrite(g,high);
	digitalWrite(d,high);
	for(j=5;j<=7;j++)
		digitalWrite(j,high);
	digitalWrite(dp,low);
	digitalWrite(f,low);
	digitalWrite(e,low);
}
//显示数字4
void digital_4(void) 
{
	digitalWrite(c,high);
	digitalWrite(b,high);
	digitalWrite(f,high);
	digitalWrite(g,high);
	digitalWrite(dp,low);
	digitalWrite(a,low);
	digitalWrite(e,low);
	digitalWrite(d,low);
}
//显示数字5
void digital_5(void) 
{
	unsigned char j;
	for(j=7;j<=9;j++)
		digitalWrite(j,high);
	digitalWrite(c,high);
	digitalWrite(d,high);
	digitalWrite(dp,low);
	digitalWrite(b,low);
	digitalWrite(e,low);
}
//显示数字6
void digital_6(void) 
{
	unsigned char j;
	for(j=7;j<=11;j++)
		digitalWrite(j,high);
	digitalWrite(c,high);
	digitalWrite(dp,low);
	digitalWrite(b,low);
}
//显示数字7
void digital_7(void) 
{
	unsigned char j;
	for(j=5;j<=7;j++)
		digitalWrite(j,high);
	digitalWrite(dp,low);
	for(j=8;j<=11;j++)
		digitalWrite(j,low);
}
//显示数字8
void digital_8(void) 
{
	unsigned char j;
	for(j=5;j<=11;j++)
		digitalWrite(j,high);
	digitalWrite(dp,low);
}
//显示数字9
void digital_9(void) 
{
	unsigned char j;
	for(j=5;j<=11;j++)
		digitalWrite(j,high);
	digitalWrite(dp,low);
	digitalWrite(e,low);
}
/*
 *当lightUp_flag=1时，就是显示两个点 
 *当lightUp_flag=0时，就是不显示两个点 
 */
void dock(int lightUp_flag) 
{
	unsigned char j;
	for(j=5;j<=11;j++)
		digitalWrite(j,low);
	if(lightUp_flag==1){
		digitalWrite(dp,high);
	}
	else{
		digitalWrite(dp,low);
	}
}
/*
 * 将数码管全部灭了
 */
void clearLED()
{
	digitalWrite(a,low);
	digitalWrite(b,low);
	digitalWrite(c,low);
	digitalWrite(d,low);
	digitalWrite(e,low);
	digitalWrite(f,low);
	digitalWrite(g,low);
	digitalWrite(dp,low);
	digitalWrite(13,high);
	digitalWrite(12,high);
	digitalWrite(3,high);
	digitalWrite(2,high);
}
/* 
 * 第n个数码管的显示data
 * n   :从0开始
 * data:数码管显示的数字[0,9]
 */
void disp(int n,int data)
{
	clearLED();			//先灭一遍，选择好了是哪个后，在点亮第n个数码管
	switch(data)
	{
		case 0:
			digital_0();
			break;
		case 1:
			digital_1();
			break;
		case 2:
			digital_2();
			break;
		case 3:
			digital_3();
			break;
		case 4:
			digital_4();
			break;
		case 5:
			digital_5();
			break;
		case 6:
			digital_6();
			break;
		case 7:
			digital_7();
			break;
		case 8:
			digital_8();
			break;
		case 9:
			digital_9();
			break;
		default:
			break;  
	}
	digitalWrite(bitn[n],low);			//点亮第n个数码管
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
	TCNT2 = 6;  							 //初始化技术寄存器的值
	sei();  								 //开总中断	
}  

int count_ms=0;							//ms计数器
int count_10ms=0;						//ms计数器
/*
 * 定时器2溢出中断
 * */
ISR(TIMER2_OVF_vect)  
{  
	TCNT2 = 6;  							//重新填写定时器2计数器
	++count_ms;  							//ms计数加1
	//当到了1s的时候，就让秒计数器加1,并且ms计数器清零
	if(count_ms>=1000){					
		count_ms=0;
		miao++;
	}
}  
/* 
 * 不更新时间，就是计数器里的东西不加了
 * */
void NotUpdataTime(){
	TIMSK2 &= ~( 1 << TOIE2 ) ;//禁止定时中断
}
/* 
 * 更新就是说，要将计数器重新工作
 * */
void updateTime(){
	init_time();
}

//前面两个显示数字preTwoNum，后面连个数码管显示数字sencondTwoNum
void disptime(int preTwoNum,int secondTwoNum){
	//一个一个的显示时间
	disp(0,preTwoNum/10);		//显示变量内容
	delay(1);
	disp(1,preTwoNum%10);		//显示变量内容
	delay(1);
	disp(2,secondTwoNum/10);		//显示变量内容
	delay(1);
	disp(3,secondTwoNum%10);		//显示变量内容
	delay(1);
}

void setup()
{
	Serial.begin(9600);  
	init_time();  
	for(int i=2;i<=13;i++)
		pinMode(i,OUTPUT);//设置4～11 引脚为输出模式
	pinMode(A0,INPUT_PULLUP);		
}
/* 
 * 参数：button接到按键的引脚号
 * 返回：按键状态。
 * 返回的按键的状态有：UNPRESSED,PRESS_MOMENT,PRESS_ALLWAYS,RELEASE_MOMENT;
 * */

int UNPRESSED= 1;
int PRESSED= 0;
int PRESS_MOMENT=111;
int PRESS_ALLWAYS=222;
int RELEASE=333;
int priorButtonState = UNPRESSED;
int buttonDetect(int button){
	int state;
	if(digitalRead(button)==PRESSED){//本次按下
		if(priorButtonState==UNPRESSED){
			state = PRESS_MOMENT;		//按下的一瞬间
		}
		else{
			state = PRESS_ALLWAYS;		//一直按着
		}
		priorButtonState = PRESSED;		//赋值
	}
	else {//本次没有按下
		if(priorButtonState == PRESSED){
			state = RELEASE;			//释放瞬间
		}
		else{
			state = UNPRESSED;			//根本没按
		}
		priorButtonState = UNPRESSED;	//赋值
	}
	return state;
}
/* *** */
boolean stopFlag=0;
int state;
void loop()
{
	//按键
	if(buttonDetect(buttonPP)==PRESS_MOMENT){
	//if(digitalRead(A0)==LOW){
		stopFlag=~stopFlag;
	}
	if(stopFlag){
		NotUpdataTime();
	}
	else{
		updateTime();
	}
	//时间处理部分
	if(count_10ms>=100)  {
		count_10ms=0;
		if(miao>=100)		    //满100百分秒清零,秒加1
		{
			miao=0;
			//beepingAndStop();			//蜂鸣
		}
	}
	disptime(miao,count_10ms);
}

void beeping(){
	//tone(beep_pin,freq);	
}

void beepingAndStop(){
	//全部显示0
	disp(0,0);		//显示变量内容
	for(int i=0; i<4; i++){
		digitalWrite(bitn[i],low);
	}
	//beeping();
}
