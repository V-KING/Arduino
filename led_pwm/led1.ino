/*
 * ====================================
 *        Version:  1.0
 *        Created:  2014-4-2 15:30:46
 *       Compiler:  arduino-IDE
 *
 *        Company:  www.sogworks.cn
 *
 * ====================================
 */

//��1.����һ��led
int led_pin= 8;
void setup(){
	pinMode(led_pin,OUTPUT);
}

void loop(){
	digitalWrite(led_pin,LOW);
}


//��2.����һ��led����˸
int led_pin= 8;
void setup(){
	pinMode(led_pin,OUTPUT);
}

void loop(){
	digitalWrite(led_pin,LOW);
	delay(500); //��ʱ0.5��
	digitalWrite(led_pin,HIGH);
	delay(500); //��ʱ0.5��
}

