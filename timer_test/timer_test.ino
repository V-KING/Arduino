/* 
 * 将定时器中断设为1ms 
 */  
void init_time()  
{  
	TCCR2A |= (1 <<WGM21) | (1 << WGM20);  
	TCCR2B |= (1 << CS22 );  //by clk/64  
	TCCR2B &= ~((1 <<CS21) | (1 <<CS20));  //by clk/64  
	TCCR2B &= ~((1 << WGM21 ) | (1 << WGM20));  
	ASSR |= ( 1 << AS2 );  
	TIMSK2 |= ( 1 << TOIE2 ) | ( 0 << OCIE2B );  
	TCNT2 = 6;  
	sei();  
}  


int count = 0; 
int sum=0;
SIGNAL(TIMER2_OVF_vect)  
{  
	TCNT2 = 6;  
	++count;  
	if( count == 1000 )  
	{  
		Serial.println(sum++);  
		count=0;  
	}  
}  

  
void setup(void)  
{  
	Serial.begin(9600);  
	init_time();  
}  

void loop( void )  
{  
	while( 1 )  
	{  
	}  ;
}  

