#include <PS2X_lib.h>  //for v1.6
#include <Servo.h>
#include <notes.h>
PS2X ps2x;
int PS2 = 0; 
Servo LXservo;
int headlight = 0 ; //指示車燈的狀態
int bright = 5 ;    //指示車燈的明暗度

int buzzerpin = 9 ; //定義蜂鳴器腳位
int poliz = 0 ;    //是否為警車的狀態
int i=0 ;

int Time = 0; //喔伊喔伊
int BuzzB = 0; //喔伊喔伊 
int mode = 0; //喔伊喔伊

int servoADJ = 0;     //用來彌補機械上的偏差
int servoAMP = 0 ;    //用來縮放轉彎的程度

const int in1 = 2;    // direction pin 1
const int in2 = 4;    // direction pin 2
const int ena = 3;    // PWM pin to change speed

unsigned long previousMillis = 0;
const long interval = 500; //可自變 

int fspeed;           // forward speed 

void setup(){
  LXservo.attach(6);
  PS2 = ps2x.config_gamepad(13,11,10,12, true, true);   //Настройка выводов: (clock, command, attention, data, true, true)
  pinMode(in1, OUTPUT);      // connection to L298n
  pinMode(in2, OUTPUT);      // connection to L298n
  pinMode(ena, OUTPUT);      // connection to L298n
  pinMode(8, OUTPUT);   // 車燈(舊)
  pinMode(9, OUTPUT);   // 嗶嗶貓(蜂鳴器)
  pinMode(5, OUTPUT);   // 車燈
  pinMode(1, OUTPUT);   // Поворот на лево
  pinMode(7, OUTPUT);   // Поворот на право
}



void loop(){
  ps2x.read_gamepad();
 
  if(ps2x.ButtonPressed(PSB_R1) & bright < 5){
    headlight = 0;
    bright += 1;
    if(headlight==0){
    analogWrite(5, 5+50*bright );
    headlight = 1;
    }
  } //將車燈變亮

  if(ps2x.ButtonPressed(PSB_R2) & bright > 0){
    headlight = 0;
    bright -= 1;
    if(headlight==0){
    analogWrite(5, 5+50*bright );
    headlight = 1;
    }
  } //將車燈變暗
  
  if(ps2x.ButtonPressed(PSB_TRIANGLE)) {
    if(headlight==0){
    analogWrite(5, 5+50*bright );
    headlight = 1;
    }
    else{
    analogWrite(5, 0 );
    headlight = 0;
    }
    
  } //車燈的開關
  
  
  // if(ps2x.ButtonPressed(PSB_CROSS)) digitalWrite(5, LOW);
     
  if(ps2x.ButtonPressed(PSB_CIRCLE)) {
  tone (9,500) ;
  }  //按下喇叭
  
   if(ps2x.ButtonReleased(PSB_CIRCLE)) {
   noTone(9) ;
  }  //放開喇叭

  if(ps2x.ButtonPressed(PSB_SQUARE)) {
    if (BuzzB==0){   //開始喔伊
      BuzzB=50;
      mode=1;
      tone(9,700);
    }
    else{         //關閉喔伊
      BuzzB=0;
      noTone(9);
      }
  }
          
Time=Time+BuzzB; //主要的喔伊區塊
 if (Time==1600 ){
 Time=0;
 if(mode==1){
  mode=2;
  tone (9,1000);
 }
else{
  mode=1;
  tone(9,700);
  }
   
 }   //連環喔伊到這裡

  /*if(ps2x.ButtonPressed(PSB_CROSS)){      //警車的鳴笛
    if(poliz<=100){
    for(i=0;i<10;i++){
      poliz+=5;
      tone(9,600+7*poliz,50);
      delay(20);
    }
  }
  
  if(poliz>=100) 
    for(i=0;i<10;i++){
      poliz-=5;
      tone(9,600+7*x,50);
      delay(20);
    }
  }*/  //警車的鳴笛
   
 // if(ps2x.ButtonPressed(PSB_R1)) digitalWrite(7, HIGH);
  // if(ps2x.ButtonPressed(PSB_R2)) digitalWrite(7, LOW);
 
  if (ps2x.Analog(PSS_LY) == 128) analogWrite(ena, 0); //平常不動
  

  if (ps2x.Analog(PSS_LY) > 128){  //前進！！！
    fspeed = map(ps2x.Analog(PSS_LY), 129, 255, 0, 255);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(ena, fspeed);
   // digitalWrite(9, HIGH);

  }
  
  if (ps2x.Analog(PSS_LY) < 128){   //後退！！
    fspeed = map(ps2x.Analog(PSS_LY), 0, 127, 255, 0);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(ena, fspeed);
    //digitalWrite(9, LOW);  //舊的倒退車燈
  }
  
  LXservo.write(map(ps2x.Analog(PSS_RX), 0, 255,  65 + servoADJ - servoAMP ,  105 + servoADJ + servoAMP ) ); 
   //這是轉向器的輸出部分
   
    if (ps2x.Analog(PSS_RX) < 120){
    digitalWrite(1, HIGH);
    digitalWrite(7, LOW);
          
  }
  
    if (ps2x.Analog(PSS_RX) > 150){
    digitalWrite(7, HIGH);
    digitalWrite(1, LOW);
  }  
  
    if (ps2x.Analog(PSS_RX) > 120 && ps2x.Analog(PSS_RX) < 150){
    digitalWrite(1, LOW);
    digitalWrite(7, LOW);
  }

    if(ps2x.ButtonPressed(PSB_PAD_RIGHT) & servoADJ < 40 ){
     servoADJ += 5 ;
       }   // 舵機向右微調的基數

    if(ps2x.ButtonPressed(PSB_PAD_LEFT) & servoADJ > -40 ){
     servoADJ -= 5 ;
      
    }   // 舵機向左微調的基數

    if(ps2x.ButtonPressed(PSB_PAD_DOWN) & servoAMP > -20 ){
     servoAMP -= 5  ;
     tone(9,20*(servoAMP+50),100);
    }
      // 舵機轉動倍率減少

    if(ps2x.ButtonPressed(PSB_PAD_UP) & servoAMP < 30 ){
     servoAMP += 5  ;
     tone(9,20*(servoAMP+50),100);
     }
        // 舵機轉動倍率增加

    if(ps2x.ButtonPressed(PSB_L1) ){
     servoADJ = 0  ;
     servoAMP = 0  ;
      tone(9,2000,100) ; 
      
    }   // 歸零
  delay(10);  //整個程式的刷新速度，會影響喔伊
}    
