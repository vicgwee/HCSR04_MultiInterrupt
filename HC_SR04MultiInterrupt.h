#ifndef HC_SR04MultiInterrupt_H
#define HC_SR04MultiInterrupt_H

#include <Arduino.h>
  

class HC_SR04 {
  public:
    HC_SR04(uint8_t trigger, uint8_t echo, uint8_t pulse_microseconds = 10, uint16_t max_dist=2000);
    
    void begin();
    void start();
    bool isFinished();
    uint16_t getRange();
    
  private:
    static void _begin(uint8_t instance);
    uint8_t _instance, _pulse_microseconds;

};

#endif
