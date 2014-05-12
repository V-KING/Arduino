#define A  262
#define S  294
#define D  330
#define F1 349
#define G  392
#define H  440
#define J  494
#define K  523
#define L  587


int pwmPin=9;
int incomingByte;
void setup(){
  pinMode(pwmPin,OUTPUT);
  Serial.begin(9600);
}
void loop(){
  if(Serial.available()>0){
    incomingByte=Serial.read();
  }
  else{
    incomingByte=0;
  }
  
  switch(incomingByte)
  {
    case 'A':
      tone(pwmPin,A);
      delay(250);
      noTone(pwmPin);
      break;
    case 'S':
      tone(pwmPin,S);
      delay(250);
      noTone(pwmPin);
      break;
    case 'D':
      tone(pwmPin,D);
      delay(250);
      noTone(pwmPin);
      break;
    case 'F':
      tone(pwmPin,F1);
      delay(250);
      noTone(pwmPin);
      break;
    case 'G':
      tone(pwmPin,G);
      delay(250);
      noTone(pwmPin);
      break;
    case 'H':
      tone(pwmPin,H);
      delay(250);
      noTone(pwmPin);
      break;
    case 'J':
      tone(pwmPin,J);
      delay(250);
      noTone(pwmPin);
      break;
    case 'K':
      tone(pwmPin,K);
      delay(250);
      noTone(pwmPin);
      break;
    case 'L':
      tone(pwmPin,L);
      delay(250);
      noTone(pwmPin);
      break;
  }
  
}


