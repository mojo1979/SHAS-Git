/*******************************************************************************
* File Name: HCSR04_COUNTER.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
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

uint8 HCSR04_COUNTER_initVar = 0u;


/*******************************************************************************
* Function Name: HCSR04_COUNTER_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void HCSR04_COUNTER_Init(void) 
{
        #if (!HCSR04_COUNTER_UsingFixedFunction && !HCSR04_COUNTER_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!HCSR04_COUNTER_UsingFixedFunction && !HCSR04_COUNTER_ControlRegRemoved) */
        
        #if(!HCSR04_COUNTER_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 HCSR04_COUNTER_interruptState;
        #endif /* (!HCSR04_COUNTER_UsingFixedFunction) */
        
        #if (HCSR04_COUNTER_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            HCSR04_COUNTER_CONTROL &= HCSR04_COUNTER_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                HCSR04_COUNTER_CONTROL2 &= ((uint8)(~HCSR04_COUNTER_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                HCSR04_COUNTER_CONTROL3 &= ((uint8)(~HCSR04_COUNTER_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (HCSR04_COUNTER_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                HCSR04_COUNTER_CONTROL |= HCSR04_COUNTER_ONESHOT;
            #endif /* (HCSR04_COUNTER_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            HCSR04_COUNTER_CONTROL2 |= HCSR04_COUNTER_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            HCSR04_COUNTER_RT1 &= ((uint8)(~HCSR04_COUNTER_RT1_MASK));
            HCSR04_COUNTER_RT1 |= HCSR04_COUNTER_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            HCSR04_COUNTER_RT1 &= ((uint8)(~HCSR04_COUNTER_SYNCDSI_MASK));
            HCSR04_COUNTER_RT1 |= HCSR04_COUNTER_SYNCDSI_EN;

        #else
            #if(!HCSR04_COUNTER_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = HCSR04_COUNTER_CONTROL & ((uint8)(~HCSR04_COUNTER_CTRL_CMPMODE_MASK));
            HCSR04_COUNTER_CONTROL = ctrl | HCSR04_COUNTER_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = HCSR04_COUNTER_CONTROL & ((uint8)(~HCSR04_COUNTER_CTRL_CAPMODE_MASK));
            
            #if( 0 != HCSR04_COUNTER_CAPTURE_MODE_CONF)
                HCSR04_COUNTER_CONTROL = ctrl | HCSR04_COUNTER_DEFAULT_CAPTURE_MODE;
            #else
                HCSR04_COUNTER_CONTROL = ctrl;
            #endif /* 0 != HCSR04_COUNTER_CAPTURE_MODE */ 
            
            #endif /* (!HCSR04_COUNTER_ControlRegRemoved) */
        #endif /* (HCSR04_COUNTER_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!HCSR04_COUNTER_UsingFixedFunction)
            HCSR04_COUNTER_ClearFIFO();
        #endif /* (!HCSR04_COUNTER_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        HCSR04_COUNTER_WritePeriod(HCSR04_COUNTER_INIT_PERIOD_VALUE);
        #if (!(HCSR04_COUNTER_UsingFixedFunction && (CY_PSOC5A)))
            HCSR04_COUNTER_WriteCounter(HCSR04_COUNTER_INIT_COUNTER_VALUE);
        #endif /* (!(HCSR04_COUNTER_UsingFixedFunction && (CY_PSOC5A))) */
        HCSR04_COUNTER_SetInterruptMode(HCSR04_COUNTER_INIT_INTERRUPTS_MASK);
        
        #if (!HCSR04_COUNTER_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)HCSR04_COUNTER_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            HCSR04_COUNTER_WriteCompare(HCSR04_COUNTER_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            HCSR04_COUNTER_interruptState = CyEnterCriticalSection();
            
            HCSR04_COUNTER_STATUS_AUX_CTRL |= HCSR04_COUNTER_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(HCSR04_COUNTER_interruptState);
            
        #endif /* (!HCSR04_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HCSR04_COUNTER_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void HCSR04_COUNTER_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (HCSR04_COUNTER_UsingFixedFunction)
        HCSR04_COUNTER_GLOBAL_ENABLE |= HCSR04_COUNTER_BLOCK_EN_MASK;
        HCSR04_COUNTER_GLOBAL_STBY_ENABLE |= HCSR04_COUNTER_BLOCK_STBY_EN_MASK;
    #endif /* (HCSR04_COUNTER_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!HCSR04_COUNTER_ControlRegRemoved || HCSR04_COUNTER_UsingFixedFunction)
        HCSR04_COUNTER_CONTROL |= HCSR04_COUNTER_CTRL_ENABLE;                
    #endif /* (!HCSR04_COUNTER_ControlRegRemoved || HCSR04_COUNTER_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: HCSR04_COUNTER_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  HCSR04_COUNTER_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void HCSR04_COUNTER_Start(void) 
{
    if(HCSR04_COUNTER_initVar == 0u)
    {
        HCSR04_COUNTER_Init();
        
        HCSR04_COUNTER_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    HCSR04_COUNTER_Enable();        
}


/*******************************************************************************
* Function Name: HCSR04_COUNTER_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void HCSR04_COUNTER_Stop(void) 
{
    /* Disable Counter */
    #if(!HCSR04_COUNTER_ControlRegRemoved || HCSR04_COUNTER_UsingFixedFunction)
        HCSR04_COUNTER_CONTROL &= ((uint8)(~HCSR04_COUNTER_CTRL_ENABLE));        
    #endif /* (!HCSR04_COUNTER_ControlRegRemoved || HCSR04_COUNTER_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (HCSR04_COUNTER_UsingFixedFunction)
        HCSR04_COUNTER_GLOBAL_ENABLE &= ((uint8)(~HCSR04_COUNTER_BLOCK_EN_MASK));
        HCSR04_COUNTER_GLOBAL_STBY_ENABLE &= ((uint8)(~HCSR04_COUNTER_BLOCK_STBY_EN_MASK));
    #endif /* (HCSR04_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HCSR04_COUNTER_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void HCSR04_COUNTER_SetInterruptMode(uint8 interruptsMask) 
{
    HCSR04_COUNTER_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: HCSR04_COUNTER_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   HCSR04_COUNTER_ReadStatusRegister(void) 
{
    return HCSR04_COUNTER_STATUS;
}


#if(!HCSR04_COUNTER_ControlRegRemoved)
/*******************************************************************************
* Function Name: HCSR04_COUNTER_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   HCSR04_COUNTER_ReadControlRegister(void) 
{
    return HCSR04_COUNTER_CONTROL;
}


/*******************************************************************************
* Function Name: HCSR04_COUNTER_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    HCSR04_COUNTER_WriteControlRegister(uint8 control) 
{
    HCSR04_COUNTER_CONTROL = control;
}

#endif  /* (!HCSR04_COUNTER_ControlRegRemoved) */


#if (!(HCSR04_COUNTER_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: HCSR04_COUNTER_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void HCSR04_COUNTER_WriteCounter(uint16 counter) \
                                   
{
    #if(HCSR04_COUNTER_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (HCSR04_COUNTER_GLOBAL_ENABLE & HCSR04_COUNTER_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        HCSR04_COUNTER_GLOBAL_ENABLE |= HCSR04_COUNTER_BLOCK_EN_MASK;
        CY_SET_REG16(HCSR04_COUNTER_COUNTER_LSB_PTR, (uint16)counter);
        HCSR04_COUNTER_GLOBAL_ENABLE &= ((uint8)(~HCSR04_COUNTER_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(HCSR04_COUNTER_COUNTER_LSB_PTR, counter);
    #endif /* (HCSR04_COUNTER_UsingFixedFunction) */
}
#endif /* (!(HCSR04_COUNTER_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: HCSR04_COUNTER_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) The present value of the counter.
*
*******************************************************************************/
uint16 HCSR04_COUNTER_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(HCSR04_COUNTER_UsingFixedFunction)
		(void)CY_GET_REG16(HCSR04_COUNTER_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(HCSR04_COUNTER_COUNTER_LSB_PTR_8BIT);
	#endif/* (HCSR04_COUNTER_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(HCSR04_COUNTER_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(HCSR04_COUNTER_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(HCSR04_COUNTER_STATICCOUNT_LSB_PTR));
    #endif /* (HCSR04_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HCSR04_COUNTER_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint16) Present Capture value.
*
*******************************************************************************/
uint16 HCSR04_COUNTER_ReadCapture(void) 
{
    #if(HCSR04_COUNTER_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(HCSR04_COUNTER_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(HCSR04_COUNTER_STATICCOUNT_LSB_PTR));
    #endif /* (HCSR04_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HCSR04_COUNTER_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint16) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void HCSR04_COUNTER_WritePeriod(uint16 period) 
{
    #if(HCSR04_COUNTER_UsingFixedFunction)
        CY_SET_REG16(HCSR04_COUNTER_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(HCSR04_COUNTER_PERIOD_LSB_PTR, period);
    #endif /* (HCSR04_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HCSR04_COUNTER_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) Present period value.
*
*******************************************************************************/
uint16 HCSR04_COUNTER_ReadPeriod(void) 
{
    #if(HCSR04_COUNTER_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(HCSR04_COUNTER_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(HCSR04_COUNTER_PERIOD_LSB_PTR));
    #endif /* (HCSR04_COUNTER_UsingFixedFunction) */
}


#if (!HCSR04_COUNTER_UsingFixedFunction)
/*******************************************************************************
* Function Name: HCSR04_COUNTER_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void HCSR04_COUNTER_WriteCompare(uint16 compare) \
                                   
{
    #if(HCSR04_COUNTER_UsingFixedFunction)
        CY_SET_REG16(HCSR04_COUNTER_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(HCSR04_COUNTER_COMPARE_LSB_PTR, compare);
    #endif /* (HCSR04_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: HCSR04_COUNTER_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint16) Present compare value.
*
*******************************************************************************/
uint16 HCSR04_COUNTER_ReadCompare(void) 
{
    return (CY_GET_REG16(HCSR04_COUNTER_COMPARE_LSB_PTR));
}


#if (HCSR04_COUNTER_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: HCSR04_COUNTER_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void HCSR04_COUNTER_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    HCSR04_COUNTER_CONTROL &= ((uint8)(~HCSR04_COUNTER_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    HCSR04_COUNTER_CONTROL |= compareMode;
}
#endif  /* (HCSR04_COUNTER_COMPARE_MODE_SOFTWARE) */


#if (HCSR04_COUNTER_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: HCSR04_COUNTER_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void HCSR04_COUNTER_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    HCSR04_COUNTER_CONTROL &= ((uint8)(~HCSR04_COUNTER_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    HCSR04_COUNTER_CONTROL |= ((uint8)((uint8)captureMode << HCSR04_COUNTER_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (HCSR04_COUNTER_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: HCSR04_COUNTER_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void HCSR04_COUNTER_ClearFIFO(void) 
{

    while(0u != (HCSR04_COUNTER_ReadStatusRegister() & HCSR04_COUNTER_STATUS_FIFONEMP))
    {
        (void)HCSR04_COUNTER_ReadCapture();
    }

}
#endif  /* (!HCSR04_COUNTER_UsingFixedFunction) */


/* [] END OF FILE */

