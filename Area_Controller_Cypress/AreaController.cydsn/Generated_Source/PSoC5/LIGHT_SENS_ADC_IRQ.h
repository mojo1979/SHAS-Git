/*******************************************************************************
* File Name: LIGHT_SENS_ADC_IRQ.h
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
#if !defined(CY_ISR_LIGHT_SENS_ADC_IRQ_H)
#define CY_ISR_LIGHT_SENS_ADC_IRQ_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void LIGHT_SENS_ADC_IRQ_Start(void);
void LIGHT_SENS_ADC_IRQ_StartEx(cyisraddress address);
void LIGHT_SENS_ADC_IRQ_Stop(void);

CY_ISR_PROTO(LIGHT_SENS_ADC_IRQ_Interrupt);

void LIGHT_SENS_ADC_IRQ_SetVector(cyisraddress address);
cyisraddress LIGHT_SENS_ADC_IRQ_GetVector(void);

void LIGHT_SENS_ADC_IRQ_SetPriority(uint8 priority);
uint8 LIGHT_SENS_ADC_IRQ_GetPriority(void);

void LIGHT_SENS_ADC_IRQ_Enable(void);
uint8 LIGHT_SENS_ADC_IRQ_GetState(void);
void LIGHT_SENS_ADC_IRQ_Disable(void);

void LIGHT_SENS_ADC_IRQ_SetPending(void);
void LIGHT_SENS_ADC_IRQ_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the LIGHT_SENS_ADC_IRQ ISR. */
#define LIGHT_SENS_ADC_IRQ_INTC_VECTOR            ((reg32 *) LIGHT_SENS_ADC_IRQ__INTC_VECT)

/* Address of the LIGHT_SENS_ADC_IRQ ISR priority. */
#define LIGHT_SENS_ADC_IRQ_INTC_PRIOR             ((reg8 *) LIGHT_SENS_ADC_IRQ__INTC_PRIOR_REG)

/* Priority of the LIGHT_SENS_ADC_IRQ interrupt. */
#define LIGHT_SENS_ADC_IRQ_INTC_PRIOR_NUMBER      LIGHT_SENS_ADC_IRQ__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable LIGHT_SENS_ADC_IRQ interrupt. */
#define LIGHT_SENS_ADC_IRQ_INTC_SET_EN            ((reg32 *) LIGHT_SENS_ADC_IRQ__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the LIGHT_SENS_ADC_IRQ interrupt. */
#define LIGHT_SENS_ADC_IRQ_INTC_CLR_EN            ((reg32 *) LIGHT_SENS_ADC_IRQ__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the LIGHT_SENS_ADC_IRQ interrupt state to pending. */
#define LIGHT_SENS_ADC_IRQ_INTC_SET_PD            ((reg32 *) LIGHT_SENS_ADC_IRQ__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the LIGHT_SENS_ADC_IRQ interrupt. */
#define LIGHT_SENS_ADC_IRQ_INTC_CLR_PD            ((reg32 *) LIGHT_SENS_ADC_IRQ__INTC_CLR_PD_REG)


#endif /* CY_ISR_LIGHT_SENS_ADC_IRQ_H */


/* [] END OF FILE */
