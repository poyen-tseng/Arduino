int topleft;
int topright;
int downleft;
int downright;
int waittime = 1;

//紅線5V  棕線GND  侷限PWM

//所有程式改寫自https://www.instructables.com/DIY-Miniature-Solar-Tracker/

void setup() {
  pinMode(9, OUTPUT); //即OCR1A，控制左右
  pinMode(10, OUTPUT);//即OCR1B，控制上下
  TCCR1A = 0;
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
  TCCR1B = 0;
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
  ICR1 = 40000;
  OCR1A = 3000;
  OCR1B = 3600;

  //絕對記得要加入內部上拉電阻(下面4行)，不然自己人工外部加入也行，用外部人工加入的只是比較麻煩一些
  pinMode(A0, INPUT_PULLUP);
pinMode(A1, INPUT_PULLUP);
pinMode(A2, INPUT_PULLUP);
pinMode(A3, INPUT_PULLUP);

}


void loop() {
  topleft = analogRead(A0);
  topright = analogRead(A1);
  downleft = analogRead(A2);
  downright = analogRead(A3);

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

//訂閱Greatscott -->  https://www.youtube.com/c/greatscottlab
