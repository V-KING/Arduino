/*
 * ============================================
 *       Filename:  morse_lcd_i2c.c
 *        Version:  1.0
 *        Created:  2014-2-10 10:54
 *        Complete: 2014-2-11 14:22
 *         Author: V__KING__ 
 *        Company: sogworks 
 * ============================================
 *用法：
 *  1.短按就是DI，出现"."
 *  2.长按就是DA，LCD显示"-"
 *  3.不按2s以上就是一个morse字符的终止，在LCD上以"/"显示表一个字符的终止
 *  
 *注意：
 *  1.可以自己定义morse码的编码
 *  2.只需要改：95~96行的代码，或者在95~96行之后添加自写代码
 *
 * ============================================
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define ledPin 13
#define ldr 3
int high = 1;
int low = 0;
int value = 0;
int buttonState = high;
int lastButtonState = low;
int blinking = false;
long previousMillis = 0;
long last_press_time=0 ;
long unPressTime=0 ;
long pressTime = 0;
long last_unpress_time = 0;
String getMorse[10];
int n=0;
int flag=0;
//int un_press_totall_time=0;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
	Serial.begin(9600);
	lcd.init();
	lcd.backlight();
	pinMode(ledPin, OUTPUT);
	pinMode(ldr,INPUT);
}

void loop() {
	getSignal();
}

void getSignal() {
	//读取按键的值value，也可以是其他的值，例如光照强度
	value = analogRead(ldr);
	if(value < 500) buttonState = low;
	else buttonState = high;
	//如果本次的按键状态是low(按下去),并且上次状态是high并且上次ledpin没有亮
	if (buttonState == low && lastButtonState == high  &&  blinking == false) {
		last_press_time = millis();
		unPressTime= millis() - last_unpress_time;
		blinking = true;				//ledpin亮
		lastButtonState = buttonState;	//将本次的状态和上次状态同步
		digitalWrite(ledPin,HIGH);
	}
	//本次状态时high(没有按),上次状态是按下
	else if (buttonState == high && lastButtonState == low && blinking == true) { 
		last_unpress_time= millis();
		pressTime = millis() - last_press_time;
		blinking = false;				//ledpin没有不亮
		lastButtonState = buttonState;	//将本次的状态和上次状态同步
		digitalWrite(ledPin,LOW);
		//为什么需要un_press_totall_time?我们需要在放开手的瞬间才显示结束符"/"
		//如果不这样要按下后unPressTime才会被赋值，才大于2000
		//un_press_totall_time=unPressTime;
		flag=1;
	}
	else {//非0非1的时候,就是你一直按着的状态或者你一直不按的状态，也就是本次状态和上次状态都是一样的。
		if(blinking==true)
			last_unpress_time= millis();
		lastButtonState = buttonState;
	}

	//亮1t+灭1t==》DI，按下的时间长度来确定是DI还是DA
	if(pressTime > 100 ) {
		if(pressTime < 500) {
			lcd.print(".");
			pressTime = 0;
			getMorse[n]+=".";
		}
		else {
			lcd.print("-");
			pressTime = 0;
			getMorse[n]+="-";
		}
	}

	//没有按下的时间长度>2000ms的时候就是结束，我们以字符'/'来结束一个morse字符并且显示出来,flag只使它交换执行,松开的一瞬间flag=1(上面)；
	if( millis() - last_unpress_time>2000 && flag==1){
		//un_press_totall_time=0;
		if(getMorse[n]=="...") lcd.print("s");
		else if(getMorse[n]=="---") lcd.print("o");
		lcd.print("/");
		n++;
		if(n>10) n=0;					//控制溢出，getMorse有10个String类型的元素
		flag=0;
	}
}




