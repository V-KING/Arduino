void setup()
{
  Serial.begin(9600);
}
/*  
void loop(){
  Serial.print(millis());
  Serial.print(",");
  Serial.print(map(analogRead(0),0,1023,0,200));
  Serial.print(",");
  Serial.print(2);
  Serial.println(",");
}
*/
void loop(){	
	byte a=map(analogRead(0),0,1023,0,200);//200以上的是其他的格式
	//发送的是byte类型数据，0-255，当然可以0-200
	//Serial.write(0xFF);
	//Serial.write(a);
	//发送字符串
	//byte buf[4]={201,'h','i','\n'};
	//Serial.write(buf,4);
	Serial.write(201);
	Serial.print("hello world");
	Serial.write('\n');
	//Serial.print("kv");
	Serial.write(44);
	Serial.write(33);
}
