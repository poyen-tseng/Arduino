void button(){
  
  
  if (digitalRead(2) == HIGH){  butt = 1; }
    else butt = 0;
  if ((butt == 1) && (curstat == 0)&&(reported ==0)) {
        //確認之前沒有按過，啟動感知程序
        prstime = millis();
        futtime = millis() + 600; //0.6秒
        curstat = 1;
      }
    if ((butt == 0) && (curstat == 1) && (millis() < futtime)&&(reported == 0)) {
      interval = 1; //期間內有中斷發生
      //Serial.println(interval); //換行，表示資料有在更新
      }
    if ((butt == 1) && (interval == 1) && (millis() < futtime)&&(reported == 0) ) {
      //發現按下，而且之前有按過，中間還有間隔，這是連2按!!
      //Serial.println("double press");
      reported = 1 ;
      interval = 0;
      curstat = 0;
      mode(2);
      }
    if ((curstat == 1) && (millis() == futtime) && (interval == 0) &&(reported == 0) ) {
      //有觸發&&時間到&&沒有中斷，這是長按!!
      /*Serial.println("long press");*/
      interval = 0 ;
      reported = 1;
      mode(3);
      
    }
    if ((curstat == 1) && (millis() == futtime) && (interval == 1) &&(reported == 0) ) {
      //有觸發&&時間到&&有中斷，這是單按!!
      //Serial.println("single press");
      attachInterrupt(0, digitalInterrupt, FALLING); 
      Serial.println("!!");
      interval = 0 ;
      reported = 1;
      mode(1);
      //sleep = !sleep;
      
      Serial.println("1");
      
      ADCSRA &= ~(1 << 7);
      //ENABLE SLEEP - this enables the sleep mode
      SMCR |= (1 << 2); //power down mode
      SMCR |= 1;//enable sleep
      MCUCR |= (3 << 5); 
      MCUCR = (MCUCR & ~(1 << 5)) | (1 << 6); 
      __asm__  __volatile__("sleep");
      
    
      
    }
    if(millis() > futtime){
      reported = 0;
    }
    if ((butt == 0) && (curstat == 1) && (millis() > futtime)) {
      curstat = 0;//curstat工作結束，下台鞠躬 (讀取LOW是為了避免是按鈕長按太久)
    }
}
