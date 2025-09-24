void setup() {
 Serial.begin(115200);
 //while (!Serial) { ;}
}
void loop() {
 float voltage = 5.0*analogRead(A0)/1023;
 Serial.println(voltage,2);
 delay(100);
 Serial.flush();
} 
