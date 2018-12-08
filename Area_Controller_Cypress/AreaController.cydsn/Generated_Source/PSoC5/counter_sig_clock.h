/*******************************************************************************
* File Name: counter_sig_clock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_counter_sig_clock_H)
#define CY_CLOCK_counter_sig_clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void counter_sig_clock_Start(void) ;
void counter_sig_clock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void counter_sig_clock_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void counter_sig_clock_StandbyPower(uint8 state) ;
void counter_sig_clock_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 counter_sig_clock_GetDividerRegister(void) ;
void counter_sig_clock_SetModeRegister(uint8 modeBitMask) ;
void counter_sig_clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 counter_sig_clock_GetModeRegister(void) ;
void counter_sig_clock_SetSourceRegister(uint8 clkSource) ;
uint8 counter_sig_clock_GetSourceRegister(void) ;
#if defined(counter_sig_clock__CFG3)
void counter_sig_clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 counter_sig_clock_GetPhaseRegister(void) ;
#endif /* defined(counter_sig_clock__CFG3) */

#define counter_sig_clock_Enable()                       counter_sig_clock_Start()
#define counter_sig_clock_Disable()                      counter_sig_clock_Stop()
#define counter_sig_clock_SetDivider(clkDivider)         counter_sig_clock_SetDividerRegister(clkDivider, 1u)
#define counter_sig_clock_SetDividerValue(clkDivider)    counter_sig_clock_SetDividerRegister((clkDivider) - 1u, 1u)
#define counter_sig_clock_SetMode(clkMode)               counter_sig_clock_SetModeRegister(clkMode)
#define counter_sig_clock_SetSource(clkSource)           counter_sig_clock_SetSourceRegister(clkSource)
#if defined(counter_sig_clock__CFG3)
#define counter_sig_clock_SetPhase(clkPhase)             counter_sig_clock_SetPhaseRegister(clkPhase)
#define counter_sig_clock_SetPhaseValue(clkPhase)        counter_sig_clock_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(counter_sig_clock__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define counter_sig_clock_CLKEN              (* (reg8 *) counter_sig_clock__PM_ACT_CFG)
#define counter_sig_clock_CLKEN_PTR          ((reg8 *) counter_sig_clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define counter_sig_clock_CLKSTBY            (* (reg8 *) counter_sig_clock__PM_STBY_CFG)
#define counter_sig_clock_CLKSTBY_PTR        ((reg8 *) counter_sig_clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define counter_sig_clock_DIV_LSB            (* (reg8 *) counter_sig_clock__CFG0)
#define counter_sig_clock_DIV_LSB_PTR        ((reg8 *) counter_sig_clock__CFG0)
#define counter_sig_clock_DIV_PTR            ((reg16 *) counter_sig_clock__CFG0)

/* Clock MSB divider configuration register. */
#define counter_sig_clock_DIV_MSB            (* (reg8 *) counter_sig_clock__CFG1)
#define counter_sig_clock_DIV_MSB_PTR        ((reg8 *) counter_sig_clock__CFG1)

/* Mode and source configuration register */
#define counter_sig_clock_MOD_SRC            (* (reg8 *) counter_sig_clock__CFG2)
#define counter_sig_clock_MOD_SRC_PTR        ((reg8 *) counter_sig_clock__CFG2)

#if defined(counter_sig_clock__CFG3)
/* Analog clock phase configuration register */
#define counter_sig_clock_PHASE              (* (reg8 *) counter_sig_clock__CFG3)
#define counter_sig_clock_PHASE_PTR          ((reg8 *) counter_sig_clock__CFG3)
#endif /* defined(counter_sig_clock__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define counter_sig_clock_CLKEN_MASK         counter_sig_clock__PM_ACT_MSK
#define counter_sig_clock_CLKSTBY_MASK       counter_sig_clock__PM_STBY_MSK

/* CFG2 field masks */
#define counter_sig_clock_SRC_SEL_MSK        counter_sig_clock__CFG2_SRC_SEL_MASK
#define counter_sig_clock_MODE_MASK          (~(counter_sig_clock_SRC_SEL_MSK))

#if defined(counter_sig_clock__CFG3)
/* CFG3 phase mask */
#define counter_sig_clock_PHASE_MASK         counter_sig_clock__CFG3_PHASE_DLY_MASK
#endif /* defined(counter_sig_clock__CFG3) */

#endif /* CY_CLOCK_counter_sig_clock_H */


/* [] END OF FILE */
