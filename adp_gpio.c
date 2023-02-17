/*
 * adp_gpio.c
 *
 *  Created on: May 24, 2022
 *      Author: pujak
 */

#include "adp_gpio.h"

/* Private macros ------------------------------------------------------------*/
#define GPIO_BTNS_USED_MASK   0x000000ff
#define GPIO_7SEG_USED_MASK   0xffff0000
#define GPIO_7SEG1_OFFSET     16
#define GPIO_7SEG2_OFFSET     24

/* External variables --------------------------------------------------------*/
extern NDS_DRIVER_GPIO Driver_GPIO;

/* Private variables -------------------------------------------------------- */
static const uint8_t segments[10] = {
    0x3f, 0x06, 0xdb, 0x4f, 0xe6,
    0x6d, 0xfc, 0x07, 0x7f, 0x67
};

/* Private function definitions ----------------------------------------------*/
static void segment_write(int offset, int num)
{
    Driver_GPIO.Write(0xFF << offset, 1);
    Driver_GPIO.Write(segments[num%10] << offset, 0);
}

/* Public function definitions ---------------------------------------------- */
void adp_init(NDS_GPIO_SignalEvent_t cb_event)
{
    // initialize GPIO
    Driver_GPIO.Initialize(cb_event);

    // initialize push buttons
    adp_pinInit(GPIO_BTNS_USED_MASK, NDS_GPIO_DIR_INPUT);

    // initialize 7-segments
    adp_pinInit(GPIO_7SEG_USED_MASK, NDS_GPIO_DIR_OUTPUT);
}

void adp_pinInit(uint32_t u32_mask, uint8_t u8_isOutput)
{
    if (u8_isOutput)
    {
        // set GPIO direction as output
        Driver_GPIO.SetDir(u32_mask, NDS_GPIO_DIR_OUTPUT);
    }
    else
    {
        // set GPIO direction as input
        Driver_GPIO.SetDir(u32_mask, NDS_GPIO_DIR_INPUT);

        // Set interrupt mode to negative edge and enable it
        Driver_GPIO.Control(NDS_GPIO_SET_INTR_NEGATIVE_EDGE 
                            | NDS_GPIO_INTR_ENABLE,
                            u32_mask);
    }
}

void adp_7segWrite(int channel, int num)
{
    switch (channel) {
        case 0:
            segment_write(GPIO_7SEG1_OFFSET, num);
            break;
        case 1:
            segment_write(GPIO_7SEG2_OFFSET, num);
            break;
        default:
            segment_write(GPIO_7SEG1_OFFSET, num % 10);
            segment_write(GPIO_7SEG2_OFFSET, num / 10);
            break;
    }
}


