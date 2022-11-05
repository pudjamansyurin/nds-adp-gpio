/*
 * adp_gpio.c
 *
 *  Created on: May 24, 2022
 *      Author: pujak
 */

#include "adp_gpio.h"

extern NDS_DRIVER_GPIO Driver_GPIO;
#define GPIO_Dri       Driver_GPIO

/* Private macros */
#define GPIO_SW_USED_MASK     0x000000ff
#define GPIO_7SEG_USED_MASK   0xffff0000
#define GPIO_7SEG1_OFFSET     16
#define GPIO_7SEG2_OFFSET     24

/* Private variables */
static uint8_t segments[10] = {
	0x3f, 0x06, 0xdb, 0x4f, 0xe6,
	0x6d, 0xfc, 0x07, 0x7f, 0x67
};

/* Private function definitions */
static void segment_write(int offset, int num)
{
	GPIO_Dri.Write(0xFF << offset, 1);
	GPIO_Dri.Write(segments[num%10] << offset, 0);
}

/* Public function definitions */
void adp_btnInit(NDS_GPIO_SignalEvent_t cb_event)
{
	// initialize GPIO
	GPIO_Dri.Initialize(cb_event);

	// set GPIO direction (switches: input)
	GPIO_Dri.SetDir(GPIO_SW_USED_MASK, NDS_GPIO_DIR_INPUT);

	// Set switches interrupt mode to negative edge and enable it
	GPIO_Dri.Control(NDS_GPIO_SET_INTR_NEGATIVE_EDGE | NDS_GPIO_INTR_ENABLE,
			GPIO_SW_USED_MASK);
}

void adp_7segInit(void)
{
	// set GPIO direction (7-segments: output)
	GPIO_Dri.SetDir(GPIO_7SEG_USED_MASK, NDS_GPIO_DIR_OUTPUT);
}


void adp_7segWrite(int channel, int num)
{
	switch (channel) {
		case 0:
			segment_write(GPIO_7SEG1_OFFSET, num);
			break;
		case 1:
			segment_write(GPIO_7SEG1_OFFSET, num);
			break;
		default:
			segment_write(GPIO_7SEG1_OFFSET, num % 10);
			segment_write(GPIO_7SEG2_OFFSET, num / 10);
			break;
	}
}


