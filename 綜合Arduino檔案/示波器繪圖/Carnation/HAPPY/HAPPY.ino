//Inputs/Outputs
int X_pin = 6;
int Y_pin = 5;
int Pot = A0;

int point_delay = 1000;         //Delay between loops in us
#define how_many_vertices_HAPPY  33
#define how_many_vertices  38 //Put here the amount of vertices that you ahve
//Coordinates for the X & Y (remember, up to 254 coordinates)
byte coordinate_HAPPY[how_many_vertices_HAPPY * 2] = {
  5,64,
  6,5,
  5,32,
  42,32,
  42,64,
  42,64,

  61,62,
  82,5,
  97,45,
  66,44,
  97,45,
  103,63,
  
  121,64,
  121,7,
  148,8,
  155,21,
  148,37,
  121,37,
  121,64,

  174,61,
  174,6,
  198,8,
  205,21,
  198,34,
  173,34,
  174,61,

  234,62,
  233,36,
  218,7,
  233,36,
  251,5,
  233,36,
  233,62,  
   
};

byte coordinate[how_many_vertices * 2] = {
  70, 254,
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
    point_delay = map(analogRead(Pot), 0, 1024, 10, 2000);            //Read analog value adn map it to a range between 10 and 2000us
    if (millis() / 5000 < 1) {
      for (loopcount = 0; loopcount < how_many_vertices_HAPPY * 2; loopcount++)
      {
        if (loopcount % 2 == 0) {
          analogWrite(X_pin, coordinate_HAPPY[loopcount]);                          //In this "for" we change the analog PWM width according to X axis and Y axis
          analogWrite(Y_pin, coordinate_HAPPY[loopcount + 1]);
        }
        delayMicroseconds(point_delay);                                 //Add the delay
      }
    }
    


    if (millis() / 5000 > 1) {
      for (loopcount = 0; loopcount < how_many_vertices * 2; loopcount++)
      {
        if (loopcount % 2 == 0) {
          analogWrite(X_pin, coordinate[loopcount]);                          //In this "for" we change the analog PWM width according to X axis and Y axis
          analogWrite(Y_pin, coordinate[loopcount + 1]);
        }
        delayMicroseconds(point_delay);                                 //Add the delay
      }
    }
  }
}
