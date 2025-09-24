
#define righttail 9

float inp;
float N1 = 0;
float N2 = 0;
float N3 = 0;

//boolean FLABUTT = 0;
uint32_t T_R = 0;
unsigned long T_SAY1 = 0, T_SAY0 = 0;
int j = 0;
int NUM_REG1 = 0;
uint8_t SAY_COUNT = 0;
int k=0;
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
//強制照明
void loop() {
  if (Serial.available()) { //跟他講說要手動輸入
    inp = Serial.parseFloat();


  }
  N1 = floor(inp);
  N2 = floor((inp - N1) / 0.1);
  N3 = floor((inp - N1 - 0.1 * N2) / 0.01);
  /*
    Serial.print("inp= ");
    Serial.print(inp);

    Serial.print("\tN1= ");
    Serial.print(N1);
    Serial.print("\tN2= ");
    Serial.print(N2);
    Serial.print("\tN3= ");
    Serial.println(N3);
  */
  //delay(800);

  if (digitalRead(7) == HIGH) {

    /*
      if(N1<5){
      for (int i = 0; i < N1; i++) {
            tone(11, 3500, 20);
      delay(100);

      }}
      if(N1>5){
      tone(11, 3500, 200);
      delay(300);
      for (int i = 0; i < N1-5; i++) {

      tone(11, 3500, 20);
      delay(100);

      }}
    */
    SAYVOLT(N1, 4000);
    /*
    if (SAY_COUNT == 0) {
      SAYVOLT(N1, 4000);
      k=SAYVOLT;
      Serial.println(k);
      if (SAYVOLT == 1) {
        SAY_COUNT += 1;
        T_SAY0 = millis();
      }
      if (SAYVOLT == 1 && millis()> T_SAY0 + 300) {
        SAYVOLT(N2, 3000);
        if (SAYVOLT == 1) {
          SAY_COUNT += 1;
        }
      }
      */
      /*delay(200);
        SAYVOLT(N2,3000);
        delay(200);
        SAYVOLT(N3,5000);

        delay(300);


        delay(1000);
      */
    }
  }
