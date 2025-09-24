void time_signal(){
if (t >= 1200) {
    t = 0;
  }
  else {
    t += 1;
  }
  delay(30);
  //設定時脈週期，，每30秒繞一圈
}
  
