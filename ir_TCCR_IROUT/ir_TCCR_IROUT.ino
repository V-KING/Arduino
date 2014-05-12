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
  irsend.enableIROut(38);
  TCCR2A |= _BV(COM2B1);

  attachInterrupt(0,recv_isr,CHANGE);
  //irsend.sendNEC(1,1);
}
void loop() {
  //irsend.sendNEC(1,1);

	if(g_flag==1){
		g_flag=0;
		Serial.println("detected!");
	}
}
