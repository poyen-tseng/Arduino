/*pinout describe
    Vout 太陽能板
    Vin  電池、負載
    VT  => arduino 讀電壓的數據 0~1024
    AT  => 讀電流

*/
//量測電流才要用MX471，電壓用Arduino量測才準確
//這個檔案作為階段性備份，下一版要用內部ref 1.1V
const int max471AT = A0;
const int Vsense = A2;
int RawValueA = 0;
int RawValueV = 0;
float Current = 0;
float Voltage = 0;

void setup() {
  pinMode(max471AT, INPUT);
  pinMode(max471VT, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  RawValueA = analogRead(max471AT);
  RawValueV = analogRead(max471VT);
  
  Current = (RawValueA * 0.6761 )-44; // scale the ADC 
  //Voltage = (RawValueA * 0.6761 )-44; // scale the ADC 
  //Current = (RawValue * 5.0 ) / 1024.0; // scale the ADC
  /*
  Serial.print("RawAT = "); // shows the voltage measured
  Serial.print(RawValueA); //3 digits after decimal point
  Serial.print("\t Current = "); // shows the voltage measured
  Serial.print(Current, 3); //3 digits after decimal point
  Serial.println(" mA DC"); //3 digits after decimal point
  */
  Serial.print("RawVT = "); // shows the voltage measured
  Serial.print(RawValueV); //3 digits after decimal point
  Serial.print("\t Voltage = "); // shows the voltage measured
  Serial.print(Voltage, 3); //3 digits after decimal point
  Serial.println(" V DC"); //3 digits after decimal point
  delay(200);
}
