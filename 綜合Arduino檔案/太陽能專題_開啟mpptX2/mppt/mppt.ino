int horizon,horizonMax,horizonMaxPosition; //horizon是即時資訊 horizonMax是歷史高點
int Xdone;

void setup() {
  horizon=horizonMax=horizonMaxPosition=0;
  pinMode(9, OUTPUT);         //即OCR1A，控制左右
  pinMode(10, OUTPUT);        //即OCR1B，控制上下
  TCCR1A = 0;
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
  TCCR1B = 0;
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
  ICR1 = 40000;
  for(int i=0;i<100;i++){
    if(OCR1A < 6100){
      OCR1A+=50;                      //初始左右舵機位置
    }
    else if(OCR1A > 6200){
      OCR1A-=50;                       //初始左右舵機位置
    }
    else break;
  delayMicroseconds(50);
  }
  OCR1B=1000;
  //Serial.begin(9600);
  //horizonMaxPosition==0;
}

void loop() {
  
  for(int t=0;t<3000;t++){
    if(t>0 && t<100 && Xdone==0){      
      if(horizon>horizonMax){           //紀錄最大值的相關資訊
        horizonMax=horizon;
        horizonMaxPosition=OCR1A;
      }
      
      if (OCR1A < 1000) {
      OCR1A = 1000;
      Xdone=1;
      }
      else{                           //規範舵機的極限，萬一他把自己轉爆了
        OCR1A = OCR1A - 20;
        horizon=analogRead(A0);
      }
      
/*這裡摺疊了 Serial.Print
      Serial.print("horizon=");
      Serial.print(horizon);

      Serial.print(" horizonMax=");
      Serial.print(horizonMax);

      Serial.print(" position=");
      Serial.print(OCR1A);
      
      Serial.print(" horizonMaxPosition=");
      Serial.println(horizonMaxPosition);
   */   
      
    }
    delayMicroseconds(20);
  }
  
  if(Xdone==1){
    delay(30);  
    if(OCR1A > horizonMaxPosition+42){
      OCR1A-=30;                        //調整水平舵機位置到最亮的那個地方
      
    }
    if(OCR1A<horizonMaxPosition){
      OCR1A+=30;
    
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
