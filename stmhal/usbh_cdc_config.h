/*
 * usbh_cdc_config.h
 *
 *  Created on: Oct 24, 2015
 *      Author: neilh77
 */

#ifndef STMHAL_USBH_CDC_CONFIG_H_
#define STMHAL_USBH_CDC_CONFIG_H_


void pyb_Usbh_GetDefaultConfiguration(USBH_HandleTypeDef *phost,UsbOtgCore_Phy_t CoreId);
void pyb_Usbh_CDC_SendFile(USBH_HandleTypeDef *phost,uint8_t fileidx);//from CDC_Standalone\src\cdc_send.c

#endif /* STMHAL_USBH_CDC_CONFIG_H_ */
