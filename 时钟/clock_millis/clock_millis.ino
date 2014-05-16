
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
//定义命令字
#define CLK_MODE 	11
#define COME_DOWN_MODE  22


//设置控制各段的数字IO 脚
int aPin=7;			//定义数字接口7 连接a 段数码管
int bPin=6;			// 定义数字接口6 连接b 段数码管
int cPin=5;			// 定义数字接口5 连接c 段数码管
int dPin=10;			// 定义数字接口10 连接d 段数码管
int ePin=11;			// 定义数字接口11 连接e 段数码管
int fPin=8;			// 定义数字接口8 连接f 段数码管
int gPin=9;			// 定义数字接口9 连接g 段数码管
int dpPin=4;			// 定义数字接口4 连接dp 段数码管
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
byte fen=59;	         	  //分
byte shi=23;           		  //时
/* **串口相关变量** */
int restBytes=0;		  //串口中剩下的字节数
int COMMON=1;

//数码管显示函数，8段对应8个参数；输入为1则点亮，输入为0则熄灭
void displaySeg(boolean a,boolean b,boolean c,boolean d,
	boolean e,boolean f,boolean g,boolean dp) {
    if(a)     digitalWrite(aPin,!COMMON);
    else    digitalWrite(aPin,COMMON);
    if(b)     digitalWrite(bPin,!COMMON);
    else    digitalWrite(bPin,COMMON);
    if(c)     digitalWrite(cPin,!COMMON);
    else    digitalWrite(cPin,COMMON);
    if(d)     digitalWrite(dPin,!COMMON);
    else    digitalWrite(dPin,COMMON);
    if(e)     digitalWrite(ePin,!COMMON);
    else    digitalWrite(ePin,COMMON);
    if(f)     digitalWrite(fPin,!COMMON);
    else    digitalWrite(fPin,COMMON);
    if(g)     digitalWrite(gPin,!COMMON);
    else    digitalWrite(gPin,COMMON);
    if(dp)     digitalWrite(dpPin,!COMMON);
    else    digitalWrite(dpPin,COMMON);

}

//数字显示函数，参数为要显示的数字0-9
void displayNum(byte data) {
    switch (data) {
        case 0:
            displaySeg(1,1,1,1,1,1,0,0);
            break;
        case 1:
            displaySeg(0,1,1,0,0,0,0,0);
            break;
        case 2:
            displaySeg(1,1,0,1,1,0,1,0);
            break;
        case 3:
            displaySeg(1,1,1,1,0,0,1,0);   
            break;       
        case 4:   
            displaySeg(0,1,1,0,0,1,1,0);       
            break;           
        case 5:           
            displaySeg(1,0,1,1,0,1,1,0);           
            break;           
        case 6:               
            displaySeg(1,0,1,1,1,1,1,0);               
            break;               
        case 7:                   
            displaySeg(1,1,1,0,0,0,0,0);
            break;                                       
        case 8:                       
            displaySeg(1,1,1,1,1,1,1,0);                       
            break;                       
        case 9:                           
            displaySeg(1,1,1,1,0,1,1,0);                           
            break;
        default:
            displaySeg(0,0,0,0,0,0,0,0);                       
    }
}



/*
 *当lightUp_flag=1时，就是显示两个点 
 *当lightUp_flag=0时，就是不显示两个点 
 */
void dock(int lightUp_flag) 
{
    if(lightUp_flag==1){
	displaySeg(0,0,0,0,0,0,0,1);                       
    }
    else{
	displaySeg(0,0,0,0,0,0,0,0);                       
    }
}
/*
 * 将数码管全部灭了
 */
void clearLED()
{
    displaySeg(0,0,0,0,0,0,0,0);                       
    for(int i=0; i<4; i++){
	digitalWrite(bitn[i],!COMMON);
    }

}
/* 
 * 第n个数码管的显示data
 * n   :从0开始
 * data:数码管显示的数字[0,9]
 */
void disp(int n,int data)
{
    clearLED();
    switch(data)
    {
    case 0:
	displayNum(0);
        break;
    case 1:
	displayNum(1);
        break;
    case 2:
	displayNum(2);
        break;
    case 3:
	displayNum(3);
        break;
    case 4:
	displayNum(4);
        break;
    case 5:
	displayNum(5);
        break;
    case 6:
	displayNum(6);
        break;
    case 7:
	displayNum(7);
        break;
    case 8:
	displayNum(8);
        break;
    case 9:
	displayNum(9);
        break;
    default:
	displayNum(10);
        break;  
    }
    for(int i=0; i<4; i++){
	digitalWrite(bitn[i],!COMMON);
    }
    digitalWrite(bitn[n],COMMON);		//点亮第n个数码管
}

/*
 * 前面两个显示数字preTwoNum，后面连个数码管显示数字sencondTwoNum
 * */
void disptime(int preTwoNum,int secondTwoNum){
    //一个一个的显示时间
    int interval=1;
    disp(0,preTwoNum/10);		//显示变量内容
    delay(interval);
    disp(1,preTwoNum%10);		//显示变量内容
    delay(interval);
    disp(2,secondTwoNum/10);		//显示变量内容
    delay(interval);
    disp(3,secondTwoNum%10);		//显示变量内容
    delay(interval);
    clearLED();
}



unsigned long setTime;
unsigned long preS;				//用来记录每秒刷新1次的
unsigned long passms;				//从开机起总共过去了多少ms
unsigned long nows;				//从00:00:00起总共过去了多少ms,这个是正真的时间
unsigned long dispshi=0,dispfen=0,dispmiao=0;	//要显示的时分秒
unsigned long startms=0;	 		//记录计时前的时间（ms）
void setup()
{
    Serial.begin(9600);  
    for(int i=2;i<=13;i++)
        pinMode(i,OUTPUT);//设置4～11 引脚为输出模式
    startms=millis();	  //记录计时前的时间（ms）
}

void loop()
{
    restBytes=Serial.available();
    //如果刚好是4个就读出来,这里其实可以加一个过滤，让读取的数据只能是0-9的数字，后面可以加上，很简单
    if(restBytes == 4){
        shi1=Serial.read()-48;//读取到的ascii码减去字符'0'的ascii码值
        shi2=Serial.read()-48;
        fen1=Serial.read()-48;
        fen2=Serial.read()-48;
        shi=shi1*10 + shi2;
        fen=fen1*10 + fen2;
    }
    //串口中byte的格式如果不是4个，我们就清空串口
    else{
	while(Serial.available()>0){
	    Serial.read();		
	}
    }

    setTime = (shi*3600000) + (fen*60000);//43,920,000
    //每过一秒就刷新一次要显示的时间
    if(millis()- preS>=1000){
        preS=millis();
        passms=millis()-startms;
	//从进入循环到现在总共过了nows秒时间
        nows=passms/1000+setTime/1000;
	//计算要显示的时间,时是24进制，分是60进制，秒是60进制
        dispshi=nows/3600%24;
        dispfen=nows/60%60;
        dispmiao=nows%60;   
	//在串口显示时间
        Serial.print(dispshi,DEC);
        Serial.print(":");
        Serial.print(dispfen,DEC);        
        Serial.print(":");
        Serial.println(dispmiao,DEC);   
    }
    //数码管显示
    disptime(dispshi,dispfen);	
}
