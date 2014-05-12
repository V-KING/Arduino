int Red = 6;                  //
int Green = 5;                //pin definitions
int Blue = 3;                 //
int r = 125;                  //
int g = 125;                  //default all the pins to 125(white)
int b = 125;                  //

void setup()
{
Serial.begin(9600);           // starts and sets the baud rate to 9600
pinMode(Red,OUTPUT);
pinMode(Green,OUTPUT);        // set the pin modes
pinMode(Blue,OUTPUT);
}
void loop()
{
if(Serial.available()==9)      // while there is data
  {
    r= (Serial.read()-48)*100;   // read the first byte
    r=r + (Serial.read()-48)*10; // read the second byte......
    r=r + Serial.read()-48;      // so on so forth
    g= (Serial.read()-48)*100; 
    g=g+ (Serial.read()-48)*10;
    g=g + Serial.read()-48;
    b= (Serial.read()-48)*100 ;
    b=b+ (Serial.read()-48)*10;
    b=b + Serial.read()-48;
    int d = Serial.read();// this is just to clear the end line character
  }
  setColor(r,g,b);
}
void setColor(int red, int green, int blue)
{
  analogWrite(Red, 255-red);
  analogWrite(Green, 255-green);
  analogWrite(Blue, 255-blue);  
}

