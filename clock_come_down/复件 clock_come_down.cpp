
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
//����������
#define CLK_MODE 	11
#define COME_DOWN_MODE  22


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
byte miao2=0;          		  //����������
byte fen=0;	         	  //��
byte shi=12;           		  //ʱ
/* **������ر���** */           
int restBytes=0;		  //������ʣ�µ��ֽ���
/* **�����ر���** */
int buttonPP = A0;		  //play OR pause ����
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
    digitalWrite(c,high);		//�����ֽӿ�5 ���Ÿߵ�ƽ������c ��
    digitalWrite(b,high);		//����b ��
    for(j=7;j<=11;j++)			//Ϩ�������
	digitalWrite(j,low);
    digitalWrite(dp,low);		//Ϩ��С����DP ��
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
    digitalWrite(bitn[n],low);		//������n�������
}

/* 
 * ����ʱ���ж���Ϊ1ms 
 */
void init_time()  
{  
    TCCR2A |= (1 <<WGM21) | (1 << WGM20);  	//fast PWMģʽ
    TCCR2B |= (1 << CS22 );  		    	//64��Ƶ
    TCCR2B &= ~((1 <<CS21) | (1 <<CS20));  	//64��Ƶ
    TCCR2B &= ~((1 << WGM21 ) | (1 << WGM20));  
    ASSR |= ( 1 << AS2 );                  	//ʱ�Ӻ;���ͬ��
    TIMSK2 |= ( 1 << TOIE2 ) | ( 0 << OCIE2B ); //ʹ�ܶ�ʱ�ж�
    TCNT2 = 6;					//��ʼ�������Ĵ�����ֵ
    sei();  					//�����ж�	
}  

int count_ms=0;					//ms������
int count_10ms=0;				//ms������
int flag_count10msRun=0;			//ms������
/*
 * ��ʱ��2����ж�
 * */
ISR(TIMER2_OVF_vect)  
{  
    TCNT2 = 6;  				//������д��ʱ��2������
    ++count_ms;  				//ms������1
    //������1s��ʱ�򣬾������������1,����ms����������
    if(count_ms>=1000){					
	count_ms=0;
	miao++;
    }
    if(count_ms>=10 && flag_count10msRun==1){
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
    static int delay1,delay2,delay3,delay4;
    delay1=delay2=delay3=delay4=millis();
    disp(0,preTwoNum/10);		//��ʾ��������
    delayMicroseconds(1000);
    disp(1,preTwoNum%10);		//��ʾ��������
    delayMicroseconds(1000);
    disp(2,secondTwoNum/10);		//��ʾ��������
    delayMicroseconds(1000);
    disp(3,secondTwoNum%10);		//��ʾ��������
    delayMicroseconds(1000);
    clearLED();
    //delay(8);
}


//ǰ��������ʾ����preTwoNum�����������������ʾ����sencondTwoNum
void disptime2(int preTwoNum,int secondTwoNum){
    //һ��һ������ʾʱ��
    int interval=500;
	static int active0 =1;
	static int active1 =0;
	static int active2 =0;
	static int active3 =0;
    static int previous1=millis();	
    static int previous2=previous1;
    static int previous3=previous1;
    static int previous0=previous1;
	
	if(active0 && (millis()-previous0 < interval)){
    	disp(0,preTwoNum/10);		//��ʾ��������
    	active0=0;
		active1=1;
	}
	if ( active1 && (millis()-previous1 >= interval) ) {
   	 	previous2 = millis();
    	disp(1,preTwoNum%10);		//��ʾ��������
		previous1 = millis();
		active1=0;
		active2=1;
		
	}
	if ( active2 && (millis()-previous2 >= interval) ) {
   	 	previous3 = millis();
    	disp(2,secondTwoNum/10);		//��ʾ��������
		previous2 = millis();
		active2=0;
		active3=1;
	}
	if ( active3 && (millis()-previous3 >= interval) ) {
   	 	previous0 = millis();
    	disp(3,secondTwoNum%10);		//��ʾ��������
		previous3 = millis();
		active3=0;
		active0=1;
	}
    clearLED();
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
int RELEASE_MOMENT=333;
static int priorButtonState = UNPRESSED;
int buttonDetect(int button){
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
	    state = RELEASE_MOMENT;		//�ͷ�˲��
	}
	else{
	    state = UNPRESSED;			//����û��
	}
	priorButtonState = UNPRESSED;		//��ֵ
    }
    return state;
}

static int priorButtonState1 = UNPRESSED;
int buttonDetect1(int button){
    int state;
    if(digitalRead(button)==PRESSED){//���ΰ���
	if(priorButtonState1==UNPRESSED){
	    state = PRESS_MOMENT;		//���µ�һ˲��
	}
	else{
	    state = PRESS_ALLWAYS;		//һֱ����
	}
	priorButtonState1 = PRESSED;		//��ֵ
    }
    else {//����û�а���
	if(priorButtonState1 == PRESSED){
	    state = RELEASE_MOMENT;		//�ͷ�˲��
	}
	else{
	    state = UNPRESSED;			//����û��
	}
	priorButtonState1 = UNPRESSED;		//��ֵ
    }
    return state;
}
/* 
 * siren2.ino�е�ɨ�����
 * */
int button_state = HIGH;      //�洢������һ�μ���״̬�������жϰ����Ƿ���
int buttonDetect3() {
	if(digitalRead(A5) == LOW){   //�����ȡ����������Ϊ�͵�ƽ����ʾ����������
		button_state=LOW;	      //�Ѱ���״̬������Ϊ��
		return 0;		      //����û���ͷţ�����0
	}
	else {			      //�����ȡ����������Ϊ�ߵ�ƽ
		if(button_state==LOW) {	      //���������һ״̬Ϊ�͵�ƽ�����ʾ�������ͷ�
			button_state=HIGH;        //������״̬������Ϊ��
			return 1;	              //�����ͷţ�����1
		}
		else {			      //����δ���£�����0
			return 0;
		}
	}
}
/* 
 * ��key���л�ģʽ
 * ���أ��л���ģʽ
 * ���룺
 * */
int mode = CLK_MODE;
int	modeArray[2] ={	CLK_MODE, COME_DOWN_MODE};
static int keyIndex=0;				//Ĭ�ϴ�0��ʼ
int ifKeySwitchMode(){
    static int buttonActionState1;		//��Ű���״̬
    buttonActionState1=buttonDetect1(A1);
    if(buttonActionState1==RELEASE_MOMENT){
	++keyIndex;
	if( keyIndex==sizeof(modeArray)/sizeof(modeArray[0]) ){
	    keyIndex=0;
	}
	mode=modeArray[keyIndex];		//��ü�ֵ	
    }
    //Serial.print("mode = ");
    //Serial.println(mode);
    return mode;
}
/* *** */
boolean stopFlag=0;
int state;
void setup()
{
    Serial.begin(9600);  
    init_time();  
    for(int i=2;i<=13;i++)
	pinMode(i,OUTPUT);//����4��11 ����Ϊ���ģʽ
}

int setTime;
void loop()
{
    restBytes=Serial.available();
    //����պ���4���Ͷ�����,������ʵ���Լ�һ�����ˣ��ö�ȡ������ֻ����0-9�����֣�������Լ��ϣ��ܼ�
    if(restBytes == 4){
	shi1=Serial.read()-48;//��ȡ����ascii���ȥ�ַ�'0'��ascii��ֵ
	shi2=Serial.read()-48;
	fen1=Serial.read()-48;
	fen2=Serial.read()-48;
	shi=shi1*10 + shi2;
	fen=fen1*10 + fen2;
    }
    //������byte�ĸ�ʽ�������4�������Ǿ���մ���
    else{
	while(Serial.available()>0){
	    Serial.read();
		
	}
    }

	setTime = shi*60*60*1000;
	static int startms=millis();
	if(millis()- preS>=1000){
		preS=0;
		passms=millis()-startms;
		nowTime=passms+setTime;
	}
	disptime2(int preTwoNum,int secondTwoNum);	
	
}

parseInt();


void clockMode(){
    if((mode=ifKeySwitchMode()) == COME_DOWN_MODE){
	return;
    }
    //test
    //ms-->miao //��millis()
    if(miao>=60)		//��60������,�ּ�1
    {
	miao=0;
	fen++;
	if(fen>=60)		//��60�־�����,ʱ��1
	{	
	    fen=0;		   
	    shi++;
	    if(shi>=24)	   	//��24Сʱ��0
		shi=0;
	}
    }
    //û��500ms��ʱ�����
    if(count_ms<500){	   	//ǰ500ms��ʱ���һֱ����������
	clearLED();
	digitalWrite(bitn[1],low);
	dock(1);		//д1���ǵ���
    }
    else if(count_ms<1000){	//��500ms��һֱ����������
	clearLED();
	digitalWrite(bitn[1],low);
	dock(0);		//д0������
    }	
    disptime(shi,fen);

    //��ȡ�������byte�ĸ���
    restBytes=Serial.available();
    //����պ���4���Ͷ�����,������ʵ���Լ�һ�����ˣ��ö�ȡ������ֻ����0-9�����֣�������Լ��ϣ��ܼ�
    if(restBytes == 4){
	shi1=Serial.read()-48;//��ȡ����ascii���ȥ�ַ�'0'��ascii��ֵ
	shi2=Serial.read()-48;
	fen1=Serial.read()-48;
	fen2=Serial.read()-48;
	shi=shi1*10 + shi2;
	fen=fen1*10 + fen2;
    }
    //������byte�ĸ�ʽ�������4�������Ǿ���մ���
    else{
	while(Serial.available()>0){
	    Serial.read();
	}
    }          
}


/*
 * ����ʱģʽ
 * */
int flag=0;
void comeDownMode(){
    //��һ�μ��key1
    //Serial.println(">>>comeDownBegin...");
    //key1
    if((mode=ifKeySwitchMode()) == CLK_MODE){
	return;
    }

/* ****** */
    //����key0
    if(buttonDetect3()==1){
	flag_count10msRun=1;
	//Serial.println("-----------A5 press------------");
	flag = 1;
	//miao2=miao;
    }
    
    if(flag){
	flag_count10msRun=1;
    }
    else{
	flag_count10msRun=0;
	miao2=0;
	count_10ms=0;
    }
/* ****** */
    //ʱ�䴦����
    if(count_10ms>=100)  {
	count_10ms=0;
	miao2++;
	if(miao2>=100)		    //��100�ٷ�������,���1
	{
	    miao2=0;
	}
    }
    //��2�μ��key1
    if((mode=ifKeySwitchMode()) == CLK_MODE){
	return;
    }
    //��ʾ
    //Serial.println("xxxxxxxxxxxxxxxxxxxxxx");
    disptime(miao2,count_10ms);
    //�����μ��key1
    if((mode=ifKeySwitchMode()) == CLK_MODE){
	return;
    }
    //Serial.println("<<<<out ");
}


/*
 * ʱ�ӿ�����
 * �������ʾʱ�Ӳ���run��
 * ����������key1�л������Ͼ�����ʱ��
 * 
 * ����������run����ʾ��
 * ����1����key1 ��û�з�ӳ,��Ч.
 * ����2����key0���ص�ʱ�ӣ�ʱ��not RUN.
 * ����3����key1�����not RUN.
 * ����4���ٰ�key1�����û�з�ӳ����Ч��
 * ����5����key0��ʱ����ʾ��RUN
 *
 *
 *
 * 2014.5.13.19.17������siren2.ino�ļ���������򣬻���ͬ��������
 * 	˵������ɨ����򣬶�����û������ġ�
 *
 */
