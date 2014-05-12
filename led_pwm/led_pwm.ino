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


//例3,用电位器控制一个led闪烁，pwm
int led_pin= 8;
int analog_pin= A0;
void setup(){
	Serial.begin(9600);
	pinMode(led_pin,OUTPUT);
	pinMode(analog_pin,INPUT);
}

	int val;
void loop(){
	val=analogRead(analog_pin);	
	digitalWrite(led_pin,HIGH);
	Serial.println(val);
	delay(val);
	digitalWrite(led_pin,LOW);
	delay(val);
}

//例4.呼吸灯,和闪烁类似，只是多了两个for控制pwm
void setup()
{
  pinMode(8,OUTPUT);  
}

void loop()
{
  for (int a=0; a<=255; a++)
  {
    analogWrite(8,a);
    delay(2);
  }
  for (int a=255; a>=0; a--)
  {
    analogWrite(8,a);
    delay(2);
  }
}


//例5.用电位器调节led的亮度,注意pwm和频率的区别
int led_pin = 8;
int analog_pin= A0;
void setup(){
	pinMode(led_pin,OUTPUT);
	pinMode(analog_pin,INPUT);
}

	int val=0;
void loop(){
	val = map(analogRead(analog_pin),0,1023,0,255);
	analogWrite(led_pin,val);
}


//例6.两个灯轮流的闪烁,自动的由慢而快的闪烁
int red_led_pin = 8;
int green_led_pin = 5;
void setup(){
	pinMode(red_led_pin ,OUTPUT);
	pinMode(green_led_pin,OUTPUT);
	digitalWrite(red_led_pin,LOW);
	digitalWrite(green_led_pin,LOW);
}

void loop(){
	for(int i=100; i>0; i--){
		digitalWrite(red_led_pin,HIGH);
		digitalWrite(green_led_pin,LOW);
		delay(i);
		digitalWrite(green_led_pin,HIGH);
		digitalWrite(red_led_pin,LOW);
		delay(i);
	}
}


//7.两个灯轮流的闪烁,利用电位器手动的调节灯的闪烁速度
//只需要在原来的基础上删除for语句，加入analogRead
int red_led_pin = 3;
int green_led_pin = 5;
int analog_pin = A0;
void setup(){
	pinMode(red_led_pin ,OUTPUT);
	pinMode(green_led_pin,OUTPUT);
	digitalWrite(red_led_pin,LOW);
	digitalWrite(green_led_pin,LOW);
}
int val=0;
void loop(){
	val = analogRead(A0);
	digitalWrite(red_led_pin,HIGH);
	digitalWrite(green_led_pin,LOW);
	delay(val);
	digitalWrite(green_led_pin,HIGH);
	digitalWrite(red_led_pin,LOW);
	delay(val);
}


