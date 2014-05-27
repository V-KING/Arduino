
/*
 * Lini Mestar 
 * Matt Remick for Taylor Series & Cordic method Functions
 * Calculator Mathematical Association of America Spring 2013
 * Version 1.0c
 * THIS VERSION  + - * / Tsin Tcos Tsin Csin Ccos Ctan log10 sqrt
 * FIXED: COMPUTES PI BY PRESSING THE (*) BUTTON
 - KNOWN BUG: DOESN'T WORK WITH TANGENT
 * FIXED: TAKE MORE THAN 4 DIGITS (MAX IS 10)
 * FIXED: NO MORE "JUMP" FOR USER
 * FIXED: CHECKS FOR VALID INPUT( NO INPUT)
 * FIXED: AFTER #, DOES NOT BLINK UNTIL NEW OPERATION
 * FIXED: DEBOUNCING KEYS
 * FIXED: DOES NOT OUTPUT (-) VALUES
 * FIXED: PRECISION lcd.print(1.23456, 4) gives "1.2346"
 * FIXED: DOES NOT SHOW TIME TOOK TO COMPLETE
 * FIXED: DOES NOT USE EXTRA PINS
 * FIXED: THIS VERSION DOES NOT WORKING WITH A,B,C & D
 * FIXED: BUTTON BOUNCING
 * FIXED: SHOWING 122 INSTEAD 12
 */

//Libraries
#include <LiquidCrystal.h>

//LCD Hookups
#define RS 10
#define EN 11
#define D4 2
#define D5 3
#define D6 4
#define D7 5


//delay op showing
#define DELAY 3000
#define QHOLD 2000

//LCD Setup
LiquidCrystal lcd(EN, RS, D7, D6, D5, D4);



boolean beenHere=false,
opAddition=false, opSubtract=false, 
opMultiply=false, opDivide=false,
opCsin=false, opCcos=false, opCtan=false,
opTsin=false, opTcos=false, opTtan=false,
opNLog=false, opLogBTen=false, opSQRT=false, opE=false;

boolean piee = false;

//Time Setup
unsigned long T0, T1;

//Calculator constants
const double pi = 3.14159265358979323846;
const double e  = 2.718281828459045;
int counter = 0;
int keepTrack = 0;

//Numbers Inputed
int long num1=0, num2=0;
int long num3=0;





void options(){
  lcd.setCursor(1,0);
  lcd.print("  A)ADD  C)MULTIPY  B1)Tsin");
  lcd.setCursor(1,1);
  lcd.print("  B)SUB. D)DIVIDE   B6)Csin");
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("  B2)Tcos  B3)Ttan  B4)Log(  B5)");
  lcd.write(8);
  lcd.print("(");
  lcd.setCursor(1,1);
  lcd.print("  B7)Ccos  B8)Ctan    *B=BUTTON*");
}  //options

void sum(){
  T0 = millis();
  double sum=num1+num2;
  T1 = millis();
  lcd.print(sum,0);
  delay(DELAY);
}  //sum

void subtract(){
  T0 = millis();
  double dif=num1-num2;
  T1 = millis();
  lcd.print(dif,0);
  delay(DELAY);
}  //subtract

void multiply(){
  T0 = millis();
  double prod=num1*num2;
  T1 = millis();
  lcd.print(prod,0);
  delay(DELAY);
}  //multiply

void divide(){
  T0 = millis();
  float blah=double(num1)/double(num2);
  T1 = millis();
  lcd.print(blah,4);
  delay(DELAY);
}  //divide


void setup(){
  Serial.begin(9600);
  lcd.write(6);//红桃k
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.blink();
}  //setup


void loop()
{
  // char key = keypad.getKey();
  /******************************
   * KEYPAD READING W/ DEBOUNCING
   *******************************/
  if(key != NO_KEY){
    if((key !='*')&&(key !='#')&&(key !='A')
      &&(key !='B')&&(key !='C')&&(key !='D'))
    {
      if(!beenHere){
        num1 = (num1*10) + int(key-'0');
        lcd.setCursor(0,0);
        lcd.print(num1);
        counter++;
      }
      else if(beenHere){
        num2 = (num2*10) + int(key-'0');
        lcd.setCursor(counter+1,0);
        lcd.print(num2);
        keepTrack++;
      }
    }
    else if(key=='A'){
      lcd.print("+");
      beenHere=true;
      opAddition=true;
    }
    else if (key=='B'){
      lcd.print("-");
      beenHere=true;
      opSubtract=true;
    }
    else if (key=='C'){
      lcd.print("*");
      beenHere=true;
      opMultiply=true;
    }
    else if (key=='D'){
      lcd.print("/");
      beenHere=true;
      opDivide=true;
    }
    else if (key=='*'){
      lcd.write(9);
      piee=true;
      if( (beenHere && opTsin)
        || (beenHere && opTcos) 
        || (beenHere && opCtan)
        || (beenHere && opCcos)
        || (beenHere && opCsin)
        || (beenHere && opTtan) )
      {
        num3*=pi;
      }
      else if( 
      (beenHere && opNLog)
        ||  (beenHere && opE)
        ||  (beenHere) 
        ||  (beenHere && opSQRT)
        ||  (beenHere && opLogBTen) )
      {
        num2*=pi;
      }
    }
    else if(key=='#'){
      if(keepTrack == 0){
        lcd.noBlink();
        lcd.setCursor(0,1);
        lcd.print(" bad input ");
        lcd.write(10);
        delay(QHOLD);
        goto endThis;
      }
      else{
        lcd.noBlink();
        lcd.print("=");
        lcd.setCursor(0,1);
        if(opAddition){
          sum();
        }
        else if(opSubtract){
          subtract();
        }
        else if(opMultiply){
          multiply();         
        }
        else if(opDivide){
          divide();
        }
endThis:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.blink();
        num1= num2= num3= 0;
        beenHere=false;
        opAddition= opSubtract= false;
        opMultiply=opCsin= false;
        opDivide=opCcos=false;
        opTtan=opTsin=opTcos=opCtan= false;
        opNLog=opLogBTen=opSQRT=opE=false;
        piee=false;
        counter=0;
        keepTrack=0;
      }  //blahere
    }
    /***************************************
     * EXTERNAL BUTTON READING W/ DEBOUNCING
     ****************************************/
  }
}  //loop


