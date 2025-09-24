
#include "I2Cdev.h"
#include "MPU6050.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif
MPU6050 accelgyro;
int16_t ax, ay, az, gx, gy, gz;
float aax, aay, aaz ,avg;
float ggx, ggy ,ggz ,ggg;
int t ,ggg3 ,ggg1 , ggg2 ;
long ggga;
#define OUTPUT_READABLE_ACCELGYRO

void setup() {
  t=0;
  ggg3=0;
  ggg1=0;
  ggg2=0;
  pinMode(6, OUTPUT);
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    Serial.begin(38400);
    accelgyro.initialize();

    // use the code below to change accel/gyro offset values
    /*
    Serial.println("Updating internal sensor offsets...");
    // -76  -2359 1688  0 0 0
    Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print("\n");
    accelgyro.setXGyroOffset(220);
    accelgyro.setYGyroOffset(76);
    accelgyro.setZGyroOffset(-85);
    Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print("\n");
    */
}

void loop() {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
   //t=sqrt(sq(ax)*1L+sq(ay)*1L+sq(az)*1L);
    //aax=(ax-1084)/1632.65;
    //aay=(ay-148)/1632.65;
    //aaz=(az+1933)/1632.65;
   // avg=(sqrt(sq(aax)+sq(aay)+sq(aaz)));
    ggx=(gx+400 );
    ggy=(gy+188 );
    ggz=(gz+378 );
    ggg=sqrt(sq(ggx)+sq(ggy)+sq(ggz));
    if(t<3){
      t++;
    }
    
    if(t==1){
      ggg1=ggg/10;
     }
    Serial.print(" ggg1: "); 
    Serial.print(ggg1);
    if(t==2){
      ggg2=ggg/10;
    }
    Serial.print("\tggg2: "); 
    Serial.print(ggg2);
    if(t==3){
      ggg3=ggg/10;
    }
    Serial.print("\tggg3: ");
    Serial.print(ggg3);
    ggga=ggg3+ggg1+ggg2;
    Serial.print("\tt ");
    Serial.print(t);
    if(t>2){
      t=0;
    }
    #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
        //Serial.print("a/g:\t");
        //Serial.print("ax: ");Serial.print(aax); 
        //Serial.print(" ay: ");Serial.print(aay); 
        //Serial.print(" az: ");Serial.print(aaz);
        //Serial.println();         
        //Serial.print(" gx: "); 
        //Serial.print(ggx);
        //Serial.print(" gy: "); 
        //Serial.print(ggy);
        //Serial.print("\tgz: ");
        //Serial.print(ggz);
        
        
        Serial.print("\tggg:  ");
        Serial.print(ggg);
        Serial.print("\tggga:  ");
        Serial.println(ggga);

    #endif
    /*
    if (avg>=11.5){
      digitalWrite(6,HIGH);
      delay(1000);
    }
    else{
      digitalWrite(6,LOW);
      
    }
    */
    delay(500);
}
