#include <EEPROM.h>

/*
 * IRrecord: record and play back IR signals as a minimal 
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * An IR LED must be connected to the output PWM pin 3.
 * A button must be connected to the input BUTTON_PIN; this is the
 * send button.
 * A visible LED can be connected to STATUS_PIN to provide status.
 *
 * The logic is:
 * If the button is pressed, send the IR code.
 * If an IR code is received, record it.
 *
 * Version 0.11 September, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 * 为了能永久性的保存学习的代码，就将学习后的代码存入EEPROM中。
 */

#include <IRremote.h>
#include "avr/pgmspace.h"

int RECV_PIN = 11;
int BUTTON_PIN = 12;
int STATUS_PIN = 13;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;
int button_eeprom_state=1;
int last_buttone_eepromState=1;
int button_eeprom=4;
void setup()
{
	Serial.begin(9600);
	irrecv.enableIRIn(); // Start the receiver
	pinMode(BUTTON_PIN, INPUT);
	pinMode(STATUS_PIN, OUTPUT);
}

// Storage for the recorded code
int codeType = -1; // The type of code
unsigned long codeValue; // The code value if not raw
unsigned int rawCodes[RAWBUF] ; // The durations if raw
int codeLen; // The length of the code
int toggle = 0; // The RC5/6 toggle state

// Stores the code for later playback
// Most of this code is just logging
void storeCode(decode_results *results) {
	codeType = results->decode_type;
	int count = results->rawlen;
	if (codeType == UNKNOWN) {
		Serial.println("Received unknown code, saving as raw");
		codeLen = results->rawlen - 1;
		// To store raw codes:
		// Drop first value (gap)
		// Convert from ticks to microseconds
		// Tweak marks shorter, and spaces longer to cancel out IR receiver distortion
		for (int i = 1; i <= codeLen; i++) {
			if (i % 2) {
				// Mark
				rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK - MARK_EXCESS;
				Serial.print(" m");
			} 
			else {
				// Space
				rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK + MARK_EXCESS;
				Serial.print(" s");
			}
			Serial.print(rawCodes[i - 1], DEC);
			if(last_buttone_eepromState==0 && button_eeprom_state==0){
				EEPROM.write(i,rawCodes[i-1]);
				EEPROM.write(i-1,codeLen);
				last_buttone_eepromState=button_eeprom_state;
			}else{
				last_buttone_eepromState=1;
			}
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
		
		if(last_buttone_eepromState==0 && button_eeprom_state==0){
				EEPROM.write(100,codeValue);
				EEPROM.write(101,codeLen);
				last_buttone_eepromState=button_eeprom_state;
			}else{
				last_buttone_eepromState=1;
			}
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
		//pwm频率是38khz
		codeLen=EEPROM.read(0);
		for(int i=1;i<codeLen; i++){
			rawCodes[i-1]=EEPROM.read(i);
		}
		irsend.sendRaw(rawCodes, codeLen, 38);
		Serial.println("Sent raw");
	}
}

int lastButtonState;

void loop() {
	button_eeprom_state=digitalRead(button_eeprom);

	int buttonState = digitalRead(BUTTON_PIN);
	if (lastButtonState == HIGH && buttonState == LOW) {
		Serial.println("Released");
		irrecv.enableIRIn(); //使能红外接收
	}

	//如果buttonState按下就发送 
	if (buttonState) {
		delay(25);
		if(buttonState){
			Serial.println("Pressed, sending");
			digitalWrite(STATUS_PIN, HIGH);
			sendCode(lastButtonState == buttonState);
			digitalWrite(STATUS_PIN, LOW);
			delay(100); //延时等待发送完 
	} 
	else if (irrecv.decode(&results)) {
		digitalWrite(STATUS_PIN, HIGH);
		storeCode(&results);
		irrecv.resume(); //重启接收器 
		digitalWrite(STATUS_PIN, LOW);
	}
	lastButtonState = buttonState;
}

}




