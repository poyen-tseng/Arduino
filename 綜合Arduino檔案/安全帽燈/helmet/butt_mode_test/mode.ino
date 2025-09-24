uint8_t mode(uint8_t inp){
  //作為輸入儲存器 1短 2連擊 3長按
  
//將所有子模式設為零，避免之後有2個程式同時啟動
    switch(inp){
      case 1: /*Serial.println("SHORT");*/break;
      case 2: /*Serial.println("DOUBLE");*/
              if(mod==1){
                mod1+=1; 
                if(mod1>3){ mod1=1; } //溢位歸零
                Serial.print("mod1=");
                Serial.println(mod1); }
              if(mod==2){
                mod2+=1; 
                if(mod2>2){mod2=1;  } 
                Serial.print("mod2=");
                Serial.println(mod2);}
              if(mod==3){
                mod3+=1; 
                if(mod3>1){mod3=1;  } 
                Serial.print("mod3=");
                Serial.println(mod3);}
              if(mod==4){
                mod4+=1; 
                if(mod4>3){mod4=1;  } 
                Serial.print("mod4=");
                Serial.println(mod4);}
              break;
      
      case 3: /*Serial.println("LONG"); */
              mod +=1 ; 
              mod1=0; 
              mod2=0; 
              mod3=0; 
              mod4=0; //當用LONG切換母模式，將所有子模式歸零
              if(mod>4){mod=1;} 
              Serial.print("mod=");
              Serial.println(mod);
              break;
    }
    //return inp;
}
