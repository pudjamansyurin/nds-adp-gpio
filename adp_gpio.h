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

/* Public function declarations */
void adp_btnInit(NDS_GPIO_SignalEvent_t cb_event);
void adp_7segInit(void);
void adp_7segWrite(int channel, int num);

#endif /* NDS_ADP_GPIO_H_ */
