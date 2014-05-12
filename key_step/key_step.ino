#define DEBUG 1

int previous=0;
#include<my_stepper.h>
My_stepper stepper(8,9,10,11);



void key1press(void)
{
 	stepper.my_step(64,1);
}

void key2press(void)
{
 	stepper.my_step(64,-1);
}

void donothing(void)
{
 	stepper.my_step(0,-1);
}

void setup()
{
	Serial.begin(9600);
	stepper.my_setSpeed(600);
}


void loop()
{
	int val=analogRead(A0);		
#if DEBUG 
	Serial.println(val);
#endif

	if(val>1023/2-10 && val<1023/2+10){
		key1press();	
	}
	else if(val<100){
		key2press();
	}
	else{
		donothing();
	}
}




