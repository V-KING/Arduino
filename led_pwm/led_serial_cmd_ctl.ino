/*
 * ====================================
 *        Version:  1.0
 *        Created:  2014-4-2 15:51:07
 *       Revision:  none
 *       Compiler:  arduino-IDE 
 *
 *        Company:  www.sogworks.cn
 *
 * ====================================
 */


//��1,�ô��ڿ���led��˸ʱ�䣬����ʲôƵ����˸��ʱ�����۾ͷ���������
int led_pin= 8;
int analog_pin= A0;
void setup(){
	Serial.begin(9600);
	pinMode(led_pin,OUTPUT);
	pinMode(analog_pin,INPUT);
}
int s_data=0;

void loop(){
	if(Serial.available()){
		s_data=Serial.parseInt();
		Serial.read();
	}
	digitalWrite(led_pin,HIGH);
	Serial.println(s_data);
	delay(s_data);
	digitalWrite(led_pin,LOW);
	delay(s_data);
}


//��2.��serial input����led������
int led_pin = 3;
void setup(){
  Serial.begin(9600);
  pinMode(led_pin,OUTPUT);
}
int val=0;
void loop(){
  if(Serial.available()){
    val=Serial.parseInt();
    Serial.read();
  }
  if(val>255 || val <0){
    Serial.println("Err:please input a intiger value between 0 to 255 !auto set Max=255");
    delay(1000);
    if(val>255){
      val=255;
    }
    else{
      val=0;
    }
  }
  else{
    analogWrite(led_pin,val);
  }
}


//��3.��������������˸,���봮�����ݵ��ڵƵ���˸�ٶ�
int red_led_pin = 3;
int green_led_pin = 5;
int analog_pin = A0;
void setup(){
  Serial.begin(9600);
  pinMode(red_led_pin ,OUTPUT);
  pinMode(green_led_pin,OUTPUT);
  digitalWrite(red_led_pin,LOW);
  digitalWrite(green_led_pin,LOW);
}
int val=0; 
void loop(){
  if(Serial.available()){
    val=Serial.parseInt();
    Serial.read();
  }
  digitalWrite(red_led_pin,HIGH);
  digitalWrite(green_led_pin,LOW);
  delay(val);
  digitalWrite(green_led_pin,HIGH);
  digitalWrite(red_led_pin,LOW);
  delay(val);
}






