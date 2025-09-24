#include <avr/sleep.h>;
void setup() {
  noInterrupts();
  CLKPR = 1 << CLKPCE;   
  CLKPR = 8;// 將CPU速度設定為 16MHz / 256   
  interrupts(); 
  //bitSet(DDRD, 6); 
  DDRD = DDRD | B11111100;
}

void loop() {  
  //bitSet(PORTD, 6); // 翻轉   
  PORTD = B00000000;
  delay(4);// CPU慢了256倍，所以延遲時間為 4ms 
  PORTD = B01000000;
  delay(4);
}
