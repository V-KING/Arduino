
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
int xDistance=0;
int yDistance=0;

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

  //mouse begin
  Mouse.begin();
}  

void loop()  
{  
  if(digitalRead(8)==HIGH){
    Mouse.end();
  }
  else
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

    Serial.print(fXg);
    Serial.print(",  ");
    Serial.println(fYg);
    xDistance=fYg;
    yDistance=fXg;
    
    if (xDistance<-60 ){
      xDistance=-2;
    }else if(xDistance<-20){
      xDistance=-1;
    }else if(xDistance<20 ){
      xDistance=0;
    }else if(xDistance<60){
      xDistance=1;
    }else{
      xDistance=2;
    }
    
    if (yDistance<-60 ){
      yDistance=-2;
    }else if(yDistance<-20){
      yDistance=-1;
    }else if(yDistance<20 ){
      yDistance=0;
    }else if(yDistance<60){
      yDistance=1;
    }else{
      yDistance=2;
    }

    if((xDistance!=0) || (yDistance!=0))
    {
      Mouse.move(xDistance*5,yDistance*5,0);
    }
    delay(15);      //v=(1/20)*xDistance
  }
}  







