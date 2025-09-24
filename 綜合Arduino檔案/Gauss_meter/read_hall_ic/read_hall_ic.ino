
float val=0;

void setup() {
  Serial.begin(115200);

}

void loop() {
//  val=analogRead(A3);
  Serial.println(analogRead(A3)*3.051757); //GS

}
