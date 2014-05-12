void setup(){
  Serial.begin(9600);
}

void loop(){
  for (int i= 0; i<100000; i++)
  {
    Serial.print("yeelink:");
    Serial.println(random());
    delay(5000);
  }
}




