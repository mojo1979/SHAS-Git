/*******************************************************************************
* File Name: HCSR04_PWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "HCSR04_PWM.h"

static HCSR04_PWM_backupStruct HCSR04_PWM_backup;


/*******************************************************************************
* Function Name: HCSR04_PWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  HCSR04_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void HCSR04_PWM_SaveConfig(void) 
{

    #if(!HCSR04_PWM_UsingFixedFunction)
        #if(!HCSR04_PWM_PWMModeIsCenterAligned)
            HCSR04_PWM_backup.PWMPeriod = HCSR04_PWM_ReadPeriod();
        #endif /* (!HCSR04_PWM_PWMModeIsCenterAligned) */
        HCSR04_PWM_backup.PWMUdb = HCSR04_PWM_ReadCounter();
        #if (HCSR04_PWM_UseStatus)
            HCSR04_PWM_backup.InterruptMaskValue = HCSR04_PWM_STATUS_MASK;
        #endif /* (HCSR04_PWM_UseStatus) */

        #if(HCSR04_PWM_DeadBandMode == HCSR04_PWM__B_PWM__DBM_256_CLOCKS || \
            HCSR04_PWM_DeadBandMode == HCSR04_PWM__B_PWM__DBM_2_4_CLOCKS)
            HCSR04_PWM_backup.PWMdeadBandValue = HCSR04_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(HCSR04_PWM_KillModeMinTime)
             HCSR04_PWM_backup.PWMKillCounterPeriod = HCSR04_PWM_ReadKillTime();
        #endif /* (HCSR04_PWM_KillModeMinTime) */

        #if(HCSR04_PWM_UseControl)
            HCSR04_PWM_backup.PWMControlRegister = HCSR04_PWM_ReadControlRegister();
        #endif /* (HCSR04_PWM_UseControl) */
    #endif  /* (!HCSR04_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HCSR04_PWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  HCSR04_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void HCSR04_PWM_RestoreConfig(void) 
{
        #if(!HCSR04_PWM_UsingFixedFunction)
            #if(!HCSR04_PWM_PWMModeIsCenterAligned)
                HCSR04_PWM_WritePeriod(HCSR04_PWM_backup.PWMPeriod);
            #endif /* (!HCSR04_PWM_PWMModeIsCenterAligned) */

            HCSR04_PWM_WriteCounter(HCSR04_PWM_backup.PWMUdb);

            #if (HCSR04_PWM_UseStatus)
                HCSR04_PWM_STATUS_MASK = HCSR04_PWM_backup.InterruptMaskValue;
            #endif /* (HCSR04_PWM_UseStatus) */

            #if(HCSR04_PWM_DeadBandMode == HCSR04_PWM__B_PWM__DBM_256_CLOCKS || \
                HCSR04_PWM_DeadBandMode == HCSR04_PWM__B_PWM__DBM_2_4_CLOCKS)
                HCSR04_PWM_WriteDeadTime(HCSR04_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(HCSR04_PWM_KillModeMinTime)
                HCSR04_PWM_WriteKillTime(HCSR04_PWM_backup.PWMKillCounterPeriod);
            #endif /* (HCSR04_PWM_KillModeMinTime) */

            #if(HCSR04_PWM_UseControl)
                HCSR04_PWM_WriteControlRegister(HCSR04_PWM_backup.PWMControlRegister);
            #endif /* (HCSR04_PWM_UseControl) */
        #endif  /* (!HCSR04_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: HCSR04_PWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  HCSR04_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void HCSR04_PWM_Sleep(void) 
{
    #if(HCSR04_PWM_UseControl)
        if(HCSR04_PWM_CTRL_ENABLE == (HCSR04_PWM_CONTROL & HCSR04_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            HCSR04_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            HCSR04_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (HCSR04_PWM_UseControl) */

    /* Stop component */
    HCSR04_PWM_Stop();

    /* Save registers configuration */
    HCSR04_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: HCSR04_PWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  HCSR04_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void HCSR04_PWM_Wakeup(void) 
{
     /* Restore registers values */
    HCSR04_PWM_RestoreConfig();

    if(HCSR04_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        HCSR04_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
