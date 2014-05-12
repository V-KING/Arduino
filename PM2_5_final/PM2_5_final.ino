/* 
 JST Pin 1   => Arduino GND
 JST Pin 3   => Arduino 5VDC
 JST Pin 4   => Arduino Digital Pin 8
 */

int pin = 8;
unsigned long duration;	
unsigned long starttime;			 
unsigned long sampletime_ms = 30000;//采样时间 30s ；
unsigned long LT = 0;				//采样时间30s内所有低电平时间总和
float ratio = 0;
float concentration = 0;
float particles_per_L=0;

void setup() {
  Serial.begin(9600);
  pinMode(8,INPUT);
  starttime = millis();				//获得当前时间，也就是每个LOW开始的时间点
}

void loop() {
  duration = pulseIn(pin, LOW); 	//一个低电平的时间
  LT = LT+duration;					//所有低电平时间的总和

  if ((millis()-starttime) > sampletime_ms)//if the sampel time == 30s
  {
    ratio = LT/(sampletime_ms*1.0);  //百分比
	
	/*下面是由曲线规律得到的公式，concentration是指1立方英尺的颗粒数
	 *1立方英尺=0.0283立方米=0.0283*1000升
	 */
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; 
	particles_per_L=concentration/28.3;
    Serial.print(LT);
    Serial.print(",");
    Serial.print(ratio);
    Serial.print(",");
    Serial.println(particles_per_L);
    LT = 0;
    starttime = millis();			//下一个LOW的时间点
  }
}
