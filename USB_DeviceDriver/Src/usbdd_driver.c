/*
 * usbdd_driver.c
 *
 *  Created on: 14-Mar-2023
 *      Author: Neel.Madhav
 */

//USB_OTG_GlobalTypeDef
#include "usbdd_driver.h"
void USB_Init(void)
{
	//Enable Clock for AHB1 and GPIOB
	RCC-> AHB1ENR |= (1 << 1);

	//Set Alternate functionality mode
	GPIOB -> AFR[1] |= (0b1100 << 24);
	GPIOB -> AFR[1] |= (0b1100 << 28);

	//Configure USB pins to work in alternate functionality mode
	GPIOB -> MODER |= (0b1010 << 28);

}

void Core_Init(void)
{
	//Enable clock for USB core
	RCC-> AHB1ENR |= (1 << 29);

	//Configure the USB core to run in device mode and to use the embedded full speed PHY
	USB_OTG_HS -> GUSBCFG |= (1 << 6) | (0x09 << 10) | (1 << 30);

	//Enable VBUS sensing device
	USB_OTG_HS -> GCCFG |= (1 << 21);

	//Un-mask the main USB core interrupts
	USB_OTG_HS -> GINTMSK |= (1 << 12) | (1 << 13) | (1 << 3) | (1 << 11) | (1 << 18) | (1 << 5) | (1 << 31);

	//Clear all pending core interrupts
	USB_OTG_HS -> GINTSTS = 0xFFFFFFFF;

	//Un-mask USB global interrupts
	USB_OTG_HS -> GAHBCFG |= (1 << 0);
}

void Connect(void)
{
	USB_OTG_HS -> GCCFG |= (1 << 16);
	//USB_OTG_DeviceTypeDef -> DCTL &= ~(1 << 1);
	//USB_OTG_HS_DEVICE
}

void Disconnect(void)
{
	USB_OTG_HS -> GCCFG &= ~(1 << 16);
	//USB_OTG_DeviceTypeDef -> DCTL |= (1 << 1);
}
