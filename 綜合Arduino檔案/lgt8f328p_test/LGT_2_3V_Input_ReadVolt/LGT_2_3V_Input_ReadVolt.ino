
#define LED_BUILTIN 13

void setup() {
Serial.begin(1200);

}

void loop() {
  //float volt = analogRead(A0);// 1023/5=204.6
  Serial.print("volt");
  Serial.println(volt);
  /*if (614 < volt < 675.2) {
    //3.0-3.3V
    digitalWrite(13, HIGH);
    
  }*/
}
