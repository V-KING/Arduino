#define DHTPIN11 A0




void setup()
{
	Serial.begin(9600);
	Serial.println("DHT11 begin");
	
	
}

void loop()
{
  long hum_10=0, hum_01=0, temp_10=0, temp_01=0, chksum=0,chk=0;
  
  	delay(1000);	//上电等1s
	//设置为输入，并上拉为高电平
	pinMode(DHTPIN11, INPUT);
	digitalWrite(DHTPIN11,HIGH);
  
	pinMode(DHTPIN11,OUTPUT);
	digitalWrite(DHTPIN11,LOW);
	delay(18);
        digitalWrite(DHTPIN11,HIGH);
        delayMicroseconds(40);
	
	//将数据线设置为输入模式，释放了总线	
	//现在Arduino接收DHT11的80us低电平回应
	//什么时候结束?因该是Arduino收到一个下降沿时
	pinMode(DHTPIN11,INPUT);
	while(LOW==digitalRead(DHTPIN11));
	
	//DHT11 告诉Arduino我要拉高准备
	//Arduino怎么知道DHT已经准备好了呢?
	while(HIGH==digitalRead(DHTPIN11));

	//现在开始读了
	for(int i=0; i<40; i++)
	{
		if(i < 8)				     //one byte
		{
	 	 	hum_10 <<= 1;
			while(digitalRead(DHTPIN11) == LOW);
			unsigned long t = micros();
			while(digitalRead(DHTPIN11)== HIGH);
	 	 	if((micros()-t) > 40){
	   	 		hum_10 |= 0x01;
	 	 	}	
		}
		else if(i < 16)				 // two byte
		{
	 	 	hum_01 <<= 1;
	  		while(digitalRead(DHTPIN11) == LOW);
			unsigned long t = micros();
			while(digitalRead(DHTPIN11)== HIGH);
	 	 	if((micros()-t) > 40){
	   	 		hum_10 |= 0x01;
	 	 	}	
		}
		else if(i < 24)				// three byte
		{
	 	 	temp_10 <<= 1;
	 	 	while(digitalRead(DHTPIN11) == LOW);
			unsigned long t = micros();
			while(digitalRead(DHTPIN11)== HIGH);
	 	 	if((micros()-t) > 40){
	   	 		temp_10 |= 0x01;
	 	 	}	
		}
		else if(i < 32)			  // four byte
		{
	  		temp_01 <<= 1;
	  		while(digitalRead(DHTPIN11) == LOW);
			unsigned long t = micros();
			while(digitalRead(DHTPIN11)== HIGH);
	 	 	if((micros()-t) > 40){
	   	 		temp_01 |= 0x01;
	 	 	}	
		
		}
		else					  // five byte  checksum
		{
	 	 	chksum <<= 1;
	 	 	while(digitalRead(DHTPIN11) == LOW);
			unsigned long t = micros();
			while(digitalRead(DHTPIN11)== HIGH);
	 	 	if((micros()-t) > 40){
	   	 		chksum |= 0x01;
	 	 	}	
		}
	}
	chk = hum_10;					// Calculate to Checksum
  	chk += hum_01;
  	chk += temp_10;
  	chk += temp_01;

  	if(chk != chksum){				// Received data is OK
		Serial.println("chksum is not right");
    	return ;
	}
  	else{
		Serial.println("chksum is right,data recv succese");
  	}
	
	Serial.print("Hum:"); //串口调试
        Serial.print(hum_10);
        Serial.print(".");
        Serial.println(hum_01);
    
        Serial.print("Temp:"); //串口调试
        Serial.print(temp_10);
        Serial.print(".");
        Serial.println(temp_01);
	
        delay(2000);

}


