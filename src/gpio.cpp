#include "gpio.hpp"

namespace gpio {

     void configure_pin(volatile uint32_t *gpio_base, const GpioConfig &config) {
        uint64_t reg_offset = bcm2837::gpio::GPFSEL0 + (config.pin / 10) * 4;
        uint64_t bit_pos = (config.pin % 10) * 3;

        uint32_t reg_value = read_reg(gpio_base, reg_offset);
        reg_value &= ~(0b111 << bit_pos); // Clear existing function
        reg_value |= (config.function << bit_pos); // Set new function
        write_reg(gpio_base, reg_offset, reg_value);
    }

    void set_pin(volatile uint32_t *gpio_base, uint8_t pin) {
        uint64_t reg_index = pin / 32;
        uint64_t bit_pos = pin % 32;
        write_reg(gpio_base, bcm2837::gpio::GPSET0 + reg_index * 4, (1u << bit_pos));
    }

    void clear_pin(volatile uint32_t *gpio_base, uint8_t pin) {
        uint64_t reg_index = pin / 32;
        uint64_t bit_pos = pin % 32;
        write_reg(gpio_base, bcm2837::gpio::GPCLR0 + reg_index * 4, (1u << bit_pos));
    }

    bool read_pin(volatile uint32_t *gpio_base, uint8_t pin) {
        uint64_t reg_index = pin / 32;
        uint64_t bit_pos = pin % 32;
        return (read_reg(gpio_base, bcm2837::gpio::GPLEV0 + reg_index * 4) >> bit_pos) & 1u;
    }

    
}