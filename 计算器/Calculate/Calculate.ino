#include <LiquidCrystal.h>
#include <IRremote.h>
//定义按键
#define OFF 		0xFFA25D
#define MODE		0xFF629D
#define VOICE_OFF 	0xFFE21D
#define PLAY_PAUSE 	0xFF22DD
#define UP 		0xFF02FD
#define NEXT 		0xFFC23D
#define EQ 		0xFFE01F
#define SUB 		0xFFA857
#define PLUS 		0xFF906F
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



LiquidCrystal lcd(12, 11, 5, 4, 3, 2);



int readData[3];
int value = '0';
int keyValue=0;
int RECV_PIN = 9;
IRrecv irrecv(RECV_PIN);
decode_results results;
long num1,num2,num3;

char key;
int col=0,raw =0;
int flag_recved=0;
int flag_dispPlus =0;
int flag_dispSub =0;
int flag_dispMul =0;
int flag_dispDiv =0;
int flag_isDigtal = 1;
int op_plus =0;
int op_sub  =0;
int op_mul  =0;
int op_div  =0;
int isFirstPressSub =1;
double rest =0 ;
/**
 * 获取遥控器的键值
 * @return 遥控器上的按键
 */
int getkey(){
	switch (results.value){
	    case ONE:
			return '1';
			break;
	    case TWO:
			return '2';
			break;
	    case THREE:
			return '3';
			break;
	    case FOUR:
			return '4';
			break;
	    case FIVE:
			return '5';
			break;
	    case SIX:
			return '6';
			break;
	    case SEVEN:
			return '7';
			break;
	    case EIGHT:
			return '8';
			break;
	    case NINE:
			return '9';
			break;
	    case ZERO:
			return '0';
			break;
		case PLUS:
			return '+';
		case SUB:
			return '-';
		case UP:
			return '*';
		case NEXT:
			return '/';
		case EQ:
			return '=';
		case PLAY_PAUSE:
			return '.';
		case OFF:
			return 'c';
	    default://没用
			break;
	}
}


void setup(){
   Serial.begin(9600);
   //使能红外
   irrecv.enableIRIn(); // Start the receiver   
   //初始化lcd
   lcd.begin(16, 2);
   lcd.print("calculate");
   delay(500);
   lcd.clear();
   lcd.setCursor(0,0);
}

void loop(){
	flag_recved = irrecv.decode(&results);
    if (flag_recved ) {
    	key = getkey();
    	//如果是按数字
    	if(key >= '0' && key <='9'){
    		flag_isDigtal = 1;
    	}
    	else{
    		flag_isDigtal = 0;
    	}
    	//如果是按数字
    	if( flag_isDigtal) {				//------------------数字   		
    		//没有按+，num1继续加
    		num1 = (num1*10) + int(key-'0');

            //显示
  			lcd.setCursor(col,0);
  			lcd.print(key);
  			col++;

  			flag_dispPlus = 1;
  			flag_dispSub = 1;
 			flag_dispMul =1;
 			flag_dispDiv =1;

    	}
    	else if(key == '+' && flag_dispPlus ){		//按完数字后，或者按完 =后才可以显示+			
    		//只选择减号，在按=的时候，就只计算加，rest = rest + num1;
    		op_plus = 1;
    		op_sub  =0;
    		op_mul  =0;
    		op_div  =0;
    		flag_dispPlus = 0;		//如果连续按+，+就不显示,没用					
    		//计算结果
    		rest += num1;
    		num1 = 0;				//计算完后数字清零，用来存下一个数

    		lcd.setCursor(col,0);
    		lcd.print(key);
    		col++;
    		flag_isDigtal = 1;							//------------------数字
    	}
    	else if(key == '-' && flag_dispSub ){
    		//只选择减号，在按=的时候，就只计算减，rest = rest - num1;
    		op_plus =0;	
    		op_sub  =1;
    		op_mul  =0;
    		op_div  =0;
    		//下次就不显示-
    		flag_dispSub = 0;
    		//计算结果
    		//第一次是按-,rest = num1
    		if(isFirstPressSub){
    			rest = num1;
    			isFirstPressSub=0;
    		}
    		else{
    			rest -= num1;
    		}
    		
    		num1 = 0;				//计算完后数字清零，用来存下一个数

    		lcd.setCursor(col,0);
    		lcd.print(key);
    		col++;
    	}
    	else if(key == '*' && flag_dispMul ){
    		flag_dispMul = 0;
    		//计算结果
    		rest *= num1;
    		num1 = 0;				//计算完后数字清零，用来存下一个数

    		lcd.setCursor(col,0);
    		lcd.print(key);
    		col++;
       	}
    	else if(key == '/' && flag_dispDiv ){
    		flag_dispDiv = 0;
    		//计算结果
    		rest /= num1;
    		num1 = 0;				//计算完后数字清零，用来存下一个数

    		lcd.setCursor(col,0);
    		lcd.print(key);
    		col++;
    	}
    	else if(key == '='){
    		if(op_plus ==1 ){
    			rest += num1;
    		}
    		if(op_sub ==1 ){
    			rest -= num1;
    		}
    		if(op_mul ==1 ){
    			rest *= num1;
    		}   
    		if(op_div ==1 ){
    			rest /= num1;
    		} 		    		
    		lcd.setCursor(col,0);
    		lcd.print(key);
    		lcd.setCursor(0,1);
    		lcd.print(rest);
    		//清零，复位
    		num1 = 0;						//算完后，num1要清零
    		op_plus = 0;
    		op_sub = 0;
    		op_mul = 0;
    		op_div = 0;
    	}
    	else if(key == 'c'){
    		lcd.clear();
    		rest = 0;
    		num1 = 0;
    		col=0;
    		isFirstPressSub = 1;
            op_plus = 0;
            op_sub = 0;
            op_mul = 0;
            op_div = 0;
    	}


		irrecv.resume(); // Receive the next value
    }
}

