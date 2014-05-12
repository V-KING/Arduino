int switchPin = 2;
int value = 0; 

void setup() {
  pinMode(switchPin, INPUT);
  Serial.begin(9600);  
}

void loop() {
  value = digitalRead(switchPin);
  if (HIGH == value) {
    Serial.println("Is here");
  } else {
    Serial.println("Not here");
  }
}

