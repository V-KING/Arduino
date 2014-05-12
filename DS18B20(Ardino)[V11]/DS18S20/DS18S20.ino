/*
   模块 -> 板子
	VCC -> 3.3V
	GND -> GND
	DQ  -> pin 2
*/

#include <OneWire.h> 

int DS18S20_Pin = 2; //DS18S20信号线接数字引脚2

//定义温度芯片的 I/O
OneWire ds(DS18S20_Pin);  // 数字引脚2上

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  float temperature = getTemp();
  Serial.print("yeelink:");
  Serial.println(temperature);
  
  delay(10000); //延迟点时间，让DS18B20能够稍微的稳定下来，这样好读取稳定的数据
}

//getTemp()返回温度值
float getTemp(){
  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //如果没有1-Wire的设备，就复位搜索
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
	  //CRC校验
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); 			 // 用寄生电源开始转换

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);  				 // 读取Scratchpad

  
  for (int i = 0; i < 9; i++) { // 读取9个byte数据，其中包括CRC校验的数据
    data[i] = ds.read();
  }
  
  ds.reset_search();			 //重新复位搜索
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //将数据合成一起?
  float TemperatureSum = tempRead / 16; //除以16就是相当于向右移动4位，也就是将数据的小数部分去除
  
  return TemperatureSum;
  
}

