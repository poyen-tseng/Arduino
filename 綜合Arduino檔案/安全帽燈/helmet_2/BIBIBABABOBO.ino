/*-----
 * 僅做音頻的測試與紀錄
 * 
 * 
 */

void low_power() {
  tone(11, 2800, 100);
  delay(180);
  tone(11, 1000, 100);
  delay(150);
  tone(11, 250, 100);
}
void no_power() {
  tone(11, 2800, 100);
  delay(150);
  tone(11, 2800, 100);
  delay(150);
  tone(11, 1000, 100);
  delay(180);
  tone(11, 1000, 100);
  delay(180);
  tone(11, 250, 150);
  delay(220);
  tone(11, 250, 150);
  delay(350);
  tone(11, 200, 150);
  delay(350);
  tone(11, 200, 150);
  delay(450);
  tone(11, 180, 150);
}
