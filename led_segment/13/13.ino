//设置阴极接口
int a = 1;
int b = 2;
int c = 3;
int d = 4;
int e = 5;
int f = 6;
int g = 7;
int p = 8;
//设置阳极接口
int d4 = 9;
int d3 = 10;
int d2 = 11;
int d1 = 12;
//设置变量
long n = 0;
int x = 100;
int del = 55;  //此处数值对时钟进行微调
 
void setup()
{
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(p, OUTPUT);
}
 
void loop()
{
  clearLEDs();
  pickDigit(1);
  pickNumber((n/x/1000)%10);
  delayMicroseconds(del);
 
  clearLEDs();
  pickDigit(2);
  pickNumber((n/x/100)%10);
  delayMicroseconds(del);
 
  clearLEDs();
  pickDigit(3);
  dispDec(3);
  pickNumber((n/x/10)%10);
  delayMicroseconds(del);
 
  clearLEDs();
  pickDigit(4);
  pickNumber(n/x%10);
  delayMicroseconds(del);
 
  n++;
 
  if (digitalRead(13) == HIGH)
  {
    n = 0;
  }
}
 
void pickDigit(int x)  //定义pickDigit(x),其作用是开启dx端口
{
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
 
  switch(x)
  {
  case 1: 
    digitalWrite(d1, HIGH); 
    break;
  case 2: 
    digitalWrite(d2, HIGH); 
    break;
  case 3: 
    digitalWrite(d3, HIGH); 
    break;
  default: 
    digitalWrite(d4, HIGH); 
    break;
  }
}
 
void pickNumber(int x)   //定义pickNumber(x),其作用是显示数字x
{
  switch(x)
  {
  default: 
    zero(); 
    break;
  case 1: 
    one(); 
    break;
  case 2: 
    two(); 
    break;
  case 3: 
    three(); 
    break;
  case 4: 
    four(); 
    break;
  case 5: 
    five(); 
    break;
  case 6: 
    six(); 
    break;
  case 7: 
    seven(); 
    break;
  case 8: 
    eight(); 
    break;
  case 9: 
    nine(); 
    break;
  }
}
 
void dispDec(int x)  //设定开启小数点
{
  digitalWrite(p,HIGH);
}
 
void clearLEDs()  //清屏
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(p,HIGH);
}
 
void zero()  //定义数字0时阴极那些管脚开关
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void one()  //定义数字1时阴极那些管脚开关
{
  digitalWrite(a, HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void two()  //定义数字2时阴极那些管脚开关
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void three()  //定义数字3时阴极那些管脚开关
{
  digitalWrite(a, HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g,HIGH);
}
 
void four()  //定义数字4时阴极那些管脚开关
{
  digitalWrite(a, HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g,HIGH);
}
 
void five()  //定义数字5时阴极那些管脚开关
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g,HIGH);
}
 
void six()  //定义数字6时阴极那些管脚开关
{
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void seven()  //定义数字7时阴极那些管脚开关
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g,HIGH);
}
 
void eight()  //定义数字8时阴极那些管脚开关
{
  digitalWrite(a,HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g, HIGH);
}
 
void nine()  //定义数字9时阴极那些管脚开关
{
  digitalWrite(a, HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

