int pin =8 ;
unsigned long low_duration;
unsigned long starttime;
unsigned long sampletime=30000;
unsigned long low_occupy_time=0;
unsigned long low_duration_all=0;

float ratio=0;
float concentration=0;
void setup(){
  pinMode(pin,INPUT);
  Serial.begin(9600);
  starttime=millis();
}

void loop(){
  low_duration = pulseIn(pin,LOW);
  low_duration_all += low_duration;
  if((millis()-starttime)>=sampletime)
  {
    ratio= low_duration_all/(sampletime*1.0);
    concentration=1.1*pow(ratio,3) - 3.8*pow(ratio,2) + 520*ratio + 0.62;
    
    Serial.print("low_duration: ");
    Serial.println(low_duration);
    Serial.print("ratio: ");
    Serial.println(ratio);
    Serial.print("concentration");
    Serial.println(concentration);
    
    low_duration_all=0;
    starttime=0;
  }
  
  
}




