/**
  ******************************************************************************
  * @file    USBH_conf.h
  * @author  MCD Application Team
  * @version V3.0.0
  * @date    18-February-2014
  * @brief   General low level driver configuration
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  *This is defined for STM32F405 -
  * Has two USB OTG FS Phy - USB1 and USB2
  * USB1 (12MBits) implementedManual refs as OTG_FS
  *   PYBv1.0 on USB micro AB connector
  *   4 bidirectional endpoints
  *   8 host channels with periodic OUT support
  *   OTG/Host mode power switch ON PB4-BLU-P2 shared with LED-BLUE
  *   Supports HNP/SNP/INP termination resistors for SRP/HNP
  *  
  *  USB2 PHY FS (12Mbits) Manual refs as OTG_HS
  *   PYBv1.0 on pins OTH_HS_DM/PB14  OTG_HS_DP/PB15 
  *   6 bidirectional endpoints
  *   12 host channels with periodic OUT support
  *   USB DMA
  *   
  *   
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBH_CONF__H__
#define __USBH_CONF__H__

#include "stm32f4xx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gc.h"
#include "u_utilities.h"

//Add the following for compatibility with HAL
#define __HAL_RCC_GPIOA_CLK_ENABLE()  __GPIOA_CLK_ENABLE()
#define __HAL_RCC_GPIOB_CLK_ENABLE()  __GPIOB_CLK_ENABLE()
#define __HAL_RCC_GPIOC_CLK_ENABLE()  __GPIOC_CLK_ENABLE()
//#define __GPIOD_CLK_ENABLE()
//#define __GPIOE_CLK_ENABLE()
#define __HAL_RCC_GPIOH_CLK_ENABLE() __GPIOH_CLK_ENABLE()
#define __HAL_RCC_GPIOI_CLK_ENABLE() __GPIOI_CLK_ENABLE()


#define __HAL_RCC_USB_OTG_FS_CLK_ENABLE()  __USB_OTG_FS_CLK_ENABLE()
#define __HAL_RCC_USB_OTG_FS_CLK_DISABLE() __USB_OTG_FS_CLK_DISABLE()

#define __HAL_RCC_USB_OTG_HS_CLK_ENABLE()  __USB_OTG_HS_CLK_ENABLE()
#define __HAL_RCC_USB_OTG_HS_CLK_DISABLE()  __USB_OTG_HS_CLK_DISABLE()
#define __HAL_RCC_USB_OTG_HS_ULPI_CLK_ENABLE() __USB_OTG_HS_ULPI_CLK_ENABLE()
#define __HAL_RCC_USB_OTG_HS_ULPI_CLK_DISABLE() __USB_OTG_HS_ULPI_CLK_DISABLE()

/* Includes ------------------------------------------------------------------*/

/** @addtogroup USBH_OTG_DRIVER
  * @{
  */
  
/** @defgroup USBH_CONF
  * @brief usb otg low level driver configuration file
  * @{
  */ 

/** @defgroup USBH_CONF_Exported_Defines
  * @{
  */ 

#define USBH_MAX_NUM_ENDPOINTS                2
//#define USBH_MAX_NUM_INTERFACES               2
#define USBH_MAX_NUM_INTERFACES               2
#define USBH_MAX_NUM_CONFIGURATION            1
#define USBH_KEEP_CFG_DESCRIPTOR              1
#define USBH_MAX_NUM_SUPPORTED_CLASS          1
#define USBH_MAX_SIZE_CONFIGURATION           0x200
#define USBH_MAX_DATA_BUFFER                  0x200
#define USBH_DEBUG_LEVEL                      3
//#define USBH_USE_OS                           1
#define USBH_USE_OS                           0

/** @defgroup USBH_Exported_Macros
  * @{
  */ 

 /* Memory management macros */   
#define USBH_malloc(p1)           gc_alloc (p1,0)
#define USBH_free                 gc_free
#define USBH_memset               memset
#define USBH_memcpy               memcpy
    
 /* DEBUG macros */  

#if (USBH_DEBUG_LEVEL > 0)
#define  USBH_UsrLog  tprintf
#else
#define USBH_UsrLog(...)
#endif


#if (USBH_DEBUG_LEVEL > 1)

#define  USBH_ErrLog  tprintf
#else
#define USBH_ErrLog(...)
#endif


#if (USBH_DEBUG_LEVEL > 2)
#define  USBH_DbgLog   tprintf
#else
#define USBH_DbgLog(...)
#endif

/*
#if (USBH_DEBUG_LEVEL > 0)
#define  USBH_UsrLog(...)   printf(__VA_ARGS__);\
                            printf("\n");
#else
#define USBH_UsrLog(...)
#endif


#if (USBH_DEBUG_LEVEL > 1)

#define  USBH_ErrLog(...)   printf("ERROR: ") ;\
                            printf(__VA_ARGS__);\
                            printf("\n");
#else
#define USBH_ErrLog(...)
#endif


#if (USBH_DEBUG_LEVEL > 2)
#define  USBH_DbgLog(...)   printf("DEBUG : ") ;\
                            printf(__VA_ARGS__);\
                            printf("\n");
#else
#define USBH_DbgLog(...)
#endif
*/
/**
  * @}
  */ 
   
/**
  * @}
  */ 


/** @defgroup USBH_CONF_Exported_Types
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USBH_CONF_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup USBH_CONF_Exported_Variables
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup USBH_CONF_Exported_FunctionsPrototype
  * @{
  */ 
/**
  * @}
  */ 


#endif //__USBH_CONF__H__


/**
  * @}
  */ 

/**
  * @}
  */ 
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

