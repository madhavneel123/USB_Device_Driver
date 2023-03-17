/*
 * usbdd_framework.c
 *
 *  Created on: 14-Mar-2023
 *      Author: Neel.Madhav
 */

#include "usbdd_framework.h"

void USB_Initialize(void)
{
	USB_Init();
	Core_Init();
	Connect();
}

