else {
    //定義 強制開啟 模式 (主燈、副燈 皆亮  尾燈暗)
    digitalWrite (6, HIGH);//main light
    digitalWrite (8, HIGH);//side light
    digitalWrite (10, LOW);//tail light
  }
