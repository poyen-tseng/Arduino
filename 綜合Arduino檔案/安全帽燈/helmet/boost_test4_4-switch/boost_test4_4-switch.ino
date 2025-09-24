int pwm = 0;



void setup() {
  analogReference(INTERNAL);
  Serial.begin(115200);
TCCR0B = TCCR0B & 0b11111000 | 0x01; //set pin 5,6 pwm frequency to 62500Hz (0x01). 0x02 divide by 8...
//pwm frequency setting: https://prototyperobotics.com/steps/2

//analogWrite(5,0);
pinMode(6, OUTPUT);
pinMode(5, OUTPUT);
}

void loop() {
  float output  = analogRead(A0);
  Serial.print("\tout:");
  Serial.println(output);

  
  if (output < 164)
   {
    pwm = pwm+1;
    pwm = constrain(pwm, 5, 10);
   }
   
  //If the desired value is LOWER than the real value, we decreaase PWM width
  if (output >164)
   {
    pwm = pwm-1;
    pwm = constrain(pwm, 5, 10);
   }
    digitalWrite(5,HIGH);
   analogWrite(6,1);  //Finally, in 5v, out 7V
}
