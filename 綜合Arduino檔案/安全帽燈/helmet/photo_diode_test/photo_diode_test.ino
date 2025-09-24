/*
 * 這個測試使用了光敏二極體作為感測器，使用內部參考，因為光敏二極體能"發"的電不多，甚至使用三用電表都會奪走太多能量
 */


void setup() {
  analogReference(INTERNAL); //偵測電壓，用內部1.1V (實際1.8V)//LGT默認為1.1V，EASY~
  Serial.begin(115200);
  //pinMode(A2, INPUT_PULLUP);
  
}

void loop() {
  Serial.println(analogRead(A2));
  delay(100);
}

/*實驗結果
 * 410電燈全關，用毛巾包住
 * 450、460算是傍晚
 * 480就很亮了
 * 800手電筒(50000LUX)
 * 
 * 
 */
