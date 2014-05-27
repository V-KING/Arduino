/*==================================================
 *     Name: come_down2_addBeep.ino
 *  Version: 1.0 - 2014/5/10 16:21:17
 *  Company: WWW.SOGWORKS.CN
 * Function:	从9-0的倒计时器 ，当时到了，就蜂鸣，蜂鸣时间5s。
 * 	在此期间：
 * 	若时间还在跑，按了key就停止倒计时.
 * 	若已经时间停止跑了，按key就是重新开启倒计时.
 ==================================================*/

/* 
 *数码管引脚号:(3462BS这一面对着你)
 *数码管上排：10 - 6
 *数码管下排：1  - 5 
 *
 * 数码管引脚号对应的 led段：
 * 数码管引脚-----------------Arduino管脚
 *   3   ----> 电阻 ---------> GND       
 * A-7   --------------------> 7
 * B-6   --------------------> 6
 * C-4   --------------------> 5
 * D-2   --------------------> 10
 * E-1   --------------------> 11
 * F-9   --------------------> 8
 * G-10  --------------------> 9
 * DP-5  --------------------> 4
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
/* 
 * 我们用的3462BS是共阳极的所以应该是,之前用的是共阴极的数码管
 * 所以可以只需要改动下面一行代码就可以了
 */
int high=HIGH;					  //共阴极时high=HIGH；
int low=LOW;					  //共阳极时low=LOW;
/* **定时器用到的变量** */
byte miao=9;          		  //秒

static unsigned long previouTotalBeepTime;	//用来计算是否到了beeping的时间,到了就不响了


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
    digitalWrite(a,high);
    digitalWrite(b,high);
    digitalWrite(c,high);
    digitalWrite(d,high);
    digitalWrite(f,high);
    digitalWrite(g,high);
    digitalWrite(e,low);
    digitalWrite(dp,low);
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
	digitalWrite(dp,high);	//点亮dp段
    }
    else{
	digitalWrite(dp,low);	//灭dp段
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
    //位控制
    digitalWrite(13,high);
    digitalWrite(12,high);
    digitalWrite(3,high);
    digitalWrite(2,high);
}
/* 
 * 显示数字data
 * */
void disp(int data)
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
	default:	//什么事也不干
	    break;  
    }
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
int buttonAction(int button){
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
/* 
 * 蜂鸣器响5s钟
 * */
void beeping(){
    static unsigned long previouBeepMoment1=millis();		//用来计算每个音调响多久用的
    if(millis()-previouTotalBeepTime< 5000){			//也就是大与5000时就不响了,不执行下面了
	if(millis() - previouBeepMoment1 <= 500){		//不到500ms就响750HZ 的频率
	    //noTone(3);
	    tone(3,750,500);
	    noTone(3);						//发现这里关不掉tone的,但是可以去掉噪音
	}
	else if(millis() - previouBeepMoment1 <= 1000){		//(500,1000)之间响1000HZ 频率
	    //noTone(3);
	    tone(3,1000,500);
	    noTone(3);						//发现这里关不掉tone的,但是可以去掉噪音
	}
	else{
	    previouBeepMoment1 = millis();			//beeping完5s后，更新previouTotalBeepTime
	}
    }
}

/* *** */
boolean stopFlag=0;				//停止时间跑的flag
int flag_int0=0;				//记录外部中断0的标志
unsigned long preS;				//用来记录每秒刷新1次的
unsigned long lastInterrup;			//记录上一中断之后时刻的时间戳
unsigned long nowInterrup;			//记录当前中断的时间戳

void setup()
{
    Serial.begin(9600);  
    //设置4～11 引脚为输出模式
    for(int i=2;i<=13;i++){
	pinMode(i,OUTPUT);
    }
    //digitalWrite(A0,HIGH);			//AO引脚为输入，上拉
    miao=10;					//初始化要显示的秒
    pinMode(2,INPUT_PULLUP);			//数字引脚2为输入，上拉
    lastInterrup=millis();			//记录上一中断之后时刻的时间戳
    attachInterrupt(0, keyPressInterrupt, FALLING);		//设置中断,在3引脚上，设置为外部下降沿中断
}

void loop()
{
    //检测按键，如果是按键按下的一瞬间,就是暂停和继续切换
    if(checkKeyIsPressed()){				
	stopFlag=~stopFlag;
    }

    //如果没有停止,就不断的每过1000ms渐减,如果是停止的，miao就赋值10
    if(!stopFlag){
	if(millis()- preS>=1000){
	    preS=millis();
	    miao--;	    	
	}
    }
    else{
	miao=10;
    }
    disp(miao);					//如果不是0-9，就是全部都是灭的。
    //delay(1);					//如果不加delay就会有一些显示不太清，特别是9
    //如果时间到了，就显示的是0，我们应该重新把miao=10
    if(miao == 0){
	miao=10;				//重新把miao=10
	previouTotalBeepTime=millis(); 		//用来记算总共蜂鸣多长时间的。
	//等待按键按下推出while循环,在这个循环里，为了实时性，在beeping中不加delay函数
	while(!checkKeyIsPressed()){ 		//没有按就在while内循环
	    disp(0);				//显示0
	    beeping();				//响5s钟
	}
    }    
}
/* 
 * 检查按键，如果是按下的，yes  OR no
 * 返回1：检测到按键是按下的
 * 返回0：检测到按键不是是按下的 
 *  
 * */
int checkKeyIsPressed(){
    int state=0;
    //flag_int0==1就是有外部中断，就是key上有动作(但是不一定是按下)
    if(flag_int0==1){
	flag_int0=0;				//将有外部中断标志清零
	if((nowInterrup-lastInterrup)>=10) {	//计算两个外部中断之间的时间间隔
	    delay(10);				//延时后检查外部中断引脚的电平
	    if (digitalRead(2)==LOW){ 		//前面是下降沿中断，延时后发现是低电平，就说明是按键按下
		lastInterrup=nowInterrup;	//本次的中断时间，赋值给lastInterrup
		state=1;			//记录现在的状态
	    }
	}
    }
    return state;				//返回现在状态
}
/* 
 * 外部中断0函数，这里是按键中断
 * */
void keyPressInterrupt(){
    nowInterrup=millis();			//更新现在的时间
    flag_int0=1;				//等于1表示已经发生外部中断
}
