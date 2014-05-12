#ifndef DS18B20_h
#define DS18B20_h
#include <OneWire.h> 
class DS18B20
{
	public:
		DS18B20( int );
		~DS18B20();
		float getTemp();
		float getTempF();
	private:
		OneWire *OW;
};
#endif
