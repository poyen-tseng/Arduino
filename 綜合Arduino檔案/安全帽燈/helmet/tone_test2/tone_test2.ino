long T_BZ = 0;
bool beeped = 0;
bool beeped3 = 0;
bool beeped2 = 0;
void setup() {
  pinMode(2, INPUT);
  pinMode(7, INPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(9) == HIGH) {
    tone(11, 5000, 70);
    tone(11, 500, 100);
  }
  if (digitalRead(10) == HIGH) {
    tone(11, 200, 70);
    tone(11, 3000, 100);
  }
  /*如上把2個tone黏起來可以製造滑音



     如下短音要用20， 下下是連2音
  */
  if (digitalRead(7) == HIGH && beeped == 0) {
    tone(11, 6500, 200);
    beeped = 1;
  }
  if (digitalRead(2) == HIGH && beeped2 == 0) {
   // Serial.println("1");
    if (T_BZ < millis() && beeped3 == 0) {
      tone(11, 5000, 10);
      T_BZ = millis() + 900;
      //Serial.println("2");
      beeped3 = 1;
    }
    if (T_BZ - 200 < millis() ) {
      tone(11, 4500, 15);
      //Serial.println("3");
      beeped3 = 0;
    }
    beeped2 = 1;
    Serial.print(T_BZ);
    Serial.println("4");
    
  }
  delay(300);
  beeped = 0;
  
  beeped2 = 0;
  //T_BZ = millis();

  /*
    delay(1000);*/


  /*
      if ((millis() - T_BZ) > 200 && beeped == 0) {
        tone(11, 7000, 130);
        T_BZ = millis();
        beeped = 1;
      }
      if (millis() - T_BZ > 600 && beeped == 1) {
        noTone(11);

        beeped = 0; tone(11, 5000, 100);
      }
  */


}
