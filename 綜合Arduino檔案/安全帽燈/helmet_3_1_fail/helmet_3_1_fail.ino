byte outputPin[]={0,1,3,4,5,6,8,9,10,13};
byte inputPin[]={2};
byte mode[4];



float v; //這個v還不曉得要幹嘛
//uint8_t ;
uint16_t pwm=200;     //降壓的輸出PWM
uint16_t anareadA0;   //輸出的回授 (3.3K/10+3.3K)
uint16_t anareadA1;   //電池電源   (2.2K/10+2.2K)
uint8_t batstate=2;   //[2滿電] [1半電] [0喔不喵]
uint16_t anareadA2;   //光敏      (光敏二極體，460以下算暗的了)

float brightness;  //光敏數據累加  (最多64K)
uint8_t chekst_brtns; //check sent brightness不然他會在一小段時間內重複執行個很多次

uint8_t enviro;       //[2大白天] 4KΩ/1000lux [1黃昏] 50KΩ/20lux [0晚上暗咪哞]
uint8_t chek2set_evro; //check to set enviro 要在brightness 量測6次以後，再進行enviro輸出
/*這裡有個小小問題：
 * 
 */

//不要用LGT不要用LGT太可怕太難用資訊不全

void setup() {
  for(byte i=0;i<10;i++){
    pinMode(outputPin[i],OUTPUT); //將所有腳位設為輸出
  }
  pinMode(A3, INPUT_PULLUP);//uhh內建上拉電阻好像是38K(至少要開啟2個上拉，才會是38K，否則一個是41K)
  pinMode(A1, INPUT_PULLUP);
  
  analogReference(INTERNAL); //偵測電壓，用內部1.1V (實際1.8V)//LGT默認為1.1V，EASY~
  Serial.begin(9600);
  //tone(10, 4000, 70);
  
}

void loop() {
/*------------------輸出電源調控--------------------*/
  pwm = constrain(pwm, 1, 254);//避免PWM爆錶 //尬的，LGT最滿不是255，是16384！
  //if(millis()%10==0){
    anareadA0=analogRead(A0); //輸出回饋
    anareadA1=analogRead(A1); //電池電量偵測
    anareadA2=analogRead(A2); //光敏二極體_暗460
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
        //tone(10, 3000, 200); 
        //Serial.print("-----半--------");     
      }
    }  
    if (554 > anareadA1 ){
      //從半電變成沒電
      //喔不！停電了
      //ahhhhh！
      if(batstate>0){
        batstate=0;
        //tone(10, 1500, 200); 
        //Serial.print("------0-------");
      }
    }
  }
/*--------------環境亮度判斷------------------*/  
/*
記得，460以下算是暗的
*/ 
  
  if((millis()/10)%100==0 && chekst_brtns==0){ 
    //累加5次(1秒1次)就好
    //寫成   /10)%100   這樣，是因為不太可能程式每次執行到這裡時，正好millis都是整數，會被辣掉。但總會在10mS內執行完吧!
    brightness+=anareadA2;
    chekst_brtns=1;
    chek2set_evro+=1;
    Serial.print("anareadA2= ");
    Serial.println(anareadA2);
  }
  if((millis()/10)%100>50 && chekst_brtns==1){
    //check sent brightness不然他會在一小段時間內重複執行個很多次
    chekst_brtns=0;
  }
    /*
    Serial.print("brightness= ");
    Serial.print(brightness);
    Serial.print("  enviro= ");
    Serial.println(enviro);
    */
  if(chek2set_evro>5 ){
    //將檢驗結果送出(6秒1次)
    //寫成  /10)%600  這樣，是因為不太可能程式每次執行到這裡時，正好millis都是整數，會被辣掉。但總會在10mS內執行完吧!
    
    
    if(brightness>3000){
        //460*6=2760
        //實測2870
        //this is 白天
        
        enviro=2;
        tone(10, 5000, 80); 
    }
    else {
        //this is 晚上
        enviro=1;
        tone(10, 3000, 80); 
    }
    
    Serial.print("brightness= ");
    Serial.print(brightness);
    
    Serial.print(" enviro= ");
    Serial.println(enviro);
    Serial.println("");
    
    brightness=0;
    chek2set_evro=0;
  }
/*ready 2 delete
  if((millis()/10)%600>50 && chekst_evro==1){
    //check sent enviro不然他會在一小段時間內重複執行個很多次
    chekst_evro=0;
  }
*/
//昨日的bug紀錄：每8次中，就有一次的anaReadA2再結算時，跑到下一次那哩，因此需要看看millis哪裡會有公倍數問題
  
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
