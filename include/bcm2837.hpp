# pragma once 
#include <cstdint>

namespace bcm2837 {

    constexpr uint64_t PERIPH_BASE = 0x3F000000;

    namespace gpio {
        constexpr uint64_t BASE = PERIPH_BASE + 0x200000;

        constexpr uint64_t GPFSEL0 =  0x00;
        constexpr uint64_t GPFSEL1 =  0x04;
        constexpr uint64_t GPFSEL2 =  0x08;
        constexpr uint64_t GPFSEL3 =  0x0C;
        constexpr uint64_t GPFSEL4 =  0x10;
        constexpr uint64_t GPFSEL5 =  0x14;
        constexpr uint64_t GPSET0  =  0x1C;
        constexpr uint64_t GPSET1  =  0x20;
        constexpr uint64_t GPCLR0  =  0x28;
        constexpr uint64_t GPCLR1  =  0x2C;
        constexpr uint64_t GPLEV0  =  0x34;
        constexpr uint64_t GPLEV1  =  0x38; 


        constexpr uint64_t FUNC_INPUT  = 0b000;
        constexpr uint64_t FUNC_OUTPUT = 0b001;
        
    }
}