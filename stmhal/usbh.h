/*
 * usbh.h
 *
 *  Created on: Oct 24, 2015
 *      Author: neilh77
 */

#ifndef STMHAL_USBH_H_
#define STMHAL_USBH_H_

typedef enum {
	// The physical IDs are used in the HAL
	USB_OTG_FS_CORE_ID=1,
	USB_OTG_HS_CORE_ID=0
} UsbOtgCore_Phy_t;

typedef enum {
  USBHAS_APPLICATION_IDLE = 0,
  USBHAS_APPLICATION_START,
  USBHAS_APPLICATION_READY,
  USBHAS_APPLICATION_RUNNING,
  USBHAS_APPLICATION_DISCONNECT,
} Usbh_AppState_t;


/* In HS mode and when the DMA is used, all variables and data structures dealing
   with the DMA during the transaction process should be 4-bytes aligned */

#if defined   (__GNUC__)        /* GNU Compiler */
  #define __ALIGN_END    __attribute__ ((aligned (4)))
  #define __ALIGN_BEGIN
#else
  #define __ALIGN_END
  #if defined   (__CC_ARM)      /* ARM Compiler */
    #define __ALIGN_BEGIN    __align(4)
  #elif defined (__ICCARM__)    /* IAR Compiler */
    #define __ALIGN_BEGIN
  #elif defined  (__TASKING__)  /* TASKING Compiler */
    #define __ALIGN_BEGIN    __align(4)
  #endif /* __CC_ARM */
#endif /* __GNUC__ */



#endif /* STMHAL_USBH_H_ */
