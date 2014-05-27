
//GREE: 8A20050A
#include <IRremote.h>
//定义按键
#define ON_OFF 		0xFFA25D
#define MODE		0xFF629D
#define MUTE 	    0xFFE21D
#define PLAY_PAUSE 	0xFF22DD
#define PREVIOUS 	0xFF02FD
#define NEXT 		0xFFC23D
#define EQ 			0xFFE01F
#define SUB 		0xFFA857
#define ADD 		0xFF906F
#define ZERO 		0xFF6897
#define RETURN 		0xFF9867
#define U_SD		0xFFB04F
#define ONE			0xFF30CF
#define TWO			0xFF18E7
#define THREE		0xFF7A85
#define FOUR		0xFF10EF
#define FIVE		0xFF38C7
#define SIX			0xFF5AA5
#define SEVEN		0xFF42BD
#define EIGHT		0xFF4AB5
#define NINE		0xFF52AD
#define REPEAT		0xffffffff


int RECV_PIN = 9;
IRrecv irrecv(RECV_PIN);
decode_results results;
int flag2,flag3,flag4,flag5,flag6;


unsigned long byte1;
unsigned long byte2;
unsigned long byte3;
unsigned long byte4;

int revert(int byte1){
    long value=0;
    for(int i=0; i<8; i++){
        value <<= 1;
        if( (byte1 >> i) & 0x01 ){
            value=value | 0x01; 

        }
        Serial.print((byte1 >> i) & 0x01);
    }
    Serial.print(" ");
    return value;
}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  for(int i=2; i<=6; i++){
	  pinMode(i,OUTPUT);
	}
}
int i=1;
void loop() {
if (irrecv.decode(&results)) {
    /*if(results.decode_type == NEC)*/{
        byte1 = (results.value>>0)  & 0xff;
    
        byte2 = (results.value>>8)  & 0xff;
    
        byte3 = (results.value>>16) & 0xff;
    
        byte4 = (results.value>>24) & 0xff;

   
    
        byte4 = revert(byte4);byte3 = revert(byte3);byte2 = revert(byte2);byte1 = revert(byte1);
        Serial.println();
        results.value=(byte4 << 24)|(byte3<<16)|(byte2<<8)|(byte1);
    }

    switch (results.value){
    	case ONE:
    		flag2=!flag2;
    		digitalWrite(2,flag2);
    		break;
    	case TWO:
    	    flag3=!flag3;
    		digitalWrite(3,flag3);
    		break;
    	case THREE:
    	    flag4=!flag4;
    		digitalWrite(4,flag4);
    		break;
    	case FOUR:
    	    flag5=!flag5;
    		digitalWrite(5,flag5);
    		break;
    	case FIVE:
    	    flag6=!flag6;
    		digitalWrite(6,flag6);
    		break;
        case OFF:
            for(int i=2; i<=6; i++){
                digitalWrite(i,LOW);
            }
    	default:
    		break;
    }
    
    irrecv.resume(); // Receive the next value
  }
}

