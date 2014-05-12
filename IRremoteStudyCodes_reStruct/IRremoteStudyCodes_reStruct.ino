/*
 * 硬件连接：
 * 红外接收引脚 -> RECV_PIN
 * 红外发送管   -> PIN3
 * 发送按键     -> BUTTONE_PIN
 * 存储到EEPROM按键 -> pin4
 *
 * 介绍:
 * 按键按下，就发送红外数据
 * 没有按下，就是一直接受数据，并且存储数据
 * EEPROM按键按下就是接收
 *
 */

#include <IRremote.h>
#include "avr/pgmspace.h"
#include "ir_irresults.h"




int RECV_PIN = 11;
int BUTTON_PIN = 12;
int STATUS_PIN = 13;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

//decode_results results;

/* -1
// 用来存储的变量
int codeType = -1; //code类型 
unsigned long codeValue; // 可识别code的值The code value if not raw
unsigned int rawCodes[RAWBUF] ; // 不可识别的时候就存储ontime和offtime
int codeLen; // 不可识别code的rawcodes的长度
int toggle = 0; // The RC5/6 toggle state
*/

// 存储最近一次接受得到的数据
void storeCode(decode_results *results) {
	codeType = results->decode_type;
	int count = results->rawlen;
	if (codeType == UNKNOWN) {
		Serial.println("Received unknown code, saving as raw");
		codeLen = results->rawlen - 1;
		// To store raw codes:
		// 第一个数据rawbuf[0]丢弃不要(gap)
		// Convert from ticks to microseconds
		// Tweak marks shorter, and spaces longer to cancel out IR receiver distortion
		for (int i = 1; i <= codeLen; i++) {
			if (i % 2) {
				// Mark
				ir_result.rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK - MARK_EXCESS;
				Serial.print(" m");
			} 
			else {
				// Space
				ir_result.rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK + MARK_EXCESS;
				Serial.print(" s");
			}
			Serial.print(ir_result.rawCodes[i - 1], DEC);
		}
		Serial.println("");
	}
	else {
		if (codeType == NEC) {
			Serial.print("Received NEC: ");
			if (results->value == REPEAT) {
				// Don't record a NEC repeat value as that's useless.
				Serial.println("repeat; ignoring.");
				return;
			}
		} 
		else if (codeType == SONY) {
			Serial.print("Received SONY: ");
		} 
		else if (codeType == RC5) {
			Serial.print("Received RC5: ");
		} 
		else if (codeType == RC6) {
			Serial.print("Received RC6: ");
		} 
		else {
			Serial.print("Unexpected codeType ");
			Serial.print(codeType, DEC);
			Serial.println("");
		}
		Serial.println(results->value, HEX);
		codeValue = results->value;
		codeLen = results->bits;
	}
}

void sendCode(int repeat) {
	if (codeType == NEC) {
		if (repeat) {
			irsend.sendNEC(REPEAT, codeLen);
			Serial.println("Sent NEC repeat");
		} 
		else {
			irsend.sendNEC(codeValue, codeLen);
			Serial.print("Sent NEC ");
			Serial.println(codeValue, HEX);
		}
	} 
	else if (codeType == SONY) {
		irsend.sendSony(codeValue, codeLen);
		Serial.print("Sent Sony ");
		Serial.println(codeValue, HEX);
	} 
	else if (codeType == RC5 || codeType == RC6) {
		if (!repeat) {
			// Flip the toggle bit for a new button press
			toggle = 1 - toggle;
		}
		// Put the toggle bit into the code to send
		codeValue = codeValue & ~(1 << (codeLen - 1));
		codeValue = codeValue | (toggle << (codeLen - 1));
		if (codeType == RC5) {
			Serial.print("Sent RC5 ");
			Serial.println(codeValue, HEX);
			irsend.sendRC5(codeValue, codeLen);
		} 
		else {
			irsend.sendRC6(codeValue, codeLen);
			Serial.print("Sent RC6 ");
			Serial.println(codeValue, HEX);
		}
	} 
	else if (codeType == UNKNOWN /* i.e. raw */) {
		//  38 KHz的频率
		irsend.sendRaw(ir_result.rawCodes, codeLen, 38);
		Serial.println("Sent raw");
	}
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

	if (buttonState) {
		delay(25);
		if(buttonState){
			Serial.println("Pressed, sending");
			digitalWrite(STATUS_PIN, HIGH);
			sendCode(lastButtonState == buttonState);
			digitalWrite(STATUS_PIN, LOW);
			delay(100); // Wait a bit between retransmissions
		}
	} 
	else if (irrecv.decode(&ir_result.results)) {  //cg:results->ir_results.results
		digitalWrite(STATUS_PIN, HIGH);
		storeCode(&ir_result.results);				//cg:results->ir_results.results
		irrecv.resume(); // resume receiver
		digitalWrite(STATUS_PIN, LOW);
	}
	lastButtonState = buttonState;
}





