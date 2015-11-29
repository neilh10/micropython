/*
 * usbh.c
 *
 *  Created on: Oct 24, 2015
 *      Author: neilh77
 */



#include "usbh_core.h"
#include "usbh.h"
#include "usbh_cdc.h"
#include "usbh_cdc_config.h"
#include "usbh_conf.h"



__ALIGN_BEGIN  USBH_HandleTypeDef hUSBH_FS_Otg __ALIGN_END; //Otg_FS
__ALIGN_BEGIN  USBH_HandleTypeDef hUSBH_HS_Otg __ALIGN_END; //Otg_HS

Usbh_AppState_t UsbhFSCdc_ApplState_e =  USBHAS_APPLICATION_IDLE;
Usbh_AppState_t UsbhHSCdc_ApplState_e =  USBHAS_APPLICATION_IDLE;

static int hostFS_is_enabled = 0;
static int hostHS_is_enabled = 0;


#define RX_BUFF_SIZE   0x400  /* Max Received data 1KB */
uint8_t CDC_RX_Buffer[RX_BUFF_SIZE]; //This would be part of the users zone

void (* pUsbHSCDC_callback )(struct _USBH_HandleTypeDef *pHandle, uint8_t  *rxBuffer, uint8_t size);
USBH_StatusTypeDef pyb_UsbhHS_CDC_ReceiveRegister(uint8_t  *CDC_RX_BufferIn, uint32_t RX_BUFF_SIZE_IN,
		 void (*pUsrFunc)(USBH_HandleTypeDef *phost,uint8_t  *rxBuffer, uint8_t size)
		) {

	pUsbHSCDC_callback = pUsrFunc;
	//TODO - register supplied buffer

	return USBH_OK;
}
static void DbgDumpReceivedData(USBH_HandleTypeDef *phost,uint8_t *pbuff, uint32_t length)
{
  USBH_DbgLog("UsbhHS Rx data size=%d",(int)length);
  //while(size--)  {  }
}


//USBH_CDC_Receive(&hUSBHost, CDC_RX_Buffer, RX_BUFF_SIZE);
void USBH_CDC_ReceiveCallback(USBH_HandleTypeDef *phost)
{
  uint16_t size;
  //uint8_t *ptr = CDC_RX_Buffer;

  size = USBH_CDC_GetLastReceivedDataSize(phost);
 //Check which USB called back (&hUSBH_HS_Otg == phost)
  /* user callback for end of device basic enumeration */
   if(pUsbHSCDC_callback != NULL)
   {
	   pUsbHSCDC_callback(phost, CDC_RX_Buffer,size); //TODO - change to supplied buffer
   }
  DbgDumpReceivedData(phost,CDC_RX_Buffer,size);

  USBH_CDC_Receive(&hUSBH_HS_Otg, CDC_RX_Buffer, RX_BUFF_SIZE); //use !next buffer
}


USBH_StatusTypeDef pyb_UsbhHS_CDC_Transmit(uint8_t  *CDC_TX_Buffer, uint32_t TX_BUFF_SIZE) {

	USBH_StatusTypeDef Status = USBH_BUSY;
	if ( USBHAS_APPLICATION_READY== UsbhHSCdc_ApplState_e ) {
		Status = USBH_CDC_Transmit(&hUSBH_HS_Otg, CDC_TX_Buffer, TX_BUFF_SIZE);
	} //TODO FUT take buffer and transmit when ready
	return Status;
}

void USBH_CDC_TransmitCallback(USBH_HandleTypeDef *phost)
{
	USBH_DbgLog("UsbhHS Evnt CDC Complete");
}

//void pyb_UsbhFS_CoreEvents(USBH_HandleTypeDef *phost, uint8_t id){} //Fut
void pyb_UsbhFS_CoreEvents(USBH_HandleTypeDef *phost, uint8_t id){

// tprintf("usbh.c:UsbhFS Evnt %d",(int)id);
 USBH_DbgLog("UsbhFS Evnt %d",(int)id);
 switch (id) {
 case HOST_USER_SELECT_CONFIGURATION: //CDC end of enumeration
   break;

 case HOST_USER_CLASS_ACTIVE: //TODO Assumes only CDC - but for multi could request class
   pyb_Usbh_GetDefaultConfiguration(&hUSBH_FS_Otg,USB_OTG_FS_CORE_ID);
   UsbhHSCdc_ApplState_e = USBHAS_APPLICATION_READY;
   break;

 case HOST_USER_CLASS_SELECTED:
   //TODO ?? UsbhCdc_ApplState_e = USBHAS_APPLICATION_RUNNING;
   break;

 case HOST_USER_CONNECTION: //Cable plugged in?
	UsbhHSCdc_ApplState_e = USBHAS_APPLICATION_START;
	break;

 case HOST_USER_DISCONNECTION: //Cable Unplugged??
	UsbhHSCdc_ApplState_e = USBHAS_APPLICATION_DISCONNECT;
	break;
 default: //HOST_USER_UNRECOVERED_ERROR
	 //??USBH_ReEnumerate(&hUSBHost);
    break;
 }
}
void pyb_UsbhHS_CoreEvents(USBH_HandleTypeDef *phost, uint8_t id){

 //tprintf("rusbh.c:UsbhHS Evnt %d",(int)id);
 USBH_DbgLog("UsbhHS Evnt %d",(int)id);
 switch (id) {
 case HOST_USER_SELECT_CONFIGURATION: //CDC end of enumeration
   break;

 case HOST_USER_CLASS_ACTIVE: //TODO Assumes only CDC - but for multi could request class
   pyb_Usbh_GetDefaultConfiguration(&hUSBH_HS_Otg,USB_OTG_HS_CORE_ID);
   UsbhHSCdc_ApplState_e = USBHAS_APPLICATION_READY;
   break;

 case HOST_USER_CLASS_SELECTED:
   //TODO ?? UsbhCdc_ApplState_e = USBHAS_APPLICATION_RUNNING;
   break;

 case HOST_USER_CONNECTION: //Cable plugged in?
	UsbhHSCdc_ApplState_e = USBHAS_APPLICATION_START;
	break;

 case HOST_USER_DISCONNECTION: //Cable Unplugged??
	UsbhHSCdc_ApplState_e = USBHAS_APPLICATION_DISCONNECT;
	break;
 default: //HOST_USER_UNRECOVERED_ERROR
	 //??USBH_ReEnumerate(&hUSBHost);
    break;
 }
}

uint32_t v1_old=0x5aa5;
int pyb_usbHS_checkStatus(char *pInfo){
	uint32_t v1; //v2;
	//USB_OTG_GlobalTypeDef *USBx;
	int retStatus=0;

	 //mp_hal_stdout_tx_str("~U~");
	 //USBx = (USB_OTG_GlobalTypeDef*)((HCD_HandleTypeDef)hUSBH_HS_Otg.pData)->instance;
	 v1 = USB_OTG_HS->GINTSTS;
	 //v2 = USB_OTG_HS->GINTMSK;

	 if (v1_old != v1) {
		 tprintf (" %s 0x%X/%x m=%x  s=%x:",
				 pInfo,(unsigned int)v1,(unsigned int)v1_old,(unsigned int)USB_OTG_HS->GINTMSK,
		 	 (unsigned int)hUSBH_HS_Otg.gState);
		 v1_old =v1;
		 retStatus=1;
	 }
	 return retStatus;
}
void pyb_usb_host_init(void) {
    USBH_StatusTypeDef status;

#define MICROPY_USB1_OTG (0)
#define MICROPY_USB2_HOST (1)
#if MICROPY_USB1_OTG
    if (!hostFS_is_enabled) {
        // only init USBH once in the device's power-lifetime
	    /* Init Host Library */

	    //TODO nh
        //TODO del USBH_Init(&USB_OTG_Core, USB_OTG_FS_CORE_ID, &USB_Host, &HID_cb, &USR_Callbacks);
	    status=USBH_Init(&hUSBH_FS_Otg, pyb_UsbhFS_CoreEvents, USB_OTG_FS_CORE_ID);

	//	      void (*pUsrFunc)(USBH_HandleTypeDef *phost, uint8_t ),
	    if (USBH_OK==status) {
	        //TODO from boot.py ??
	        //USBH_RegisterClass(&hUSBH_FS_Otg, USBH_HID_CLASS); //uncomment when tested
	        USBH_RegisterClass(&hUSBH_FS_Otg, USBH_CDC_CLASS); //uncomment when tested
	        //USBH_RegisterClass(&hUSBH_FS_Otg, USBH_MSC_CLASS); //uncomment when tested

	        USBH_Start(&hUSBH_FS_Otg);
	        tprintf("usb1_otg started");

	    } else {
	       USBH_ErrLog("USB1_OtgInitErr %d",status);
	    }

    } {tprintf("usb1_otg init -attempted again");}
    hostFS_is_enabled = 1;
#endif //MICROPY_USB1_OTG

#if MICROPY_USB2_HOST
    if (!hostHS_is_enabled) {
        // only init USBH once in the device's power-lifetime
	    /* Init Host Library */

	    //TODO nh
        //TODO del USBH_Init(&USB_OTG_Core, USB_OTG_FS_CORE_ID, &USB_Host, &HID_cb, &USR_Callbacks);
	    status=USBH_Init(&hUSBH_HS_Otg, pyb_UsbhHS_CoreEvents, USB_OTG_HS_CORE_ID);

	//	      void (*pUsrFunc)(USBH_HandleTypeDef *phost, uint8_t ),
	    if (USBH_OK==status) {
	        //TODO from boot.py ??
	        //USBH_RegisterClass(&hUSBH_HS_Otg, USBH_HID_CLASS); //uncomment when tested
	        USBH_RegisterClass(&hUSBH_HS_Otg, USBH_CDC_CLASS); //uncomment when tested
	        //USBH_RegisterClass(&hUSBH_HS_Otg, USBH_MSC_CLASS); //uncomment when tested

	        USBH_Start(&hUSBH_HS_Otg);
	        tprintf("usb2_host started ");

	    } else {
	       USBH_ErrLog("USB2_HostInit Err %d",status);
	    }

    } {printf("usb2_HostInit -attempted again");}
    hostHS_is_enabled = 1;
#endif //MICROPY_USB2_HOST

}

void pyb_usb_host_process(void) {
    //TODO del USBH_Process(&USB_OTG_Core, &USB_Host);
	int semaChange;
	semaChange = pyb_usbHS_checkStatus("usbhP");

	USBH_Process(&hUSBH_HS_Otg);
	if (semaChange) {tprintf ("-->%x",(unsigned int)hUSBH_HS_Otg.gState);}

}

