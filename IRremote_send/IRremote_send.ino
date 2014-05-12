/* 
 硬件连接：
 pin4连接到按键
 * */

#include <IRremote.h>
IRsend irsend;
int buttonFlag=0;

void setup()
{
  Serial.begin(9600);
  pinMode(4,INPUT);
}

void loop() {
  if(digitalRead(4)){
    delay(20);
    if(digitalRead(4)){
      pressTime=millis();
      buttonFlag=1;
    }
  }
  if (1==buttonFlag&& millis()-pressTime<50) {
      irsend.sendNEC(0x8A20050A, 32); // Sony TV power code
  }
} 


if (las)
