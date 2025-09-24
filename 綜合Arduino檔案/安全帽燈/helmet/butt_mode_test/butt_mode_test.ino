
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
  
  
  
  }
  void loop() {
    
    button();

    
     
    
    
  }
    
