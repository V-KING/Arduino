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
int dis;

void loop()
{
  dis=ultrasonic.MeasureInCentimeters();  //测得距离
  delay(1);
  //Serial.println(dis);


//如果距离是大于25cm,就是停在1000ms的位置，根据不同的电机调整
//如果是大于25cm，就全速前进打人
	if(dis<25)				
	{
		myservo.writeMicroseconds(900);	
//              while(myservo.read()>1){
//                myservo.write(--pos);
//                delay(1);	
//              }
	}
	else{	
		//pos=map(dis,0,120,0,180);	
               // if(myservo.read()!=180)
		  myservo.writeMicroseconds(2100);
//                 while(myservo.read()<179){
//                  myservo.write(++pos);
//                  delay(1);	
//              }
        }
 }

