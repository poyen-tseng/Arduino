//定義 自動 模式 (白天：主燈6閃爍)(晚上：主燈6恆亮、副燈8閃爍)
void front_back(){
  
    if (sun < 512 && t % 25 == 0 ) {
      //白天電阻小，分得電壓少  主燈6亮    副燈8恆暗  尾燈10亮

      digitalWrite (6, HIGH);
      digitalWrite (8, LOW );
      digitalWrite (10, HIGH);
    }
    if (sun < 512 && t % 25 == 1) {
      //白天電阻小，分得電壓少  主燈6暗    副燈8恆暗  尾燈10暗
      digitalWrite (6, LOW);
      digitalWrite (8, LOW );
      digitalWrite (10, LOW);
    }
    if (sun > 512 && t % 10 == 0 ) {
      //晚上電阻大，分得電壓多  主燈6恆亮   副燈8亮   尾燈10亮
      digitalWrite (6, HIGH);
      digitalWrite (8, HIGH );
      digitalWrite (10, HIGH);
    }
    if (sun > 512 && t % 10 == 1) {
      //白天電阻小，分得電壓少  主燈6恆亮   副燈8暗   尾燈10暗
      digitalWrite (6, HIGH);
      digitalWrite (8, LOW );
      digitalWrite (10, LOW);
    }
}    
