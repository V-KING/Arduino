#define NOTE_D0 -1
#define NOTE_D1 294
#define NOTE_D2 330
#define NOTE_D3 350
#define NOTE_D4 393
#define NOTE_D5 441
#define NOTE_D6 495
#define NOTE_D7 556

#define NOTE_DL1 147
#define NOTE_DL2 165
#define NOTE_DL3 175
#define NOTE_DL4 196
#define NOTE_DL5 221
#define NOTE_DL6 248
#define NOTE_DL7 278

#define NOTE_DH1 589
#define NOTE_DH2 661
#define NOTE_DH3 700
#define NOTE_DH4 786
#define NOTE_DH5 882
#define NOTE_DH6 990
#define NOTE_DH7 112


#define D0 -1
#define D1 294
#define D2 330
#define D3 350
#define D4 393
#define D5 441
#define D6 495
#define D7 556

#define DL1 147
#define DL2 165
#define DL3 175
#define DL4 196
#define DL5 221
#define DL6 248
#define DL7 278

#define DH1 589
#define DH2 661
#define DH3 700
#define DH4 786
#define DH5 882
#define DH6 990
#define DH7 112

//以上部分是定义是把每个音符和频率值对应起来，其实不用打这么多，但是都打上了，后面可以随意编写D调的各种歌，我这里用NOTE_D+数字表示音符，NOTE_DH+数字表示上面有点的那种音符，NOTE_DL+数字表示下面有点的那种音符。这样后面写起来比较好识别。
#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625
//这部分是用英文对应了拍子，这样后面也比较好看
int TaLang_tone[]={
D6,D6,D7,DH1,D7,D6,D3,    D6,D6,D7,DH1,D7,D6,   D6,D6,D7,DH1,D7,D6,D3,   D6,D6,D7,DH1,D7,D6,

DL6,DL6,D1,D2,D3,D4,D3,D2,   DL6,DL6,D1,D2,D3,D4,D3,   DL6,DL6,D1,D2,D3,D4,D3,D2,   D3,D1,D2,D1,DL7,D6,

D6,D3,D3,D6,D3,D3,D6,D3,D5,D6,   D5,D3,D2,D1,D5,D3,     DL6,DL6,D1,D2,D3,D4,D3,D2,   D3,D1,D2,D1,DL7,DL6 

D6,D6,D7,DH1,D7,D6,D3,       D6,D6,D7,DH1,D7,D6         D6,D6,D7,DH1,D7,D6,D3,      D6,D6,D7,DH1,D7,D6

};
float TaLang_duration[]={
1/2,1/4,1/4, 1/2,1/2, 1, 1,    1/2,1/4,1/4,1/2,1/2, 2,      1/2,1/4,1/4, 1/2,1/2, 1, 1,       1/2,1/4,1/4, 1/2,1/2, 2,

1/2,1/4,1/4,1/2,1/4,1/4,1, 1,   1/2,1/4,1/4, 1/2,1/4,1/4,2,   1/2,1/4,1/4, 1/2,1/4,1/4, 1,1,   1/2,1/4,1/4, 1/2,1/2,2,

1/2,1/4,1/4, 1/2,1/4,1/4, 1, 1/2,1/4,1/4,  1/2,1/4,1/4, 1/2,1/2, 2,   1/2,1/4,1/4, 1/2,1/4,1/4, 1,1,   1/2,1/4,1/4, 1/2,1/2,2,

1/2,1/4,1/4, 1/2,1/2, 1, 1,              1/2,1/4,1/4, 1/2,1/2, 2,   1/2,1/4,1/4, 1/2,1/2, 1, 1,      1/2,1/4,1/4, 1/2,1/2, 2

};

int tune[] =
{
  NOTE_DH1,NOTE_D6,NOTE_D5,NOTE_D6,NOTE_D0,
  NOTE_DH1,NOTE_D6,NOTE_D5,NOTE_DH1,NOTE_D6,NOTE_D0,NOTE_D6,
  NOTE_D6,NOTE_D6,NOTE_D5,NOTE_D6,NOTE_D0,NOTE_D6,
  NOTE_DH1,NOTE_D6,NOTE_D5,NOTE_DH1,NOTE_D6,NOTE_D0,
  
  NOTE_D1,NOTE_D1,NOTE_D3,
  NOTE_D1,NOTE_D1,NOTE_D3,NOTE_D0,
  NOTE_D6,NOTE_D6,NOTE_D6,NOTE_D5,NOTE_D6,
  NOTE_D5,NOTE_D1,NOTE_D3,NOTE_D0,
  NOTE_DH1,NOTE_D6,NOTE_D6,NOTE_D5,NOTE_D6,
  NOTE_D5,NOTE_D1,NOTE_D2,NOTE_D0,
  NOTE_D7,NOTE_D7,NOTE_D5,NOTE_D3,
  NOTE_D5,
  NOTE_DH1,NOTE_D0,NOTE_D6,NOTE_D6,NOTE_D5,NOTE_D5,NOTE_D6,NOTE_D6,
  NOTE_D0,NOTE_D5,NOTE_D1,NOTE_D3,NOTE_D0,
  NOTE_DH1,NOTE_D0,NOTE_D6,NOTE_D6,NOTE_D5,NOTE_D5,NOTE_D6,NOTE_D6,
  NOTE_D0,NOTE_D5,NOTE_D1,NOTE_D2,NOTE_D0,
  NOTE_D3,NOTE_D3,NOTE_D1,NOTE_DL6,
  NOTE_D1,
  NOTE_D3,NOTE_D5,NOTE_D6,NOTE_D6,
  NOTE_D3,NOTE_D5,NOTE_D6,NOTE_D6,
  NOTE_DH1,NOTE_D0,NOTE_D7,NOTE_D5,
  NOTE_D6,
};//这部分就是整首曲子的音符部分，用了一个序列定义为tune，整数

float duration[]=
{
  1,1,0.5,0.5,1,
  0.5,0.5,0.5,0.5,1,0.5,0.5,
  0.5,1,0.5,1,0.5,0.5,
  0.5,0.5,0.5,0.5,1,1,
  
  1,1,1+1,
  0.5,1,1+0.5,1,
  1,1,0.5,0.5,1,
  0.5,1,1+0.5,1,
  0.5,0.5,0.5,0.5,1+1,
  0.5,1,1+0.5,1,
  1+1,0.5,0.5,1,
  1+1+1+1,
  0.5,0.5,0.5+0.25,0.25,0.5+0.25,0.25,0.5+0.25,0.25,
  0.5,1,0.5,1,1,
  0.5,0.5,0.5+0.25,0.25,0.5+0.25,0.25,0.5+0.25,0.25,
  0.5,1,0.5,1,1,
  1+1,0.5,0.5,1,
  1+1+1+1,
  0.5,1,0.5,1+1,
  0.5,1,0.5,1+1,
  1+1,0.5,0.5,1,
  1+1+1+1
};



//http://hao.360.cn/  piano melody 
#define A  262
#define S  294
#define D  330
#define F  349
#define G  392
#define H  440
#define J  494
#define K  550
#define L  600



int GuangYinGuShi_melody[]={
		G,G,G,H,G,D,D,S,D,A,D,K,K,H,K,H,G,
		K,K,H,K,H,G,G,H,G,A,D,G,G,H,G,D,S,
		G,G,G,H,G,D,D,S,D,A,D,K,K,H,K,H,G,
		K,K,H,K,H,G,G,H,G,D,G,K,K,K,H,J,K,L
};


typedef struct
{
	int pitch; 
	int dimation;
}Note;
// 1			2		3		 4 			5	  		6       7
// C 			D	 	E	 	 F	 	 	G	 		A	 	B
//261.6256	293.6648   329.6276 349.2282   391.9954		440		493.8833


#define DO 262
#define RE 294
#define MI 329
#define FA 349
#define SOL 392
#define LA  440
#define SI  494
#define TIME 400
int pwmPin=9;
Note MonGood[]={
	//6.	  		  //_5		 //3		 //5	
	{LA,TIME+TIME/2}, {SOL,TIME/2},{MI,TIME},{SOL,TIME},

	//1^		   //6_		  //_5		//6-
	{DO*2,TIME},{LA,TIME/2},{SOL,TIME/2} ,{LA,2*TIME},
	// 3      //5_		//_6		   //5
	{MI,TIME},{SOL,TIME/2},{LA,TIME/2},{SOL,TIME},
	// 3	 	//1_		//_6,
	{MI,TIME},{DO,TIME/2},{LA/2,TIME/2},
	//5_		//_3		//2-		   //2.
	{SOL,TIME/2},{MI,TIME/2},{RE,TIME*2},{RE,TIME+TIME/2},
	//_3 	//5			//5_			//_6
	{MI,TIME/2},{SOL,TIME},{SOL,TIME/2},{LA,TIME/2},
	// 3		//2			//1-			//5.
	{MI,TIME},{RE,TIME},{DO,TIME*2},{SOL,TIME+TIME/2},
	//_3		//2_		//_1 		//6,_
	{MI,TIME/2},{RE,TIME/2},{DO,TIME/2},{LA/2,TIME/2},
	//_1		//5,--
	{DO,TIME/2},{SOL/2,TIME*3}

};
Note Dachangjin[]={  	
	// 2		3			3		3.				_2				1
	{RE,TIME}, {MI,TIME},{MI,TIME},{MI,TIME+TIME/2},{RE,TIME/2},{DO,TIME},
	//6,		1			2		1--				2			3			3
	{LA/2,TIME},{DO,TIME},{RE,TIME},{DO,TIME*3},{RE,TIME},{MI,TIME},{MI,TIME},
	//3.				_5			3			3			2			3
	{MI,TIME+TIME/2},{SOL,TIME/2},{MI,TIME},{MI,TIME},{RE,TIME},{MI,TIME},
	//3--		5			6			6		  6.				_5
	{MI,TIME*3},{SOL,TIME},{LA,TIME},{LA,TIME},{LA,TIME+TIME/2},{SOL,TIME/2},
	// 3		3		5				6		5---			2			3
	{MI,TIME},{MI,TIME},{SOL,TIME},{LA,TIME},{SOL,TIME*3},{RE,TIME},{MI,TIME},
	// 3		2.				_3				3		  2			3
	{MI,TIME},{RE,TIME+TIME/2},{MI,TIME/2},{MI,TIME},{RE,TIME},{MI,TIME},
	//6,		1_			  _6,			  6,-
	{LA/2,TIME},{DO,TIME/2},{LA/2,TIME/2},{LA/2,TIME*2},
	//2_		_2			2_				_1			6,
	{RE,TIME/2},{RE,TIME/2},{RE,TIME/2},{DO,TIME/2},{LA/2,TIME},
	//2_		_2			2_				_1	  		6,
	{RE,TIME/2},{RE,TIME/2},{RE,TIME/2},{DO,TIME/2},{LA/2,TIME},
	// 2		3		1			2.					_3			5
	{RE,TIME},{MI,TIME},{DO,TIME},{RE,TIME+TIME/2},{MI,TIME/2},{SOL,TIME},
	//6_		_6				6_			_5			3
	{LA,TIME/2},{LA,TIME/2},{LA,TIME/2},{SOL,TIME/2},{MI,TIME},
	//2_		_2			2_				_1			6,
	{RE,TIME/2},{RE,TIME/2},{RE,TIME/2},{DO,TIME/2},{LA/2,TIME},
	//6,		5,.					  _6,			 6,--
	{LA/2,TIME},{SOL/2,TIME+TIME/2},{LA/2,TIME/2},{LA/2,TIME*3},
	//2_		_2			2_				_1			6,
	{RE,TIME/2},{RE,TIME/2},{RE,TIME/2},{DO,TIME/2},{LA/2,TIME},
	//2_		_2			2_				_1	  		6,
	{RE,TIME/2},{RE,TIME/2},{RE,TIME/2},{DO,TIME/2},{LA/2,TIME},
	// 2		3		1			2.					_3			5
	{RE,TIME},{MI,TIME},{DO,TIME},{RE,TIME+TIME/2},{MI,TIME/2},{SOL,TIME},
	//6_		_6				6_			_5			3
	{LA,TIME/2},{LA,TIME/2},{LA,TIME/2},{SOL,TIME/2},{MI,TIME},
	//2_		_2			2_				_1			6,
	{RE,TIME/2},{RE,TIME/2},{RE,TIME/2},{DO,TIME/2},{LA/2,TIME},
	//6,		5,.					  _6,			 6,--
	{LA/2,TIME},{SOL/2,TIME+TIME/2},{LA/2,TIME/2},{LA/2,TIME*3}

};



void setup()
{
  pinMode(pwmPin,OUTPUT);
}

void loop()
{
	int i = 0;
	int n = 2;	
        for(int i=0;i<sizeof(TaLang_tune)/sizeof(TaLang_tune[0]);i++)//循环音符的次数
        {
          tone(pwmPin,TaLang_tune[i]);//此函数依次播放tune序列里的数组，即每个音符
          delay(400*TaLang_duration[i]);//每个音符持续的时间，即节拍duration，400是调整时间的越大，曲子速度越慢，越小曲子速度越快，自己掌握吧
          noTone(pwmPin);//停止当前音符，进入下一音符
        }
        delay(5000);//等待5秒
        //-----------------------------------------------------------------//
        for(int i=0;i<sizeof(tune)/sizeof(tune[0]);i++)//循环音符的次数
        {
          tone(pwmPin,tune[i]);//此函数依次播放tune序列里的数组，即每个音符
          delay(400*duration[i]);//每个音符持续的时间，即节拍duration，400是调整时间的越大，曲子速度越慢，越小曲子速度越快，自己掌握吧
          noTone(pwmPin);//停止当前音符，进入下一音符
        }
        delay(5000);//等待5秒
        //-----------------------------------------------------------------//

        for(i = 0;i<sizeof(GuangYinGuShi_melody)/sizeof(Note);i++ )
	{
		tone(pwmPin,GuangYinGuShi_melody[i]);
		delay(500); 
                noTone(pwmPin);
                //delay(5000);
	}
        //-----------------------------------------------------------------//

	for(i = 0;i<sizeof(Dachangjin)/sizeof(Note);i++ )
	{
		tone(pwmPin,Dachangjin[i].pitch);
		delay(Dachangjin[i].dimation ); 
                noTone(pwmPin);
                //delay(5000);
	}
        //-----------------------------------------------------------------//

        for(i = 0;i<sizeof(MonGood)/sizeof(Note);i++ )
	{
		tone(pwmPin,MonGood[i].pitch);
		delay(MonGood[i].dimation ); 
                noTone(pwmPin);
                //delay(5000);
	}
}

