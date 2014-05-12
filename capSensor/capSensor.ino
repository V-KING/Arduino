/*
 *pin8 -> R灯 -> GND,
 *pin9 -> G灯 -> GND
 *pin4发射端 -> 1M电阻 ->  手
 *pin2接收端 -> 手
 *pin4发射端 -> 1M电阻 ->  手
 *pin3接收端 -> 手
 * */

#include <CapacitiveSensor.h>
CapacitiveSensor capSensor = CapacitiveSensor(4,2);
CapacitiveSensor capSensor2 = CapacitiveSensor(4,3);

int threshold =1000;

const int ledPin=8;
const int ledPin2=9;


void setup()
{
	Serial.begin(9600);
	pinMode(ledPin,OUTPUT);
	pinMode(ledPin2,OUTPUT);
}

void loop()
{
	long sensorValue = capSensor.capacitiveSensor(30);	
	long sensorValue2 = capSensor2.capacitiveSensor(30);	
	Serial.println(sensorValue);

	if(sensorValue > threshold){
		digitalWrite(ledPin,LOW);	
	}
	else{ 
		digitalWrite(ledPin,HIGH);	
	}

	if(sensorValue2 > threshold){
		digitalWrite(ledPin2,LOW);	
	}
	else{ 
		digitalWrite(ledPin2,HIGH);	
	}
	//delay(10);
}
