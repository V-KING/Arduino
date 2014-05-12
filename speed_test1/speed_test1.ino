/*材料:st188*1,200欧姆电阻*1,20k欧姆电阻*1 
 *连线:对照st188手册中进行连线，电阻R1=200欧姆
 *速度=里程/时间：v=s/t；c=2*r*PI；s=count*c；=> v=(count*2*r*PI)/t
 *我们要实时的查看速度，所以1s计算一次速度，然后清零
 *假设：轮子的周长=1m；1s·
 * */
#define R 		1     		//定义车轮的半径
#define PI		3.14 		//定义圆周率
int pin2=2;
int count=0;
int count_state=1;
int count_last_state=0;

float time_total=0;
float time_5sec=0;
int time_5sec_last=0;
float v=0;

void Interrupter_count(){
	count++;
}

void setup(){
	Serial.begin(9600);
	pinMode(A0,INPUT); 
	
}


int c=1; //c=2*R*PI
void loop(){
	if(millis()-time_5sec>=1000){	//每1s我们清零一次and计算一次速度
		v= (count*c); 			//1s走多长的距离，轮子周长=1m
	Serial.print("v= ");
	Serial.println(v);
		count=0;
		time_5sec=millis();
	}
	//Serial.print("count= ");
	//Serial.println(count);

	int a=analogRead(A0);
	if(a>900){
		count_state=1;
	}
	else{
		count_state=0;
	}

	if(count_state==1 && count_last_state==0 ){
		count++;
		//Serial.print("count= ");
		//Serial.println(count);
		count_last_state=count_state;
	}
	else{
		count_last_state=count_state;
	}
}

