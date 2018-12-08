/*******************************************************************************
* File Name: RxISR.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_RxISR_H)
#define CY_ISR_RxISR_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void RxISR_Start(void);
void RxISR_StartEx(cyisraddress address);
void RxISR_Stop(void);

CY_ISR_PROTO(RxISR_Interrupt);

void RxISR_SetVector(cyisraddress address);
cyisraddress RxISR_GetVector(void);

void RxISR_SetPriority(uint8 priority);
uint8 RxISR_GetPriority(void);

void RxISR_Enable(void);
uint8 RxISR_GetState(void);
void RxISR_Disable(void);

void RxISR_SetPending(void);
void RxISR_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the RxISR ISR. */
#define RxISR_INTC_VECTOR            ((reg32 *) RxISR__INTC_VECT)

/* Address of the RxISR ISR priority. */
#define RxISR_INTC_PRIOR             ((reg8 *) RxISR__INTC_PRIOR_REG)

/* Priority of the RxISR interrupt. */
#define RxISR_INTC_PRIOR_NUMBER      RxISR__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable RxISR interrupt. */
#define RxISR_INTC_SET_EN            ((reg32 *) RxISR__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the RxISR interrupt. */
#define RxISR_INTC_CLR_EN            ((reg32 *) RxISR__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the RxISR interrupt state to pending. */
#define RxISR_INTC_SET_PD            ((reg32 *) RxISR__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the RxISR interrupt. */
#define RxISR_INTC_CLR_PD            ((reg32 *) RxISR__INTC_CLR_PD_REG)


#endif /* CY_ISR_RxISR_H */


/* [] END OF FILE */
