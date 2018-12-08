/*******************************************************************************
* File Name: HCSR04_COUNTER_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "HCSR04_COUNTER.h"

static HCSR04_COUNTER_backupStruct HCSR04_COUNTER_backup;


/*******************************************************************************
* Function Name: HCSR04_COUNTER_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  HCSR04_COUNTER_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void HCSR04_COUNTER_SaveConfig(void) 
{
    #if (!HCSR04_COUNTER_UsingFixedFunction)

        HCSR04_COUNTER_backup.CounterUdb = HCSR04_COUNTER_ReadCounter();

        #if(!HCSR04_COUNTER_ControlRegRemoved)
            HCSR04_COUNTER_backup.CounterControlRegister = HCSR04_COUNTER_ReadControlRegister();
        #endif /* (!HCSR04_COUNTER_ControlRegRemoved) */

    #endif /* (!HCSR04_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HCSR04_COUNTER_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  HCSR04_COUNTER_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void HCSR04_COUNTER_RestoreConfig(void) 
{      
    #if (!HCSR04_COUNTER_UsingFixedFunction)

       HCSR04_COUNTER_WriteCounter(HCSR04_COUNTER_backup.CounterUdb);

        #if(!HCSR04_COUNTER_ControlRegRemoved)
            HCSR04_COUNTER_WriteControlRegister(HCSR04_COUNTER_backup.CounterControlRegister);
        #endif /* (!HCSR04_COUNTER_ControlRegRemoved) */

    #endif /* (!HCSR04_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HCSR04_COUNTER_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  HCSR04_COUNTER_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void HCSR04_COUNTER_Sleep(void) 
{
    #if(!HCSR04_COUNTER_ControlRegRemoved)
        /* Save Counter's enable state */
        if(HCSR04_COUNTER_CTRL_ENABLE == (HCSR04_COUNTER_CONTROL & HCSR04_COUNTER_CTRL_ENABLE))
        {
            /* Counter is enabled */
            HCSR04_COUNTER_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            HCSR04_COUNTER_backup.CounterEnableState = 0u;
        }
    #else
        HCSR04_COUNTER_backup.CounterEnableState = 1u;
        if(HCSR04_COUNTER_backup.CounterEnableState != 0u)
        {
            HCSR04_COUNTER_backup.CounterEnableState = 0u;
        }
    #endif /* (!HCSR04_COUNTER_ControlRegRemoved) */
    
    HCSR04_COUNTER_Stop();
    HCSR04_COUNTER_SaveConfig();
}


/*******************************************************************************
* Function Name: HCSR04_COUNTER_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  HCSR04_COUNTER_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void HCSR04_COUNTER_Wakeup(void) 
{
    HCSR04_COUNTER_RestoreConfig();
    #if(!HCSR04_COUNTER_ControlRegRemoved)
        if(HCSR04_COUNTER_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            HCSR04_COUNTER_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!HCSR04_COUNTER_ControlRegRemoved) */
    
}


/* [] END OF FILE */
