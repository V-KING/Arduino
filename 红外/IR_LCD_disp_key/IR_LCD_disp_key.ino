/*
 * ====================================================
 *      Name: IR_LCD_disp_key.ino
 *   Version: 1.0 
 *  Compiler: arduino-IDE
 *   Company: WWW.SOGWORKS.CN 
 * Functioin: 接收红外数据，
 *            并将遥控器的0啊1啊模式啊，在LCD显示
 * =====================================================
 * */
#include <IRremote.h>          //添加红外库
#include <LiquidCrystal.h>    //添加液晶库

//定义按键,根据遥控器，由左到右，由上到下
#define ON_OFF 		0xFFA25D
#define MODE		0xFF629D
#define MUTE 	    	0xFFE21D
#define PLAY_PAUSE 	0xFF22DD
#define PREVIOUS 	0xFF02FD
#define NEXT 		0xFFC23D
#define EQ 		0xFFE01F
#define SUB 		0xFFA857
#define ADD 		0xFF906F
#define ZERO 		0xFF6897
#define RETURN 		0xFF9867
#define U_SD		0xFFB04F
#define ONE		0xFF30CF
#define TWO		0xFF18E7
#define THREE		0xFF7A85
#define FOUR		0xFF10EF
#define FIVE		0xFF38C7
#define SIX		0xFF5AA5
#define SEVEN		0xFF42BD
#define EIGHT		0xFF4AB5
#define NINE		0xFF52AD
#define REPEAT		0xffffffff


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//定义液晶对象，采用最简单接法




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
    }
    return value;
}

void setup()
{   
    lcd.begin(16,2);	 //初始化液晶，16列，2行
    Serial.begin(9600);
    irrecv.enableIRIn(); // 使能接收
    for(int i=2; i<=6; i++){
	pinMode(i,OUTPUT);
    }
    pinMode(10,OUTPUT);
    pinMode(6,OUTPUT);
    analogWrite(6,100);	//背光设置
    analogWrite(10,200);	//对比度设置,发现有问题，显示的数据会有乱码
}

void loop() {
    //码准备好了就可以去读拉
    if (irrecv.decode(&results)) {
	Serial.println(results.value);
	if(results.value == ONE) {		//读取码值				
	    lcd.clear();                
	    lcd.setCursor(0,0);			//设置LCD的位置，setCursor(列,行)
	    lcd.print("1");			//在LCD上显示码值			
	}
	else if(results.value == TWO){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("2");                     //在LCD上显示码值			
	}
	else if(results.value == THREE){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("3");                     //在LCD上显示码值			
	}
	else if(results.value == FOUR){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("4");                     //在LCD上显示码值			
	}
	else if(results.value == FIVE){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("5");                     //在LCD上显示码值			
	}
	else if(results.value == SIX){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("6");                     //在LCD上显示码值			
	}
	else if(results.value == SEVEN){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("7");                     //在LCD上显示码值			
	}
	else if(results.value == EIGHT){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("8");                     //在LCD上显示码值			
	}
	else if(results.value == NINE){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("9");                     //在LCD上显示码值			
	}
	else if(results.value == ZERO){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("0");                     //在LCD上显示码值			
	}
	else if(results.value ==  ON_OFF){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("ON_OFF");                //在LCD上显示码值			
	}
	else if(results.value == MODE){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("Mode");                  //在LCD上显示码值			
	}
	else if(results.value == MUTE){    	//读取码值				
	    lcd.clear();    		                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("mute");                  //在LCD上显示码值			
	}
	else if(results.value == PLAY_PAUSE){    //读取码值					
	    lcd.clear();                                                                 
	    lcd.setCursor(0,0);                  //设置LCD的位置，setCursor(列,行)
	    lcd.print("PLAY_PAUSE");             //在LCD上显示码值			
	}
	else if(results.value == PREVIOUS){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("PREVIOUS");              //在LCD上显示码值			
	}
	else if(results.value == NEXT){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("NEXT");                  //在LCD上显示码值			
	}
	else if(results.value == EQ){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("EQ");                    //在LCD上显示码值			
	}
	else if(results.value == SUB){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("-");                     //在LCD上显示码值			
	}
	else if(results.value == ADD){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("+");                     //在LCD上显示码值			
	}
	else if(results.value == RETURN){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("RETURN");                //在LCD上显示码值			
	}
	else if(results.value == U_SD){    	//读取码值				
	    lcd.clear();                                                                
	    lcd.setCursor(0,0);                 //设置LCD的位置，setCursor(列,行)
	    lcd.print("U/SD");                  //在LCD上显示码值			
	}
	irrecv.resume();                        // 接收下一个红外值
    }
}

