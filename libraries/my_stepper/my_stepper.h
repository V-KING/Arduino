/*
 *       Filename:  my_stepper.h
 *
 *    Description: 	八拍方式步进电机 
 *
 *        Version:  1.0
 *        Created:  2014-1-13 11:16:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (V__KING__), 
 *        Company: 	sogworks 
 *
 * =====================================================================================
 */
#ifndef MY_STEPPR_H
#define MY_STEPPR_H



class My_stepper{
	public:
		My_stepper(int p1,int p2,int p3,int p4);
		void my_stepMotor(int thisStep);
		void my_setSpeed(long whatSpeed);
		void my_step(int steps_to_move,int direction);

	private:
		int whatSpeed;			//set speed
		long step_delay;		//it relate to speed
		long last_step_time;
		int step_number;
		int number_of_steps;	//1:64
		int Pin0,Pin1,Pin2,Pin3;
};





#endif
