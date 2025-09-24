void volt_loop() {
if (t % 30 == 0) {
    //每 秒檢查一次電壓  
    v = 5.0 * analogRead(A0) / 1023;
    //定義低電壓警示
    if (3.7 < v) {
      //高電量
      digitalWrite (12, LOW);
    }
    if ((3.2 < v && v < 3.7) && (t % 40 == 0)) {
      //中電量 亮
      digitalWrite (12, HIGH);
      if (b == 2) {
        b = 1;
        low_power()
      }
    }
    if (3.2 < v && v < 3.7  && t % 40 == 4) {
      //中電量 暗
      digitalWrite (12, LOW);
    }
    if (v < 3.2  && t % 10 == 0) {
      //低電量 亮
      digitalWrite (12, HIGH);
      if (b == 1 || b == 2) {
        b = 0;
        no_power();
        tone(11, 180, 150);
      }
    }
    if (v < 3.2  && t % 10 == 2) {
      //低電量 暗
      digitalWrite (12, LOW);
    }
  }
}
  
