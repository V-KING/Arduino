#include<IRremote.h>

IRsend irsend;
int g_flag=0;
int g_pwm_pin=3;

void recv_isr()
{
	g_flag=1;

}
void pwm()
{
	TCCR2A |= _BV(COM2B1);
}


void setup()
{
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  digitalWrite(3,LOW);
}
void loop() {
}

