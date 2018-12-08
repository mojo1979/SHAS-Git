/*******************************************************************************
* File Name: A_SENS.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_A_SENS_H)
#define CY_AMUX_A_SENS_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*        Function Prototypes
***************************************/

void A_SENS_Start(void) ;
#define A_SENS_Init() A_SENS_Start()
void A_SENS_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void A_SENS_Stop(void); */
/* void A_SENS_Select(uint8 channel); */
/* void A_SENS_Connect(uint8 channel); */
/* void A_SENS_Disconnect(uint8 channel); */
/* void A_SENS_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define A_SENS_CHANNELS  3u
#define A_SENS_MUXTYPE   1
#define A_SENS_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define A_SENS_NULL_CHANNEL 0xFFu
#define A_SENS_MUX_SINGLE   1
#define A_SENS_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if A_SENS_MUXTYPE == A_SENS_MUX_SINGLE
# if !A_SENS_ATMOSTONE
#  define A_SENS_Connect(channel) A_SENS_Set(channel)
# endif
# define A_SENS_Disconnect(channel) A_SENS_Unset(channel)
#else
# if !A_SENS_ATMOSTONE
void A_SENS_Connect(uint8 channel) ;
# endif
void A_SENS_Disconnect(uint8 channel) ;
#endif

#if A_SENS_ATMOSTONE
# define A_SENS_Stop() A_SENS_DisconnectAll()
# define A_SENS_Select(channel) A_SENS_FastSelect(channel)
void A_SENS_DisconnectAll(void) ;
#else
# define A_SENS_Stop() A_SENS_Start()
void A_SENS_Select(uint8 channel) ;
# define A_SENS_DisconnectAll() A_SENS_Start()
#endif

#endif /* CY_AMUX_A_SENS_H */


/* [] END OF FILE */
