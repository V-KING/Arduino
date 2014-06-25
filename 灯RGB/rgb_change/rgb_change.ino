/*
 * ====================================================
 *      Name: IR_LCD_disp_key.ino
 *   Version: 1.0 
 *  Compiler: Arduino-IDE
 *   Company: WWW.SOGWORKS.CN 
 *  Function: 1.在没有触发红外的情况下，就是慢慢的渐变 
 *            2.在触发了红外的情况下，就快速的渐变一下，然互又恢复慢慢的渐变 
 * RGB分别接：数字引脚567
 * 注意：如果注释掉297~311行代码，并且 去掉312~317行的代码，就是随机的RGB
 * ========================================rr=============
 * */

#include<IRremote.h>

//RGB元素表 
struct rgbElement {
    int fadeTime;            // 从一个颜色渐变到另一个颜色的时间how long to fade from previous values of RGB to the ones specified in this rgbElement (0 to 65,535)
    int holdTime;            // how long to keep the RGB values once they are faded in (0 or 1000 to 65,535)
    unsigned char red;       // 红色灯的亮度值brightness value for Red LED (0 to 255)
    unsigned char green;     // 绿色灯亮度值brightness value for Green LED (0 to 255)
    unsigned char blue;      // 蓝色灯的亮度值brightness value for Blue LED (0 to 255)
} const lightTab[]  = {
    {     0,   500, 255,   0,   0 },
    {   500,     0,   0,   0,   0 },
    {     0,   500,   0, 255,   0 },
    {   500,     0,   0,   0,   0 },
    {     0,   500,   0,   0, 255 },
    {   500,     0,   0,   0,   0 },
    {  2500,  2500, 255,   0,   0 },
    {  2500,  2500,   0, 255,   0 },
    {  2500,  2500,   0,   0, 255 },
    {  2500,  2500, 155,  64,   0 },
    {  2500,  2500,  64, 255,  64 },
    {  2500,  2500,   0,  64, 255 },
    {  2500,  2500,  64,   0,  64 },
    {     0,  1500, 155,   0,   0 },
    {     0,  1500,   0, 255,   0 },
    {     0,  1500,   0,   0, 255 },
    {     0,  1500, 140,   0, 240 },
    {     0,  1500, 155, 155,   0 },
    {     0,  1500, 155, 255, 255 },
    {     0,  1500, 128, 128, 128 },
    {     0,  1500,  48,  48,  58 },
    {     0,  1500,   0,   0,   0 },
    {  2500,  2500, 155,   0,   0 },
    {  2500,  2500, 155, 255,   0 },
    {  2500,  2500,   0, 255,   0 },
    {  2500,  2500,   0, 255, 255 },
    {  2500,  2500,   0,   0, 255 },
    {  2500,  2500, 155,   0, 255 },
    {  2500,     0,   0,   0,   0 },
    {  2500,  2500, 155,   0,   0 },
    {  2500,  2500, 155, 255,   0 },
    {  2500,  2500,   0, 255,   0 },
    {  2500,  2500,   0, 255, 255 },
    {  2500,  2500,   0,   0, 255 },
    {  2500,  2500, 155,   0, 255 },
    {  2500,     0,   0,   0,   0 },
    {  2500,  2500, 154,  32,   0 },
    {  2500,  2500, 154, 128,   0 },
    {  2500,  2500, 154, 240,   0 },
    {  2500,  2500, 128, 240,   0 },
    {     0,  2500,   0,   0,   0 },
    {  2500,  2500,   0,  16, 255 },
    {  2500,  2500,   0, 128, 255 },
    {  2500,  2500,   0, 240, 128 },
    {  2500,  2500,  16,  16, 240 },
    {  2500,  2500, 140,  16, 240 },
    {  2500,  2500,  64,   0, 250 },
    {     0,  2500,  10,  10,  10 },
    {     0,  2500,   0,   0,   0 },
    {  2500,  2500, 140,   0, 240 },
    {  2500,  2500,  32,   0, 240 },
    {  2500,  2500, 128,   0, 128 },
    {  2500,  2500, 140,   0,  32 },
    {  2500,     0,   0,   0,  10 },
    {  2500,     0,   0,   0,   0 },
    {  1000,  1000,   0,   0,   0 },
    {  1000,  1000,  32,   0,   0 },
    {  1000,  1000,  64,   0,   0 },
    {     0,  1000,  96,   0,   0 },
    {  1000,     0, 128,   0,   0 },
    {  1000,     0, 160,  32,   0 },
    {  1000,     0, 192,  64,   0 },
    {  1000,     0, 124,  96,   0 },
    {     0,  1000, 155, 128,   0 },
    {  1000,  1000,   0, 160,   0 },
    {     0,  1000,   0, 192,   0 },
    {  1000,  1000,   0, 224,  32 },
    {  1000,     0,   0, 255,  64 },
    {  1000,     0,   0,   0,  96 },
    {  1000,     0,   0,   0, 128 },
    {  1000,     0,   0,   0, 160 },
    {  1000,     0,   0,   0, 192 },
    {  1000,     0,   0,   0, 224 },
    {  1000,  1000,   0,   0, 255 },
    {  1000,     0,   0,   0,   0 },
    {     0,  1000,   0,   0, 255 },
    {  1000,  1000,  32,   0,   0 },
    {  1000,  1000,  96,   0,   0 },
    {  1000,  1000, 160,   0,   0 },
    {  1000,     0, 255,   0,   0 },
    {  1000,  1000,   0,  96,   0 },
    {  1000,  1000,   0, 160,  32 },
    {  1000,  1000,   0, 224,  64 },
    {  1000,  1000,   0, 255,  96 },
    {  1000,  1000,   0,   0, 128 },
    {  1000,  1000,   0,   0, 160 },
    {     0,  1000,   0,  32, 192 },
    {     0,  1000,   0,  64, 224 },
    {     0,  1000,   0,  96, 225 },
    {     0,  1000,   0, 128,   0 },
    {     0,  1000,   0, 160,   0 },
    {     0,  1000,   0, 192,  32 },
    {     0,  1000,   0, 224,  64 },
    {     0,  1000,   0, 255,  96 },
    {     0,  1000,   0,   0, 255 },
    {     0,  1000,   0,   0,   0 },
    {     0,     0,   0,   0,   0 }
};

IRsend irsend;
int g_flag=0;
int Start_Over=0;
int g_pwm_pin=3; 
int RedPin = 5;                 //红色led引脚  
int GreenPin = 6;               //绿色led引脚 
int BluePin	 = 7;                //蓝色led引脚 
int r = 125;                 //默认设置为125 
int g = 125;                  
int b = 125;                  

/**
 * 产生3个随机数给LED
 */
void rgbrandom(){
    for (int i = 0; i < 1000; ++i)
    {
	analogWrite(RedPin,random(255));
	analogWrite(GreenPin,random(255));
	analogWrite(BluePin,random(255));
	delay(10);
    }
}

/**
 * 中断0的中断函数，FALLONG触发
 */
void recv_isr()
{
    g_flag=1;          //用来中断的标志位
    Start_Over=1;      //用来中断的标志位
}
/**
 * 用的别人的渐变算法,给RGB的引脚发送RGB的值
 * @param index  lightTable的索引值 
 */
void sendrgbElement( int index ) {
    // get values of rgbElement from lightTab
    int FadeTime =lightTab[index].fadeTime;
    int HoldTime = lightTab[index].holdTime;
    unsigned char Red = lightTab[index].red;
    unsigned char Green = lightTab[index].green;
    unsigned char Blue = lightTab[index].blue;

    // get previous RGB brightness values from lightTab
    //   (these values are set to 0 if index to lightTab = 0)
    unsigned char redPrev = 0;    // keep track of previous Red brightness value
    unsigned char greenPrev = 0;  // keep track of previous Green brightness value
    unsigned char bluePrev = 0;   // keep track of previous Blue brightness value
    if (index != 0) {
	redPrev = lightTab[index-1].red;
	greenPrev = lightTab[index-1].green;
	bluePrev = lightTab[index-1].blue;
    }

    // set color timing values
    //   everytime the fadeCounter reaches this timing value in the fade loop
    //   we will update the color value for the color (default value of 0 for no updating)
    int redTime = 0;
    int greenTime = 0;
    int blueTime = 0;

    // set values of temp colors
    //   starting from the previous color values,
    //   these will change to the color values just gotten from rgbElement over fadeTime
    unsigned char redTemp = redPrev;
    unsigned char greenTemp = greenPrev;
    unsigned char blueTemp = bluePrev;

    // fade LEDs up or down, from previous values to current values
    int redDelta = Red - redPrev;                // total amount to fade red value (up or down) during fadeTime
    int greenDelta = Green - greenPrev;          // total amount to fade green value (up or down) during fadeTime
    int blueDelta = Blue - bluePrev;             // total amount to fade blue value (up or down) during fadeTime

    if (redDelta != 0) {
	redTime = (FadeTime / redDelta);           // increment Red value every time we reach this fade value in the fade loop
	if (redTime < 0) redTime = -redTime;       //    absolute value
	redTime = redTime + 1;                     // adjust for truncation of integer division
    }                                            //
    int redTimeInc = redTime;                    // increment Red value every time the fadeCounter increments this amount

    if (greenDelta != 0) {
	greenTime = (FadeTime / greenDelta);       // increment Green value every time we reach this fade value in the fade loop
	if (greenTime < 0) greenTime = -greenTime; //    absolute value
	greenTime = greenTime + 1;                 // adjust for truncation of integer division
    }                                            //
    int greenTimeInc = greenTime;                // increment Green value every time the fadeCounter increments this amount

    if (blueDelta != 0) {
	blueTime = (FadeTime / blueDelta);         // increment Blue value every time we reach this fade value in the fade loop
	if (blueTime < 0) blueTime = -blueTime;    //    absolute value
	blueTime = blueTime + 1;                   // adjust for truncation of integer division
    }                                            //
    int blueTimeInc = blueTime;                  // increment Blue value every time the fade value increments this amount

    // set color increment values
    //   the amount to increment color value each time we update it in the fade loop
    //   (default value of 1, to slowly increase brightness each time through the fade loop)
    unsigned char redInc = 1;
    unsigned char greenInc = 1;
    unsigned char blueInc = 1;
    // if we need to fade down the brightness, then make the increment values negative
    if (redDelta < 0) redInc = -1;
    if (greenDelta < 0) greenInc = -1;
    if (blueDelta < 0) blueInc = -1;

    // if FadeTime = 0, then just set the LEDs blinking at the RGB values (the fade loop will not be executed)
    if (FadeTime == 0) {
	/*    greenTemp = Green; // no need to manually pulse Green LED on PB2 (pin 7) now, since it will be done in the hold loop
	      OCR1A = Red;       // update PWM for Red LED on OC1A (pin 6)
	      OCR1B = Blue;      // update PWM for Blue LED on OC1B (pin 3)
	      */  
	greenTemp = Green;
	analogWrite(GreenPin, greenTemp);
	analogWrite(RedPin,Red);
	analogWrite(BluePin,Blue);
	delay(1);
    }

    // fade loop
    //   this loop will independently fade each LED up or down according to all of the above variables
    //   (it will take a length of time, FadeTime, to accomplish the task)
    //   this loop is not executed if FadeTime = 0 (since 1 is not <= 0, in the "for" loop)
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
	// pulseGreen(greenTemp); // one manual PWM pulse on the Green LED on PB2 (pin 7) for a period of 400 microseconds
	// OCR1A = redTemp;       // update PWM for Red LED on OC1A (pin 6)
	// OCR1B = blueTemp;      // update PWM for Blue LED on OC1B (pin 3)
	analogWrite(GreenPin,greenTemp);
	analogWrite(RedPin,redTemp);
	analogWrite(BluePin,blueTemp);
	delay(1);
	// pulseIR();             // pulse the IR emitter for a little bit (if there's a reflection to the IR detector as a result, then the ISR will set Start_Over = 1)
	if ( Start_Over ) return;  // if the IR detector saw IR, then we should reset and start over (Start_Over gets set to 1 in the interrupt routine if the IR detector saw IR)
    }
    // analogWrite(GreenPin,Green);
    // analogWrite(RedPin,Red);
    // analogWrite(BluePin,Blue); 
    /*  OCR1A = Red;    // leave Timer1 PWM at final brightness value for Red (in case there were rounding errors in above math)
	OCR1B = Blue;   // leave Timer1 PWM at final brightness value for Blue (in case there were rounding errors in above math)
	*/
    // hold loop
    //   hold all LEDs at current values for HoldTime
    for (int holdCounter=0; holdCounter<HoldTime; holdCounter++) {
	// pulseGreen(greenTemp); // one manual PWM pulse on the Green LED on PB2 (pin 7) for a period of 400 microseconds
	analogWrite(GreenPin,greenTemp);
	analogWrite(RedPin,redTemp);
	analogWrite(BluePin,blueTemp);
	//delay(1);
	// the Red LED will continue to pulse automatically from the hardware Timer1
	// the Blue LED will continue to pulse automatically from the hardware Timer1
	// pulseIR();             // pulse the IR emitter for a little bit (if there's a reflection to the IR detector as a result, then the ISR will set Start_Over = 1)
	if ( Start_Over ) return;  // if the IR detector saw IR, then we should reset and start over (Start_Over gets set to 1 in the interrupt routine if the IR detector saw IR)
    }
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
    attachInterrupt(0,recv_isr,FALLING);
}

void loop() { 
    //下面的代码是触发红外后，rgb灯就渐变的很快，没触发就是渐变的很慢
/*start_over:
    int index = 0;  
    interrupts();				//使能中断
    Start_Over = 0;//Start_Over清零
    for (int count=0; count<180; count++) {	
	do {
	    sendrgbElement(index);		// 发送RGB元素给LED 
	    index++;				// increment to point to next rgbElement in lightTab
	    if ( Start_Over ) break;		// 如果检测到有东西碰到红外就从头开始if the IR detector saw IR, then we should reset and start over
	} while ( !( (lightTab[index].fadeTime == 0 ) && (lightTab[index].holdTime == 0 ) ) );//如果两个时间都不等于0
	if ( Start_Over ) break;		// 如果检测到有东西碰到红外就从头开始if the IR detector saw IR, then we should reset and start over
	index = 0;
    }
    if ( Start_Over ) goto start_over;		//如果检测到有东西碰到红外就从头开始 
    noInterrupts();                 		// 禁止中断*/
    //下面代码是用来触发红外之后，rgb灯就乱变
    if(g_flag  ==1){
      g_flag =0;
      rgbrandom();
      Serial.println("detected!");
      }
}

