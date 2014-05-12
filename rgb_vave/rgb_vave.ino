#include<IRremote.h>

IRsend irsend;
int g_flag=0;
int g_pwm_pin=3;

void recv_isr()
{
	g_flag=1;

}
/*  
void setup()
{
  Serial.begin(9600);
  irsend.enableIROut(38);
  TCCR2A |= _BV(COM2B1);

  attachInterrupt(0,recv_isr,LOW);
  //irsend.sendNEC(1,1);
}
void loop() {
  //irsend.sendNEC(1,1);

	if(g_flag==1){
		g_flag=0;
		Serial.println("detected!");
	}
}
*/
void pwm()
{
	TCNT2=0;
	pinMode(3,OUTPUT);
	TCCR2A |= _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
	TCCR2B = _BV(WGM22) | _BV(CS21);
}

void setup()
{
  Serial.begin(9600);

  pwm();

  attachInterrupt(0,recv_isr,LOW);
  //irsend.sendNEC(1,1);
}
void loop() {
  //irsend.sendNEC(1,1);

	if(g_flag==1){
		g_flag=0;
		Serial.println("detected!");
	}
}
