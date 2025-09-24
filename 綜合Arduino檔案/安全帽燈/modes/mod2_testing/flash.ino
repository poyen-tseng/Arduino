void flash1(uint16_t FRE, uint8_t  PIN, uint16_t  DUR) {

  if (millis() % FRE < 5) {
    digitalWrite (PIN, HIGH);
    t1 = millis();
    //Serial.println(millis());
  }
  if (millis() > t1 + DUR) {
    digitalWrite (PIN, LOW);
  }
}

void flash2(uint16_t FRE, uint8_t  PIN, uint16_t  DUR) {

  if (millis() % FRE == 0) {
    digitalWrite (PIN, HIGH);
    t2 = millis();
    //Serial.println(millis());
  }
  if (millis() == t2 + DUR) {
    digitalWrite (PIN, LOW);
  }
}
void flash3(uint16_t BIGFRE,uint16_t HOWMANY,uint16_t SMALLFRE, uint8_t  PIN, uint16_t  DUR){
if ((millis() % BIGFRE < HOWMANY) && (millis() % BIGFRE) % SMALLFRE < 5) {
      digitalWrite (PIN, HIGH);
      t3 = millis();
    }
    if (millis() > t3 + DUR) {
      digitalWrite (PIN, LOW);
    }
}
