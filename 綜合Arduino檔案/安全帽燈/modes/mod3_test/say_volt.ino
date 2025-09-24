int SAYVOLT(int  NUM, int TONE) {
  


  if (NUM >= 5 && (NUM_REG1 !=( NUM - 4))) {

    tone(11, TONE, 350);
    NUM_REG1 = NUM - 4;
    T_SAY1 = millis();

    Serial.println(NUM); 
    Serial.println(NUM_REG1);
    //goto A1;
  }


  if (NUM < 5) {
    NUM_REG1 = NUM;
  }

  if (millis() > T_SAY1 + 180) {
    T_SAY1 = millis();
    if (j < NUM_REG1) {
      j += 1;
      tone(11, TONE, 20);
      //goto A1;
      //Serial.println(j);
      //return 0;
    }
    else {
      j = 0;
      NUM_REG1 = 0;
      //return 1;
      //Serial.println(j);
    }
    /*   for (int i = 0; i < NUM; i++) {
            tone(11, TONE, 20);
            //delay(150);
          }
    */
  }



  /*
    if (NUM >= 5) {
    tone(11, TONE, 350);
    delay(400);
    for (int i = 0; i < NUM - 5; i++) {

      tone(11, TONE, 20);
      delay(150);

    }
  */

}
