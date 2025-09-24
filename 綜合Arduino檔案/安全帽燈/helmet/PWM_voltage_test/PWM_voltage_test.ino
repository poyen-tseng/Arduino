//PWM電壓模擬測試 普通版
void setup() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
Serial.begin(9600);
}

void loop() {
  analogWrite(5, 102);//應是正好2V  1.89V
  analogWrite(6, 103);//2.0196V 1.9V
  analogWrite(9, 204);//4V  3.77V
  analogWrite(10, 205);//4.0196V  3.79V
  //analogWrite(11, 206);//4.0392V  3.81V
  analogWrite(11, 255);//5V
  Serial.println(analogRead(A0));//718
  //Serial.println(analogRead(A0)/255*5);

}
