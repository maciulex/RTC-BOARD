//#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <stdio.h>
#include "RTC.cpp"

#define ALLWAYS_HIGHT 15
#define INPUT_ONE 14
#define INPUT_TWO 13
#define INPUT_THREE 12



void loop() {
    RTC::init();
    while (true) {
        if (gpio_get(INPUT_ONE)) {
            RTC::test();
        } else if (gpio_get(INPUT_TWO)) {
            RTC::test2();
        } else if (gpio_get(INPUT_THREE)) {
            RTC::test4();
        } else {
            RTC::test3();
        }
        sleep_ms(999);
    }    
}

int main() {
    stdio_init_all();

    gpio_init(ALLWAYS_HIGHT);
    gpio_set_dir(ALLWAYS_HIGHT, GPIO_OUT);
    gpio_put(ALLWAYS_HIGHT, 1);

    gpio_init(INPUT_ONE);
    gpio_set_dir(INPUT_ONE, GPIO_IN);
    
    gpio_init(INPUT_TWO);
    gpio_set_dir(INPUT_TWO, GPIO_IN);

    gpio_init(INPUT_THREE);
    gpio_set_dir(INPUT_THREE, GPIO_IN);
    sleep_ms(1);
    loop();

    return 0;
}