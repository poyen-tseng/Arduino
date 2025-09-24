
#define TONEPIN 11

float inp;
float N1 = 0;
float N2 = 0;
float N3 = 0;

unsigned long T_mors;
//boolean FLABUTT = 0;
//宣告摩斯碼陣列，10種數字，每字5音，0短1長，由1到9再是0
int ms[10][5] = {
  {0, 1, 1, 1, 1,}, //1
  {0, 0, 1, 1, 1,}, //2
  {0, 0, 0, 1, 1,}, //3
  {0, 0, 0, 0, 1,}, //4
  {0, 0, 0, 0, 0,}, //5
  {1, 0, 0, 0, 0,}, //6
  {1, 1, 0, 0, 0,}, //7
  {1, 1, 1, 0, 0,}, //8
  {1, 1, 1, 1, 0,}, //9
  {1, 1, 1, 1, 1,} //0
};
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
  

  if (digitalRead(7) == HIGH) {
    
    if(millis()>T_mors){
      
    }

  }
}


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
