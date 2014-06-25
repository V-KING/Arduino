/*
 * ====================================================
 *      Name: ul2.ino 
 *   Version: 1.0
 *  Compiler: Arduino-IDE
 *   Company: WWW.SOGWORKS.CN
 *  Function: 超声波距离LCD显示
 * =====================================================
 * */
#include <LiquidCrystal.h>    //添加液晶库
#include <Ultrasonic.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//定义液晶对象，采用最简单接法
Ultrasonic ultrasonic(7);

 void setup(){
   lcd.begin(16,2);
}
void loop()
{
  int dis = ultrasonic.MeasureInCentimeters();    //得到距离
  delay(60);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("The distance:");
  lcd.setCursor(0,1) ;
  lcd.print(dis);
  lcd.setCursor(5,1) ;  
  lcd.print("CM");
}


void dispAccordingTo(unsigned long distance)
{
  if(distance < 10){         //(0,10)
    //1
  }
  else if(distance < 100){      //(10,100)
    //2
  }
  else if(distance < 1000){    //(100,1000)
    //
  }
  else if(distance < 250034){   //(1000,250034)
    //放开的
  }
  else{               //(250034,无穷大)

  }
}
   
