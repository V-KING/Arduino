/*
 * ====================================================
 *      Name: ul1.ino
 *   Version: 1.0
 *  Compiler: Arduino-IDE
 *   Company: WWW.SOGWORKS.CN
 *  Function: 超声波声呐
 * =====================================================
 * */

int ulPin=5;  
int duration=0;


void setup(){
    Serial.begin(9600);
    pinMode(ulPin, OUTPUT);
}

int readUl(){
    int dis;
    // dis = analogRead(A0);
    // dis = map(dis, 0, 1023, 2, 110); 
    //下面是为了发一个10us的出发信号
    pinMode(ulPin, OUTPUT);
    digitalWrite(ulPin, LOW);
    delayMicroseconds(2);
    digitalWrite(ulPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ulPin,LOW);
    //然后，就是arduino接收超声波模块的输出回响信号
    pinMode(ulPin, INPUT);              //设置成输入模式
    duration = pulseIn(ulPin,HIGH);     //根据超声波时序图可知，我们只要知道高电平的时间
    dis = duration/29/2;         //微秒的单位除以58等于厘米,声音的速度：344m/s,来回就要除以2  
                                                //为什么除以58等于厘米?  Y米=（X秒*344）/2
                                                // X秒=（ 2*Y米）/344 ==》X秒=0.0058*Y米 ==》厘米=微秒/58
    
    delay(60);				 	//建议的测量周期,不然就测不准了
    return dis;					//返回距离
}

void beepingForDis(int dis1){
    int duration;
    duration = map(dis1 , 0, 50 , 20, 1500);	//因为距离已经<50了，所以只需要映射(0,50) -> (20,1500)
    tone(8,2000);				//音调
    delay(20);					//延长音时间
    noTone(8);
    delay(duration);				//延迟随着距离越近就响得越急
}

void loop()
{
    int dis1;
    while((dis1= readUl() )<50){
        beepingForDis(dis1);
    }
}

