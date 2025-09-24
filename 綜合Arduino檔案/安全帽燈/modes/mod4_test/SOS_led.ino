#define led_pin 6
unsigned long t1;

void flash1(uint16_t FRE, uint8_t  PIN, uint16_t  DUR) {

  if (millis() % FRE < 5) { //這裡用"<5"是為了增加容錯率
    digitalWrite (PIN, HIGH);
    t1 = millis();
    //Serial.println(millis());
  }
  if (millis() > t1 + DUR) {
    digitalWrite (PIN, LOW);
  }
}
void SOS_led(){
  
  between_flash = 750;
  if (T2 < millis() - between_flash) {
    switch (flash) {
      case 1: flash1(250, led_pin,  100);  Serial.println("wwwwww");        break;
      case 2: flash1(250, led_pin,  100);  Serial.println("yy");         break;
      case 3: flash1(250, led_pin,  100);                                  break;
      
      case 4: flash = 0; start_say = 0;digitalWrite (led_pin, LOW);            break;
    }
    T2 = millis();
    if (flash < 4) {
      flash += 1;
    }
  }
}
