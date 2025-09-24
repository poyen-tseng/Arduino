int t;


void setup() {
 t=0;
 //pinMode(4, INPUT);//4th pin connect to a 3 mode switch
 
 pinMode(6, OUTPUT);//main light
}
void loop() {
  // put your main code here, to run repeatedly:
if(t%10==0 ){
    //定義蜂鳴器模式 
    digitalWrite (6, HIGH);
  }
  if(t%10==1 ){
    //定義蜂鳴器模式 
    digitalWrite (6, LOW);
  }
    delay(30);
  if(t>=120){
    t=0;
  }
  else{
    t+=1;
  }
}
