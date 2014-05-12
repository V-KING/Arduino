#include <DS18B20.h>


int DS18S20_Pin = 2; //DS18S20信号线接数字引脚2

//定义温度芯片的 I/O
DS18B20 ds(DS18S20_Pin);  // 数字引脚2上

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  float temperature = ds.getTemp();//or ds.getTempF();
  Serial.print("yeelink:");
  Serial.println(temperature);
  
  delay(10000); //延迟点时间，让DS18B20能够稍微的稳定下来，这样好读取稳定的数据
}

