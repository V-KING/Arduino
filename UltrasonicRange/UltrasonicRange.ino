#include <Ultrasonic.h>
#include <NewSoftSerial.h>


Ultrasonic ultrasonic(7);
 void setup(){
   Serial.begin(9600);
}
void loop()
{
  long dis;
  dis=ultrasonic.MeasureInCentimeters();
  delay(1000);
   Serial.print("the distence is: ");
   Serial.print(dis);
   Serial.println("cm");
 }
   

