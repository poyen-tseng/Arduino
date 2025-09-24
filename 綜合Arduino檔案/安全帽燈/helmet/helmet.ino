/*-----------省電註記------------------
 * 使用Vin PIN來輸入電源(3.3V)，而不是5V PIN
 * 移除板載LED
 * MCU降頻至 1MHz (1/16倍)
 * 更深層的休眠模式
 * 
 * 將所有的PINOUT設定為OUTPUT，那將會讓沒用的腳接地
 * 關閉ADC
 * 設定BOD
 * 
 * 將delay換成watch dog delay，30毫秒也能睡！
 * 
 * 按鈕喚醒，可用設定的，或暫切總電源，reboot一下
 * 
 * 
 */
/*------------其他功能註記-------------
 * 簡少開機時的延遲時間
 * 加入左後方的車輛警示(超音波測距模組)
 * //PORTB 代替digitalWrite，加速
 * 
 */
 /*--------電池電壓註記----------
  * 鋰離子電池
  * 0/3.2/3.7
  * 
  * 磷酸鐵鋰電池
  * 0/3.18/3.0
  */
int t;   //時間標記
float v; //電壓值 A0
float sun; //平均環境亮度 A2
float sun1; //環境亮度 A2 (有三個sun是為了避免突然的樹蔭或強光)
float sun2; //環境亮度 A2
float sun3; //環境亮度 A2
/*
float v1;
float v2;
float v3;
float va;
*/

int b;   //電池電量狀態 2高 1中 0低


void setup() {
  Serial.begin(9600);
 t=0;
 
 pinMode(2, INPUT);//2nd pin connect to a buzzer mode switch
 pinMode(4, INPUT);//4th pin connect to a light mode switch
//A0 use for battery voltage reading
 
 pinMode(6, OUTPUT);//main light ----pin 6 is "PWMable"----
 pinMode(8, OUTPUT);//side light
//A2 use for voltage sensor (day or ight)
 pinMode(10, OUTPUT);//tail light
 
 pinMode(11, OUTPUT);//Buzzer
 pinMode(12, OUTPUT);//small red LED----low voltage indicater
 
//剛開機時，做電池初測，供後續作比較
v = 5.0*analogRead(A0)/1023;
//Serial.print(v);
//delay(3000);

 if(3.7<v){
    //高電量
    b=2;    
  }
 if(3.2<v && v<3.7){
    //中電量
    b=1;
      tone(11, 2800, 100);
      delay(180);
      tone(11, 1000, 100);
      delay(150);
      tone(11, 250, 100);
  }
 if(v<3.2){
    //低電量
    b=0;
    tone(11, 2800, 100);
      delay(150);
      tone(11, 2800, 100);
      delay(150);
      tone(11, 1000, 100);
      delay(180);
      tone(11, 1000, 100);
      delay(180);
      tone(11, 250, 150);
      delay(220);
      tone(11, 250, 150);
      delay(350);
      tone(11, 200, 150);
      delay(350);
      tone(11, 200, 150);
      delay(450);
      tone(11, 180, 150);
  }


  
}

void loop() {
  //定義安全帽的 自動 和 強制開啟 模式


/*
if(t%300==1){
  v1=5.0*analogRead(A0)/1023;
}
if(t%300==101){
  v2=5.0*analogRead(A0)/1023;
}
if(t%300==201){
  v3=5.0*analogRead(A0)/1023;
}
va=(v1+v2+v3)/3.0;
*/

//Serial.print("v:");
//Serial.print(v);

/*
Serial.print(" v1:");
Serial.print(sun1);
Serial.print(" v2:");
Serial.print(sun2);
Serial.print(" v3:");
Serial.print(sun3);
*/

/*
Serial.print(" va:");
Serial.println(va);
  */
  Serial.print(" sun:");
Serial.println(sun);
  
  if(digitalRead(4)==LOW){
  //定義 自動 模式 (白天：主燈6閃爍)(晚上：主燈6恆亮、副燈8閃爍)

    if(t%200==1){
      sun1=analogRead(A2);  //每5秒取樣一次環境亮度A2
    }
    if(t%200==60){
      sun2=analogRead(A2);  //每5秒取樣一次環境亮度A2
    }
    if(t%200==120){
      sun3=analogRead(A2);  //每5秒取樣一次環境亮度A2
    }
    sun=(sun1+sun1+sun3)/3; //再將三次的數據做平均A2
    
    if(sun<512 && t%25==0 ){
      //白天電阻小，分得電壓少  主燈6亮    副燈8恆暗  尾燈10亮
      
      digitalWrite (6, HIGH);
      digitalWrite (8, LOW );
      digitalWrite (10, HIGH);
    }
    if(sun<512 && t%25==1){
      //白天電阻小，分得電壓少  主燈6暗    副燈8恆暗  尾燈10暗
      digitalWrite (6, LOW);
      digitalWrite (8, LOW );
      digitalWrite (10, LOW);
    }

    if(sun>512 && t%10==0 ){
      //晚上電阻大，分得電壓多  主燈6恆亮   副燈8亮   尾燈10亮
      
      digitalWrite (6, HIGH);
      digitalWrite (8, HIGH );
      digitalWrite (10, HIGH);
    }
    if(sun>512 && t%10==1){
      //白天電阻小，分得電壓少  主燈6恆亮   副燈8暗   尾燈10暗
      digitalWrite (6, HIGH);
      digitalWrite (8, LOW );
      digitalWrite (10, LOW);
    }
    
    
    
  }
  else{
    //定義 強制開啟 模式 (主燈、副燈 皆亮  尾燈暗)
    digitalWrite (6, HIGH);//main light
    digitalWrite (8, HIGH);//side light
    digitalWrite (10, LOW);//tail light
  }

  if(digitalRead(2)==HIGH && (t%30==0 || t%30==3)){
    //定義蜂鳴器模式 
    digitalWrite (11, HIGH);
  }
  if(digitalRead(2)==HIGH && (t%30==1 || t%30==4)){
    //定義蜂鳴器模式 
    digitalWrite (11, LOW);
  }


if(t%30==0){
//每 秒檢查一次電壓  
  v = 5.0*analogRead(A0)/1023;
  //定義低電壓警示
  if(3.7<v){
    //高電量
    digitalWrite (12, LOW);
    
  }
  
  if((3.2<v && v<3.7)&&(t%40==0)){
    //中電量 亮
    digitalWrite (12,HIGH);
    if(b==2){
      b=1;
      Serial.println("===========================");
      Serial.println(b);
      tone(11, 2800, 100);
      delay(180);
      tone(11, 1000, 100);
      delay(150);
      tone(11, 250, 100);
      
    }
  }
  if(3.2<v && v<3.7  && t%40==4){
    //中電量 暗
    digitalWrite (12,LOW);
  }
  
  if(v<3.2  && t%10==0){
    //低電量 亮
    digitalWrite (12,HIGH);
    if(b==1 || b==2){
      b=0;
      tone(11, 2800, 100);
      delay(150);
      tone(11, 2800, 100);
      delay(150);
      tone(11, 1000, 100);
      delay(180);
      tone(11, 1000, 100);
      delay(180);
      tone(11, 250, 150);
      delay(220);
      tone(11, 250, 150);
      delay(350);
      tone(11, 200, 150);
      delay(350);
      tone(11, 200, 150);
      delay(450);
      tone(11, 180, 150);
    }
  }
  if(v<3.2  && t%10==2){
    //低電量 暗
    digitalWrite (12,LOW);
  }
}

  
  
  //設定時脈週期，，每30秒繞一圈
  delay(30);
  if(t>=1200){
    t=0;
  }
  else{
    t+=1;
  }

  

}
