/*******************************************************************************
* File Name: HCSR04_TRIG.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_HCSR04_TRIG_H) /* Pins HCSR04_TRIG_H */
#define CY_PINS_HCSR04_TRIG_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HCSR04_TRIG_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HCSR04_TRIG__PORT == 15 && ((HCSR04_TRIG__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    HCSR04_TRIG_Write(uint8 value);
void    HCSR04_TRIG_SetDriveMode(uint8 mode);
uint8   HCSR04_TRIG_ReadDataReg(void);
uint8   HCSR04_TRIG_Read(void);
void    HCSR04_TRIG_SetInterruptMode(uint16 position, uint16 mode);
uint8   HCSR04_TRIG_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the HCSR04_TRIG_SetDriveMode() function.
     *  @{
     */
        #define HCSR04_TRIG_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define HCSR04_TRIG_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define HCSR04_TRIG_DM_RES_UP          PIN_DM_RES_UP
        #define HCSR04_TRIG_DM_RES_DWN         PIN_DM_RES_DWN
        #define HCSR04_TRIG_DM_OD_LO           PIN_DM_OD_LO
        #define HCSR04_TRIG_DM_OD_HI           PIN_DM_OD_HI
        #define HCSR04_TRIG_DM_STRONG          PIN_DM_STRONG
        #define HCSR04_TRIG_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define HCSR04_TRIG_MASK               HCSR04_TRIG__MASK
#define HCSR04_TRIG_SHIFT              HCSR04_TRIG__SHIFT
#define HCSR04_TRIG_WIDTH              1u

/* Interrupt constants */
#if defined(HCSR04_TRIG__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HCSR04_TRIG_SetInterruptMode() function.
     *  @{
     */
        #define HCSR04_TRIG_INTR_NONE      (uint16)(0x0000u)
        #define HCSR04_TRIG_INTR_RISING    (uint16)(0x0001u)
        #define HCSR04_TRIG_INTR_FALLING   (uint16)(0x0002u)
        #define HCSR04_TRIG_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define HCSR04_TRIG_INTR_MASK      (0x01u) 
#endif /* (HCSR04_TRIG__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HCSR04_TRIG_PS                     (* (reg8 *) HCSR04_TRIG__PS)
/* Data Register */
#define HCSR04_TRIG_DR                     (* (reg8 *) HCSR04_TRIG__DR)
/* Port Number */
#define HCSR04_TRIG_PRT_NUM                (* (reg8 *) HCSR04_TRIG__PRT) 
/* Connect to Analog Globals */                                                  
#define HCSR04_TRIG_AG                     (* (reg8 *) HCSR04_TRIG__AG)                       
/* Analog MUX bux enable */
#define HCSR04_TRIG_AMUX                   (* (reg8 *) HCSR04_TRIG__AMUX) 
/* Bidirectional Enable */                                                        
#define HCSR04_TRIG_BIE                    (* (reg8 *) HCSR04_TRIG__BIE)
/* Bit-mask for Aliased Register Access */
#define HCSR04_TRIG_BIT_MASK               (* (reg8 *) HCSR04_TRIG__BIT_MASK)
/* Bypass Enable */
#define HCSR04_TRIG_BYP                    (* (reg8 *) HCSR04_TRIG__BYP)
/* Port wide control signals */                                                   
#define HCSR04_TRIG_CTL                    (* (reg8 *) HCSR04_TRIG__CTL)
/* Drive Modes */
#define HCSR04_TRIG_DM0                    (* (reg8 *) HCSR04_TRIG__DM0) 
#define HCSR04_TRIG_DM1                    (* (reg8 *) HCSR04_TRIG__DM1)
#define HCSR04_TRIG_DM2                    (* (reg8 *) HCSR04_TRIG__DM2) 
/* Input Buffer Disable Override */
#define HCSR04_TRIG_INP_DIS                (* (reg8 *) HCSR04_TRIG__INP_DIS)
/* LCD Common or Segment Drive */
#define HCSR04_TRIG_LCD_COM_SEG            (* (reg8 *) HCSR04_TRIG__LCD_COM_SEG)
/* Enable Segment LCD */
#define HCSR04_TRIG_LCD_EN                 (* (reg8 *) HCSR04_TRIG__LCD_EN)
/* Slew Rate Control */
#define HCSR04_TRIG_SLW                    (* (reg8 *) HCSR04_TRIG__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HCSR04_TRIG_PRTDSI__CAPS_SEL       (* (reg8 *) HCSR04_TRIG__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HCSR04_TRIG_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HCSR04_TRIG__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HCSR04_TRIG_PRTDSI__OE_SEL0        (* (reg8 *) HCSR04_TRIG__PRTDSI__OE_SEL0) 
#define HCSR04_TRIG_PRTDSI__OE_SEL1        (* (reg8 *) HCSR04_TRIG__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HCSR04_TRIG_PRTDSI__OUT_SEL0       (* (reg8 *) HCSR04_TRIG__PRTDSI__OUT_SEL0) 
#define HCSR04_TRIG_PRTDSI__OUT_SEL1       (* (reg8 *) HCSR04_TRIG__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HCSR04_TRIG_PRTDSI__SYNC_OUT       (* (reg8 *) HCSR04_TRIG__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(HCSR04_TRIG__SIO_CFG)
    #define HCSR04_TRIG_SIO_HYST_EN        (* (reg8 *) HCSR04_TRIG__SIO_HYST_EN)
    #define HCSR04_TRIG_SIO_REG_HIFREQ     (* (reg8 *) HCSR04_TRIG__SIO_REG_HIFREQ)
    #define HCSR04_TRIG_SIO_CFG            (* (reg8 *) HCSR04_TRIG__SIO_CFG)
    #define HCSR04_TRIG_SIO_DIFF           (* (reg8 *) HCSR04_TRIG__SIO_DIFF)
#endif /* (HCSR04_TRIG__SIO_CFG) */

/* Interrupt Registers */
#if defined(HCSR04_TRIG__INTSTAT)
    #define HCSR04_TRIG_INTSTAT            (* (reg8 *) HCSR04_TRIG__INTSTAT)
    #define HCSR04_TRIG_SNAP               (* (reg8 *) HCSR04_TRIG__SNAP)
    
	#define HCSR04_TRIG_0_INTTYPE_REG 		(* (reg8 *) HCSR04_TRIG__0__INTTYPE)
#endif /* (HCSR04_TRIG__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HCSR04_TRIG_H */


/* [] END OF FILE */
