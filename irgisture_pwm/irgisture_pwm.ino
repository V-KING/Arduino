#include <PWM.h>
#define DEBUG 1
//pin9发出40khz的pwm
//pin2，pin3是中断触发引脚
int PWM_PIN=9;
int pin2=2;
int pin3=3;

static long t1=0;
static long t2=0;
//外部中断函数
void Irrecv1(void)
{
	t1=millis();
}
//外部中断函数
void Irrecv2(void)
{
	t2=millis();	
}

void setup()
{

	Serial.begin(9600);
	//初始化定时器
	InitTimersSafe();	
#if DEBUG
	Serial.println("inited timer.");
#endif

	bool success=SetPinFrequencySafe(PWM_PIN,40000); //设置引脚的频率，设置成功返回ture
	pwmWrite(PWM_PIN, 128);
#if DEBUG
	if(success)
	{
		Serial.println("set pin's Frequency safe mode success.");
	}
	else
	{
		Serial.println("fail to set pin's Frequency. ");	
		return;
	}
#endif
	//两个中断源的引脚设置为输入
	pinMode(pin2,INPUT);
	pinMode(pin3,INPUT);

#if DEBUG
	Serial.println("set pin2 and pin3 INPUT");	
#endif
	//安装中断
	attachInterrupt(0, Irrecv1, FALLING);
	attachInterrupt(1, Irrecv2, FALLING);

#if DEBUG
	Serial.println("set interrupt functions Irrecv1 Irrecv2");	
#endif

}

void loop()
{
	//根据情况，满足往右挥的条件
	if(t1-t2>0 && t1-t2<100)	
	{
		Serial.println("-->");
		t1=t2=millis();
	}
	//满足往左挥的条件
	else if(t2-t1>0 && t2-t1<100)	
	{
		Serial.println("<--");
		t1=t2=millis();
	}
}
