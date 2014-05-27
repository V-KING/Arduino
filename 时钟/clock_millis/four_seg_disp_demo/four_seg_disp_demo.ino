/*
 * ==================================================
 *      Name: four_seg_disp_demo.ino
 *   Version: 1.0 - 2014/5/15 17:05:49
 *   Company: WWW.SOGWORKS.CN
 *  Function: �ĸ��������ʾ 
 *==================================================
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
int aPin=7;			//�������ֽӿ�7 ����a �������
int bPin=6;			// �������ֽӿ�6 ����b �������
int cPin=5;			// �������ֽӿ�5 ����c �������
int dPin=10;			// �������ֽӿ�10 ����d �������
int ePin=11;			// �������ֽӿ�11 ����e �������
int fPin=8;			// �������ֽӿ�8 ����f �������
int gPin=9;			// �������ֽӿ�9 ����g �������
int dpPin=4;			// �������ֽӿ�4 ����dp �������
int bitn[4]={
    13,12,3,2};		//���ĸ�����ܣ����������ǵĹ��������ŷֱ��arduino��13,12,3,2����
/* 
 * �����õ�3462BS�ǹ�����������Ӧ����,֮ǰ�õ��ǹ������������
 * ���Կ���ֻ��Ҫ�Ķ�����һ�д���Ϳ�����
 * ����������--->
 *
 */
int delayTime=1;                       //��ʱ��ʱ��
/* **������ر���** */
int restBytes=0;		  //������ʣ�µ��ֽ���
int COMMON=1;

//�������ʾ������8�ζ�Ӧ8������������Ϊ1�����������Ϊ0��Ϩ��
void displaySeg(boolean a,boolean b,boolean c,boolean d,
	boolean e,boolean f,boolean g,boolean dp) {
    if(a)     digitalWrite(aPin,!COMMON);		//aҪ�����Ļ����Ǻ͹�����COMMON��һ��������!COMMON
    else    digitalWrite(aPin,COMMON);
    if(b)     digitalWrite(bPin,!COMMON);
    else    digitalWrite(bPin,COMMON);
    if(c)     digitalWrite(cPin,!COMMON);
    else    digitalWrite(cPin,COMMON);
    if(d)     digitalWrite(dPin,!COMMON);
    else    digitalWrite(dPin,COMMON);
    if(e)     digitalWrite(ePin,!COMMON);
    else    digitalWrite(ePin,COMMON);
    if(f)     digitalWrite(fPin,!COMMON);
    else    digitalWrite(fPin,COMMON);
    if(g)     digitalWrite(gPin,!COMMON);
    else    digitalWrite(gPin,COMMON);
    if(dp)     digitalWrite(dpPin,!COMMON);
    else    digitalWrite(dpPin,COMMON);

}

//������ʾ����������ΪҪ��ʾ������0-9
void displayNum(byte data) {
    switch (data) {
        case 0:
            displaySeg(1,1,1,1,1,1,0,0);	//���������ԭ��ͼ������led
            break;
        case 1:
            displaySeg(0,1,1,0,0,0,0,0);
            break;
        case 2:
            displaySeg(1,1,0,1,1,0,1,0);
            break;
        case 3:
            displaySeg(1,1,1,1,0,0,1,0);   
            break;       
        case 4:   
            displaySeg(0,1,1,0,0,1,1,0);       
            break;           
        case 5:           
            displaySeg(1,0,1,1,0,1,1,0);           
            break;           
        case 6:               
            displaySeg(1,0,1,1,1,1,1,0);               
            break;               
        case 7:                   
            displaySeg(1,1,1,0,0,0,0,0);
            break;                                       
        case 8:                       
            displaySeg(1,1,1,1,1,1,1,0);                       
            break;                       
        case 9:                           
            displaySeg(1,1,1,1,0,1,1,0);                           
            break;
        default:
            displaySeg(0,0,0,0,0,0,0,0);                       
    }
}



/*
 *��lightUp_flag=1ʱ��������ʾ������ 
 *��lightUp_flag=0ʱ�����ǲ���ʾ������ 
 */
void dock(int lightUp_flag) 
{
    if(lightUp_flag==1){
	displaySeg(0,0,0,0,0,0,0,1);                       
    }
    else{
	displaySeg(0,0,0,0,0,0,0,0);                       
    }
}
/*
 * �������ȫ������
 */
void clearLED()
{
    displaySeg(0,0,0,0,0,0,0,0);                       
    for(int i=0; i<4; i++){
	digitalWrite(bitn[i],!COMMON);
    }

}
/* 
 * ��n������ܵ���ʾdata
 * n   :��0��ʼ
 * data:�������ʾ������[0,9]
 */
void disp(int n,int data)
{
    clearLED();
    switch(data)
    {
    case 0:
	displayNum(0);
        break;
    case 1:
	displayNum(1);
        break;
    case 2:
	displayNum(2);
        break;
    case 3:
	displayNum(3);
        break;
    case 4:
	displayNum(4);
        break;
    case 5:
	displayNum(5);
        break;
    case 6:
	displayNum(6);
        break;
    case 7:
	displayNum(7);
        break;
    case 8:
	displayNum(8);
        break;
    case 9:
	displayNum(9);
        break;
    default:
	displayNum(10);
        break;  
    }
    //����������ܵĹ�����������������
    for(int i=0; i<4; i++){
	digitalWrite(bitn[i],!COMMON);
    }
    digitalWrite(bitn[n],COMMON);		//������n�������
}

/*
 * ǰ��������ʾ����preTwoNum�����������������ʾ����sencondTwoNum
 * */
void disptime(int preTwoNum,int secondTwoNum,int interval){
    //һ��һ������ʾʱ��
    disp(0,preTwoNum/10);		//��ʾ��������
    delay(interval);
    disp(1,preTwoNum%10);		//��ʾ��������
    delay(interval);
    disp(2,secondTwoNum/10);		//��ʾ��������
    delay(interval);
    disp(3,secondTwoNum%10);		//��ʾ��������
    delay(interval);
    clearLED();
}

void setup()
{
    Serial.begin(9600);  
    for(int i=2;i<=13;i++)
        pinMode(i,OUTPUT);//����4��11 ����Ϊ���ģʽ
}

void loop()
{
    restBytes=Serial.available();
    //�����е����ݡ�
    if(restBytes > 0){
	delayTime=Serial.parseInt(); 
    }
    //�������ʾ��1234��ˢ�µ�Ƶ��ΪdelayTime
    disptime(12,34,delayTime);	
}
