//#include "letters.h"
#ifndef _LETTER_H_
#define _LETTER_H_

byte A[] = {
  B00011000,
  B00111100,
  B01100110,
  B01100110,
  B01111110,
  B01100110,
  B01100110,
  B01100110,
};

byte B[] = {

};

byte C[] = {

};

byte D[] = {

};

byte E[] = {
  B01111111,
  B01100000,
  B01100000,
  B01111110,
  B01111110,
  B01100000,
  B01100000,
  B01111111,
};

byte F[] = {

};

byte G[] = {
  B01111111,
  B01100000,
  B01100000,
  B01100000,
  B01101111,
  B01101111,
  B01100011,
  B01111111,  
};

byte H[] = {
  B01100010,
  B01100010,
  B01100010,
  B01111110,
  B01111110,
  B01100010,
  B01100010,
  B01100010,
};

byte I[] = {
  B01111111,
  B01111111,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B01111111,
  B01111111,
};

byte J[] = {

};

byte K[] = {

};

byte L[] = {
  B01100000,
  B01100000,
  B01100000,
  B01100000,
  B01100000,
  B01100000,
  B01111111,
  B01111111,
};

byte M[] = {

};

byte N[] = {
  B01100011,
  B01100011,
  B00110011,
  B01111011,
  B01111011,
  B01101111,
  B01100111,
  B01100011,
};

byte O[] = {
  B01111111,
  B01111111,
  B01100011,
  B01100011,
  B01100011,
  B01100011,
  B01111111,
  B01111111
};

byte P[] = {

};

byte Q[] = {

};

byte R[] = {
  B01111111,
  B01100011,
  B01100011,
  B01111110,
  B01111110,
  B01100011,
  B01100011,
  B01100011,
};

byte S[] = {
  B00111110,
  B01100000,
  B00110000,
  B00011000,
  B00001100,
  B00000110,
  B00000011,
  B00111110,
};

byte T[] = {
  B01111111,
  B01111111,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
};

byte U[] = {

};

byte V[] = {

};

byte W[] = {

};

byte X[] = {

};

byte Y[] = {
  B00110011,
  B00110011,
  B00110011,
  B00011110,
  B00011110,
  B00001100,
  B00001100,
  B00001100,
};

byte Z[] = {

};

byte EXCLAMATION[] = {
  B00111000, // 1
  B00111000, // 2
  B00111000, // 3
  B00111000, // 4
  B00111000, // 5
  B00000000, // 6
  B00000000, // 7
  B00111000, // 8
};

byte SPACE[] = {
  B00000000, // 1
  B00000000, // 2
  B00000000, // 3
  B00000000, // 4
  B00000000, // 5
  B00000000, // 6
  B00000000, // 7
  B00000000, // 8
};
#endif

int LEDpins[]={
  2,3,4,5,6,7,8,9};
int number_cols=8;
int invert =0;
int number_rows=8;
int delay_col=1;


void setup() {
  int r;

  for (r = 0; r < number_rows; r++) {
    pinMode(LEDpins[ r ], OUTPUT);
    digitalWrite(LEDpins[ r ], OUTPUT);
  }

}

void loop() {
  //  show(S, 0); 
  //  show(O, 0);
  //  show(S, 0);
  show(H, 1); 
  show(S, 1);
  show(O, 1);
  show(R, 1);
 show(N, 1);
  delay(10);
}

void show(byte letter[], int invert) {
  int c, r, real_col;

  for (c = 0; c < number_cols; c++) {

    real_col = invert ? (number_cols - 1) - c : c;

    for (r = 0; r < number_rows; r++) {
      digitalWrite(LEDpins[ r ], !bitRead(letter[ r ], real_col));
    }
    delay(10);
  }

}


