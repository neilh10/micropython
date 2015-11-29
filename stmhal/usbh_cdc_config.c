/*
 * usbh_config_cdc.c
 *
 *  Created on: Oct 24, 2015
 *      Author: neilh77
 */
//#include "usbh_def.h"
#include "usbh_core.h"
#include "usbh.h"
#include "usbh_cdc.h"
#include "usbh_cdc_config.h"




static CDC_LineCodingTypeDef UsbhLineCoding[2];
//static CDC_LineCodingTypeDef Usb_DefaultLineCoding;
static CDC_LineCodingTypeDef UsbhDefaultLineCoding[2];

void  pyb_Usbh_GetDefaultConfiguration(USBH_HandleTypeDef *phost,UsbOtgCore_Phy_t CoreId) {

	//assert(phost)
	//assert(CoreId>=2)
	USBH_CDC_GetLineCoding(phost, &UsbhLineCoding[CoreId]);
	UsbhDefaultLineCoding[CoreId] = UsbhLineCoding[CoreId];

}



