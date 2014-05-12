/*
 *       Filename:  my_stepper.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014-1-13 11:40:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (V__KING__), 
 *        Company: 	sogworks 
 *
 * =====================================================================================
 */

#include"my_stepper.h"
#include"Arduino.h"
My_stepper::My_stepper(int p1,int p2,int p3,int p4)
{
	this->Pin0=p1;	
	this->Pin1=p2;
	this->Pin2=p3;
	this->Pin3=p4;
	pinMode(this->Pin0,OUTPUT);
	pinMode(this->Pin1,OUTPUT);
	pinMode(this->Pin2,OUTPUT);
	pinMode(this->Pin3,OUTPUT);
	
}
void My_stepper::my_stepMotor(int thisStep)
{
	switch (thisStep) {
		case 0:
			digitalWrite(this->Pin0, LOW);
			digitalWrite(this->Pin1, LOW);
			digitalWrite(this->Pin2, LOW);
			digitalWrite(this->Pin3, HIGH);
			break;
		case 1:
			digitalWrite(this->Pin0, LOW);
			digitalWrite(this->Pin1, LOW);
			digitalWrite(this->Pin2, HIGH);
			digitalWrite(this->Pin3, HIGH);
			break;
		case 2:
			digitalWrite(this->Pin0, LOW);
			digitalWrite(this->Pin1, LOW);
			digitalWrite(this->Pin2, HIGH);
			digitalWrite(this->Pin3, LOW);
			break;
		case 3:
			digitalWrite(this->Pin0, LOW);
			digitalWrite(this->Pin1, HIGH);
			digitalWrite(this->Pin2, HIGH);
			digitalWrite(this->Pin3, LOW);
			break;
		case 4:
			digitalWrite(this->Pin0, LOW);
			digitalWrite(this->Pin1, HIGH);
			digitalWrite(this->Pin2, LOW);
			digitalWrite(this->Pin3, LOW);
			break;
		case 5:
			digitalWrite(this->Pin0, HIGH);
			digitalWrite(this->Pin1, HIGH);
			digitalWrite(this->Pin2, LOW);
			digitalWrite(this->Pin3, LOW);
			break;
		case 6:
			digitalWrite(this->Pin0, HIGH);
			digitalWrite(this->Pin1, LOW);
			digitalWrite(this->Pin2, LOW);
			digitalWrite(this->Pin3, LOW);
			break;
		case 7:
			digitalWrite(this->Pin0, HIGH);
			digitalWrite(this->Pin1, LOW);
			digitalWrite(this->Pin2, LOW);
			digitalWrite(this->Pin3, HIGH);
			break;
		default:
			digitalWrite(this->Pin0, LOW);
			digitalWrite(this->Pin1, LOW);
			digitalWrite(this->Pin2, LOW);
			digitalWrite(this->Pin3, LOW);
			break;
	} 
}

void My_stepper::my_setSpeed(long whatSpeed)
{
 	this->number_of_steps=64;
  this->step_delay = 60L * 1000L / this->number_of_steps / whatSpeed;
}


void My_stepper::my_step(int steps_to_move,int direction)
{  
	int steps_left = abs(steps_to_move);  // how many steps to take

	// decrement the number of steps, moving one step each time:
	while(steps_left > 0) {
		// move only if the appropriate delay has passed:examples
		if (millis() - this->last_step_time >= this->step_delay) {
			// get the timeStamp of when you stepped:
			this->last_step_time = millis();
			// increment or decrement the step number,
			// depending on direction:
			if (direction == 1) {
				this->step_number++;
				if (this->step_number == this->number_of_steps) {
					this->step_number = 0;
				}
			} 
			else if(direction==-1){
				if (this->step_number == 0) {
					this->step_number = this->number_of_steps;
				}
				this->step_number--;
				Serial.println(this->step_number);
			}
			// decrement the steps left:
			steps_left--;
			// step the motor to step number 0, 1, 2, or 3:
			my_stepMotor(this->step_number % 8);
		}
	}
}
