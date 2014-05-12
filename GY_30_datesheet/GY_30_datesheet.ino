#include <Wire.h> //IIC

#include <math.h> 

int address = 0x23; 

byte buff[2];

void setup()

{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  int i=0;
  uint16_t val=0;
  Wire.beginTransmission(address);
  //Wire.write(0x01);//1lx reolution 120ms
  Wire.write(0x10);
  Wire.endTransmission();
  delay(180);

  //Wire.beginTransmission(address);
  Wire.requestFrom(address,2);
  while(Wire.available())
  {
    if(2==i){
      i=0;
    }
    else
      buff[i++]=Wire.read();
  }

  //Wire.endTransmission(); 

  val=(buff[0]<<8|buff[1])/1.2;
  Serial.print(val,DEC);     
  Serial.println("[lx]"); 
  delay(150);

}





