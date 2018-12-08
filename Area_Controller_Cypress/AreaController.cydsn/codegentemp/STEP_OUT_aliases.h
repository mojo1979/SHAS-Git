/*******************************************************************************
* File Name: STEP_OUT.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_STEP_OUT_ALIASES_H) /* Pins STEP_OUT_ALIASES_H */
#define CY_PINS_STEP_OUT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define STEP_OUT_0			(STEP_OUT__0__PC)
#define STEP_OUT_0_INTR	((uint16)((uint16)0x0001u << STEP_OUT__0__SHIFT))

#define STEP_OUT_1			(STEP_OUT__1__PC)
#define STEP_OUT_1_INTR	((uint16)((uint16)0x0001u << STEP_OUT__1__SHIFT))

#define STEP_OUT_2			(STEP_OUT__2__PC)
#define STEP_OUT_2_INTR	((uint16)((uint16)0x0001u << STEP_OUT__2__SHIFT))

#define STEP_OUT_3			(STEP_OUT__3__PC)
#define STEP_OUT_3_INTR	((uint16)((uint16)0x0001u << STEP_OUT__3__SHIFT))

#define STEP_OUT_INTR_ALL	 ((uint16)(STEP_OUT_0_INTR| STEP_OUT_1_INTR| STEP_OUT_2_INTR| STEP_OUT_3_INTR))

#endif /* End Pins STEP_OUT_ALIASES_H */


/* [] END OF FILE */
