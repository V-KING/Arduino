#include <Servo.h> 
#include <Ultrasonic.h>
#include <NewSoftSerial.h>
int pos=0;	

Ultrasonic ultrasonic(7);				//定义Ultrasonic实例
Servo myservo;					//定义Servo实例

 void setup(){
  // Serial.begin(9600);
	myservo.attach(9);				//绑定PWM引脚9
	myservo.writeMicroseconds(1000);			//让servo电机停在你想停的位置
  //Serial.println("begin servo");
}
int dis,lastdis;
int Servo_Delay=1;
int val;
void loop()
{
  dis=ultrasonic.MeasureInCentimeters();  //测得距离
  val=dis-lastdis;
  delay(1);
  //Serial.println(dis);
if(val< 10 && val > (-10))  //
		val = lastdis;      

//如果距离是大于25cm,就是停在1000ms的位置，根据不同的电机调整
//如果是大于25cm，就全速前进打人
	if(val<25)				
	{
		
                    moveLeft();
	}
	else{	
		moveRight();
        }
    lastdis=dis;
 }
void moveLeft()      //左转
{
	myservo.write(0);
	delay(Servo_Delay);    
}

void moveRight()      //右转
{
	pos=pos+0.5;
	myservo.write(180);

}
