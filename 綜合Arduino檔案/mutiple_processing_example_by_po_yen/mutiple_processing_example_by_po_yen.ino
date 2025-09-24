
int t;

void setup() {
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
Serial.begin(9600);
t=1;
}

void loop() {
  Serial.println(t);
  if(t>=4){
    t=1;
  }
  else{
    t+=1;
  }
    
    /*
    if(t==1,t==5,t==9){
      
    digitalWrite (4, HIGH);
    }
    if(t==3){
      digitalWrite (4, LOW);
    }
    */
    /*
    if(t==1,t==3,t==5,t==7,t==9,t==11){
      digitalWrite (5, HIGH);
    }
    if(t==2,t==4,t==6,t==8,t==10,t==12){
      digitalWrite (5, LOW);
    }
    */
    if(t==1||t==3){
      digitalWrite (5, HIGH);
    }
    if(t==2||t==4){
      digitalWrite (5, LOW);
    }
    
 delay(600);
}
