/* 
long step_delay=0;
long last_step_time=0;
int step_number=0;

int Pin0=8,Pin1=9,Pin2=10,Pin3=11;
int number_of_steps=64;	//1:64
*/


/******************/
int previous=0;
#include<my_stepper.h>
My_stepper stepper(8,9,10,11);
void setup()
{
  	Serial.begin(9600);
	stepper.my_setSpeed(500);
}

void loop()
{
	int val = analogRead(0);
  //stepper.my_step(64*64/2,-1);//arg1：64*64 step == 2*PI,转半圈。arg2:如果为1就是正传，-1反转
 	stepper.my_step((val-previous)>3?(val-previous):0,  (val-previous)/abs(val-previous));
	previous=val;
}

