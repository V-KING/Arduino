const int analogPin = A0;
 
void setup() {
  Serial.begin(9600);
  pinMode(analogPin,INPUT);
}
 
void loop() {
int sensorReading = analogRead(analogPin);
 Serial.println(sensorReading);

int ledLevel = map(sensorReading, 0, 1023, 0, 100);
 
Serial.print(ledLevel);
Serial.println("mg/L");

delay(1000);
}
