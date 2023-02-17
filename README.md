# Andes GPIO module for ADP-XC7K160 development board

## Module description
- GPIO initialization for buttons input using interrupt
- GPIO initialization for seven segments as ouput


#### **`main.c`**
```c
#include "nds-adp-gpio/adp_gpio.h"

/* Private function definitions --------------------------------------------- */
static void gpio_callback(uint32_t u32_pin)
{
    // do something with this event button
    switch (u32_pin)
    {
        case NDS_GPIO_EVENT_PIN0:
             break;

        case NDS_GPIO_EVENT_PIN8:
             break;

        default:
             break;
    }
}

/* Public function definitions ---------------------------------------------- */
int main(void)
{
    uint8_t u8_cntr = 0;

    // Initialize buttons
    adp_init(gpio_callback);

    // Initialize other GPIO
    adp_pinInit(NDS_GPIO_EVENT_PIN8, NDS_GPIO_DIR_INPUT);
    
    // Set each 7-segment channel to zero
    adp_7segWrite(0, 0);
    adp_7segWrite(1, 0);

    while(1) {
        // Set all 7-segment channel at once
        adp_7segWrite(-1, u8_cntr++);
        delay(1);
    }
}

```
