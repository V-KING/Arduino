int pin=5; // 定义超声波信号发出接口 
int duration=0;
int RangeInCentimeters=0;
void setup() { 
  Serial.begin(9600);   

} 
void loop() { 
  pinMode(pin, OUTPUT); 
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin,LOW);

  pinMode(pin, INPUT); 

  duration = pulseIn(pin,HIGH);
  RangeInCentimeters = duration/29/2;	
  Serial.println(RangeInCentimeters);
  delay(800);
}


