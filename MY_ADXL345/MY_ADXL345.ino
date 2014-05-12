static int SDA__ =4;
static int SCL__= 5;
//#define Register_ID 0  
#define Register_2D 0x2D  
#define Register_X0 0x32  
#define Register_X1 0x33  
#define Register_Y0 0x34  
#define Register_Y1 0x35  
#define Register_Z0 0x36  
#define Register_Z1 0x37
static int ACK= 0;
static int NACK =1;
#define SLAVEADDRSS 0xA6
unsigned char x0,x1,y0,y1,z0,z1;

unsigned char buf[6]={0};
unsigned char dev_id;
unsigned char x,y,z;  


void IIC_start(){
  pinMode(SDA__,OUTPUT);
  pinMode(SCL__,OUTPUT); //SCL__一直都是OUTPUT
  digitalWrite(SCL__,HIGH);
  digitalWrite(SDA__,HIGH);
  delayMicroseconds(5);
  digitalWrite(SDA__,LOW);
  delayMicroseconds(5);
  digitalWrite(SCL__,LOW);
}
void IIC_stop(){
  pinMode(SDA__,OUTPUT);
  digitalWrite(SDA__,LOW);
  digitalWrite(SCL__,HIGH);
  delayMicroseconds(5);
  digitalWrite(SDA__,HIGH);
  delayMicroseconds(5);
}

void IIC_slaveACK() //SCL__在高电平期间，SDA__被从设备拉为低电平表示应答  
{
  int i;
  pinMode(SDA__,INPUT);
  digitalWrite(SCL__,HIGH);
  delayMicroseconds(5);
  i=digitalRead(SDA__);
  digitalWrite(SCL__,LOW);
  delayMicroseconds(5);
}
void IIC_masterACK(int ack)
{
  pinMode(SDA__,OUTPUT);
  digitalWrite(SDA__,ack);
  digitalWrite(SCL__,HIGH);
  delayMicroseconds(5);
  digitalWrite(SCL__,LOW);
  delayMicroseconds(5);
}

void IIC_sendByte(byte data)
{
	unsigned char i,j;
	pinMode(SDA__,OUTPUT);
	for(i=0;i<8;i++)
	{
		digitalWrite(SDA__,(data &  1<<(8-i)) >> (8-i));
                digitalWrite(SCL__,HIGH);
		delayMicroseconds(5);
		digitalWrite(SCL__,LOW);		
		delayMicroseconds(5);
	}
}
unsigned char IIC_recvByte()
{
	unsigned char i,j;
	unsigned char data=0;
	pinMode(SDA__,INPUT);
	for(i=0;i<8;i++)
	{
		data<<=1;
		digitalWrite(SCL__,HIGH);
		data|=digitalRead(SDA__);
                digitalWrite(SCL__,LOW);
		delayMicroseconds(5);
	}
	return data;
}

void single_Write_ADXL345(unsigned char REG_addr,unsigned char REG_data){
	IIC_start();	
	IIC_sendByte(SLAVEADDRSS);
	IIC_slaveACK();
	IIC_sendByte(REG_addr);
	IIC_slaveACK();
	IIC_sendByte(REG_data);
	IIC_slaveACK();	
	IIC_stop();
}

void multiple_byte_write_ADXL345(unsigned char REG_addr,unsigned char REG_data1,unsigned char REG_data2)
{
	IIC_start();
	IIC_sendByte(SLAVEADDRSS);
	IIC_slaveACK();
	IIC_sendByte(REG_addr);
	IIC_slaveACK();
	IIC_sendByte(REG_data1);
	IIC_slaveACK();
	IIC_sendByte(REG_data2);
	IIC_slaveACK();
	IIC_stop();
}
unsigned char single_read_ADXL345(unsigned char REG_addr)
{
	unsigned char data=0;
	IIC_start();		
	IIC_sendByte(SLAVEADDRSS);
	IIC_slaveACK();
	IIC_sendByte(REG_addr);	
	IIC_slaveACK();
	IIC_start();
	IIC_sendByte(SLAVEADDRSS|1);
	IIC_slaveACK();
	data=IIC_recvByte();
	IIC_masterACK(NACK);
	IIC_stop();
	return data;
}
void multiple_byte_read_ADXL345(unsigned char buf[],char num,unsigned char REG_addr)
{
	int i;
	IIC_start();
	IIC_sendByte(SLAVEADDRSS);
	IIC_slaveACK();
	IIC_sendByte(REG_addr);
	IIC_slaveACK();
	IIC_start();
	IIC_sendByte(SLAVEADDRSS|1);
	IIC_slaveACK();
	for(i=0;i<num-1;i++)	//前面的是回复ACK
	{
		buf[i]=IIC_recvByte();
		IIC_masterACK(ACK);
	}
	buf[i]=IIC_recvByte();	//最后回复的是NACK
	IIC_masterACK(NACK);
		
	IIC_stop();
	delayMicroseconds(5);
}
void Init_ADXL345()
{
   single_Write_ADXL345(0x31,0x0B);   //测量范围,正负16g，13位模式
   single_Write_ADXL345(0x2C,0x08);   //速率设定为12.5 参考pdf13页
   single_Write_ADXL345(0x2D,0x08);   //选择电源模式   参考pdf24页
   single_Write_ADXL345(0x2E,0x80);   //使能 DATA_READY 中断
   single_Write_ADXL345(0x1E,0x00);   //X 偏移量 根据测试传感器的状态写入pdf29页
   single_Write_ADXL345(0x1F,0x00);   //Y 偏移量 根据测试传感器的状态写入pdf29页
   single_Write_ADXL345(0x20,0x05);   //Z 偏移量 根据测试传感器的状态写入pdf29页
}

void setup()
{
  Serial.begin(9600);
  Init_ADXL345();
  delay(100);
}
void loop()
{
  x0=single_read_ADXL345(Register_X0);
  x1=single_read_ADXL345(Register_X1);
  x=x0+(x1<<8);
  y0=single_read_ADXL345(Register_Y0);
  y1=single_read_ADXL345(Register_Y1);
  y=y0+(y1<<8);
  z0=single_read_ADXL345(Register_Z0);
  z1=single_read_ADXL345(Register_Z1);
  z=z0+(z1<<8);
  Serial.print("x=");Serial.print(x);
  Serial.print("  y=");Serial.print(y);
  Serial.print("  z=");Serial.print(z);
  Serial.println();
}


