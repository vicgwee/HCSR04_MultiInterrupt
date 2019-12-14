#define maximum_no_of_HC_SR04s 3    

#include "HC_SR04MultiInterrupt.h"

namespace HC_SR04MultiInterrupt{
    uint8_t instance_counter;
    uint8_t trig_pin[maximum_no_of_HC_SR04s];
    uint8_t echo_pin[maximum_no_of_HC_SR04s];
    volatile uint32_t start_time[maximum_no_of_HC_SR04s];
    volatile uint32_t end_time[maximum_no_of_HC_SR04s];
    volatile bool finished[maximum_no_of_HC_SR04s];

    void echo_ISR_generic(uint8_t instance){
        switch(digitalRead(echo_pin[instance])){
        case HIGH:
            start_time[instance]=micros();
            break;
        case LOW:
            end_time[instance]=micros();
            finished[instance]=true;
            break;
        }
    }

    void echo_ISR_0() {
        echo_ISR_generic(0);
    }

    void echo_ISR_1() {
        echo_ISR_generic(1);
    }

    void echo_ISR_2() {
        echo_ISR_generic(2);
    }
    
    #if maximum_no_of_HC_SR04s > 3
    void echo_ISR_3() {
        echo_ISR_generic(3);
    }
    
    void echo_ISR_4() {
        echo_ISR_generic(4);
    }

    void echo_ISR_5() {
        echo_ISR_generic(5);
    }

    void echo_ISR_6() {
        echo_ISR_generic(6);
    }

    void echo_ISR_7() {
        echo_ISR_generic(7);
    }

    void echo_ISR_8() {
        echo_ISR_generic(8);
    }

    void echo_ISR_9() {
        echo_ISR_generic(9);
    }
    #endif
    #if maximum_no_of_HC_SR04s > 10
    void echo_ISR_10() {
        echo_ISR_generic(10);
    }

    void echo_ISR_11() {
        echo_ISR_generic(11);
    }

    void echo_ISR_12() {
        echo_ISR_generic(12);
    }

    void echo_ISR_13() {
        echo_ISR_generic(13);
    }

    void echo_ISR_14() {
        echo_ISR_generic(14);
    }

    void echo_ISR_15() {
        echo_ISR_generic(15);
    }

    void echo_ISR_16() {
        echo_ISR_generic(16);
    }

    void echo_ISR_17() {
        echo_ISR_generic(17);
    }

    void echo_ISR_18() {
        echo_ISR_generic(18);
    }

    void echo_ISR_19() {
        echo_ISR_generic(19);
    }
    #endif
}


HC_SR04::HC_SR04(uint8_t trigger, uint8_t echo, uint8_t pulse_microseconds, uint16_t max_dist)
    : _pulse_microseconds(pulse_microseconds)
{ 
    using namespace HC_SR04MultiInterrupt;
    _instance = instance_counter;
    if(_instance < maximum_no_of_HC_SR04s){
        trig_pin[_instance] = trigger;
        echo_pin[_instance] = echo;
        finished[_instance] = false;
        instance_counter++;
    }
}

void HC_SR04::begin(){
    _begin(_instance);
}

void HC_SR04::_begin(uint8_t instance){
    using namespace HC_SR04MultiInterrupt;
    pinMode(trig_pin[instance], OUTPUT);
    digitalWrite(trig_pin[instance], LOW);
    pinMode(echo_pin[instance], INPUT);  
    switch (instance) {
        case 0:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_0, CHANGE);
            break;
        case 1:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_1, CHANGE);
            break;
        case 2:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_2, CHANGE);
            break;
    #if (maximum_no_of_HC_SR04s > 3)
        case 3:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_3, CHANGE);
            break;
        case 4:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_4, CHANGE);
            break;
        case 5:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_5, CHANGE);
            break;
        case 6:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_6, CHANGE);
            break;
        case 7:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_7, CHANGE);
            break;
        case 8:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_8, CHANGE);
            break;
        case 9:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_9, CHANGE);
            break;
    #endif
    #if (maximum_no_of_HC_SR04s > 10)
        case 10:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_10, CHANGE);
            break;
        case 11:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_11, CHANGE);
            break;
        case 12:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_12, CHANGE);
            break;
        case 13:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_13, CHANGE);
            break;
        case 14:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_14, CHANGE);
            break;
        case 15:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_15, CHANGE);
            break;
        case 16:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_16, CHANGE);
            break;
        case 17:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_17, CHANGE);
            break;
        case 18:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_18, CHANGE);
            break;
        case 19:
            attachInterrupt(digitalPinToInterrupt(echo_pin[instance]), echo_ISR_19, CHANGE);
            break;
    #endif
    }
}

void HC_SR04::start(){
    using namespace HC_SR04MultiInterrupt;
    finished[_instance]=false;
    digitalWrite(trig_pin[_instance], HIGH);
    delayMicroseconds(_pulse_microseconds);
    digitalWrite(trig_pin[_instance], LOW);  
}

uint16_t HC_SR04::getRange(){
    using namespace HC_SR04MultiInterrupt;
    return ((end_time[_instance]-start_time[_instance])*353/2048); //elapsed / 5.8
}

bool HC_SR04::isFinished(){
    return HC_SR04MultiInterrupt::finished[_instance]; 
}