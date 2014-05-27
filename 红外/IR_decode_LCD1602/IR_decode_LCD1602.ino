/*
 * ====================================================
 *      Name: IR_decode_LCD1602.ino
 *   Version: 1.0 
 *  Compiler: arduino-IDE
 *   Company: WWW.SOGWORKS.CN 
 * Functioin: 接收红外数据，
 *            并将数据以2进制和16进制格式显示在lcd1602液晶屏上
 * =====================================================
 * */


#include <IRremote.h>         //添加红外库
#include <LiquidCrystal.h>    //添加液晶库


int RECV_PIN = 9;           //定义接受引脚
IRrecv irrecv(RECV_PIN);    //定义接收实例
decode_results results;     //定义存放接收数据的变量


unsigned long byte1;
unsigned long byte2;
unsigned long byte3;
unsigned long byte4;
int raw=0,col=0;
/**
 * 按照二进制反转,例如10011111变成11111001
 * 从最低位开始，一位一位的取出，再向左移动。
 * 其中如果取出的为1，就使最低位为1。
 * 这样就可以把高低位反转
 * @param  byte1 你要反转的字节
 * @return       已经反转的字节
 */
int revert(int byte1){
    long value=0;
    for(int i=0; i<8; i++){
	value <<= 1;
	if( (byte1 >> i) & 0x01 ){
	    value=value | 0x01; 

	}
    Serial.print((byte1 >> i) & 0x01);			//在串口中显示
    }
    Serial.print(" ");					//在串口中显示
    return value;
}

void setup()
{   
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
    for(int i=2; i<=6; i++){
	pinMode(i,OUTPUT);
    }
}

void loop() {
    if (irrecv.decode(&results)) {
	//将数据分割成4个字节
	byte1 = (results.value>>0)  & 0xff; //从左数起，第1字节
	byte2 = (results.value>>8)  & 0xff; //从左数起，第2字节       
	byte3 = (results.value>>16) & 0xff; //从左数起，第3字节
	byte4 = (results.value>>24) & 0xff; //从左数起，第4字节
	//依次将四个字节反转
	byte4 = revert(byte4);
	byte3 = revert(byte3);
	byte2 = revert(byte2);
	byte1 = revert(byte1);
	//打印一个数据之后就换行
	Serial.println();			//我们在revert函数中一位一位的打印，在这里就是打印了32位后 换行
	//重新将数据粘合起来
	results.value=(byte4 << 24)|(byte3<<16)|(byte2<<8)|(byte1);
	Serial.print("0x");			//16进制是由0x开头的
	//将前面的一个或者两个0补上
	if(results.value / pow(16,7) < 1){      //浮点数的会带小数点，所以可能有0.001，所以用<1
	    Serial.print(0);
	}
	if(results.value/ pow(16,6) <= 1 ){     //浮点数的会带小数点，所以可能有0.001，所以用<1
	    Serial.print(0);                    
	}
	Serial.println(results.value,HEX);      //串口打印
	raw = (raw+1+2) % 2;                    //%总共的，是不可能溢出，再加上1相当于raw++
	irrecv.resume();                        // 接收下一个红外值
    }
}
