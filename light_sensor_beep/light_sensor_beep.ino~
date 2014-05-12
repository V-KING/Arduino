const int ledPin=13;
int sensorValue=0;
int sensorHigh=0;
int sensorLow=0;

void setup()
{
	Serial.begin(9600);
	pinMode(ledPin,OUTPUT);	
	digitalWrite(ledPin,HIGH);
	while(millis()<5000)
	{
		sensorValue=analogRead(A0);
		if(sensorValue>sensorHigh)
		{
			sensorHigh=sensorValue;	
		}
		if(sensorValue<sensorLow)
		{
			sensorLow=sensorValue;	
		}
	}
}

void loop()
{
	sensorValue=analogRead(A0);
	//Serial.println(sensorValue);
	int pitch=map(sensorValue,sensorLow,sensorHigh,50,4000);
	Serial.println(pitch);
	tone(9,pitch);
	delay(50);
}
