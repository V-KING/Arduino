/*
 * ==================================================
 *      Name: four_seg_disp_demo.ino
 *   Version: 1.0 - 2014/5/15 17:05:49
 *   Company: WWW.SOGWORKS.CN
 *  Function: 四个数码管显示 
 *==================================================
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
int delayTime=1;                       //延时的时间
/* **串口相关变量** */
int restBytes=0;		  //串口中剩下的字节数
int COMMON=1;

//数码管显示函数，8段对应8个参数；输入为1则点亮，输入为0则熄灭
void displaySeg(boolean a,boolean b,boolean c,boolean d,
	boolean e,boolean f,boolean g,boolean dp) {
    if(a)     digitalWrite(aPin,!COMMON);		//a要点亮的话就是和公共端COMMON不一样，所以!COMMON
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
            displaySeg(1,1,1,1,1,1,0,0);	//对照数码管原理图，点亮led
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
    //将所有数码管的共阳极都让他不工作
    for(int i=0; i<4; i++){
	digitalWrite(bitn[i],!COMMON);
    }
    digitalWrite(bitn[n],COMMON);		//点亮第n个数码管
}

/*
 * 前面两个显示数字preTwoNum，后面连个数码管显示数字sencondTwoNum
 * */
void disptime(int preTwoNum,int secondTwoNum,int interval){
    //一个一个的显示时间
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

void setup()
{
    Serial.begin(9600);  
    for(int i=2;i<=13;i++)
        pinMode(i,OUTPUT);//设置4～11 引脚为输出模式
}

void loop()
{
    restBytes=Serial.available();
    //串口中的数据。
    if(restBytes > 0){
	delayTime=Serial.parseInt(); 
    }
    //数码管显示，1234，刷新的频率为delayTime
    disptime(12,34,delayTime);	
}
