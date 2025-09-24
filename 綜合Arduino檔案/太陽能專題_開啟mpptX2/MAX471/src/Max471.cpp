#include "Max471.h"
#include <Arduino.h>

//#define DBG

Max471::Max471(int voltPin, int ampPin,double refVolt,double offset, double voltPerAmp, double voltRatio){
    _voltPin = voltPin;
    _ampPin = ampPin;
    _refVolt = refVolt;
    _offset = offset;
    _voltPerAmp = voltPerAmp;
    _voltRatio = voltRatio;

}

double Max471::getmVolt(){
  return _refVolt * (analogRead(_voltPin) / 1.023) * _voltRatio;
}

double Max471::getmAmp(){
  return (_refVolt * (analogRead(_ampPin) / 1.023) - _offset) / _voltPerAmp;
}

double Max471::getmWatt(){
  return getmAmp() * getmVolt();
}

