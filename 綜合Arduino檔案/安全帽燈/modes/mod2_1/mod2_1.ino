
#define righttail 9


boolean FLABUTT = 0;
uint32_t T_F = 0;

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
  pinMode(6, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
}
//強制照明
void loop() {
  if(digitalRead(2)==HIGH && (millis()-T_F) > 200){
    FLABUTT = !FLABUTT;
    T_F = millis();
  }
  digitalWrite (6, FLABUTT);
}
