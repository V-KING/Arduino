//中音
#define D0 -1
#define D1 294
#define D2 330
#define D3 350
#define D4 393
#define D5 441
#define D6 495
#define D7 556
//低音
#define DL1 147
#define DL2 165
#define DL3 175
#define DL4 196
#define DL5 221
#define DL6 248
#define DL7 278
//高音
#define DH1 589
#define DH2 661
#define DH3 700
#define DH4 786
#define DH5 882
#define DH6 990
#define DH7 112

//以上部分是定义是把每个音符和频率值对应起来，其实不用打这么多，但是都打上了，后面可以随意编写D调的各种歌，我这里用NOTE_D+数字表示音符，NOTE_DH+数字表示上面有点的那种音符，NOTE_DL+数字表示下面有点的那种音符。这样后面写起来比较好识别。
#define WHOLE 1			//全拍
#define HALF 1/2		//半拍
#define QUARTER 1/4		//四分之一拍
#define EIGHTH 1/8		//八分之一拍
#define SIXTEENTH 1/16	//十六分之一拍
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
}
