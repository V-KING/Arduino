/* 
 *��������źţ�
 *��������ţ�10 - 6
 *��������ţ�1  - 5 
 *
 * ��������źŶ�Ӧ�� led�Σ�
 *7; A-7
 *6; B-6
 *5; C-4
 *10 D-2
 *11 E-1
 *8; F-9
 *9; G-10
 *4; DP-5
 * */
//13�ӵ�һ�������
//12�ӵڶ��������
//���ÿ��Ƹ��ε�����IO ��
int a=7;//�������ֽӿ�7 ����a �������
int b=6;// �������ֽӿ�6 ����b �������
int c=5;// �������ֽӿ�5 ����c �������
int d=10;// �������ֽӿ�10 ����d �������
int e=11;// �������ֽӿ�11 ����e �������
int f=8;// �������ֽӿ�8 ����f �������
int g=9;// �������ֽӿ�9 ����g �������
int dp=4;// �������ֽӿ�4 ����dp �������
int num1=13;
int num2=12;
void digital_0(void) //��ʾ����0
{
  unsigned char j;
  for(j=5;j<=11;j++)
    digitalWrite(j,HIGH);
  digitalWrite(dp,LOW);
  digitalWrite(g,LOW);
}
void digital_1() //��ʾ����1
{
  unsigned char j;
  digitalWrite(c,HIGH);//�����ֽӿ�5 ���Ÿߵ�ƽ������c ��
  digitalWrite(b,HIGH);//����b ��
  for(j=7;j<=11;j++)//Ϩ�������
    digitalWrite(j,LOW);
  digitalWrite(dp,LOW);//Ϩ��С����DP ��
}
void digital_2() //��ʾ����2
{
  unsigned char j;
  digitalWrite(b,HIGH);
  digitalWrite(a,HIGH);
  for(j=9;j<=11;j++)
    digitalWrite(j,HIGH);
  digitalWrite(dp,LOW);
  digitalWrite(c,LOW);
  digitalWrite(f,LOW);
}

void digital_3(void) //��ʾ����3
{
  unsigned char j;
  digitalWrite(g,HIGH);
  digitalWrite(d,HIGH);
  for(j=5;j<=7;j++)
    digitalWrite(j,HIGH);
  digitalWrite(dp,LOW);
  digitalWrite(f,LOW);
  digitalWrite(e,LOW);
}
void digital_4(void) //��ʾ����4
{
  digitalWrite(c,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
  digitalWrite(dp,LOW);
  digitalWrite(a,LOW);
  digitalWrite(e,LOW);
  digitalWrite(d,LOW);
}

void digital_5(void) //��ʾ����5
{
  unsigned char j;
  for(j=7;j<=9;j++)
    digitalWrite(j,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(dp,LOW);
  digitalWrite(b,LOW);
  digitalWrite(e,LOW);
}
void digital_6(void) //��ʾ����6
{
  unsigned char j;
  for(j=7;j<=11;j++)
    digitalWrite(j,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(dp,LOW);
  digitalWrite(b,LOW);
}
void digital_7(void) //��ʾ����7
{
  unsigned char j;
  for(j=5;j<=7;j++)
    digitalWrite(j,HIGH);
  digitalWrite(dp,LOW);
  for(j=8;j<=11;j++)
    digitalWrite(j,LOW);
}

void digital_8(void) //��ʾ����8
{
  unsigned char j;
  for(j=5;j<=11;j++)
    digitalWrite(j,HIGH);
  digitalWrite(dp,LOW);
}
void digital_9(void) //��ʾ����9
{
  unsigned char j;
  for(j=5;j<=11;j++)
    digitalWrite(j,HIGH);
  digitalWrite(dp,LOW);
  digitalWrite(e,LOW);
}
void disp_dp(int x)
{
	digitalWrite(dp,HIGH);
}
void clear()
{
	digitalWrite(a,HIGH);
	digitalWrite(b,HIGH);
	digitalWrite(c,HIGH);
	digitalWrite(d,HIGH);
	digitalWrite(e,HIGH);
	digitalWrite(f,HIGH);
	digitalWrite(g,HIGH);
	digitalWrite(dp,HIGH);
}

void pick_witch(int whitch_gnd_pin)
{
	digitalWrite(whitch_gnd_pin,LOW);
}

void setup()
{
  int i;//�������
  for(i=4;i<=11;i++)
    pinMode(i,OUTPUT);//����4��11 ����Ϊ���ģʽ
}



void loop()
{
  while(1)
  {
	clear();
	pick_witch(13);	
	digital_6();
    delayMicroseconds(55);
	
	clear();
	pick_witch(12);	
	digital_7();
	delayMicroseconds(55);
  }
}

