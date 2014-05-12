float read_GP2Y0A21_range(byte pin) {
	int tmp;

	tmp = analogRead(pin);
	if (tmp < 3)
		return -1; // invalid value
        return 2547.8/((float)tmp*0.49-10.41)-0.42;
	//return (6787.0 /((float)tmp - 3.0)) - 4.0;
        //return 65*pow(tmp, -1.10);
} 
//10~80 CM range
void setup()
{
  Serial.begin(9600);
  pinMode(A0,INPUT);
}

void loop(){
  float distence=read_GP2Y0A21_range(A0);
  Serial.print("distence=");
  Serial.println(distence);
  delay(1000);
}
