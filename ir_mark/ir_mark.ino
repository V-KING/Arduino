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
	pinMode(3,OUTPUT);
}

void setup()
{
  Serial.begin(9600);
  irsend.enableIROut(38);
  attachInterrupt(0,recv_isr,FALLING);
  //irsend.sendNEC(1,1);
}
void loop() {
  irsend.mark(500);
  

	if(g_flag==1){
		g_flag=0;
		Serial.println("detected!");
	}
}

