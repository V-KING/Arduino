/*《音乐随你而动》
 *超声波接线：
 *Trig -> Echo -> pin5
 *Vcc -> 5V
 *Gnd -> GND
 *喇叭接线：
 *pin9 -> 喇叭+极 
 *喇叭负极 -> 200欧姆电阻 -> GND
 *
 * */

/*
 *出发信号（由arduino发出）和输出回响信号（由超声波模块自己发出）
 *都是同一个脚pin5,因为看时序可知道，他们不是同一时刻的信号
 */
int ulPin=5;  
int pwmPin=9;
int sensorHigh=0;
int duration=0;
int RangeInCentimeters=0;  //定义距离
int sensorLow=0;

void setup() { 
  Serial.begin(9600);   
  pinMode(ulPin, OUTPUT);

  digitalWrite(pwmPin,HIGH);

  pinMode(pwmPin,OUTPUT);	

} 

void loop() { 
  //下面是为了发一个10us的出发信号
  pinMode(ulPin, OUTPUT);
  digitalWrite(ulPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ulPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ulPin,LOW);
  //然后，就是arduino接收超声波模块的输出回响信号
  pinMode(ulPin, INPUT); 			        //设置成输入模式
  duration = pulseIn(ulPin,HIGH);			//根据超声波时序图可知，我们只要知道高电平的时间
  RangeInCentimeters = duration/29/2;	        //微秒的单位除以58等于厘米,声音的速度：344m/s,来回就要除以2	
                                                //为什么除以58等于厘米?  Y米=（X秒*344）/2
                                                // X秒=（ 2*Y米）/344 ==》X秒=0.0058*Y米 ==》厘米=微秒/58
  int pitch=map(RangeInCentimeters,2,110,50,5000);
  Serial.println(pitch);
  tone(pwmPin,pitch);			        //让pwmPin引脚输出pitch的频率
  delay(300);				        //频率持续时间200ms
  noTone(pwmPin);				//关闭
}




