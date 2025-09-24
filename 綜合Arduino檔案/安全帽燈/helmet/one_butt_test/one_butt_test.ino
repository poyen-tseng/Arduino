int curstat = 0;  //當前狀態，以供後續比較
int futtime = 0;  //未來接著要進行檢測的那個時間
int reported = 0; //已經回報過了嗎？
void setup() {
  pinMode(7, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("START!!");

}
void loop() {
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
      if(reported == 1){
        //這個綁在長按後面，用作清零
      Serial.println("fixed");
      reported = 0;
      curstat = 0;
      }
      else{
      Serial.println("short");
      curstat = 0;
      }

    }
  }
}
