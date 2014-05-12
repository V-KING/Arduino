//定义频率，每一种频率代表一个音调
//1234567分别代表1234567的音调
#define A  262
#define S  294
#define D  330
#define F1 349
#define G  392
#define H  440
#define J  494
#define K  523
#define L  587


int pwmPin=9;						//pwm的引脚为9
int button;					//到arduino板子的数据
void setup(){
  pinMode(pwmPin,OUTPUT);			//pwmPin引脚输出控制蜂鸣器发声
  Serial.begin(9600);
}
void loop(){
int i;
	for( i=1; i<=9; i++)
	{
		button=0;
		button=digitalRead(i);
	}
  int x=button* i;
  switch(x)					//在上面的循环中我讲button=0；然后读取digitalRead(i)给button，
  {									//也就是说如果button为1时，button*1==i;
    case 1:
      tone(pwmPin,A);				//频率不一样，发出的音调也不一样
      delay(250);					//这个频率持续的时间，音调持续时间
      noTone(pwmPin);
      break;
    case 2:
      tone(pwmPin,S);
      delay(250);
      noTone(pwmPin);
      break;
    case 3:
      tone(pwmPin,D);
      delay(250);
      noTone(pwmPin);
      break;
    case 4:
      tone(pwmPin,F1);
      delay(250);
      noTone(pwmPin);
      break;
    case 5:
      tone(pwmPin,G);
      delay(250);
      noTone(pwmPin);
      break;
    case 6:
      tone(pwmPin,H);
      delay(250);
      noTone(pwmPin);
      break;
    case 7:
      tone(pwmPin,J);
      delay(250);
      noTone(pwmPin);
      break;
    case 8:
      tone(pwmPin,K);
      delay(250);
      noTone(pwmPin);
      break;
    case 9:
      tone(pwmPin,L);
      delay(250);
      noTone(pwmPin);
      break;
  }
}
