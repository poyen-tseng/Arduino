//半開的康乃馨_閃爍

//Inputs/Outputs
int X_pin = 6;
int Y_pin = 5;
int Pot = A0;

int point_delay = 1000;         //Delay between loops in us
#define how_many_vertices  27 //Put here the amount of vertices that you ahve
//Coordinates for the X & Y (remember, up to 254 coordinates)
byte coordinate[how_many_vertices * 2] = {
  116, 255,
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
    point_delay = 1500;            //Read analog value adn map it to a range between 10 and 2000us
    for (int i=0;i<30;i++) {
      for (loopcount = 0; loopcount < how_many_vertices * 2; loopcount++)
      {
        if (loopcount % 2 == 0) {
          analogWrite(X_pin, coordinate[loopcount]);                          //In this "for" we change the analog PWM width according to X axis and Y axis
          analogWrite(Y_pin, coordinate[loopcount + 1]);
          
        }
        delayMicroseconds(point_delay);                                 //Add the delay
      }
    }
    for (int i=0;i<30;i++) {
      for (loopcount = 0; loopcount < how_many_vertices * 2; loopcount++)
      {
        if (loopcount % 2 == 0) {
          analogWrite(X_pin, 0);                          //In this "for" we change the analog PWM width according to X axis and Y axis
          analogWrite(Y_pin, 0);
          
        }
        delayMicroseconds(point_delay);                                 //Add the delay
      }
    }


  }
}
