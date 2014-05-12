#include <Servo.h>

Servo myservo;        //定义伺服对象
int LDR1_Pin = A0;    //analog pin A0
int LDR2_Pin = A5;    //analog pin A5
int Servo_Pin = 9;    //digital pin 9
float threshold = 20; //定义界限值threshold，如果两光敏差值val大于threshold就怎么怎么样
int Servo_Delay = 10; //就是让舵机慢点转，延时一下
float pos = 90;       //舵机（也叫伺服电机）到90度的位置，也就是中间位置
int LDR1;             //光照传感1的值
int LDR2;             //光照传感2的值
int val;              //两个光照传感的差值
int led = 13;         //连接到板子上的led，板子上自动一个led

void setup()              
{
	Serial.begin(9600);         
	pinMode(led, OUTPUT);  		//让pin 13上的led设置为输出模式
	digitalWrite(led, HIGH);	//led灭
	myservo.attach(Servo_Pin);  //将伺服电机（舵机）依附到Servo_Pin上
	myservo.write(90);          //让舵机转到90度的位置，即中间位置
	delay(1000);                
	digitalWrite(led, LOW);
}

void loop()
{
	LDR1 = analogRead(LDR1_Pin);  //read LDR1光照传感值 
	LDR2 = analogRead(LDR2_Pin);  //read LDR1光照传感值 
	val = LDR1 - LDR2;            //计算两个光照传感差值

	if(val < threshold && val > (-threshold))  //
		val = 0;      

	//因为本舵机转动的角度不能超过180，转动的角度范围是：10度到170度，
	//千万不要转动超过180范围的值，容易损坏舵机
	if(val > 0)
		if(pos > 10)	    
			moveLeft();    //舵机向左转
	if(val < 0)
		if(pos < 170)
			moveRight();   //舵机向右转
	//debug();             //调试
}

void moveLeft()      //左转
{
	pos=pos-0.5;
	digitalWrite(led, HIGH);
	myservo.write(pos);
	delay(Servo_Delay);    
	digitalWrite(led, LOW);
}

void moveRight()      //右转
{
	pos=pos+0.5;
	digitalWrite(led, HIGH);
	myservo.write(pos);
	delay(Servo_Delay);    
	digitalWrite(led, LOW);
}

void debug()         //调试函数
{
	Serial.print("Position : ");
	Serial.println(pos);
	Serial.print("Val : ");
	Serial.println(val);
	//Serial.print("LDR1 : ");
	//Serial.println(LDR1);
	//Serial.print("LDR2 : ");
	//Serial.println(LDR2);
}

