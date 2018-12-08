/*******************************************************************************
* File Name: HCSR04_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "HCSR04.h"

static HCSR04_backupStruct HCSR04_backup;


/*******************************************************************************
* Function Name: HCSR04_SaveConfig
********************************************************************************
*
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
*  HCSR04_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void HCSR04_SaveConfig(void) 
{
    #if (!HCSR04_UsingFixedFunction)
        HCSR04_backup.TimerUdb = HCSR04_ReadCounter();
        HCSR04_backup.InterruptMaskValue = HCSR04_STATUS_MASK;
        #if (HCSR04_UsingHWCaptureCounter)
            HCSR04_backup.TimerCaptureCounter = HCSR04_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!HCSR04_UDB_CONTROL_REG_REMOVED)
            HCSR04_backup.TimerControlRegister = HCSR04_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: HCSR04_RestoreConfig
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
*  HCSR04_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void HCSR04_RestoreConfig(void) 
{   
    #if (!HCSR04_UsingFixedFunction)

        HCSR04_WriteCounter(HCSR04_backup.TimerUdb);
        HCSR04_STATUS_MASK =HCSR04_backup.InterruptMaskValue;
        #if (HCSR04_UsingHWCaptureCounter)
            HCSR04_SetCaptureCount(HCSR04_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!HCSR04_UDB_CONTROL_REG_REMOVED)
            HCSR04_WriteControlRegister(HCSR04_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: HCSR04_Sleep
********************************************************************************
*
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
*  HCSR04_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void HCSR04_Sleep(void) 
{
    #if(!HCSR04_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(HCSR04_CTRL_ENABLE == (HCSR04_CONTROL & HCSR04_CTRL_ENABLE))
        {
            /* Timer is enabled */
            HCSR04_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            HCSR04_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    HCSR04_Stop();
    HCSR04_SaveConfig();
}


/*******************************************************************************
* Function Name: HCSR04_Wakeup
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
*  HCSR04_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void HCSR04_Wakeup(void) 
{
    HCSR04_RestoreConfig();
    #if(!HCSR04_UDB_CONTROL_REG_REMOVED)
        if(HCSR04_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                HCSR04_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
