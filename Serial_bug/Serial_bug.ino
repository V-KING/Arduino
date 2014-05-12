
#include <avr/io.h>      // this contains all the IO port definitions
#include <avr/interrupt.h>
#include <avr/signal.h>

#define TIMER1_PRESCALE_1 1
#define TIMER1_PRESCALE_8 2
#define TIMER1_PRESCALE_64 3
#define TIMER1_PRESCALE_256 4
#define TIMER1_PRESCALE_1024 5

/* turn a numeric literal into a hex constant
   (avoids problems with leading zeroes)
   8-bit constants max value 0x11111111, always fits in unsigned long
*/
#define HEX__(n) 0x##n##LU

/* 8-bit conversion function */
#define B8__(x) ((x&0x0000000FLU)?1:0)  \
               +((x&0x000000F0LU)?2:0)  \
               +((x&0x00000F00LU)?4:0)  \
               +((x&0x0000F000LU)?8:0)  \
               +((x&0x000F0000LU)?16:0) \
               +((x&0x00F00000LU)?32:0) \
               +((x&0x0F000000LU)?64:0) \
               +((x&0xF0000000LU)?128:0)


#define B8(d) ((unsigned char)B8__(HEX__(d)))

const static int image[] = {
  B8(11111111),
  B8(11111111),
  B8(00001110),
  B8(00111100),
  B8(11110000),
  B8(11110000),
  B8(00111100),
  B8(00001110),
  B8(11111111),
  B8(11111111),
  B8(00000000),
  B8(01100000),
  B8(11110100),
  B8(10010100),
  B8(10010100),
  B8(11111100),
  B8(11111000),
  B8(10000000),
  B8(00000000),
  B8(11111111),
  B8(11111111),
  B8(00110000),
  B8(01111000),
  B8(11111100),
  B8(11001100),
  B8(10000000),
  B8(00000000),
  B8(01111000),
  B8(11111100),
  B8(11010100),
  B8(11010100),
  B8(11011100),
  B8(01011000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00001110),
  B8(11011111),
  B8(11011111),
  B8(00001110),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
};

#define NUM_ELEM(x) (sizeof (x) / sizeof (*(x)))
int imagesize = NUM_ELEM(image);




// this function is called when timer1 compare matches OCR1A
uint8_t j = 0;
SIGNAL( SIG_TIMER1_COMPA ) {
  if (j >= imagesize) 
    j = 0;

  PORTD= image[j];
 
  j++;
}

void setup()
{
  for(int i=2; i<=9; i++)	
  {
    pinMode(i,OUTPUT);
  }
}
void loop()
{
  DDRD= 0xFF; 
  TCCR1B = (1 << WGM12) | TIMER1_PRESCALE_1;
  OCR1A = (uint16_t)10000;
  TIMSK1|= 1 << OCIE1A; // Output Compare Interrupt Enable (timer 1, OCR1A) 
  sei(); // Set Enable Interrupts
  while(1);
}


