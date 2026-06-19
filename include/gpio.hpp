#pragma once 
#include "bcm2837.hpp"


namespace gpio {

     struct GpioConfig {
        uint8_t pin;
        uint32_t function;
    };


    inline uint32_t read_reg(volatile uint32_t *base,uint64_t offset) {
         return *(base + offset/4);
    }

    inline void write_reg(volatile uint32_t *base,uint64_t offset, uint32_t value) {
         *(base + offset/4) = value;
    }

    void configure_pin(volatile uint32_t *gpio_base, const GpioConfig &config);
    void set_pin(volatile uint32_t *gpio_base, uint8_t pin) ;  
    void clear_pin(volatile uint32_t *gpio_base, uint8_t pin) ; 
    bool read_pin(volatile uint32_t *gpio_base, uint8_t pin) ; 
    
    
 
}