#define SIZE(Buffer) (sizeof(Buffer)/sizeof(Buffer[0]))

byte Buffer[128];
byte buf;
int x,y;

void serial_send()
{
  Serial.write(buf);
}

//采样
void sample()
{ 
  for(x = 0;x < 128;x++)
   // Buffer[x] = map(analogRead(A0),0,1023,0,127);  //信号采样
    buf=map(analogRead(A0),0,1023,0,256);
//  for(x = 0;x < 128;x++)
//    Buffer[x] = 63-(Buffer[x]>>4); //计算纵坐标值
}

void setup(){ 
  Serial.begin(9600);
  pinMode(A0,INPUT);
}
void loop(){
  sample();
  serial_send();
}




