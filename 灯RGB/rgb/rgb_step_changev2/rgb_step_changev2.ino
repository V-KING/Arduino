/*
 * ====================================================
 *      Name: IR_LCD_disp_key.ino
 *   Version: 1.0 
 *  Compiler: Arduino-IDE
 *   Company: WWW.SOGWORKS.CN 
 *  Function: 1.在没有触发红外的情况下，就是慢慢的渐变 
 *            2.在触发了红外的情况下，就快速的赤橙黄绿青蓝紫变一下，然互又恢复慢慢的渐变 
 * RGB分别接：数字引脚567
 * =====================================================
 * */
#include"pitch.h"
int Start_Over=0;
int RedPin = 5;                 //红色led引脚  
int GreenPin = 6;               //绿色led引脚 
int BluePin  = 7;                //蓝色led引脚 
/**
 * 设置RGB颜色
 * @param red    红色 
 * @param green  绿 
 * @param blue   蓝 
 */
void setColor(int red, int green, int blue)
{
    analogWrite(RedPin, 255-red);
    analogWrite(GreenPin, 255-green);
    analogWrite(BluePin, 255-blue);  
}

/**
 * 延时并且还要检查是否有红外中断，假中断
 */
void delayAndCheckInterrupts(){
    for (int i = 0; i < 50; ++i){
        delay(10);
        if (Start_Over){
            return;
        }
    }
}



/**
 * [返回映射过的随机数]
 * @param  x在[1,4]范围内
 * @return  返回映射的几个值
 */
int mapRandom(int x){
    if(0==x){
    return 0;
    }
    if(1==x){
    return 500;
    }
    if(2==x){
    return 1000;
    }
    if(3==x){
    return 1500;
    }
    if(4==x){
    return 2500;
    }
}


/**
 * 用的别人的渐变算法,给RGB的引脚发送RGB的值
 * ::::我现在想传入三个参数，（r，g，b），是六个颜色，让其在六个颜色之间变。
 *     依次传入6次值，不断循环 
 * @param index  lightTable的索引值 
 */
void sendrgbElement(int Red, int Green, int Blue) {

    int FadeTime,HoldTime;
    FadeTime = 1000;
    HoldTime = 200;

    static int redPrev = 0;    // keep track of previous Red brightness value
    static int greenPrev = 0;  // keep track of previous Green brightness value
    static int  bluePrev = 0;   // keep track of previous Blue brightness value

    // set color timing values
    //   everytime the fadeCounter reaches this timing value in the fade loop
    //   we will update the color value for the color (default value of 0 for no updating)
    int redTime = 0;
    int greenTime = 0;
    int blueTime = 0;

    // set values of temp colors
    //   starting from the previous color values,
    //   these will change to the color values just gotten from rgbElement over fadeTime
    int redTemp = redPrev;
    int greenTemp = greenPrev;
    int blueTemp = bluePrev;

    // fade LEDs up or down, from previous values to current values
    int redDelta = Red - redPrev;                // total amount to fade red value (up or down) during fadeTime
    int greenDelta = Green - greenPrev;          // total amount to fade green value (up or down) during fadeTime
    int blueDelta = Blue - bluePrev;             // total amount to fade blue value (up or down) during fadeTime

    if (redDelta != 0) {
    redTime = (FadeTime / redDelta);           // increment Red value every time we reach this fade value in the fade loop
    redTime = abs(redTime);
    redTime = redTime + 1;                     // adjust for truncation of integer division
    }                                            //
    int redTimeInc = redTime;                    // increment Red value every time the fadeCounter increments this amount

    if (greenDelta != 0) {
    greenTime = (FadeTime / greenDelta);       // increment Green value every time we reach this fade value in the fade loop
    greenTime = abs(greenTime); 
    greenTime = greenTime + 1;                 // adjust for truncation of integer division
    }                                            //
    int greenTimeInc = greenTime;                // increment Green value every time the fadeCounter increments this amount

    if (blueDelta != 0) {
    blueTime = (FadeTime / blueDelta);         // increment Blue value every time we reach this fade value in the fade loop
    blueTime = abs(blueTime);
    blueTime = blueTime + 1;                   // adjust for truncation of integer division
    }                                            //
    int blueTimeInc = blueTime;                  // increment Blue value every time the fade value increments this amount


    int redInc = 1;
    int greenInc = 1;
    int blueInc = 1;
    if (redDelta < 0) redInc = -1;
    if (greenDelta < 0) greenInc = -1;
    if (blueDelta < 0) blueInc = -1;
    //循环
    for (int fadeCounter=1; fadeCounter<=FadeTime; fadeCounter++) {
    if ( fadeCounter == redTime ) {
        redTemp = redTemp + redInc;                 // increment to next red value
        redTime = redTime + redTimeInc;             // we'll increment Red value again when FadeTime reaches new redTime
    }
    if ( fadeCounter == greenTime ) {
        greenTemp = greenTemp + greenInc;           // increment to next green value
        greenTime = greenTime + greenTimeInc;       // we'll increment Green value again when FadeTime reaches new greenTime
    }
    if ( fadeCounter == blueTime ) {
        blueTemp = blueTemp + blueInc;              // increment to next blue value
        blueTime = blueTime + blueTimeInc;          // we'll increment Blue value again when FadeTime reaches new blueTime
    }
    setColor(redTemp,greenTemp,blueTemp);
    delayMicroseconds(1000);
    if ( Start_Over ) return;  // if the IR detector saw IR, then we should reset and start over (Start_Over gets set to 1 in the interrupt routine if the IR detector saw IR)
    }
    redPrev = Red;
    greenPrev = Green;
    bluePrev = Blue;
}


void setup()
{
    Serial.begin(9600);
    //将引脚设置为输出
    pinMode(RedPin, OUTPUT);
    pinMode(GreenPin, OUTPUT);
    pinMode(BluePin, OUTPUT);   
    //设置随机数种子
    randomSeed(103);
    //安置中断函数
    attachInterrupt(0,recv_isr,RISING );
}

int colorTable[6][3]=
{
    {255,0,0},      //红
    {255,255,0},    //黄
    {0,255,0},      //绿
    {0,255,255},        //青
    {0,0,255},      //蓝
    {255,0,255},        //杨红
};


/**
 * 中断0的中断函数，FALLONG触发
 */
unsigned long now1 = 0;
unsigned long now2 = 0;
bool flag1_beginTime = 1;
bool flag2 = 0;
static int count;


void recv_isr()
{
    static int i;
    i++;
    count++;
    Start_Over=1;      //用来中断的标志位
    if(flag1_beginTime){
        now1 = millis();
        flag1_beginTime = 0;
    }
    now2 = millis();
    if(now2 - now1 > 1000){
        count =1;    //因为你执行到这里的时候，肯定出发了中断，所以=1
        flag1_beginTime = 1;//或者执行完特定操作之后置1
    }
}


/**
 * 产生3个随机数给LED
 */
unsigned long pulseHIGH = 0;
void toggleIRtodo(){
    //flag1_beginTime = 1; 
    Serial.print( " :+++");
    Serial.print(now1);
    Serial.print(", ");
    Serial.print(now2);
    Serial.print(", count=");
    Serial.println(count);
    //根据count的值去做不同的操作
    if(count == 1){
        delay(200);

        setColor(255, 0, 0);  // 红色
        tone(8,NOTE_C6);
        delayAndCheckInterrupts();    
        noTone(8);

        setColor(255, 255, 0);  // yellow
        tone(8,NOTE_D6);
        delayAndCheckInterrupts();    
        noTone(8);

        setColor(0, 255, 0);  //green
        tone(8,NOTE_E6);
        delayAndCheckInterrupts();    
        noTone(8);

        setColor(0, 255, 255);  // 青色cyan
        tone(8,NOTE_F6);
        delayAndCheckInterrupts();    
        noTone(8);

        setColor(0, 0, 255);  // blue
        tone(8,NOTE_G6);
        delayAndCheckInterrupts();    
        noTone(8);

        setColor(255, 0, 255);  // 紫色 
        tone(8,NOTE_A6);
        delayAndCheckInterrupts();    
        noTone(8);
    }
    if(count >= 2){
        delay(200);

        setColor(255, 0, 255);  // 紫色 
        tone(8,NOTE_A6);
        delayAndCheckInterrupts();    
        noTone(8); 

        setColor(0, 0, 255);  // blue
        tone(8,NOTE_G6);
        delayAndCheckInterrupts();    
        noTone(8);

        setColor(0, 255, 255);  // 青色cyan
        tone(8,NOTE_F6);
        delayAndCheckInterrupts();    
        noTone(8);

        setColor(0, 255, 0);  //green
        tone(8,NOTE_E6);
        delayAndCheckInterrupts();    
        noTone(8);

        setColor(255, 255, 0);  // yellow
        tone(8,NOTE_D6);
        delayAndCheckInterrupts();    
        noTone(8);

        setColor(255, 0, 0);  // 红色
        tone(8,NOTE_C6);
        delayAndCheckInterrupts();    
        noTone(8);
    }
}

void loop() { 
    for (int i = 0; i < 6; ++i) {
        sendrgbElement(colorTable[i][0],colorTable[i][1] ,colorTable[i][2]); 
        if(Start_Over){
            Start_Over=0;
            toggleIRtodo();
        } 
    }
}
/*Serial.print(i);
                Serial.print( " :+++");
                Serial.print(now1);
                Serial.print(", ");
                Serial.print(now2);
                Serial.print(", count=");*/