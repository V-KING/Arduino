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
 * 产生3个随机数给LED
 */
void rgbrandom(){
    setColor(255, 0, 0);  // 红色
    delay(200);                //关闭了中断，会对delay()函数有很大的影响的。
    setColor(255, 255, 0);  // yellow
    delay(200);
    setColor(0, 255, 0);  //green
    delay(200);
    setColor(0, 255, 255);  // 青色cyan
    delay(200);  
    setColor(0, 0, 255);  // blue
    delay(200);
    setColor(255, 0, 255);  // 紫色 
    delay(200);
}

/**
 * 中断0的中断函数，FALLONG触发
 */
void recv_isr()
{
    Start_Over=1;      //用来中断的标志位
}


/**
 * 用的别人的渐变算法,给RGB的引脚发送RGB的值
 * @param index  lightTable的索引值 
 */
void sendrgbElement() {
    //产生一个随机数给fadeTime和holdTime,red,green,blue
    //1.产生1-4的随机数
    unsigned long FadeTime,HoldTime,Red,Green,Blue;
    FadeTime = random(1,5);     
    FadeTime = random(1,5);
    //2. 映射1-4  -> 500,1000,1500,2500
    FadeTime = mapRandom(FadeTime); 
    HoldTime = mapRandom(HoldTime); 
    Red = random(0,256);            //产生的随机数
    Green = random(0,256);
    Blue = random(0,256);
    //++++++++++++++++++++++++
    FadeTime = 1500;
    HoldTime = 1000;
   
    static unsigned char redPrev = 0;    // keep track of previous Red brightness value
    static unsigned char greenPrev = 0;  // keep track of previous Green brightness value
    static unsigned char bluePrev = 0;   // keep track of previous Blue brightness value

    /* // get values of rgbElement from lightTab
       int FadeTime =lightTab[index].fadeTime;
       int HoldTime = lightTab[index].holdTime;
       unsigned char Red = lightTab[index].red;
       unsigned char Green = lightTab[index].green;
       unsigned char Blue = lightTab[index].blue;*/

    // get previous RGB brightness values from lightTab
    //   (these values are set to 0 if index to lightTab = 0)
    /*if (index != 0) {
      redPrev = lightTab[index-1].red;
      greenPrev = lightTab[index-1].green;
      bluePrev = lightTab[index-1].blue;
      }*/

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
	redTime = abs(redTime);
	// redTime = redTime + 1;                     // adjust for truncation of integer division
    }                                            //
    int redTimeInc = redTime;                    // increment Red value every time the fadeCounter increments this amount

    if (greenDelta != 0) {
	greenTime = (FadeTime / greenDelta);       // increment Green value every time we reach this fade value in the fade loop
	greenTime = abs(greenTime); 
	// greenTime = greenTime + 1;                 // adjust for truncation of integer division
    }                                            //
    int greenTimeInc = greenTime;                // increment Green value every time the fadeCounter increments this amount

    if (blueDelta != 0) {
	blueTime = (FadeTime / blueDelta);         // increment Blue value every time we reach this fade value in the fade loop
	blueTime = abs(blueTime);
	// blueTime = blueTime + 1;                   // adjust for truncation of integer division
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

  /*  // if FadeTime = 0, then just set the LEDs blinking at the RGB values (the fade loop will not be executed)
    if (FadeTime == 0) {
	    greenTemp = Green; // no need to manually pulse Green LED on PB2 (pin 7) now, since it will be done in the hold loop
	      OCR1A = Red;       // update PWM for Red LED on OC1A (pin 6)
	      OCR1B = Blue;      // update PWM for Blue LED on OC1B (pin 3)
	        
	analogWrite(GreenPin, Green);
	analogWrite(RedPin,Red);
	analogWrite(BluePin,Blue);
	delay(2);
    }
*/
    // fade loop
    //   this loop will independently fade each LED up or down according to all of the above variables
    //   (it will take a length of time, FadeTime, to accomplish the task)
    //   this loop is not executed if FadeTime = 0 (since 1 is not <= 0, in the "for" loop)
    Serial.print(redTime); Serial.println(" ");
        Serial.print(greenTime);Serial.println(" ");
        Serial.println(blueTime);
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
	delay(1);
	// the Red LED will continue to pulse automatically from the hardware Timer1
	// the Blue LED will continue to pulse automatically from the hardware Timer1
	// pulseIR();             // pulse the IR emitter for a little bit (if there's a reflection to the IR detector as a result, then the ISR will set Start_Over = 1)
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
    attachInterrupt(0,recv_isr,FALLING);
}
//
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

void sendrgbElement_my(int index){
    //产生一个随机数给fadeTime和holdTime,red,green,blue
    //1.产生1-4的随机数
    unsigned long fadeTime,holdTime,red,green,blue;
    fadeTime = random(1,5);     
    holdTime = random(1,5);
    //2. 映射1-4  -> 500,1000,1500,2500
    fadeTime = mapRandom(fadeTime); 
    holdTime = mapRandom(holdTime); 
    red = random(0,256);            //产生的随机数
    green = random(0,256);
    blue = random(0,256);
    //保存,我们计算的是last -> 现在 之间的过渡
    static unsigned long lastFadetime,lastHoldTime,lastRed,lastGreen,lastBlue; 
   int redTemp = lastRed;//用来写进RGB灯里面的值
    int greenTemp = lastGreen;
    int blueTemp = lastBlue;
    // lastFadeTime = fadeTime;
    // lastHoldTime = holdTime;
    // lastRed = red;
    // lastGreen = green;
    // lastBlue = blue;
    //14664644,847034229,847034229
    static int redDelta = red - lastRed;
    static int greenDelta = green - lastGreen;
    static int blueDelta = blue - lastBlue;
    int redTime,greenTime,blueTime;
    //得到TimeInc,每过redTimeInc时间就让rgb值加一个redInc
    if (redDelta != 0) {
	redTime = (fadeTime / redDelta);           // increment Red value every time we reach this fade value in the fade loop
	redTime = abs(redTime); 
	redTime = redTime + 1;                     // adjust for truncation of integer division
    }                                            //
    unsigned long redTimeInc = redTime;//隔redTimeInc 这么长的时间red就增加一次
    if (greenDelta != 0) {
	greenTime = (fadeTime / greenDelta);           // increment Red value every time we reach this fade value in the fade loop
	greenTime = abs(greenTime); 
	greenTime = greenTime + 1;                     // adjust for truncation of integer division
    }                                            //
    unsigned long greenTimeInc = greenTime;         
    if (blueDelta != 0) {
	blueTime = (fadeTime / blueDelta);           // increment Red value every time we reach this fade value in the fade loop
	blueTime = abs(blueTime);   
	blueTime = blueTime + 1;                     // adjust for truncation of integer division
    }                                            //
    unsigned long blueTimeInc = blueTime;//过blueTimeInc时间就让b值加一个redInc
    //计算每过TimeInc时,改变的RGB值redInc值
    int redInc=1,greenInc=1,blueInc=1;
    if(redDelta<0)     redInc = -1;
    if(greenDelta<0) greenInc = -1;
    if(blueDelta<0)   blueInc = -1;

    //核心的代码到了，每过TimeInc的时间就让RGB的值增加redInc,greenInc,blueInc.如果fadeTime = 0就让它亮1ms
    if (fadeTime == 0) {
	analogWrite(GreenPin, green);
	analogWrite(RedPin,red);
	analogWrite(BluePin,blue);
	delay(2);
    }
    //fade循环，每过xxTimeInc时间就让rgb值加一个xxInc
    
    for (int fadeCounter=1; fadeCounter<=fadeTime; fadeCounter++) {
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
	analogWrite(GreenPin,greenTemp);
	analogWrite(RedPin,redTemp);
	analogWrite(BluePin,blueTemp);
	delay(1);
	if ( Start_Over ) return;  // if the IR detector saw IR, then we should reset and start over (Start_Over gets set to 1 in the interrupt routine if the IR detector saw IR)
    } 


    // hold loop
    for (int holdCounter=0; holdCounter<holdTime; holdCounter++) {
	analogWrite(GreenPin,greenTemp);
	analogWrite(RedPin,redTemp);
	analogWrite(BluePin,blueTemp);
	delay(10);
	if ( Start_Over ) return;  // if the IR detector saw IR, then we should reset and start over (Start_Over gets set to 1 in the interrupt routine if the IR detector saw IR)
    }
    lastFadetime = fadeTime;
    lastHoldTime = holdTime;
    lastRed = red;
    lastGreen = green;
    lastBlue = blue;
}           

void loop() { 
    interrupts();               //使能中断
    sendrgbElement();
    //下面代码是用来触发红外之后，rgb灯就红黄绿青蓝紫的变化
    if(Start_Over){
	Start_Over=0;
	rgbrandom();
    }
}
/*void loop() { 
    int index = 0;  
    interrupts();               //使能中断
    for (int count=0; count<180; count++) { 
    do {
        sendrgbElement(index);      // 发送RGB元素给LED 
        index++;                // 用来索引表中下一个元素
        if ( Start_Over ) break;        // 如果检测到有东西碰到红外就从头开始if the IR detector saw IR, then we should reset and start over
    } while ( !( (lightTab[index].fadeTime == 0 ) && (lightTab[index].holdTime == 0 ) ) );//如果两个时间都不等于0
    if ( Start_Over ) break;        // 如果检测到有东西碰到红外就从头开始if the IR detector saw IR, then we should reset and start over
    index = 0;
    }
    //下面代码是用来触发红外之后，rgb灯就红黄绿青蓝紫的变化
    if(Start_Over){
    Start_Over=0;
    rgbrandom();
    }
}
*/