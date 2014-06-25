#include <Ultrasonic.h>
#include <NewSoftSerial.h>

Ultrasonic ultrasonic(7);			//定义Ultrasonic实例




void setup(){
    Serial.begin(9600);
}

int readUl(){
    int dis;
    dis = analogRead(A0);
    dis = map(dis, 0, 1023, 2, 110); 
    // dis = ultrasonic.MeasureInCentimeters();  	//得到距离
    delay(60);				 	//建议的测量周期,不然就测不准了
    return dis;					//返回距离
}

void beepingForDis(int dis1){
    int duration;
    duration = map(dis1 , 0, 50 , 20, 1500);	//因为距离已经<50了，所以只需要映射(0,50) -> (20,1500)
    tone(8,2000);				//音调
    delay(20);					//延长音时间
    noTone(8);
    delay(duration);				//延迟随着距离越近就响得越急
}

void loop()
{
    int dis1;
    while((dis1= readUl() )<50){
        beepingForDis(dis1);
    }
}

