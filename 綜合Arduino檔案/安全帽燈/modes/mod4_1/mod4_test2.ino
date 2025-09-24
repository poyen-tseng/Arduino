
#define righttail 9

#define Short_freq 2500

float inp;
bool start_say = 0;
unsigned long T,T2;
int ring , between_ring , battery_condition, T_start_say;


void setup() {
  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) { //跟他講說要手動輸入
    battery_condition = Serial.parseFloat();
  }

  if (digitalRead(7) == HIGH && (millis()-T_start_say) > 200) {
    T_start_say = millis();
    start_say = !start_say;
    ring = 0;
  }
  if (start_say == 1) {
  SOS_beep();
  }
}
  

/*
  range
  uint8  : 0 ~ 255
  uint16 : 0 ~ 65535
  uint32 : 0 ~ 4294967295
  uint64 : 0 ~ 18446744073709551615
  unsi.long : 0 ~ 4294967295
  int8   : -128 ~ 127
  int16  : -32768 ~ 32767
  int32  : -2147483648 ~ 2147483647
  int64  : -9223372036854775808 ~ 9223372036854775807
*/
