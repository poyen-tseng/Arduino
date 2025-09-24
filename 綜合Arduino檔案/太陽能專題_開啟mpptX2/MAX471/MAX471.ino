/*pinout describe
    Vout 太陽能板
    Vin  電池、負載
    VT  => arduino 讀電壓的數據 0~1024
    AT  => 讀電流

*/

//修改自https://electronoobs.com/eng_arduino_tut81.php

//個人覺得max471不是合作電壓量測，因為他是以25V為尺度，會非常不準，應該使用arduino來量比較好

const int max471In = A0;

int RawValue = 0;
//int RawValueV = 0;
float Current = 0;
//float Voltage = 0;

void setup() {
  pinMode(max471In, INPUT);
  Serial.begin(9600);
}

void loop() {
  RawValue = analogRead(max471In);
  Current = (RawValue * 0.6761 )-44; // scale the ADC  //最主要的參數，但依然不太精準
  //Current = (RawValue * 5.0 ) / 1024.0; // scale the ADC
  Serial.print("RawAT = "); // shows the voltage measured  //額外加入的一句，做輔助參考
  Serial.print(RawValue); //3 digits after decimal point
  Serial.print("\t Current = "); // shows the voltage measured
  Serial.print(Current, 3); //3 digits after decimal point
  Serial.println(" mA DC"); //3 digits after decimal point
  delay(200);
}
