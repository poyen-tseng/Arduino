void ISR1() {
  //butt = 1;
  Serial.println("meow");
}
//bool butt = 0;
void setup() {
pinMode(2, INPUT);
attachInterrupt(0, ISR1, LOW); //注意, 0代表的是中斷編號,不是腳位哦！D2腳位的中斷編號為0, 所以此處需放0
//用LOW比用HIGH更精準，因此D2要常接高，按按鈕對地短路
Serial.begin(9600);
}

void loop() {
 
}
