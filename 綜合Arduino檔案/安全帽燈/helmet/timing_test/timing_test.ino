int t;
void setup() {
  // put your setup code here, to run once:
t=0;
Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
if(t<100){
  t++;
  }
  Serial.println(t);
if(t>=99){
  t=0;
}
delay(1000);
}
