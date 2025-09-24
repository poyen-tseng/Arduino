#define CDSPIN A1
#define BRIGHT 512
#define DARK 300

#define midlight 8
uint16_t SUN;
uint16_t SUN1;
uint16_t SUN2;
uint16_t SUN3;
#define leftlight 11
#define rightlight 12

#define midtail 6
#define lefttail 9
#define righttail

uint32_t T_cds = 0;
uint32_t t1 = 0; //溢位的話就不會閃爍了
uint32_t t2 = 0;
uint32_t t3 = 0;


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
  Serial.begin(9600);
}

void loop() {
  switch ( 1) {
    case 3:  //白天
    /*
      flash1(4000, midlight, 70);
      flash3(840, 480, 130, midtail, 20);
      */
      break;

    case 2:  //傍晚
      flash1(400, midlight, 70 );
      flash3(840, 480, 130, midtail, 20); 
      break;

    case 1:  //晚上
      flash3(700, 400, 100, midtail, 20);
      digitalWrite (midlight, HIGH);   //記得去定義其他沒用的LED腳位為LOW
      break;


  }

}
