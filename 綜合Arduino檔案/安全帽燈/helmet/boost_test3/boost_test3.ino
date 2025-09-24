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
  

  
  if (137 < output < 139){
    pwm-=1;
    pwm = constrain(pwm, 0, 254);
    }
  if (136 < output < 137 ){
    pwm+=1;
    pwm = constrain(pwm, 0, 30);
  }
  if (output < 136){  
    if(pwm>35){
      pwm=0;
      }
    pwm = pwm+1;
    pwm = constrain(pwm, 0, 30); //一開始先用低一點，避免當機時，升壓到天荒地老，之後視負載決定
    digitalWrite(5,LOW); //令PIN5為常低，接通PMOS
    analogWrite(6,pwm); //PIN6控制升壓的狀態
    Serial.print("BOOST");
   
   }
  //If the desired value is LOWER than the real value, we decreaase PWM width
  if (output >140){
    pwm += 1;
    if (output >150){
      pwm += 2;
    }
    pwm = constrain(pwm, 0, 254); //和完全斷開有一點區別，畢竟是PMOS
    digitalWrite(6,LOW); //令PIN6為常低，斷開NMOS
    analogWrite(5,pwm); //PIN5控制降壓的狀態
    Serial.print("BUCK");
   }
  Serial.print("\tout:");
  Serial.print(output);
  Serial.print("\tpwm:");
  Serial.println(pwm);
}
