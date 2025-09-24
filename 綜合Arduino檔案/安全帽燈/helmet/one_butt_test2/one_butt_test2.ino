unsigned long prstime = 0;  //按下按鈕的時間
bool interval = 0; //1秒內有間隔嗎? 0為沒有間隔
unsigned long futtime = 0;  //未來接著要進行檢測的那個時間
bool curstat = 0;  //當前狀態，以供後續比較
bool reported = 0; //避免重複報告


/*int curstat = 0;  //當前狀態，以供後續比較
  int futtime = 0;  //未來接著要進行檢測的那個時間
  int reported = 0; //已經回報過了嗎？
*/
  void setup() {
  pinMode(7, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("START!!");

  }
  void loop() {
    
    if (millis() % 10000 == 0) {
      //Serial.println(); //換行，表示資料有在更新
    }


    if ((digitalRead(7) == HIGH) && (curstat == 0)&&(reported ==0)) {
      
              
        //確認之前沒有按過，啟動感知程序
        prstime = millis();
        futtime = millis() + 600; //0.6秒
        curstat = 1;
      

    }

    if (digitalRead(7) == LOW && (curstat == 1) && (millis() < futtime)&&(reported == 0)) {
      interval = 1; //期間內有中斷發生
      //Serial.println(interval); //換行，表示資料有在更新
      
    }
    if (digitalRead(7) == HIGH && (interval == 1) && (millis() < futtime)&&(reported == 0) ) {
      //發現按下，而且之前有按過，中間還有間隔，這是連2按!!
      //Serial.print(reported);
      //Serial.println(interval);
      //Serial.println(millis());
      //Serial.println(futtime);
      Serial.println("double press");
      reported = 1 ;
      interval = 0;
      curstat = 0;
      //Serial.print(reported);
      //Serial.println(interval);
      
    }
    if ((curstat == 1) && (millis() == futtime) && (interval == 0) &&(reported == 0) ) {
      //有觸發&&時間到&&沒有中斷，這是長按!!
      Serial.println("long press");
      interval = 0 ;
      reported = 1;
    }
    if ((curstat == 1) && (millis() == futtime) && (interval == 1) &&(reported == 0) ) {
      //有觸發&&時間到&&有中斷，這是單按!!
      Serial.println("single press");
      interval = 0 ;
      reported = 1;
    }
    if(millis() > futtime){
      reported = 0;
    }
    if (digitalRead(7) == LOW && (curstat == 1) && (millis() > futtime)) {
      curstat = 0;//curstat工作結束，下台鞠躬 (讀取LOW是為了避免是按鈕長按太久)

    }

  }



//------------------------------------
/*
  for (int i = 0; i < 1000; i++) {
    delay(100); //檢測頻率不用太高，浪費資源
    if (i == 999) {
      Serial.println(); //換行，表示資料有在更新
    }
    if (digitalRead(7) == HIGH) {
      if (curstat == 1 && i == futtime && reported == 0) {
        //如果前面已經是high，而且還沒回報過
        Serial.println("long");
        curstat = 0;
        reported = 1;
      }
      if (curstat == 0) {
        //前面沒有回報過，做個紀錄，之後再來看看
        futtime = i + 5;
        curstat = 1;
      }

    }
    if ((digitalRead(7) == LOW) && curstat == 1 ) {
      if (reported == 1) {
        //這個綁在長按後面，用作清零
        Serial.println("fixed");
        reported = 0;
        curstat = 0;
      }
      else {
        Serial.println("short");
        curstat = 0;
      }

    }
  }
*/
