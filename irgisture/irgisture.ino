//在1100lux光照的情况下，你的手势控制范围为：1cm-2cm左右
//在1800lux光照的情况下，你的手势控制范围为：1cm-15cm左右 
//建议在光照良好的情况下
int pin2=2;
int pin3=3;
//比较的时间
static long t1=0;
static long t2=0;
void irRecv1(void){
	//对t1进行处理
	t1=millis();
Serial.print("t1= ");
Serial.println(t1);
}
void irRecv2(void){
	//对t2进行处理
	t2=millis();
Serial.print("t2= ");
Serial.println(t2);
}



void setup(){
  Serial.begin(115200);
  pinMode(pin2,INPUT);
  pinMode(pin3,INPUT);
  attachInterrupt(0,  irRecv1 , RISING);
  attachInterrupt(1,  irRecv2 , RISING);
  
}
void loop(){
	if(t1-t2<800&&t1-t2>0){
		Serial.println("-->");
                t1=t2=0;
	}
        else if(t2-t1<800&&t2-t1>0){	
		Serial.println("<--");
                t1=t2=0;
        }
}




