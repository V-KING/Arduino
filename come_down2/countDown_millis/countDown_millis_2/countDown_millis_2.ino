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
 *��������ţ�10 - 6
 *��������ţ�1  - 5 
 *
 * ��������źŶ�Ӧ�� led�Σ�
 * ���������-----------------Arduino�ܽ�
 *   3   ----> ���� ---------> GND       
 * A-7   --------------------> 7
 * B-6   --------------------> 6
 * C-4   --------------------> 5
 * D-2   --------------------> 10
 * E-1   --------------------> 11
 * F-9   --------------------> 8
 * G-10  --------------------> 9
 * DP-5  --------------------> 4
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
/* 
 * �����õ�3462BS�ǹ�����������Ӧ����,֮ǰ�õ��ǹ������������
 * ���Կ���ֻ��Ҫ�Ķ�����һ�д���Ϳ�����
 */
int high=HIGH;					  //������ʱhigh=HIGH��
int low=LOW;					  //������ʱlow=LOW;
/* **��ʱ���õ��ı���** */
byte miao=9;          		  //��

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
    digitalWrite(a,high);
    digitalWrite(b,high);
    digitalWrite(c,high);
    digitalWrite(d,high);
    digitalWrite(f,high);
    digitalWrite(g,high);
    digitalWrite(e,low);
    digitalWrite(dp,low);
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
	default:	//ʲô��Ҳ����
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
    if(millis()-previouTotalBeepTime< 5000){			//Ҳ���Ǵ���5000ʱ�Ͳ�����,��ִ��������
	if(millis() - previouBeepMoment1 <= 500){		//����500ms����750HZ ��Ƶ��
	    //noTone(3);
	    tone(3,750,500);
	    noTone(3);						//��������ز���tone��,���ǿ���ȥ������
	}
	else if(millis() - previouBeepMoment1 <= 1000){		//(500,1000)֮����1000HZ Ƶ��
	    //noTone(3);
	    tone(3,1000,500);
	    noTone(3);						//��������ز���tone��,���ǿ���ȥ������
	}
	else{
	    previouBeepMoment1 = millis();			//beeping��5s�󣬸���previouTotalBeepTime
	}
    }
}

/* *** */
boolean stopFlag=0;				//ֹͣʱ���ܵ�flag
int flag_int0=0;				//��¼�ⲿ�ж�0�ı�־
unsigned long preS;				//������¼ÿ��ˢ��1�ε�
unsigned long lastInterrup;			//��¼��һ�ж�֮��ʱ�̵�ʱ���
unsigned long nowInterrup;			//��¼��ǰ�жϵ�ʱ���

void setup()
{
    Serial.begin(9600);  
    //����4��11 ����Ϊ���ģʽ
    for(int i=2;i<=13;i++){
	pinMode(i,OUTPUT);
    }
    //digitalWrite(A0,HIGH);			//AO����Ϊ���룬����
    miao=10;					//��ʼ��Ҫ��ʾ����
    pinMode(2,INPUT_PULLUP);			//��������2Ϊ���룬����
    lastInterrup=millis();			//��¼��һ�ж�֮��ʱ�̵�ʱ���
    attachInterrupt(0, keyPressInterrupt, FALLING);		//�����ж�,��3�����ϣ�����Ϊ�ⲿ�½����ж�
}

void loop()
{
    //��ⰴ��������ǰ������µ�һ˲��,������ͣ�ͼ����л�
    if(checkKeyIsPressed()){				
	stopFlag=~stopFlag;
    }

    //���û��ֹͣ,�Ͳ��ϵ�ÿ��1000ms����,�����ֹͣ�ģ�miao�͸�ֵ10
    if(!stopFlag){
	if(millis()- preS>=1000){
	    preS=millis();
	    miao--;	    	
	}
    }
    else{
	miao=10;
    }
    disp(miao);					//�������0-9������ȫ��������ġ�
    //delay(1);					//�������delay�ͻ���һЩ��ʾ��̫�壬�ر���9
    //���ʱ�䵽�ˣ�����ʾ����0������Ӧ�����°�miao=10
    if(miao == 0){
	miao=10;				//���°�miao=10
	previouTotalBeepTime=millis(); 		//���������ܹ������೤ʱ��ġ�
	//�ȴ����������Ƴ�whileѭ��,�����ѭ���Ϊ��ʵʱ�ԣ���beeping�в���delay����
	while(!checkKeyIsPressed()){ 		//û�а�����while��ѭ��
	    disp(0);				//��ʾ0
	    beeping();				//��5s��
	}
    }    
}
/* 
 * ��鰴��������ǰ��µģ�yes  OR no
 * ����1����⵽�����ǰ��µ�
 * ����0����⵽���������ǰ��µ� 
 *  
 * */
int checkKeyIsPressed(){
    int state=0;
    //flag_int0==1�������ⲿ�жϣ�����key���ж���(���ǲ�һ���ǰ���)
    if(flag_int0==1){
	flag_int0=0;				//�����ⲿ�жϱ�־����
	if((nowInterrup-lastInterrup)>=10) {	//���������ⲿ�ж�֮���ʱ����
	    delay(10);				//��ʱ�����ⲿ�ж����ŵĵ�ƽ
	    if (digitalRead(2)==LOW){ 		//ǰ�����½����жϣ���ʱ�����ǵ͵�ƽ����˵���ǰ�������
		lastInterrup=nowInterrup;	//���ε��ж�ʱ�䣬��ֵ��lastInterrup
		state=1;			//��¼���ڵ�״̬
	    }
	}
    }
    return state;				//��������״̬
}
/* 
 * �ⲿ�ж�0�����������ǰ����ж�
 * */
void keyPressInterrupt(){
    nowInterrup=millis();			//�������ڵ�ʱ��
    flag_int0=1;				//����1��ʾ�Ѿ������ⲿ�ж�
}
