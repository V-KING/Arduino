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
 *  1.短按就是DI
 *  2.长按就是DA
 *  3.不按2s以上就是一个morse字符的终止
 * ============================================
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define ledPin 13
#define ldr 3
/*定义显示设备*/
#define LCD_DEV 1     //LCD_DEV 定义为1：就是LCD显示；定义为0：就是不显示
#define SERIAL_DEV 1

int value = 0;
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
  //读取按键的值value，也可以是其他的值，例如光照强度
	value = analogRead(ldr);
	int limit_value=500;
	getMorseSignal(value,limit_value);
}


//以下的代码可以不用修改，也可以根据自主需要修改
//---------getMorseSignal用的到的全局变量--------
int high = 1;
int low = 0;
int buttonState = high;
int lastButtonState = low;
int blinking = false;
long previousMillis = 0;
long last_press_time=0 ;
long unPressTime=0 ;
long pressTime = 0;
long last_unpress_time = 0;
String getMorse[16];
int n=0,m=0;
int flag=0;
int j=0;
/*---------getMorseSignal函数--------------------
功能：解析morse码并显示
输入参数：
		value：模拟输入的值。可以是光照强度，或者按键值
		limit_value: 如果小于limit_value，就是相当于按键按下，大于该值就是松开
*/
void getMorseSignal(int value,int limit_value  ){
	if(value < limit_value) buttonState = low;
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
			//lcd.print(".");
			pressTime = 0;
			getMorse[n]+=".";
		}
		else {
			//lcd.print("-");
			pressTime = 0;
			getMorse[n]+="-";
		}
	}

	//没有按下的时间长度>2000ms的时候就是结束，我们以字符'/'来结束一个morse字符并且显示出来,flag只使它交换执行,松开的一瞬间flag=1(上面)；
	if( millis() - last_unpress_time>2000 && flag==1){
		//un_press_totall_time=0;
#ifdef LCD_DEV//如果定义了I2C的lcd类 
		lcd.setCursor(j,m);      //j显示是哪一列
		if(getMorse[n]==".-") lcd.printstr("A");
		else if(getMorse[n]=="-...") lcd.printstr("B");
		else if(getMorse[n]=="-.-.") lcd.printstr("C");
		else if(getMorse[n]=="-..") lcd.printstr("D");
		else if(getMorse[n]==".") lcd.printstr("E");
		else if(getMorse[n]=="..-.") lcd.printstr("F");
		else if(getMorse[n]=="--.") lcd.printstr("G");
		else if(getMorse[n]=="....") lcd.printstr("H");
		else if(getMorse[n]=="..") lcd.printstr("I");
		else if(getMorse[n]==".---") lcd.printstr("J");
		else if(getMorse[n]=="-.-") lcd.printstr("K");
		else if(getMorse[n]==".-..") lcd.printstr("L");
		else if(getMorse[n]=="--") lcd.printstr("M");
		else if(getMorse[n]=="-.") lcd.printstr("N");
		else if(getMorse[n]=="---") lcd.printstr("O");
		else if(getMorse[n]==".--.") lcd.printstr("P");
		else if(getMorse[n]=="--.-") lcd.printstr("Q");
		else if(getMorse[n]==".-.") lcd.printstr("R");
		else if(getMorse[n]=="...") lcd.printstr("S");
		else if(getMorse[n]=="-") lcd.printstr("T");
		else if(getMorse[n]=="..-") lcd.printstr("U");
		else if(getMorse[n]=="...-") lcd.printstr("V");
		else if(getMorse[n]==".--") lcd.printstr("W");
		else if(getMorse[n]=="-..-") lcd.printstr("X");
		else if(getMorse[n]=="-.--") lcd.printstr("Y");
		else if(getMorse[n]=="--..") lcd.printstr("Z");
		else if(getMorse[n]==".----") lcd.printstr("1");
		else if(getMorse[n]=="..---") lcd.printstr("2");
		else if(getMorse[n]=="...--") lcd.printstr("3");
		else if(getMorse[n]=="....-") lcd.print("4");
		else if(getMorse[n]==".....") lcd.printstr("5");
		else if(getMorse[n]=="-....") lcd.printstr("6");
		else if(getMorse[n]=="--...") lcd.printstr("7");
		else if(getMorse[n]=="---..") lcd.printstr("8");
		else if(getMorse[n]=="----.") lcd.printstr("9");
		else if(getMorse[n]=="-----") lcd.printstr("0");
		else if(getMorse[n]=="..--..") lcd.printstr("?");
		else if(getMorse[n]=="-..-.") lcd.printstr("/");
		else if(getMorse[n]==".-.-.-") lcd.printstr(".");
		else if(getMorse[n]==".--.-.") lcd.printstr("@");
		else lcd.print(" ");
		n++;
                if(n>=16) n=0;
		if(j++>=15) {j=0;m=0;delay(1000);lcd.clear();}
#endif
#ifdef SERIAL_DEV //定义了其他的显示设备,如串口显示
		if(getMorse[n]=="...") Serial.print("s");
		else if(getMorse[n]=="---") Serial.print("o");
		Serial.print("/");
#endif
		flag=0;
	}
}


