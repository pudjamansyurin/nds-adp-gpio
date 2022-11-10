# Andes GPIO module for ADP-XC7K160 development board

## Module description
- GPIO initialization for buttons input using interrupt
- GPIO initialization for seven segments as ouput


#### **`main.c`**
```c
#include "nds-adp-gpio/adp_gpio.h"

static void btn_reader(uint32_t event)
{
	// do something with this event button
	switch (event)
	{
		case NDS_GPIO_EVENT_PIN0:
			 break;

		case NDS_GPIO_EVENT_PIN1:
			 break;

		default:
			 break;
	}
}

int main(void)
{
	uint8_t u8_cntr = 0;

	// Initialize buttons
	adp_btnInit(btn_reader);

	// Initialize 7-segment
	adp_7segInit();
    
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
