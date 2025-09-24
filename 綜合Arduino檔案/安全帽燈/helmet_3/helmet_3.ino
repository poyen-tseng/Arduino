byte outputPin[]={0,1,3,4,5,6,8,9,10,13};
byte inputPin[]={2};
byte mode[4];



float v; //這個v還不曉得要幹嘛
//uint8_t ;
uint16_t pwm=200;     //降壓的輸出PWM
uint16_t anareadA0;   //輸出的回授 (3.3K/10+3.3K)
uint16_t anareadA1;   //電池電源   (2.2K/10+2.2K)
uint8_t batstate=2;   //[2滿電] [1半電] [0喔不喵]
uint16_t anareadA2;   //光敏      (電源用ref的1.1V 固定10K to GND/光敏亮阻1K_暗阻70K+)
uint8_t digreadA5;   //按鍵

float brightness;  //光敏數據累加  (最多64K)
uint8_t chekst_brtns; //check sent brightness不然他會在一小段時間內重複執行個很多次
uint8_t enviro;       //[2大白天] 4KΩ/1000lux [1黃昏] 50KΩ/20lux [0晚上暗咪哞]
uint8_t chek2set_evro; //check to set enviro 要在brightness 量測6次以後，再進行enviro輸出

//按鈕偵測腳digitalread(A5);
unsigned long prstime = 0;  //按下按鈕的時間(用來儲存millis()，1200個小時才會溢位，安啦)
bool interval = 0; //1秒內有間隔嗎? 0為沒有間隔
unsigned long futtime = 0;  //未來接著要進行檢測的那個時間
bool curstat = 0;  //當前狀態，以供後續比較
bool reported = 0; //避免重複報告

uint8_t mod=1 , mod1=0 , mod2=0 , mod3=0 , mod4=0;
uint8_t inp=0; //作為輸入儲存器 1短 2連擊 3長按

/*這裡有個小小問題：
 * 電源會變動、光敏會變動，如何確定真正的讀值？
 * Ans: 利用電源回授(A1)加入光敏(A2)的運算
 * Sol:
 *  由於
 *      V  =A1*(1.1/1023)*(12.2K/2.2K)
 *      
 *      V   =A1*(0.98/1023)*(38K+6.8K/6.8K)
 *         
 *      A2 =V*(CDS/(CDS+10K))*(1023/1.1)
 *         =A1*5.5454...*(CDS/(10K+CDS))
 *         
 *      A2 =V*(CDS/(CDS+38K))*(1023/0.98)
 *         =A1*6.588...*(CDS/(38K+CDS))
 *  因此在此時量到的A2
 *      白天與黃昏的交界：A2=A1*5.5454*(4K/4+10K)=A1*1.5844
 *                     A2=A1*6.588*(4K/4+38K)=A1*0.6274
 *      黃昏與晚上的交界：A2=A1*5.5454*(50k/50+10K)=A1*4.6212
 *                     A2=A1*6.588*(50k/50+38K)=A1*3.7432
 *  利用此數據的方法為
 *      if(A2/A1 < 0.6274){則為白天}
 *      if(0.6274 < A2/A1 && A2/A1 < 3.7432){則為黃昏}
 *      if(3.7432 < A2/A1){則為晚上}
 *
 */

//不要用LGT不要用LGT太可怕太難用資訊不全

void setup() {
  for(byte i=0;i<10;i++){
    pinMode(outputPin[i],OUTPUT); //將所有腳位設為輸出
  }
  pinMode(A5, INPUT_PULLUP);//uhh內建上拉電阻好像是38K(至少要開啟2個上拉，才會是38K，否則一個是41K)
  pinMode(A1, INPUT_PULLUP);
  
  analogReference(INTERNAL); //偵測電壓，用內部1.1V (實際1.8V)//LGT默認為1.1V，EASY~
  Serial.begin(9600);
  //tone(10, 4000, 70);
  
}

void loop() {
/*------------------輸出電源調控--------------------*/
  pwm = constrain(pwm, 1, 254);//避免PWM爆錶 //尬的，LGT最滿不是255，是16384！
  //if(millis()%10==0){
  //這麼做是避免程式跑到一半，讀到不同的值
    anareadA0=analogRead(A0); //輸出回饋
    anareadA1=analogRead(A1); //電池電量偵測
    anareadA2=analogRead(A2); //光敏_亮1K~暗200K_(內部上拉10K)
    digreadA5=digitalRead(A5);//按鍵
  //if(millis()%100){
  //v=1.1 * anareadA0 / 1023; //100mS偵測一次電壓，權衡精準與省電
   
  
  //降壓輸出的回授分壓電阻為3.3K/10K+3.3K=0.248倍......這個10K目前是用外部的炭膜電阻
  //若v=3.4，則A0讀到3.4*0.248/1.1*1023=784.176
  //
  //因應新的(不知哪來的)1.8V參考源，
  //若v=3.4，則A0讀到3.4*0.248/1.8*1023=479.219
  //但是實驗發現，A0=880~850
  //
  //我發現：
  //儘管內置參考源為1.1V，依然受到電源電壓影響。意即，當電壓源為3.5V或4.2V時，讀到的ADC值雖然一樣，實際電壓卻會不同。
 
  //注意，內建上拉38K，外部固定6.8K，0.1517倍率
  //超怪，我又算出新的參考源變成1.8V (OK最新數據0.98V
  //那麼:
  //若v=3.9，則A1讀到3.9*0.1517/0.98*1023=617.59  (0.591V
  //若v=3.5，則A1讀到3.5*0.1517/0.98*1023=554.25  (0.530V
  //
  
  
  if (880 < anareadA0 ){
    
    pwm+=1; 
    //因用的是P型半導體，故邏輯相反
  }
  if (850 > anareadA0 ){
    
    pwm-=1; 
    //因用的是P型半導體，故邏輯相反
  }
  //analogWrite(9,16383); 
  //尬的嘞，LGT的PWM輸出最滿是16383
  analogWrite(9,pwm);
  
/*----------------電池電源偵測---------------*/
  if (millis()>3000){
    
    //等完全開機
    if (617 > anareadA1 && anareadA1 > 554){  
       
      //注意這if不能寫成if(660 > anareadA1 > 586) 會卡死，務必分成2段
      //從滿電變成半電
      if(batstate>1){
        batstate=1;
        tone(10, 3000, 200); 
        //Serial.print("-----半--------");     
      }
    }  
    if (554 > anareadA1 ){
      //從半電變成沒電
      //喔不！停電了
      //ahhhhh！
      if(batstate>0){
        batstate=0;
        tone(10, 1500, 200); 
        //Serial.print("------0-------");
      }
    }
  }
/*--------------環境亮度判斷------------------*/  
 
  if((millis()/10)%100==0 && chekst_brtns==0){ 
    //累加3次(1秒1次)就好
    //寫成除X再取%Y這樣，是因為不太可能程式每次執行到這裡時，正好millis都是整數，會被辣掉。但總會在100mS內執行完吧!
    brightness+=anareadA2;
    chekst_brtns=1;
    chek2set_evro+=1;
    
//    Serial.print("anareadA2= ");
//    Serial.println(anareadA2);
    
  }
  if((millis()/10)%100>50 && chekst_brtns==1){
    //check sent brightness不然他會在一小段時間內重複執行個很多次
    chekst_brtns=0;
  }
    
  if(chek2set_evro>2 ){
    //將檢驗結果送出(3秒1次)
        
      if(brightness>1500){
          //this is 白天
          enviro=2;
          tone(10, 3500, 700); 
      }
      else {
          enviro=1;
          tone(10, 3500, 2000); 
      }

//    Serial.print("brightness= ");
//    Serial.print(brightness);
//    
//    Serial.print(" enviro= ");
//    Serial.println(enviro);
//    Serial.println("");
    brightness=0;
    chek2set_evro=0;
  }

/*-------------按鍵偵測-----------------------*/
    if (millis()/10 % 100 == 0) {
        Serial.println(); //換行，表示資料有在更新
        /*
        Serial.print(" inp=");
        Serial.println(inp);
        inp=0;  //記得，inp用過以後，再歸零，不然還沒用就被丟了
        */
    }

    if ((digreadA5 == LOW) && (curstat == 0)&&(reported ==0)) {
      //確認之前沒有按過，啟動感知程序
        prstime = millis();
        futtime = millis() + 600; //0.6秒
        curstat = 1;
    }

    if (digreadA5 == HIGH && (curstat == 1) && (millis() < futtime)&&(reported == 0)) {
      interval = 1; //期間內有中斷發生
      //Serial.println(interval); //換行，表示資料有在更新
    }
    
    if (digreadA5 == LOW && (interval == 1) && (millis() < futtime)&&(reported == 0) ) {
      //發現按下，而且之前有按過，中間還有間隔，這是連2按!!
      //Serial.print(reported);
      //Serial.println(interval);
      //Serial.println(millis());
      //Serial.println(futtime);
      Serial.println("double press");
      inp=2;
      reported = 1 ;//避免"short press出來亂"
      interval = 0; //清空
      curstat = 0;  //清空
      //Serial.print(reported);
      //Serial.println(interval);
    }
    
    if (digreadA5 == HIGH && (curstat == 1) && (millis() >= futtime) && (interval == 0) &&(reported == 0) ) {
      //有觸發&&時間到&&沒有中斷，這是長按!!
      Serial.println("long press");
      inp=3;
      interval = 0 ;//清空
      reported = 1; //避免"short press"出來亂
    }
    
    if ((curstat == 1) && (millis() >= futtime) && (interval == 1) &&(reported == 0) ) {
      //有觸發&&時間到&&有中斷，這是單按!!
      Serial.println("single press");
      inp=1;
      interval = 0 ;//清空
      reported = 1;
    }
    
    if(millis() > futtime+10){
      reported = 0;//清空
      
    }
    
    if (digreadA5 == HIGH && (curstat == 1) && (millis() > futtime)) {
      curstat = 0;//curstat工作結束，下台鞠躬 (讀取LOW是為了避免是按鈕長按太久)
      //簡言之，這一條是避免手指抽筋，long press按太久

      
    }
    
    
    
/*-------------模式如何切換-----------------------*/
  
  switch(inp){
      case 1: Serial.println("SHORT");
              //去睡覺
              inp=0;
              break;
      case 2: Serial.println("DOUBLE");
              //進入下一個子模式
              if(mod==1){
                //一般感光
                mod1+=1; 
                if(mod1>3){ mod1=1; } 
                Serial.print("mod1=");
                Serial.println(mod1); }
                
              if(mod==2){
                //手電筒
                mod2+=1; 
                if(mod2>1){mod2=1;  } 
                Serial.print("mod2=");
                Serial.println(mod2);}
                
              if(mod==3){
                //回報(電壓)
                mod3+=1; 
                if(mod3>1){mod3=1;  } 
                Serial.print("mod3=");
                Serial.println(mod3);}

              /*  
              if(mod==4){
                //SOS(選)
                mod4+=1; 
                if(mod4>3){mod4=1;  } 
                Serial.print("mod4=");
                Serial.println(mod4);}
                
              inp=0;
              break;
              */
      
      case 3: Serial.println("LONG"); 
              mod +=1 ; 
              mod1=0; 
              mod2=0; 
              mod3=0; 
             // mod4=0; //當用LONG切換母模式，將所有子模式歸零
              if(mod>4){mod=1;} 
              Serial.print("mod=");
              Serial.println(mod);

              inp=0;
              break;
    }

/*-------------按鍵模式定義--------------------*/
/*
switch(mode[1]){
    case 0:
        //這個沒用到
        break;
    
    case 1:
        //感光
        switch(enviro){
            case 0:
                //晚上
                
                break;
            
            case 1:
                //黃昏
                
                break;
                
            case 2:
                //白天
                
                break;
            
        }
        break;
        
    case 2:
        //簡易
        
        break;
        
    case 3:
        //強制照明
        
        break;
        
    case 4:
        //強制閃燈
        
        break;
    
}
*/

/*-------------亮燈模式定義--(等會兒，太複雜不要問很可怕)-----------*/
    
  delay(3);
}
