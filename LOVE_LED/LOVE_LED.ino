//定义一个红桃心 LOVE，头往左偏侧过来看
//沿着1走，画一个‘心’的图形

byte A[] = {
  B00000000,
  B00111111,
  B01111111,
  B11001000,
  B11001000,
  B01111111,
  B00111111,
  B00000000,
};

byte B[] = {
  B00000000,
  B00110110,
  B01111111,
  B01001001,
  B01001001,
  B01111111,
  B00000000,
};

byte C[] = {
  B00000000,
  B01000010,
  B10000001,
  B10000001,
  B10000001,
  B01111110,
  B00000000,
};

byte D[] = {
  B00000000,
  B00111100,
  B01000010,
  B10000001,
  B10000001,
  B11111111,
  B00000000,
};

byte S[] = {
  B00000000,
  B01000110,
  B10001111,
  B10011001,
  B11110001,
  B01100010,
  B00000000,
};

byte O[] = {
  B00000000,
  B00111100,
  B01000010,
  B10000001,
  B10000001,
  B10000001,
  B01000010,
  B00111100,
  B00000000,
};

byte LOVE[] = {
  B00000000,
  B01110000,
  B10001000,
  B10000100,
  B01000010,
  B00100001,
  B01000010,
  B10000100,
  B10001000,
  B01110000,
  B00000000,
};

byte LOVE2[] = {
  B01110000,
  B11111000,
  B11111100,
  B01111110,
  B00111111,
  B01111110,
  B11111100,
  B11111000,
  B01110000,
};
//定义字母I，头往左偏侧过来看头，
//沿着1走，画一个‘心’的图形
byte I[]={
  B00000000,
  B00000000,
  B10000001,
  B11111111,
  B10000001,
  B00000000,
  B00000000
};
//定义字母U
byte U[]={
  B00000000,
  B11111100,
  B00000110,
  B00000110,
  B00000110,
  B00000110,
  B00000110,
  B11111100,
  B00000000,
};

//定义space
byte SPACE[]={
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
};
//信
byte XIN[]={
	0x00,0x24,0xFA,0x03,0x72,0x02,0xFA,0x02,
	0xFA,0x8A,0x8A,0xFA,0x00,0x00,0x00,0x00
};
//鸽
byte GE[]={
	0x00,0x22,0xF5,0x88,0xA7,0x90,0xD7,0x15,
	0xF5,0x85,0xB5,0xC7,0x00,0x00,0x00,0x00
};

int LEDpins[]={9,8,7,6,5,4,3,2}; //定义对应的LED引脚 
//int LEDpins[]={2,3,4,5,6,7,8,9,}; //定义对应的LED引脚 

//A8642 975

void setup() {
  int r;
  for (r = 0; r < 8; r++) {
    pinMode(LEDpins[ r ], OUTPUT);
  }
}

void loop() {
  //show(I   ,sizeof(I)   /sizeof(I[0]));
  //show(LOVE2,sizeof(LOVE2)/sizeof(LOVE2[0]));
  //show(U   ,sizeof(U)   /sizeof(U[0]));

	while(1)
	{
		show(XIN   ,sizeof(XIN)   /sizeof(XIN[0]),1);
		show(SPACE,sizeof(SPACE)/sizeof(SPACE[0]),1);
		show(GE,sizeof(GE)/sizeof(GE[0]),1);

		show(SPACE,sizeof(SPACE)/sizeof(SPACE[0]),1);
		delay(200);

		show(SPACE,sizeof(SPACE)/sizeof(SPACE[0]),1);
		show(XIN   ,sizeof(XIN)   /sizeof(XIN[0]),0);
		show(GE,sizeof(GE)/sizeof(GE[0]),0);

		show(SPACE,sizeof(SPACE)/sizeof(SPACE[0]),1);
		delay(200);
	}
}

/*
 *功能：显示字或者图形
 *参数：letter：显示的字母
 *	n：有多少行，每一行就是一个字节
 *返回：无
 *作者：firebaolong@163.com
 * */
void show(byte letter[],int n,int invert) {
	int display_raw;
  for (int i=0; i<n; i++){
	display_raw=invert ? i : (n-1-i);
    for(int j=0; j<8; j++){
      digitalWrite(LEDpins[j],!bitRead(letter[display_raw],j) );
    }
   delay(2);
  }
}
//功能：实心的显示
void show_invert(byte letter[],int n) {
  for (int i=0; i<n; i++){
    for(int j=0; j<8; j++){
      digitalWrite(LEDpins[j],bitRead(letter[i],j) );
    }
   delay(2);
  }
}


