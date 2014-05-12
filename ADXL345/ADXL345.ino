
#include <Wire.h>  

#define Register_ID 0  
#define Register_2D 0x2D  
#define Register_X0 0x32  
#define Register_X1 0x33  
#define Register_Y0 0x34  
#define Register_Y1 0x35  
#define Register_Z0 0x36  
#define Register_Z1 0x37  

int ADXAddress = 0xA7 >> 1;  // the default 7-bit slave address  
int reading = 0;  
int val=0;  
int X0,X1,X_out;  
int Y0,Y1,Y_out;  
int Z1,Z0,Z_out;  
double Xg,Yg,Zg;  
double pitch,roll;

void setup()  
{  
  Wire.begin();                  
  Serial.begin(9600);      
  delay(100);  
  // enable to measute g data  
  Wire.beginTransmission(ADXAddress);  
  Wire.write(Register_2D);  
  Wire.write(8);                //measuring enable  
  Wire.endTransmission();     // stop transmitting  

}  

void loop()  
{  
  //--------------X  
  Wire.beginTransmission(ADXAddress); // transmit to device  
  Wire.write(Register_X0);  
  Wire.write(Register_X1);  
  Wire.endTransmission();  
  Wire.requestFrom(ADXAddress,2);   
  if(Wire.available()<=2)     
  {  
    X0 = Wire.read();  
    X1 = Wire.read();   
    X1=X1<<8;  
    X_out=X0+X1;     
  }  

  //------------------Y  
  Wire.beginTransmission(ADXAddress); // transmit to device  
  Wire.write(Register_Y0);  
  Wire.write(Register_Y1);  
  Wire.endTransmission();  
  Wire.requestFrom(ADXAddress,2);   
  if(Wire.available()<=2)     
  {  
    Y0 = Wire.read();  
    Y1 = Wire.read();   
    Y1=Y1<<8;  
    Y_out=Y0+Y1;  
  }  
  //------------------Z  
  Wire.beginTransmission(ADXAddress); // transmit to device  
  Wire.write(Register_Z0);  
  Wire.write(Register_Z1);  
  Wire.endTransmission();  
  Wire.requestFrom(ADXAddress,2);   
  if(Wire.available()<=2)     
  {  
    Z0 = Wire.read();  
    Z1 = Wire.read();   
    Z1=Z1<<8;  
    Z_out=Z0+Z1;  
  }  
  /*  
   //display the real value  
   Xg=X_out/256.0;  
   Yg=Y_out/256.0;  
   Zg=Z_out/256.0;  
   */
  //display the reading value  
  Xg=X_out;  
  Yg=Y_out;  
  Zg=Z_out;  


  const  float alpha=0.5;
  int fXg,fYg,fZg;
  fXg=fYg=fZg=0;
  fXg = Xg * alpha + (fXg * (1.0 - alpha));
  fYg = Yg * alpha + (fYg * (1.0 - alpha));
  fZg = Zg * alpha + (fZg * (1.0 - alpha));

  //Roll & Pitch Equations
  roll  = (atan2(-fYg, fZg)*180.0)/M_PI;
 // roll  = (atan2(-fZg, sqrt(fYg*fYg + fXg*fXg))*180.0)/M_PI;
  //roll = (atan2(sqrt(fXg*fXg), fZg)*180.0)/M_PI;
  pitch = (atan2(fXg, sqrt(fYg*fYg + fZg*fZg))*180.0)/M_PI;
  
  Serial.print(pitch);
  Serial.print(":");
  Serial.println(roll);
  /*
  Serial.print("X= ");  
   Serial.print(Xg);  
   Serial.print("       ");  
   Serial.print("Y= ");  
   Serial.print(Yg);  
   Serial.print("       ");  
   Serial.print("Z= ");  
   Serial.println(Zg);  
   Serial.println("  ");  
   delay(100);  
   */
   delay(100);
}  



