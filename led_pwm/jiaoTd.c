int dx_red=3;
int dx_green=4;
int dx_yellow=5;


int nb_red=6;
int nb_green=7;
int nb_yellow=8;

void setup(){
	Serial.begin(9600);
}
void loop(){
	for(int i=0; i<6; i++){
		digitalWrite(i, LOW);
	}
	//东西红3s,南北绿3s
	digitalWrite(dx_red, HIGH);
	digitalWrite(nb_green, HIGH);
	delay(3000);
	//东西红2s,南北绿灯闪2s
	digitalWrite(dx_red, HIGH);
	flash_2s(nb_green);
	close_led(nb_green);
	//东西红闪2s，南北黄2s
	digitalWrite(nb_yellow,HIGH);
	flash_2s(dx_red);
	//东西红闪1s，南北黄闪1s
	dxRed_and_nbYellow_flash();
	close_led(nb_yellow);

	//东西绿2s，南北红3s
	digitalWrite(dx_green, HIGH);
	digitalWrite(nb_red, HIGH);
	delay(3000);
	//东西绿闪2s，南北红2s
	digitalWrite(nb_red, HIGH);
	flash_2s(dx_green);
	close_led(dx_green);
	//东西黄2s，南北红闪2s
	digitalWrite(dx_yellow, HIGH);	
	flash_2s(nb_red);		
	//东西黄闪1s，南北红闪1s
	flash_dx_nb_1s(dx_yellow,nb_red);
	close_led(nb_red);
}

//led灯闪烁2s
void flash_2s(int led );
{
	//20次循环*100= 2000
	for(int i=0; i<20; i++){
		digitalWrite(green, LOW);
		delay(100);
		digitalWrite(green, HIGH);
	}

}

//闪烁东西1个灯和南北1个灯1s
void flash_dx_nb_1s(int dx_led,int nb_led)
{
	for(int i=0; i<10; i++){
		digitalWrite(dx_led,LOW);	
		digitalWrite(nb_led,LOW);	
		delay(100);
		digitalWrite(dx_led,HIGH);	
		digitalWrite(nb_led,HIGH);	
	}
}
