void force_beep(){
if (digitalRead(2) == HIGH && (t % 30 == 0 || t % 30 == 3)) {
    //定義蜂鳴器模式
    digitalWrite (11, HIGH);
  }
  if (digitalRead(2) == HIGH && (t % 30 == 1 || t % 30 == 4)) {
    //定義蜂鳴器模式
    digitalWrite (11, LOW);
  }
}
