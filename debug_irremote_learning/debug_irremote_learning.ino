#include <IRremote.h>
#include "avr/pgmspace.h"
#include "ir_results.h"
int RECV_PIN = 11;
int BUTTON_PIN = 12;
int STATUS_PIN = 13;

IRrecv irrecv(RECV_PIN);
IRsend irsend; //pin3

//decode_results results;

// 用来存储的变量
//int codeType = -1; //code类型 
//unsigned long codeValue; // 可识别code的值The code value if not raw
//unsigned int rawCodes[RAWBUF] ; // 不可识别的时候就存储ontime和offtime
//int codeLen; // 不可识别code的rawcodes的长度
//int toggle = 0; // The RC5/6 toggle state

// Stores the code for later playback
// Most of this code is just logging
// 存储最近一次接受得到的数据
void storeCode(ir_results *irresults) {

}

void sendCode(int repeat,ir_results *irresults) {
  
 
}


void setup()
{
	Serial.begin(9600);
	irrecv.enableIRIn(); // 使能红外接收
	pinMode(BUTTON_PIN, INPUT);
	pinMode(STATUS_PIN, OUTPUT);
}
int lastButtonState;
void loop() {
	// If button pressed, send the code.
	int buttonState = digitalRead(BUTTON_PIN);
	if (lastButtonState == HIGH && buttonState == LOW) {
		Serial.println("Released");
		irrecv.enableIRIn(); // Re-enable receiver
	}
}

