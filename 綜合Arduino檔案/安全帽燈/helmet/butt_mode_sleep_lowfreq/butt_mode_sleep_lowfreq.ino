uint8_t mod = 1 , mod1 = 0 , mod2 = 0 , mod3 = 0 , mod4 = 0;

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
  
  noInterrupts();
  CLKPR = 1 << CLKPCE;   
  CLKPR = 0;// 將CPU速度設定為 16MHz    
  interrupts(); 
  
}
void loop() {
  if (digitalRead(7) == HIGH) {
    tone(6,21000,1000);
  }
  else digitalWrite(6, LOW);
  button();
  
  

}
void digitalInterrupt() {
  //needed for the digital input interrupt
  Serial.println("5");
  noInterrupts();
  CLKPR = 1 << CLKPCE;   
  CLKPR = 0;// 將CPU速度設定為 16MHz / 256   
  interrupts(); 
  
}
