#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "gpio.hpp"


constexpr size_t GPIO_SIZE = 0x1000;

int main() {
    int mem_fd = open("/dev/gpiomem", O_RDWR | O_SYNC);
    if (mem_fd < 0) {
        perror("Failed to open /dev/mem");
        return EXIT_FAILURE;
    }

    volatile uint32_t *mapped= (volatile uint32_t *)mmap(
        nullptr,
         GPIO_SIZE,
         PROT_READ | PROT_WRITE,
         MAP_SHARED,
         mem_fd,
         0
        //bcm2837::gpio::BASE
    );

    if (mapped == MAP_FAILED) {
        perror("Failed to mmap GPIO");
        close(mem_fd);
        return EXIT_FAILURE;
    }

    
    // Cast to volatile uint32_t* — every read/write now hits hardware.
    // reinterpret_cast is correct here: we ARE reinterpreting a void*
    // as a hardware register block.
    volatile uint32_t *gpio_base  = reinterpret_cast<volatile uint32_t *>(mapped);


    // Example: Configure GPIO pin 17 as output and toggle it
    gpio::GpioConfig led = {.pin = 21, bcm2837::gpio::FUNC_OUTPUT};
    gpio::configure_pin(gpio_base, led);

    for (int i = 0; i <100 ;++i) {
        gpio::set_pin(gpio_base, 21);
        usleep(500000); // Sleep for 500ms
        gpio::clear_pin(gpio_base, 21);
        usleep(500000); // Sleep for 500ms
        printf("%d Nithya Toggled GPIO 21 \n", i);
    }

    munmap((void *)gpio_base, GPIO_SIZE);
    close(mem_fd);
    return EXIT_SUCCESS;
}