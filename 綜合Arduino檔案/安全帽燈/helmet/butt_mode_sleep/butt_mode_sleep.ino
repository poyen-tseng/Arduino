bool sleep=0;
uint8_t mod=1 , mod1=0 , mod2=0 , mod3=0 , mod4=0;
//uint8_t inp=0; //作為輸入儲存器 1短 2連擊 3長按
  bool butt = 0; //按鈕狀態
  unsigned long prstime = 0;  //按下按鈕的時間
  bool interval = 0; //1秒內有間隔嗎? 0為沒有間隔
  unsigned long futtime = 0;  //未來接著要進行檢測的那個時間
  bool curstat = 0;  //當前狀態，以供後續比較
  bool reported = 0; //避免重複報告

  void setup() {
  Serial.begin(9600);
  Serial.println("START!!");
  pinMode(7, INPUT);//按鈕
  pinMode(2, INPUT);
  pinMode(6, OUTPUT);
  //attachInterrupt(0, digitalInterrupt, FALLING); 
  //interrupt for waking up
  /*
  //SETUP WATCHDOG TIMER
  WDTCSR = (24);//change enable and WDE - also resets
  WDTCSR = (33);//prescalers only - get rid of the WDE and WDCE bit
  WDTCSR |= (1<<6);//enable interrupt mode

  //Disable ADC - don't forget to flip back after waking up if using ADC in your application ADCSRA |= (1 << 7);
  ADCSRA &= ~(1 << 7);
  */
  /*
  //ENABLE SLEEP - this enables the sleep mode
  SMCR |= (1 << 2); //power down mode
  SMCR |= 1;//enable sleep
  */
  }
  void loop() {
    if (digitalRead(7)==HIGH){
      digitalWrite(6,HIGH);
    }
    else digitalWrite(6,LOW);
    button();
    /*
    digitalWrite(6, HIGH);
    delay(800);
    digitalWrite(6, LOW);
    delay(800);
    */
   // Serial.print(millis());

    if(sleep==1){
      //Serial.println("!!");
      /*
     //BOD DISABLE - this must be called right before the __asm__ sleep instruction
    MCUCR |= (3 << 5); 
    //set both BODS and BODSE at the same time
    
    MCUCR = (MCUCR & ~(1 << 5)) | (1 << 6); 
    //then set the BODS bit and clear the BODSE bit at the same time
    
    __asm__  __volatile__("sleep");
    //in line assembler to go to sleep
    */
    }
    
  }
void digitalInterrupt(){
  //needed for the digital input interrupt
  Serial.println("5");
  //detachInterrupt(0);
}

ISR(WDT_vect){
  //Serial.println("6");
  //DON'T FORGET THIS!  Needed for the watch dog timer.  This is called after a watch dog timer timeout - this is the interrupt function called after waking up
}// watchdog interrupt
