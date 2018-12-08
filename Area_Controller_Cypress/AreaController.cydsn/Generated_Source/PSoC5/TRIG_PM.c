/*******************************************************************************
* File Name: TRIG_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "TRIG.h"

/* Check for removal by optimization */
#if !defined(TRIG_Sync_ctrl_reg__REMOVED)

static TRIG_BACKUP_STRUCT  TRIG_backup = {0u};

    
/*******************************************************************************
* Function Name: TRIG_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TRIG_SaveConfig(void) 
{
    TRIG_backup.controlState = TRIG_Control;
}


/*******************************************************************************
* Function Name: TRIG_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void TRIG_RestoreConfig(void) 
{
     TRIG_Control = TRIG_backup.controlState;
}


/*******************************************************************************
* Function Name: TRIG_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TRIG_Sleep(void) 
{
    TRIG_SaveConfig();
}


/*******************************************************************************
* Function Name: TRIG_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TRIG_Wakeup(void)  
{
    TRIG_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
