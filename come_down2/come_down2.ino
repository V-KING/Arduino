
/*
 * ====================================================
 *      Name: come_down.ino
 *   Version: 1.0
 *  Compiler: arduino-IDE
 *   Company: WWW.SOGWORKS.CN 
 * Functioin: a clock with arduino uno
 * =====================================================
 * */

/* 
 *��������ź�:(3462BS��һ�������)
 *��������ţ�12 - 6
 *��������ţ�1  - 6 
 *
 * ��������źŶ�Ӧ�� led�Σ�
 * ��������� - arduino����
 * A-11            7
 * B-7             6
 * C-4             5
 * D-2             10
 * E-1             11
 * F-10            8
 * G-5             9
 * DP-3            4
 * DIG1-12         13
 * DIG2-9          12
 * DIG3-8          3 
 * DIG4-6          2 
 * */


typedef void (*funPointer)(void);
funPointer 

//���ÿ��Ƹ��ε�����IO ��
int a=7;			//�������ֽӿ�7 ����a �������
int b=6;			// �������ֽӿ�6 ����b �������
int c=5;			// �������ֽӿ�5 ����c �������
int d=10;			// �������ֽӿ�10 ����d �������
int e=11;			// �������ֽӿ�11 ����e �������
int f=8;			// �������ֽӿ�8 ����f �������
int g=9;			// �������ֽӿ�9 ����g �������
int dp=4;			// �������ֽӿ�4 ����dp �������
int bitn[4]={
	13,12,3,2};		//���ĸ�����ܣ����������ǵĹ��������ŷֱ��arduino��13,12,3,2����
/* 
 * �����õ�3462BS�ǹ�����������Ӧ����,֮ǰ�õ��ǹ������������
 * ���Կ���ֻ��Ҫ�Ķ�����һ�д���Ϳ�����
 * ����������--->
 *
 */
int high=LOW;					  //������ʱhigh=HIGH��
int low=HIGH;					  //������ʱlow=LOW;
/* **ʱ���õ��ı���** */
int shi1=0;                       //Сʱ�ĵ�һ����
int shi2=0;                       //Сʱ�ĵڶ�����
int fen1=0;                       //Сʱ�ĵ�һ����
int fen2=0;                       //Сʱ�ĵڶ�����
/* **��ʱ���õ��ı���** */
byte miao=0;          		  //��
byte fen=0;	          		  //��
byte shi=12;           		  //ʱ
/* **������ر���** */           
int restBytes=0;				  //������ʣ�µ��ֽ���
/* **�����ر���** */
int buttonPP = A0;				  //play OR pause ����
void digital_0(void)              //��ʾ����0
{
	unsigned char j;
	digitalWrite(a,high);
	digitalWrite(b,high);
	digitalWrite(c,high);
	digitalWrite(d,high);
	digitalWrite(e,high);
	digitalWrite(f,high);

	digitalWrite(g,low);
}
//��ʾ����1
void digital_1(void)             
{
	unsigned char j;
	digitalWrite(c,high);			//�����ֽӿ�5 ���Ÿߵ�ƽ������c ��
	digitalWrite(b,high);			//����b ��
	for(j=7;j<=11;j++)			//Ϩ�������
		digitalWrite(j,low);
	digitalWrite(dp,low);			//Ϩ��С����DP ��
}
//��ʾ����2
void digital_2(void) 			
{
	unsigned char j;
	digitalWrite(b,high);
	digitalWrite(a,high);
	for(j=9;j<=11;j++)
		digitalWrite(j,high);
	digitalWrite(dp,low);
	digitalWrite(c,low);
	digitalWrite(f,low);
}
//��ʾ����3
void digital_3(void) 			
{
	unsigned char j;
	digitalWrite(g,high);
	digitalWrite(d,high);
	for(j=5;j<=7;j++)
		digitalWrite(j,high);
	digitalWrite(dp,low);
	digitalWrite(f,low);
	digitalWrite(e,low);
}
//��ʾ����4
void digital_4(void) 
{
	digitalWrite(c,high);
	digitalWrite(b,high);
	digitalWrite(f,high);
	digitalWrite(g,high);
	digitalWrite(dp,low);
	digitalWrite(a,low);
	digitalWrite(e,low);
	digitalWrite(d,low);
}
//��ʾ����5
void digital_5(void) 
{
	unsigned char j;
	for(j=7;j<=9;j++)
		digitalWrite(j,high);
	digitalWrite(c,high);
	digitalWrite(d,high);
	digitalWrite(dp,low);
	digitalWrite(b,low);
	digitalWrite(e,low);
}
//��ʾ����6
void digital_6(void) 
{
	unsigned char j;
	for(j=7;j<=11;j++)
		digitalWrite(j,high);
	digitalWrite(c,high);
	digitalWrite(dp,low);
	digitalWrite(b,low);
}
//��ʾ����7
void digital_7(void) 
{
	unsigned char j;
	for(j=5;j<=7;j++)
		digitalWrite(j,high);
	digitalWrite(dp,low);
	for(j=8;j<=11;j++)
		digitalWrite(j,low);
}
//��ʾ����8
void digital_8(void) 
{
	unsigned char j;
	for(j=5;j<=11;j++)
		digitalWrite(j,high);
	digitalWrite(dp,low);
}
//��ʾ����9
void digital_9(void) 
{
	unsigned char j;
	for(j=5;j<=11;j++)
		digitalWrite(j,high);
	digitalWrite(dp,low);
	digitalWrite(e,low);
}
/*
 *��lightUp_flag=1ʱ��������ʾ������ 
 *��lightUp_flag=0ʱ�����ǲ���ʾ������ 
 */
void dock(int lightUp_flag) 
{
	unsigned char j;
	for(j=5;j<=11;j++)
		digitalWrite(j,low);
	if(lightUp_flag==1){
		digitalWrite(dp,high);
	}
	else{
		digitalWrite(dp,low);
	}
}
/*
 * �������ȫ������
 */
void clearLED()
{
	digitalWrite(a,low);
	digitalWrite(b,low);
	digitalWrite(c,low);
	digitalWrite(d,low);
	digitalWrite(e,low);
	digitalWrite(f,low);
	digitalWrite(g,low);
	digitalWrite(dp,low);
	digitalWrite(13,high);
	digitalWrite(12,high);
	digitalWrite(3,high);
	digitalWrite(2,high);
}
/* 
 * ��n������ܵ���ʾdata
 * n   :��0��ʼ
 * data:�������ʾ������[0,9]
 */
void disp(int n,int data)
{
	clearLED();			//����һ�飬ѡ��������ĸ����ڵ�����n�������
	switch(data)
	{
		case 0:
			digital_0();
			break;
		case 1:
			digital_1();
			break;
		case 2:
			digital_2();
			break;
		case 3:
			digital_3();
			break;
		case 4:
			digital_4();
			break;
		case 5:
			digital_5();
			break;
		case 6:
			digital_6();
			break;
		case 7:
			digital_7();
			break;
		case 8:
			digital_8();
			break;
		case 9:
			digital_9();
			break;
		default:
			break;  
	}
	digitalWrite(bitn[n],low);			//������n�������
}

/* 
 * ����ʱ���ж���Ϊ1ms 
 */
void init_time()  
{  
	TCCR2A |= (1 <<WGM21) | (1 << WGM20);  //fast PWMģʽ
	TCCR2B |= (1 << CS22 );  			     //64��Ƶ
	TCCR2B &= ~((1 <<CS21) | (1 <<CS20));  //64��Ƶ
	TCCR2B &= ~((1 << WGM21 ) | (1 << WGM20));  
	ASSR |= ( 1 << AS2 );                  //ʱ�Ӻ;���ͬ��
	TIMSK2 |= ( 1 << TOIE2 ) | ( 0 << OCIE2B );//ʹ�ܶ�ʱ�ж�
	TCNT2 = 6;  							 //��ʼ�������Ĵ�����ֵ
	sei();  								 //�����ж�	
}  
//��ⰴ���Ƿ��ͷŵĺ���
//����Ϊ�գ�����Ϊint�� 1��ʾ�����ͷţ�0��ʾδ�ͷ�
int priorButtonState = HIGH;
int buttonRelease(int button) {
	if(digitalRead(button) == LOW){   //�����ȡ����������Ϊ�͵�ƽ����ʾ����������
		priorButtonState=LOW;	      //�Ѱ���״̬������Ϊ��
		return 0;		      //����û���ͷţ�����0
	}
	else {			      //�����ȡ����������Ϊ�ߵ�ƽ
		if(priorButtonState==LOW) {	      //���������һ״̬Ϊ�͵�ƽ�����ʾ�������ͷ�
			priorButtonState=HIGH;        //������״̬������Ϊ��
			return 1;	              //�����ͷţ�����1
		}
		else {			      //����δ���£�����0
			return 0;
		}
	}
}


int count_ms=0;							//ms������
int count_10ms=0;						//ms������
int beepTime_s=0;
int flashTime_s=0;
/*
 * ��ʱ��2����ж�
 * */
ISR(TIMER2_OVF_vect)  
{  
	TCNT2 = 6;  							//������д��ʱ��2������
	++count_ms;  							//ms������1
	//������1s��ʱ�򣬾������������1,����ms����������
	if(count_ms>=1000){					
		count_ms=0;
		miao++;
		beepTime_s++;
		flashTime_s++;
	}
	if(count_ms>=10){
		count_10ms++;
	}
}  
/* 
 * ������ʱ�䣬���Ǽ�������Ķ���������
 * */
void NotUpdataTime(){
	TIMSK2 &= ~( 1 << TOIE2 ) ;//��ֹ��ʱ�ж�
}
/* 
 * ���¾���˵��Ҫ�����������¹���
 * */
void updateTime(){
	init_time();
}

//ǰ��������ʾ����preTwoNum�����������������ʾ����sencondTwoNum
void disptime(int preTwoNum,int secondTwoNum){
	//һ��һ������ʾʱ��
	disp(0,preTwoNum/10);		//��ʾ��������
	delay(1);
	disp(1,preTwoNum%10);		//��ʾ��������
	delay(1);
	disp(2,secondTwoNum/10);		//��ʾ��������
	delay(1);
	disp(3,secondTwoNum%10);		//��ʾ��������
	delay(1);
}

void setup()
{
	Serial.begin(9600);  
	init_time();  
	for(int i=2;i<=13;i++)
		pinMode(i,OUTPUT);//����4��11 ����Ϊ���ģʽ
	pinMode(A0,INPUT_PULLUP);		
	pinMode(A1,OUTPUT);		
}
/* 
 * ������button�ӵ����������ź�
 * ���أ�����״̬��
 * ���صİ�����״̬�У�UNPRESSED,PRESS_MOMENT,PRESS_ALLWAYS,RELEASE_MOMENT;
 * */

int UNPRESSED= 1;
int PRESSED= 0;
int PRESS_MOMENT=111;
int PRESS_ALLWAYS=222;
int RELEASE=333;
//int priorButtonState = UNPRESSED;
int buttonAction(int button){
	int state;
	if(digitalRead(button)==PRESSED){//���ΰ���
		if(priorButtonState==UNPRESSED){
			state = PRESS_MOMENT;		//���µ�һ˲��
		}
		else{
			state = PRESS_ALLWAYS;		//һֱ����
		}
		priorButtonState = PRESSED;		//��ֵ
	}
	else {//����û�а���
		if(priorButtonState == PRESSED){
			state = RELEASE;			//�ͷ�˲��
		}
		else{
			state = UNPRESSED;			//����û��
		}
		priorButtonState = UNPRESSED;	//��ֵ
	}
	return state;
}


/*
 * �����鵽״̬buttonActionState������״̬����
 */
void acodingKeyToDo(funPointer funAcodingKeyState, int buttonActionState){
    if(buttonActionState){
        funAcodingKeyState();
    }
}



/* *** */
boolean stopFlag=0;
int state;
void loop()
{
yeild_keyScan:

	//����
	if(buttonAction(buttonPP)==PRESS_MOMENT){
		stopFlag=~stopFlag;
	}
	if(stopFlag){
		NotUpdataTime();
	}
	else{
		updateTime();
	}
	//ʱ�䴦����
	if(count_10ms>=100)  {
		count_10ms=0;
		if(miao>=5)		    //��100�ٷ�������,���1
		{
			miao=0;

		}
	}
}


/* 
 *
 * */
int pin_beep = 3; 
void beeping(){
	Serial.println("beeping");
}



/* 
static int lable_beep=415;
static int flag_noMove;
int beepingAndStop(){
	Serial.print("lable_beep =");
	Serial.println(lable_beep);
	switch(lable_beep){
		case 415:
			while(1){
				lable_beep = 417;
				Serial.println("++while");
				case 417:
					if(!(beepTime_s==5)){    //<---------beepTime_s==3ʱ��������
						return 0;
					}
					Serial.println("disp 0");
					//ֹͣ����ʱ��
					stopFlag=1;
					miao=0,fen=0;	
					//ȫ����ʾ0
					disp(0,0);		//��ʾ��������
					for(int i=0; i<4; i++){
						digitalWrite(bitn[i],low);
					}
					//delay(5000);
					beeping();	
					beepTime_s=0;			//<---------beepTime_s
			}
	}
	Serial.println("return 1 beep");
	lable_beep=415;
	return 1;
}
*/
/*  
static int lable_flash=447;
static int flag_led=0;
int led_flash(){
	Serial.print("lable_flash=");
	Serial.println(lable_flash);
	switch(lable_flash){
		case 447:
			while(1){
				lable_flash= 454;
				Serial.println("--while");
				case 454:
					if(!(flashTime_s==1)){    //<------flashTime_s
						return 0;
					}
					Serial.println("flash");
					digitalWrite(A1,flag_led);
					flag_led=!flag_led;
					flashTime_s=0;			  //<------flashTime_s
			}
	}
	Serial.println("return 1 flash");

	lable_flash=447;
	return 1;
}

*/


