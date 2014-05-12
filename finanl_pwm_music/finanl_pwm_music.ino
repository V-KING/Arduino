/*
 *pin 9作为pwm输出，连接蜂鸣器的正极
 *蜂鸣器的负极-->电阻(510欧姆)-->GND
 * */
//定义结构体，pitch表示频率，dimation表示该频率持续的时间
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
#define TIME 400    //这里表示的是一个节拍,dimation是含有TIME
int pwmPin=9;
//世上只有妈妈好
Note InTheWorldMontherIsGood[]={
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
//大长今主题曲
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
	pinMode(pwmPin,OUTPUT);							//放音乐肯定是要输出的
}

void loop()
{
	int i = 0;
	int n = 2;	

//	for(i = 0;i<sizeof(Dachangjin)/sizeof(Note);i++ )//循环音符的次数
//	{
//		tone(pwmPin,Dachangjin[i].pitch);			 //Dachangjin[i]是结构体Note类型的，Dachangjin[i].pitch是频率，即每个音符
//		delay(Dachangjin[i].dimation );	 			 //每个音符持续的时间，即节拍dimation
//		noTone(pwmPin);					 			 //停止当前音符，进入下一音符
//	}

	for(i = 0;i<sizeof(InTheWorldMontherIsGood)/sizeof(Note);i++ )
	{
                //tone(pwmPin,InTheWorldMontherIsGood[i].pitch*1);
                tone(pwmPin,InTheWorldMontherIsGood[i].pitch*2);
		//tone(pwmPin,InTheWorldMontherIsGood[i].pitch*3);
		delay(InTheWorldMontherIsGood[i].dimation ); 
		noTone(pwmPin);
		
	}
}

