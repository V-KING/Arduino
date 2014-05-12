int previous=0;
#include<my_stepper.h>
My_stepper stepper(8,9,10,11);
void setup()
{
  	Serial.begin(9600);
	stepper.my_setSpeed(600);
}

void loop()
{
	int val = analogRead(0);
  //stepper.my_step(64*64/2,-1);//arg1：64*64 step == 2*PI,转半圈。arg2:如果为1就是正传，-1反转
 	stepper.my_step(val-previous,  (val-previous)/abs(val-previous));
	previous=val;
}

