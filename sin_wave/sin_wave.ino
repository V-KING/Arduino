int potPin=0;
int ledPin=13;

byte sin_vave_table[]={
 30,  30,  30,  40,  50,  60,  70,  80,  90, 100,110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 250, 240, 230, 220, 210, 200, 190, 180, 170, 160, 150, 140, 130, 120, 110, 100,  90,  80,  70,  60,  50,  40,  30,  30,  30 
};

int MAX=50;
int count=0;
int val=0;

void setup(){
	pinMode(ledPin,OUTPUT);
}
void loop(){
	analogWrite(ledPin,sin_vave_table[count]);
	count++;
	if(count>MAX){
		count=0;
	}
}

