/*
 * adp_gpio.h
 *
 *  Created on: May 24, 2022
 *      Author: pujak
 */

#ifndef NDS_ADP_GPIO_H_
#define NDS_ADP_GPIO_H_

#include "Driver_GPIO.h"
#include <stdint.h>

/* Public function declarations --------------------------------------------- */
void adp_init(NDS_GPIO_SignalEvent_t cb_event);
void adp_pinInit(uint32_t u32_mask, uint8_t u8_isOutput);
void adp_7segWrite(int channel, int num);

#endif /* NDS_ADP_GPIO_H_ */
