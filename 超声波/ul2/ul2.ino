
#include <LiquidCrystal.h>    //添加液晶库

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//定义液晶对象，采用最简单接法

int ulPin=5;  
int duration=0;

void setup(){
    Serial.begin(9600);
      lcd.begin(16,2);   //初始化液晶，16列，2行
      pinMode(ulPin, OUTPUT);

}
void loop()
{
  //下面是为了发一个10us的出发信号
  pinMode(ulPin, OUTPUT);
  digitalWrite(ulPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ulPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ulPin,LOW);
  //然后，就是arduino接收超声波模块的输出回响信号
  pinMode(ulPin, INPUT);              //设置成输入模式
  duration = pulseIn(ulPin,HIGH);     //根据超声波时序图可知，我们只要知道高电平的时间
  int dis = duration/29/2;         //微秒的单位除以58等于厘米,声音的速度：344m/s,来回就要除以2  
                                                //为什么除以58等于厘米?  Y米=（X秒*344）/2
                                                // X秒=（ 2*Y米）/344 ==》X秒=0.0058*Y米 ==》厘米=微秒/58
  Serial.println(dis); 
  delay(150);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("The distance:");
  lcd.setCursor(0,1) ;
  lcd.print(dis,DEC);
  lcd.setCursor(5,1) ;  
  lcd.print("CM");
}


