//���������ӿ�
int a = 1;
int b = 2;
int c = 3;
int d = 4;
int e = 5;
int f = 6;
int g = 7;
int p = 8;
//���������ӿ�
int d4 = 9;
int d3 = 10;
int d2 = 11;
int d1 = 12;
//���ñ���
long n = 0;
int x = 100;
int del = 55;  //�˴���ֵ��ʱ�ӽ���΢��
 
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
 
void pickDigit(int x)  //����pickDigit(x),�������ǿ���dx�˿�
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
 
void pickNumber(int x)   //����pickNumber(x),����������ʾ����x
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
 
void dispDec(int x)  //�趨����С����
{
  digitalWrite(p,HIGH);
}
 
void clearLEDs()  //����
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
 
void zero()  //��������0ʱ������Щ�ܽſ���
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void one()  //��������1ʱ������Щ�ܽſ���
{
  digitalWrite(a, HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void two()  //��������2ʱ������Щ�ܽſ���
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void three()  //��������3ʱ������Щ�ܽſ���
{
  digitalWrite(a, HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g,HIGH);
}
 
void four()  //��������4ʱ������Щ�ܽſ���
{
  digitalWrite(a, HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g,HIGH);
}
 
void five()  //��������5ʱ������Щ�ܽſ���
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g,HIGH);
}
 
void six()  //��������6ʱ������Щ�ܽſ���
{
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
 
void seven()  //��������7ʱ������Щ�ܽſ���
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g,HIGH);
}
 
void eight()  //��������8ʱ������Щ�ܽſ���
{
  digitalWrite(a,HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g, HIGH);
}
 
void nine()  //��������9ʱ������Щ�ܽſ���
{
  digitalWrite(a, HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

