void SAYVOLT(int  NUM, int TONE) {
  if (NUM >= 5 && (NUM_REG1 != ( NUM - 4))) {
    tone(11, TONE,250);
    NUM_REG1 = NUM - 4;
    T_SAY1 = millis();

  }
  if (NUM < 5 ) {
    NUM_REG1 = NUM;
    Serial.print("NUM_REG1= ");
    Serial.println(NUM_REG1);
    Serial.print("j=");
    Serial.println(j);
  }
  if (millis() > T_SAY1 + 200) {
    T_SAY1 = millis();
    if (j < NUM_REG1) {
      j += 1;
      tone(11, TONE, 20);
      Serial.print("j=");
      Serial.println(j);
    }
    
    else {
      
      j = 0;
      NUM_REG1 = 0;
      k+=1;
      T_k = millis();
      Serial.println("CLEAR!!");
       
      }
  }
}
