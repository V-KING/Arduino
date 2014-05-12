/*
 * =====================================================================================
 *
 *       Filename:  morse_lcd_i2c.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014-2-10 10:54:45
 *
 *         Author: V__KING__ 
 *        Company: sogworks 
 *
 * =====================================================================================
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
long startTime ;
long elapsedTime ;
long breakTime = 0;
long finalTime = 0;
long gap;
long fractional;
long totalTime;
String getMorse[10];
String alphabet[6] = {"A","B","C","D","E","F"};
String morseDB[6] = {"-.",".---",".-.-",".--","-","--.-"};
int n=0;
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
	value = analogRead(ldr);
	if(value < 500) buttonState = low;
	else buttonState = high;
	if (buttonState == low && lastButtonState == high  &&  blinking == false) {
		startTime = millis();
		breakTime= millis() - finalTime;
		blinking = true;
		delay(5);
		lastButtonState = buttonState;
		digitalWrite(ledPin,HIGH);
	}
	else if (buttonState == high && lastButtonState == low && blinking == true) {
		elapsedTime =   millis() - startTime;
		blinking = false;
		lastButtonState = buttonState;
		digitalWrite(ledPin,LOW);
		time(elapsedTime);
	}
	else {//非0非1的时候，结束时间=当前的时间
		if(blinking==true)
			finalTime= millis();
		lastButtonState = buttonState;
	}
	if(totalTime > 100) {
		if(totalTime < 500) {
			//Serial.print("DI ");
			lcd.print("DI ");
			totalTime = 0;
			getMorse[n]+=".";
		}
		else {
			//Serial.print("DA ");
			lcd.print("DA ");
			totalTime = 0;
			getMorse[n]+="-";
		}
	}
}

//处理时间的函数
void time (long) {
#if 0
	totalTime =  (int)(elapsedTime/1000L);
	gap = (int)(breakTime);
	fractional = (int)(elapsedTime % 1000L);
	totalTime += (fractional/1000);
#endif
	totalTime =  elapsedTime;
	gap = (breakTime);

	Serial.println("-----");

	if(gap>1000) { 					//按下去的时间大于250ms时
		Serial.println("-----");
		Serial.println(getMorse[n]);
		lcd.print(alphabet[n]);
		if(getMorse[n]=="...") Serial.println("B");
		else if(getMorse[n]=="-.") Serial.println("A");
		n++;

	}
#if 0
	if(breakTime>1000) {
		lcd.print(alphabet[n]);
		//    Serial.println(getMorse[n]);
		n=0;
		for(int i=0;i<10;i++)
			getMorse[i] = "";
	}
#endif
}




