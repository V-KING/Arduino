#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

unsigned char words[4][8] = {
	                    { 0x01,0x02,0x06,0x02,0x02,0x02,0x02,0x00},    //你字左边
	                    { 0x08,0x0F,0x15,0x04,0x15,0x15,0x04,0x0C},    //你字右边	                    
                            { 0x00,0x04,0x1F,0x0A,0x04,0x0A,0x00,0x00},    //好字左边
	                    { 0x1E,0x02,0x04,0x1F,0x04,0x04,0x0C,0x00}     //好字右边
	                    };

byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};

void setup() {
  lcd.createChar(0, smiley);
  lcd.createChar(1,words[0]);
  lcd.createChar(2,words[1]);
  lcd.createChar(3,words[2]);
  lcd.createChar(4,words[3]);
  lcd.begin(16, 2); 
  
  lcd.setCursor(0,0);
  lcd.write(byte(0));
  
  lcd.setCursor(1,0);
  lcd.write(byte(1));
  
   lcd.setCursor(2,0);
  lcd.write(byte(2));
  
   lcd.setCursor(3,0);
  lcd.write(byte(3));
  
   lcd.setCursor(4,0);
  lcd.write(byte(4));
  
}

void loop() {}

