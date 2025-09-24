
#define righttail 9

float inp;
bool start_say = 1;
unsigned long T = 0;
int ring, between_ring,battery_condition;
/*

  int j = 0;
  int NUM_REG1 = 0;
  int k = 0;
*/

void setup() {
  pinMode(11, OUTPUT);
  pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) { //跟他講說要手動輸入
    battery_condition = Serial.parseFloat();
  }

  if (digitalRead(7) == HIGH) {
    start_say = 1;
    ring = 0;
    
    
  }

  if (start_say == 1) {
    Serial.println(ring);
    switch(battery_condition){
    case 1:
        between_ring = 105;
        if (T < millis() - between_ring) {
          switch (ring) {
            case 1: tone(11, 1500, 100);                     break;
            case 2: tone(11, 2000, 100);                     break;
            case 3: tone(11, 2500, 100);                     break;
            case 4: tone(11, 3000, 100); between_ring = 255; break;
            case 5: tone(11, 3500, 250);                     break;
            case 6: tone(11, 3000, 250); between_ring = 305; break;
            case 7: tone(11, 3500, 300);                     break;
            case 8: ring = 0; start_say = 0;            break;
          }
          T = millis();
          if (ring < 8) {
            ring += 1;
          }
        }
    break;

    case 2:
        between_ring = 150;
        if (T < millis() - between_ring) {
          switch (ring) {
            case 1: tone(11, 2000, 100);                     break;
            case 2: tone(11, 2300, 100);                     break;
            case 3: tone(11, 2600, 100);                     break;
            case 4: tone(11, 2300, 100);                     break;
            case 5: tone(11, 2000, 100);                     break;
            case 6: ring = 0; start_say = 0;            break;
        }
        T = millis();
          if (ring < 6) {
            ring += 1;
          }
    break;

    case 3:
        between_ring = 200;
        if (T < millis() - between_ring) {
          switch (ring) {
            case 1: tone(11, 1300, 100);                     break;
            case 2: tone(11, 1000, 100);                     break;
            case 3: tone(11, 700, 100);                      break;            
            case 4: ring= 0; start_say = 0;                  break;
        }
        T = millis();
          if (ring < 4) {
            ring+= 1;
          }
    break;
        
    }    
    }
  }
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
