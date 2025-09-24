 
#define righttail 9

float inp;
float N1 = 0;
float N2 = 0;
float N3 = 0;


uint32_t T_R = 0;
unsigned long T_SAY1 = 0, T_k = 0;
int j = 0;
int NUM_REG1 = 0;
uint8_t SAY_COUNT = 0;
int k = 0;
/*
  range
  uint8  : 0 ~ 255
  uint16 : 0 ~ 65535
  uint32 : 0 ~ 4294967295
  uint64 : 0 ~ 18446744073709551615
  int8   : -128 ~ 127
  int16  : -32768 ~ 32767
  int32  : -2147483648 ~ 2147483647
  int64  : -9223372036854775808 ~ 9223372036854775807
*/
void setup() {
  pinMode(11, OUTPUT);
  pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) { //跟他講說要手動輸入
    inp = Serial.parseFloat();
    
  }
  N1 = floor(inp);
  N2 = floor((inp - N1) / 0.1);
  N3 = floor((inp - N1 - 0.1 * N2) / 0.01);

  if (digitalRead(7) == HIGH) {
    /*
    Serial.print("j=");
    Serial.print(j);
    Serial.print("\tk=");
    Serial.print(k);
    Serial.print("\tT_k=");
    Serial.println(T_k);
    */
    switch (k) {
      case 0:
        if (millis() > T_k + 500) {
          SAYVOLT(N1, 4000);
          Serial.println("嗶!");
        }
        
      case 1:
        //T_k = millis();
        if (millis() > T_k + 500) {
          SAYVOLT(N2, 3000);
        }
        /*
      case 2:
        
        if (millis() > T_k + 5000) {
          SAYVOLT(N3, 4500);
        }
        */
      default:
        //T_k = millis();
        if (millis() > T_k + 5000) {
          T_k = millis();
          k = 0;
        }
    }
  }
}
