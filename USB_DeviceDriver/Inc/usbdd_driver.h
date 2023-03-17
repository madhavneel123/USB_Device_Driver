/*
 * usbdd.h
 *
 *  Created on: 14-Mar-2023
 *      Author: Neel.Madhav
 */

#ifndef USBDD_DRIVER_H_
#define USBDD_DRIVER_H_

#include "stm32f4xx.h"

void USB_Init(void);
void Core_Init(void);
void Connect(void);
void Disconnect(void);

#endif /* USBDD_DRIVER_H_ */
