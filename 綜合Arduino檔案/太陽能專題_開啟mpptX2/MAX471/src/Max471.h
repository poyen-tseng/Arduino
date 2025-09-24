#ifndef MAX471_H_INCLUDED
#define MAX471_H_INCLUDED
#include <Arduino.h>


class Max471{
public:
    //constructor
    Max471(int voltPin, int ampPin,double refVolt,double offset, double voltPerAmp, double voltRatio);

    //getting value
    double getmVolt();
    double getmAmp();
    double getmWatt();
    
private:
    int _voltPin;
    int _ampPin;
    double _refVolt;
    double _offset;
    double _voltPerAmp;
    double _voltRatio;

};

    
#endif // ESPOBJ_H_INCLUDED
