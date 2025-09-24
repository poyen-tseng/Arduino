
#define righttail 9

#define Short_freq 2500

float inp;
bool start_say = 1;
unsigned long T,T2;
int ring ,flash, between_ring , between_flash, battery_condition;


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

  if (digitalRead(7) == HIGH) {
    start_say = !start_say;
    ring = 0;
  }

  
    switch(battery_condition){
    case 1:
        SOS_led();
        break;

    case 2:
        SOS_led();
        SOS_beep();
        break;

    case 3:
        SOS_beep();
        break;
        
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
