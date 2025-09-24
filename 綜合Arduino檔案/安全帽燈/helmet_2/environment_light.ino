void env_light() {
  float sun; //平均環境亮度 A2
  float sun1; //環境亮度 A2 (有三個sun是為了避免突然的樹蔭或強光)
  float sun2; //環境亮度 A2
  float sun3; //環境亮度 A2
  
  if (t % 200 == 1) {
    sun1 = analogRead(A2); //每5秒取樣一次環境亮度A2
  }
  if (t % 200 == 60) {
    sun2 = analogRead(A2); //每5秒取樣一次環境亮度A2
  }
  if (t % 200 == 120) {
    sun3 = analogRead(A2); //每5秒取樣一次環境亮度A2
  }
  sun = (sun1 + sun1 + sun3) / 3; //再將三次的數據做平均A2
}
