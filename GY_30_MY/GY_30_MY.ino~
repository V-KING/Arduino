#include "Wire.h" 
#include "math.h"

int BH1750_Device = 0x23; 	// I2C address for light sensor
unsigned int Lux;

void Configure_BH1750() 
{
  Wire.beginTransmission(BH1750_Device);
//  Wire.write(0x10);			// Set resolution to 1 Lux,Continuously H-Resolution Mode
  Wire.write(0x13);			//连续低精度模式，因为采样时间短，只要16ms
  Wire.endTransmission();
}

unsigned int BH1750_Read()	//
{
  unsigned int i=0;
  Wire.beginTransmission(BH1750_Device);
  Wire.requestFrom(BH1750_Device, 2);
  while(Wire.available())	//
  {
    i <<=8;
    i|= Wire.read();  
  }
  Wire.endTransmission();  
  return i/1.2;				// Convert to Lux
}

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  Configure_BH1750();

  delay(300);
}

void loop()
{
  int i;
  Lux = BH1750_Read();
  Serial.print(Lux,DEC);     
  Serial.println("[lx]"); 
  delay(16);
}

