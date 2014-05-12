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

//例1.点亮一个led
int led_pin= 8;
void setup(){
	pinMode(led_pin,OUTPUT);
}

void loop(){
	digitalWrite(led_pin,LOW);
}


//例2.点亮一个led，闪烁
int led_pin= 8;
void setup(){
	pinMode(led_pin,OUTPUT);
}

void loop(){
	digitalWrite(led_pin,LOW);
	delay(500); //延时0.5秒
	digitalWrite(led_pin,HIGH);
	delay(500); //延时0.5秒
}

