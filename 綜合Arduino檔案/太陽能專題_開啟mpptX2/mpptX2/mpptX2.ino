int horizon,horizonMax,horizonMaxPosition; //horizon是即時資訊 horizonMax是歷史高點
int Xdone;  //橫向掃描完畢

int vert,vertMax,vertMaxPosition; //vert是即時資訊 horizonMax是歷史高點
int Ygogo,Ydone;  //縱向掃描開始指示,縱向掃描完畢

void setup() {
  
 Serial.begin(9600);
  pinMode(9, OUTPUT);         //即OCR1A，控制左右
  pinMode(10, OUTPUT);        //即OCR1B，控制上下
  //最後一行，A0是太陽能板訊號
  TCCR1A = 0;
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
  TCCR1B = 0;
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
  ICR1 = 40000;
  
  delay(10);
  OCR1A=6000;
  OCR1B=800;
  
}

void loop() {
  for(int t=0;t<500;t++){
      if(t>0 && t<100 && Xdone==0){      
        if(horizon>horizonMax){           //紀錄最大值的相關資訊
          horizonMax=horizon;
          horizonMaxPosition=OCR1A;
          
        }
        if (OCR1A < 1000) {             //規範舵機的極限，萬一他把自己轉爆了
        OCR1A = 1000;
        Xdone=1;
        }
        else{                           
          OCR1A = OCR1A - 20;
          horizon=analogRead(A0);
          delay(100);
        }        
      }
      delayMicroseconds(20);
    }
  
  if(Xdone==1){
    delayMicroseconds(20);
    if(OCR1A<horizonMaxPosition){
      OCR1A+=10;
    }
    else{
      Ygogo=1;
      
    }
  }
/*-----------Y--------------*/
  if(Ygogo==1){
    for(int t=0;t<500;t++){
      if(t>0 && t<100 && Ydone==0){      
        if(vert>vertMax){           //紀錄最大值的相關資訊
          vertMax=vert;
          vertMaxPosition=OCR1B;
        }
        if (OCR1B > 2000) {             //規範舵機的極限，萬一他把自己轉爆了
        OCR1B = 2000;
        Ydone=1;
        }
        else{                           
          OCR1B = OCR1B + 20;
          delay(150);
          vert=analogRead(A0);
        } 
       }
      
    }

    if(Ydone==1){Serial.println(OCR1B);
      if(OCR1B > vertMaxPosition+42){
        OCR1B-=20;                        //調整垂直舵機位置到最亮的那個地方
      }
      if(OCR1B<vertMaxPosition){
        OCR1B+=20;
        
      }
    }
  }
 }

/*
//------------------這個區塊控制左右轉---------------------
  if (topleft > topright) {
    OCR1A = OCR1A + 1;
    delay(waittime);
  }
  if (downleft > downright) {
    OCR1A = OCR1A + 1;
    delay(waittime);
  }
  if (topleft < topright) {
    OCR1A = OCR1A - 1;
    delay(waittime);
  }
  if (downleft < downright) {
    OCR1A = OCR1A - 1;
    delay(waittime);
  }
  if (OCR1A > 4000) {
    OCR1A = 4000;
  }
  if (OCR1A < 2000) {
    OCR1A = 2000;
  }


//------------------這個區快控制上下轉-----------------  
  if (topleft > downleft) {
    OCR1B = OCR1B - 1;
    delay(waittime);
  }
  if (topright > downright) {
    OCR1B = OCR1B - 1;
    delay(waittime);
  }
  if (topleft < downleft) {
    OCR1B = OCR1B + 1;
    delay(waittime);
  }
  if (topright < downright) {
    OCR1B = OCR1B + 1;
    delay(waittime);
  }
  if (OCR1B > 4200) {
    OCR1B = 4200;
  }
  if (OCR1B < 3000) {
    OCR1B = 3000;
  }

}
*/
