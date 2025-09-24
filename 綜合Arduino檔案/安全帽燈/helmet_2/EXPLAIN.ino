/*-----------程式簡化tips--------------
 * 使用millis
 * 環境亮度偵測從「sun1,sun2,sun3加總取平均」改成「sun+= += += /3」節省變數資源
 * 先做好硬體！
 * 做硬體前先找好腳位
 * 
 */
 /*-----------硬體設計順序--------------
  * https://www.mindomo.com/zh/mindmap/ff3773441161465880948d8e86c2893c
  * 大麵包版
  * 裝LGT8F328P(X)LGT是災難
  * 裝普通LED
  * 裝無源蜂鳴器(聲音nice)
  * 標籤貼杜邦線電池輸入
  * 電阻分壓後接上電壓讀取腳位
  * 接上光敏(暗5000K亮1K)
  * 寫清楚哪隻腳有內部上拉，把標籤貼在麵包版上
  * 裝上微動開關*2(鳴笛&互動鍵)(因為內部上拉電阻，開關要通往GND)
  * 
  */
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
 * 鳴笛示警也要有喚醒的功能
 * 
 * 
 */
/*------------其他功能註記-------------
 * 簡少開機時的延遲時間
 * 加入左後方的車輛警示(超音波測距模組)
 * //PORTB 代替digitalWrite，加速
 * 
 * 
 */
 /*----------模式註記---------
  * 一般(有感光)，細分成簡易模式、高照明模式、高警示模式
  * 
  * 記得加入鳴笛示警功能(要能從休眠中甦醒，再自己進入休眠)
  * 鳴笛旋律先擱置
  * 
  * 手電筒
  * 
  * 回報，細分成電壓、氣溫
  *  
  * 
  * SOS
  * 
  * 
  * 
  * 
  * 
  */
 /*--------電池電壓註記----------
  * 鋰離子電池
  * 0/3.2/3.7
  * 
  * 磷酸鐵鋰電池
  * 0/3.18/3.6
  */

/*
should use Switch to decide whether flash or not.
Or add simple mode to save power
The main mode should have secondary light always on ,and main light mostly on and close 0.5hz in purpose of alerting.
The simple mode should have main and make two secondary light flash alternately 0.7hz, and the tail light only middle one.
Middle tail light mostly dim and flashing(?) only brighter while bike brake.
MCU power will be LD0 to 2.5v.
Buck-Boost power will be 4.2v to 2.5v
LED power will be 3.4v.
buzzer power will be 3.4v also.
MPU power will be 3.4v




*/


/*========the v3
