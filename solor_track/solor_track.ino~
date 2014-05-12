#include <Servo.h>

Servo myservo;        //servo object
int LDR1_Pin = A0;    //analog pin 0
int LDR2_Pin = A5;    //analog pin 5
int Servo_Pin = 9;    //digital pin 9
float threshold = 20;   //threshold 
int Servo_Delay = 250; //delay between movoment of servo
float pos = 90;              //position of servo
int LDR1;             //value stored for LDR1
int LDR2;             //value stored for LDR2
int val;              //difference of both LDRs
int led = 13;         //onboard led for status

void setup()              
{
  Serial.begin(9600);         //starting serial for debug
  pinMode(led, OUTPUT);  //set led to output mode
  digitalWrite(led, HIGH);
  myservo.attach(Servo_Pin);  //set servo to pin
  myservo.write(90);          //set initial position to center position
  delay(1000);                //wait for 1 sec after initialize
  digitalWrite(led, LOW);
}

void loop()
{
  LDR1 = analogRead(LDR1_Pin);  //read LDR1 reading
  LDR2 = analogRead(LDR2_Pin);  //read LDR1 reading 
  val = LDR1 - LDR2;            //difference of both LDRs

  if(val < threshold && val > (-threshold))  //value reset if lesser than threshold
      val = 0;      

  if(val > 0)
    if(pos > 50)
      moveLeft();    //move servo Left

    if(val < 0)
    if(pos < 130)
      moveRight();   //move servo Right

    //debug();             //for debugging
}

void moveRight()      //move right function
{
  pos=pos+0.5;
  digitalWrite(led, HIGH);
  myservo.write(pos);
  delay(Servo_Delay);    
  digitalWrite(led, LOW);
}

void moveLeft()      //move left function
{
  pos=pos-0.5;
  digitalWrite(led, HIGH);
  myservo.write(pos);
  delay(Servo_Delay);    
  digitalWrite(led, LOW);
}

void debug()         //debug function
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

