static int detetch_pin=2;
volatile int flag=0;
void detetch_function(void){
  flag=1;
}



void setup(){
  Serial.begin(9600);
  Serial.println("Serial begin");
  pinMode(detetch_pin,INPUT);
  attachInterrupt(0,detetch_function , RISING);
  Serial.println("attachInterrupt is set");
  Serial.println("Fire detetch begin......");
}

void loop(){
  if(flag==1){
    Serial.println("Big Fire !!");
    flag=0;
  }
}
