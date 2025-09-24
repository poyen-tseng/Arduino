
int t;   //時間標記
float v; //電壓值 A0
float sun; //平均環境亮度 A2
float sun1; //環境亮度 A2 (有三個sun是為了避免突然的樹蔭或強光)
float sun2; //環境亮度 A2
float sun3; //環境亮度 A2
int b;   //電池電量狀態 2高 1中 0低


void setup() {
  t = 0;
  //A0 use for battery voltage reading
  pinMode(6, OUTPUT);//main light ----pin 6 is "PWMable"----
  pinMode(8, OUTPUT);//side light
  //A2 use for voltage sensor (day or ight)
  pinMode(10, OUTPUT);//tail light
  pinMode(11, OUTPUT);//Buzzer
  pinMode(12, OUTPUT);//small red LED----low voltage indicater
  //剛開機時，做電池初測，供後續作比較
  v = 5.0 * analogRead(A0) / 1023;
  
}

void loop() {
  //定義安全帽的 自動 和 強制開啟 模式
  one(); //注意他的檢測頻率，one裡面的檢測頻率我拿掉了喔，之後要在這裡弄一個檢測頻率出來
  env_light(); //注意他的檢測時間(我裡面原本用的是t為時間變數，預計5秒檢測一次A2所收到的亮度電壓)


}
