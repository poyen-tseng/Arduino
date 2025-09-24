//以下程式改寫自http://electronoobs.com/eng_arduino_tut63.php

//半開的康乃馨_動態

//注意此時millis()函數無法正常運行

//Inputs/Outputs
int X_pin = 6;
int Y_pin = 5;
int Pot = A0;

int point_delay = 1000;         //Delay between loops in us
#define how_many_vertices_00  6
#define how_many_vertices_0  10
#define how_many_vertices_1  26
#define how_many_vertices_2  27 //Put here the amount of vertices that you ahve
#define how_many_vertices_3  38
//Coordinates for the X & Y (remember, up to 254 coordinates)
byte coordinate_00[how_many_vertices_00 * 2] = {
  143, 243, //花苞
  122, 195,
  111, 176,
  115, 164,
  123, 171,
  124, 195,
};

byte coordinate_0[how_many_vertices_0 * 2] = {
  143, 243, //花苞
  123, 195,
  95, 151,
  115, 165,
  95, 151,
  117, 123,
  133, 148,
  115, 165,
  133, 148,
  123, 196
};

byte coordinate_1[how_many_vertices_1 * 2] = {
  138, 226,   //準備開花
  123, 196,
  96, 149,
  93, 129,
  118, 122,
  93, 129,
  86, 111,
  96, 102,
  104, 96,
  118, 122,
  104, 96,
  115, 97,
  126, 90,
  118, 122,
  126, 90,
  133, 101,
  144, 103,
  137, 111,
  118, 122,
  137, 111,
  146, 120,
  140, 127,
  139, 138,
  132, 148,
  125, 191,
  138, 226

};

byte coordinate_2[how_many_vertices_2 * 2] = {
  116, 255,   //開一半的花
  117, 197,
  95, 145,
  96, 129,
  62, 139,
  48, 119,
  62, 104,
  96, 113,
  67, 93,
  73, 72,
  90, 72,
  109, 92,
  100, 67,
  118, 49,
  132, 66,
  124, 104,
  143, 73,
  167, 72,
  161, 95,
  137, 112,
  166, 106,
  179, 120,
  169, 137,
  138, 129,
  137, 145,
  118, 195,
  116, 241,

};

byte coordinate_3[how_many_vertices_3 * 2] = {
  70, 254,    //綻放
  100, 196,
  110, 133,
  99, 135,
  97, 125,
  7, 152,
  15, 129,
  5, 121,
  17, 112,
  8, 88,
  97, 114,
  19, 66,
  39, 57,
  37, 42,
  52, 44,
  63, 25,
  106, 101,
  86, 14,
  107, 23,
  114, 7,
  123, 22,
  149, 13,
  124, 100,
  168, 23,
  179, 46,
  194, 43,
  191, 58,
  213, 69,
  133, 110,
  222, 93,
  212, 111,
  226, 119,
  212, 129,
  224, 154,
  141, 125,
  135, 143,
  100, 195,
  70, 254,
};


void setup() {
  pinMode(X_pin, OUTPUT);     //Define the pin as output
  pinMode(Y_pin, OUTPUT);     //Define the pin as output
  pinMode(Pot, INPUT);        //Define the pin as input for the potentiometer

  //Now we adjust PWM frequency using Prescale_factor
  TCCR0A =  (TCCR0A & B10100011 + TCCR0A | B10100011);  //(1<<COM0A1 | 0<<COM0A0 | 1<<COM0B1 | 0<<COM0B0 | 1<<WGM01 | 1<<WGM00);
  TCCR0B =  (TCCR0B & B00000001 + TCCR0B | B00000001);  //(0<<FOC0A | 0<<FOC0B | 0<<WGM02 | 0<<CS02 | 0<<CS01 | 1<<CS00);
  TIMSK0 =  (TIMSK0 & B11111000);                       //(0<<OCIE0B | 0<<OCIE0A  | 0<<TOIE0);

}

void loop() {

  unsigned char loopcount;
  {
    point_delay = 2000;  //原本這是有讀取A0電位的，我將他寫定住了          //Read analog value adn map it to a range between 10 and 2000us
    for (int i = 0; i < 30; i++) {
      for (loopcount = 0; loopcount < how_many_vertices_2 * 2; loopcount++)
      {
        if (loopcount % 2 == 0) {
          analogWrite(X_pin, 0);                          //In this "for" we change the analog PWM width according to X axis and Y axis
          analogWrite(Y_pin, 0);

        }
        delayMicroseconds(point_delay);                                 //Add the delay
      }
    }

    for (int i = 0; i < 120; i++) {
      for (loopcount = 0; loopcount < how_many_vertices_00 * 2; loopcount++)
      {
        if (loopcount % 2 == 0) {
          analogWrite(X_pin, coordinate_00[loopcount]);                          //In this "for" we change the analog PWM width according to X axis and Y axis
          analogWrite(Y_pin, coordinate_00[loopcount + 1]);

        }
        delayMicroseconds(point_delay);                                 //Add the delay
      }
    }

    for (int i = 0; i < 90; i++) {
      for (loopcount = 0; loopcount < how_many_vertices_0 * 2; loopcount++)
      {
        if (loopcount % 2 == 0) {
          analogWrite(X_pin, coordinate_0[loopcount]);                          //In this "for" we change the analog PWM width according to X axis and Y axis
          analogWrite(Y_pin, coordinate_0[loopcount + 1]);
        }
        delayMicroseconds(point_delay);                                 //Add the delay
      }
    }

    for (int i = 0; i < 30; i++) {
      for (loopcount = 0; loopcount < how_many_vertices_1 * 2; loopcount++)
      {
        if (loopcount % 2 == 0) {
          analogWrite(X_pin, coordinate_1[loopcount]);                          //In this "for" we change the analog PWM width according to X axis and Y axis
          analogWrite(Y_pin, coordinate_1[loopcount + 1]);

        }
        delayMicroseconds(point_delay);                                 //Add the delay
      }
    }

    for (int i = 0; i < 30; i++) {
      for (loopcount = 0; loopcount < how_many_vertices_2 * 2; loopcount++)
      {
        if (loopcount % 2 == 0) {
          analogWrite(X_pin, coordinate_2[loopcount]);                          //In this "for" we change the analog PWM width according to X axis and Y axis
          analogWrite(Y_pin, coordinate_2[loopcount + 1]);

        }
        delayMicroseconds(point_delay);                                 //Add the delay
      }
    }

    for (int i = 0; i < 30; i++) {
      for (loopcount = 0; loopcount < how_many_vertices_3 * 2; loopcount++)
      {
        if (loopcount % 2 == 0) {
          analogWrite(X_pin, coordinate_3[loopcount]);                          //In this "for" we change the analog PWM width according to X axis and Y axis
          analogWrite(Y_pin, coordinate_3[loopcount + 1]);

        }
        delayMicroseconds(point_delay);                                 //Add the delay
      }
    }
  }
}
//by Bruce Tseng 2022/05/07
