/*==================================================
 *     Name: come_down2_addBeep.ino
 *  Version: 1.0 - 2014/5/10 16:21:17
 *  Company: WWW.SOGWORKS.CN
 * Function:	��9-0�ĵ���ʱ�� ����ʱ���ˣ��ͷ���������ʱ��5s��
 * 	�ڴ��ڼ䣺
 * 	��ʱ�仹���ܣ�����key��ֹͣ����ʱ.
 * 	���Ѿ�ʱ��ֹͣ���ˣ���key�������¿�������ʱ.
 ==================================================*/



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
int high=HIGH;					  //������ʱhigh=HIGH��
int low=LOW;					  //������ʱlow=LOW;
int buttonPP = A0;				  //play OR pause ����
/* **ʱ���õ��ı���** */
int shi1=0;                       //Сʱ�ĵ�һ����
int shi2=0;                       //Сʱ�ĵڶ�����
int fen1=0;                       //Сʱ�ĵ�һ����
int fen2=0;                       //Сʱ�ĵڶ�����
/* **��ʱ���õ��ı���** */
byte miao=9;          		  //��
byte fen=0;	          		  //��
byte shi=12;           		  //ʱ

static unsigned long previouTotalBeepTime;	//���������Ƿ���beeping��ʱ��,���˾Ͳ�����


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
	digitalWrite(dp,high);	//����dp��
    }
    else{
	digitalWrite(dp,low);	//��dp��
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
    //λ����
    digitalWrite(13,high);
    digitalWrite(12,high);
    digitalWrite(3,high);
    digitalWrite(2,high);
}
/* 
 * ��ʾ����data
 * */
void disp(int data)
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
int priorButtonState = UNPRESSED;
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
 * ��������5s��
 * */
void beeping(){
    static unsigned long previouBeepMoment1=millis();		//��������ÿ�����������õ�
    if(millis()-previouTotalBeepTime< 5000){				//Ҳ���Ǵ���5000ʱ�Ͳ�����,��ִ��������
	if(millis() - previouBeepMoment1 <= 500){			//����500ms����750HZ ��Ƶ��
	    noTone(3);
	    tone(3,750,500);
	}
	else if(millis() - previouBeepMoment1 <= 1000){		//(500,1000)֮����1000HZ Ƶ��
	    noTone(3);
	    tone(3,1000,500);
	}
	else{
	    previouBeepMoment1 = millis();					//beeping��5s�󣬸���previouTotalBeepTime
	}
    }
}

/* *** */
boolean stopFlag=0;											//ֹͣʱ���ܵ�flag
int stateButtonAction=UNPRESSED;
unsigned long setTime;
unsigned long preS;				//������¼ÿ��ˢ��1�ε�
unsigned long passms;				//�ӿ������ܹ���ȥ�˶���ms
unsigned long nows;				//��00:00:00���ܹ���ȥ�˶���ms,����������ʱ��
unsigned long dispshi=0,dispfen=0,dispmiao=0;	//Ҫ��ʾ��ʱ����
unsigned long startms=0;	 		//��¼��ʱǰ��ʱ�䣨ms��
void setup()
{
    Serial.begin(9600);  
    //����4��11 ����Ϊ���ģʽ
    for(int i=2;i<=13;i++)
	pinMode(i,OUTPUT);
    //AO����Ϊ���룬����
    digitalWrite(A0,HIGH);
    setTime = 9000;						//���ÿ�ʼ��ʱ��ms
}

void loop()
{
    //����
    if(buttonAction(A0)==PRESS_MOMENT){
	stopFlag=~stopFlag;
    }
    //��ʾֹ֮ͣǰ��ʱ��
    if(stopFlag){
	//dispmiao=0;   
	passms=millis()-startms;
	setTime = passms+9000;			//���¼�ʱ��Ҳ�����ڹ�ȥ��ʱ���ϼ���10s
	Serial.println(6);
    }
    else{
	//ÿ��һ���ˢ��һ��Ҫ��ʾ��ʱ��
	static unsigned long startms=millis();	 		//��¼��ʱǰ��ʱ�䣨ms��
	if(millis()- preS>=1000){
	    preS=millis();
	    passms=millis()-startms;
	    //�ӽ���ѭ���������ܹ�����nows��ʱ��
	    nows=setTime/1000-passms/1000;
	    //����Ҫ��ʾ��ʱ��
	    dispmiao=nows%10;   
	    //�ڴ�����ʾʱ��
	    Serial.println(dispmiao,DEC); 

	    if(dispmiao == 0){//
		previouTotalBeepTime=millis(); 	
		while((stateButtonAction=buttonAction(A0))!=PRESS_MOMENT){
		    disp(0);
		    //��5s��
		    beeping();	
		}
	    } 
	}

    }


    //�������ʾ
    disp(dispmiao);
    //delay(100);

/************

    //����ʱ���ˣ���ȥ�ر�ʱ�����,��ʾ0�����ҷ�������
    if(miao<=0)		    
    {
	miao=9;
	NotUpdataTime();
	previouTotalBeepTime=millis(); 	
	//���ϵ�������̣���ʾ��beeping
	while((stateButtonAction=buttonAction(A0))!=PRESS_MOMENT){
	    disp(0);
	    //��5s��
	    beeping();	
	}
	//���뽫previouTotalBeepTime����,��Ȼ����5000ms֮��,��Զ����������
	if( stateButtonAction == PRESS_MOMENT ){
	    previouTotalBeepTime=millis(); 	
	    updateTime();
	}
    }
    disp(miao);
    //<<���ﻹ����Ҫ��ʱһ�£���Ȼ��ʾ����������֪��Ϊʲô��>>
    delay(1);
**************/
}

