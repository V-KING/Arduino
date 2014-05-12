const int analogPin = A0; 
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;
const int colourNum=6;

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, 255-red);
  analogWrite(greenPin, 255-green);
  analogWrite(bluePin, 255-blue);  
}


void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
}

void loop() {
  int sensorReading = analogRead(analogPin);
  Serial.println(sensorReading);
  int ledLevel = map(sensorReading, 0, 1023, 1, 6);
  Serial.println(ledLevel);
  switch(ledLevel)
  {
  case 1: 
    setColor(0, 255, 255);  // 浅绿色
    break;
  case 2: 
    setColor(0, 255, 0);  // 绿色
  break;
  case 3: 
    setColor(0, 0, 255);  // 蓝色
    break;
  case 4: 
    setColor(255, 255, 0);  // 黄色
    break;
  case 5: 
    setColor(255, 0, 0);  // 红色
    break;
  case 6: 
    setColor(80, 0, 80);  // 紫色
    break;
  }
  delay(500);
}




