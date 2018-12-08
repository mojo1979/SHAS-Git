/*******************************************************************************
* File Name: LIGHT_SENS_ADC.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the Successive
*  approximation ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include "LIGHT_SENS_ADC.h"

#if(LIGHT_SENS_ADC_DEFAULT_INTERNAL_CLK)
    #include "LIGHT_SENS_ADC_theACLK.h"
#endif /* End LIGHT_SENS_ADC_DEFAULT_INTERNAL_CLK */


/***************************************
* Forward function references
***************************************/
static void LIGHT_SENS_ADC_CalcGain(uint8 resolution);


/***************************************
* Global data allocation
***************************************/
uint8 LIGHT_SENS_ADC_initVar = 0u;
volatile int16 LIGHT_SENS_ADC_offset;
volatile int16 LIGHT_SENS_ADC_countsPerVolt;     /* Obsolete Gain compensation */
volatile int32 LIGHT_SENS_ADC_countsPer10Volt;   /* Gain compensation */
volatile int16 LIGHT_SENS_ADC_shift;


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  LIGHT_SENS_ADC_Start() sets the initVar variable, calls the
*  LIGHT_SENS_ADC_Init() function, and then calls the
*  LIGHT_SENS_ADC_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The LIGHT_SENS_ADC_initVar variable is used to indicate when/if initial
*  configuration of this component has happened. The variable is initialized to
*  zero and set to 1 the first time ADC_Start() is called. This allows for
*  component Re-Start without re-initialization in all subsequent calls to the
*  LIGHT_SENS_ADC_Start() routine.
*  If re-initialization of the component is required the variable should be set
*  to zero before call of LIGHT_SENS_ADC_Start() routine, or the user may call
*  LIGHT_SENS_ADC_Init() and LIGHT_SENS_ADC_Enable() as done in the
*  LIGHT_SENS_ADC_Start() routine.
*
* Side Effect:
*  If the initVar variable is already set, this function only calls the
*  LIGHT_SENS_ADC_Enable() function.
*
*******************************************************************************/
void LIGHT_SENS_ADC_Start(void)
{

    /* If not Initialized then initialize all required hardware and software */
    if(LIGHT_SENS_ADC_initVar == 0u)
    {
        LIGHT_SENS_ADC_Init();
        LIGHT_SENS_ADC_initVar = 1u;
    }
    LIGHT_SENS_ADC_Enable();
}


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  LIGHT_SENS_ADC_Start().
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The LIGHT_SENS_ADC_offset variable is initialized to 0.
*
*******************************************************************************/
void LIGHT_SENS_ADC_Init(void)
{

    /* This is only valid if there is an internal clock */
    #if(LIGHT_SENS_ADC_DEFAULT_INTERNAL_CLK)
        LIGHT_SENS_ADC_theACLK_SetMode(CYCLK_DUTY);
    #endif /* End LIGHT_SENS_ADC_DEFAULT_INTERNAL_CLK */

    #if(LIGHT_SENS_ADC_IRQ_REMOVE == 0u)
        /* Start and set interrupt vector */
        CyIntSetPriority(LIGHT_SENS_ADC_INTC_NUMBER, LIGHT_SENS_ADC_INTC_PRIOR_NUMBER);
        (void)CyIntSetVector(LIGHT_SENS_ADC_INTC_NUMBER, &LIGHT_SENS_ADC_ISR);
    #endif   /* End LIGHT_SENS_ADC_IRQ_REMOVE */

    /* Enable IRQ mode*/
    LIGHT_SENS_ADC_SAR_CSR1_REG |= LIGHT_SENS_ADC_SAR_IRQ_MASK_EN | LIGHT_SENS_ADC_SAR_IRQ_MODE_EDGE;

    /*Set SAR ADC resolution ADC */
    LIGHT_SENS_ADC_SetResolution(LIGHT_SENS_ADC_DEFAULT_RESOLUTION);
    LIGHT_SENS_ADC_offset = 0;
}


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_Enable
********************************************************************************
*
* Summary:
*  Enables the reference, clock and power for SAR ADC.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LIGHT_SENS_ADC_Enable(void)
{
    uint8 tmpReg;
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Enable the SAR ADC block in Active Power Mode */
    LIGHT_SENS_ADC_PWRMGR_SAR_REG |= LIGHT_SENS_ADC_ACT_PWR_SAR_EN;

     /* Enable the SAR ADC in Standby Power Mode*/
    LIGHT_SENS_ADC_STBY_PWRMGR_SAR_REG |= LIGHT_SENS_ADC_STBY_PWR_SAR_EN;

    /* This is only valid if there is an internal clock */
    #if(LIGHT_SENS_ADC_DEFAULT_INTERNAL_CLK)
        LIGHT_SENS_ADC_PWRMGR_CLK_REG |= LIGHT_SENS_ADC_ACT_PWR_CLK_EN;
        LIGHT_SENS_ADC_STBY_PWRMGR_CLK_REG |= LIGHT_SENS_ADC_STBY_PWR_CLK_EN;
    #endif /* End LIGHT_SENS_ADC_DEFAULT_INTERNAL_CLK */

    /* Enable VCM buffer and Enable Int Ref Amp */
    tmpReg = LIGHT_SENS_ADC_SAR_CSR3_REG;
    tmpReg |= LIGHT_SENS_ADC_SAR_EN_BUF_VCM_EN;
    /* PD_BUF_VREF is OFF in External reference or Vdda reference mode */
    #if((LIGHT_SENS_ADC_DEFAULT_REFERENCE == LIGHT_SENS_ADC__EXT_REF) || \
        (LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VNEG_VDDA_DIFF))
        tmpReg &= (uint8)~LIGHT_SENS_ADC_SAR_EN_BUF_VREF_EN;
    #else /* In INTREF or INTREF Bypassed this buffer is ON */
        tmpReg |= LIGHT_SENS_ADC_SAR_EN_BUF_VREF_EN;
    #endif /* LIGHT_SENS_ADC_DEFAULT_REFERENCE == LIGHT_SENS_ADC__EXT_REF */
    LIGHT_SENS_ADC_SAR_CSR3_REG = tmpReg;

    /* Set reference for ADC */
    #if(LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VNEG_VDDA_DIFF)
        #if(LIGHT_SENS_ADC_DEFAULT_REFERENCE == LIGHT_SENS_ADC__EXT_REF)
            LIGHT_SENS_ADC_SAR_CSR6_REG = LIGHT_SENS_ADC_INT_BYPASS_EXT_VREF; /* S2 */
        #else /* Internal Vdda reference or obsolete bypass mode */
            LIGHT_SENS_ADC_SAR_CSR6_REG = LIGHT_SENS_ADC_VDDA_VREF;           /* S7 */
        #endif /* LIGHT_SENS_ADC_DEFAULT_REFERENCE == LIGHT_SENS_ADC__EXT_REF */
    #else  /* Reference goes through internal buffer */
        #if(LIGHT_SENS_ADC_DEFAULT_REFERENCE == LIGHT_SENS_ADC__INT_REF_NOT_BYPASSED)
            LIGHT_SENS_ADC_SAR_CSR6_REG = LIGHT_SENS_ADC_INT_VREF;            /* S3 + S4 */
        #else /* INTREF Bypassed of External */
            LIGHT_SENS_ADC_SAR_CSR6_REG = LIGHT_SENS_ADC_INT_BYPASS_EXT_VREF; /* S2 */
        #endif /* LIGHT_SENS_ADC_DEFAULT_REFERENCE == LIGHT_SENS_ADC__INT_REF_NOT_BYPASSED */
    #endif /* VNEG_VDDA_DIFF */

    /* Low non-overlap delay for sampling clock signals (for 1MSPS) */
    #if(LIGHT_SENS_ADC_HIGH_POWER_PULSE == 0u) /* MinPulseWidth <= 50 ns */
        LIGHT_SENS_ADC_SAR_CSR5_REG &= (uint8)~LIGHT_SENS_ADC_SAR_DLY_INC;
    #else /* Set High non-overlap delay for sampling clock signals (for <500KSPS)*/
        LIGHT_SENS_ADC_SAR_CSR5_REG |= LIGHT_SENS_ADC_SAR_DLY_INC;
    #endif /* LIGHT_SENS_ADC_HIGH_POWER_PULSE == 0u */

    /* Increase comparator latch enable delay by 20%, 
    *  Increase comparator bias current by 30% without impacting delaysDelay 
    *  Default for 1MSPS) 
    */
    #if(LIGHT_SENS_ADC_HIGH_POWER_PULSE == 0u)    /* MinPulseWidth <= 50 ns */
        LIGHT_SENS_ADC_SAR_CSR5_REG |= LIGHT_SENS_ADC_SAR_SEL_CSEL_DFT_CHAR;
    #else /* for <500ksps */
        LIGHT_SENS_ADC_SAR_CSR5_REG &= (uint8)~LIGHT_SENS_ADC_SAR_SEL_CSEL_DFT_CHAR;
    #endif /* LIGHT_SENS_ADC_HIGH_POWER_PULSE == 0u */

    /* Set default power and other configurations for control register 0 in multiple lines */
    LIGHT_SENS_ADC_SAR_CSR0_REG = (uint8)((uint8)LIGHT_SENS_ADC_DEFAULT_POWER << LIGHT_SENS_ADC_SAR_POWER_SHIFT)
    /* SAR_HIZ_CLEAR:   Should not be used for LP */
    #if ((CY_PSOC5LP) || (LIGHT_SENS_ADC_DEFAULT_REFERENCE != LIGHT_SENS_ADC__EXT_REF))
        | LIGHT_SENS_ADC_SAR_HIZ_CLEAR
    #endif /* SAR_HIZ_CLEAR */
    /*Set Convertion mode */
    #if(LIGHT_SENS_ADC_DEFAULT_CONV_MODE != LIGHT_SENS_ADC__FREE_RUNNING)      /* If triggered mode */
        | LIGHT_SENS_ADC_SAR_MX_SOF_UDB           /* source: UDB */
        | LIGHT_SENS_ADC_SAR_SOF_MODE_EDGE        /* Set edge-sensitive sof source */
    #endif /* LIGHT_SENS_ADC_DEFAULT_CONV_MODE */
    ; /* end of multiple line initialization */

    LIGHT_SENS_ADC_SAR_TR0_REG = LIGHT_SENS_ADC_SAR_CAP_TRIM_2;

    /* Enable clock for SAR ADC*/
    LIGHT_SENS_ADC_SAR_CLK_REG |= LIGHT_SENS_ADC_SAR_MX_CLK_EN;

    CyDelayUs(10u); /* The block is ready to use 10 us after the enable signal is set high. */

    #if(LIGHT_SENS_ADC_IRQ_REMOVE == 0u)
        /* Clear a pending interrupt */
        CyIntClearPending(LIGHT_SENS_ADC_INTC_NUMBER);
    #endif   /* End LIGHT_SENS_ADC_IRQ_REMOVE */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_Stop
********************************************************************************
*
* Summary:
*  Stops ADC conversions and puts the ADC into its lowest power mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LIGHT_SENS_ADC_Stop(void)
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Stop all conversions */
    LIGHT_SENS_ADC_SAR_CSR0_REG &= (uint8)~LIGHT_SENS_ADC_SAR_SOF_START_CONV;
    /* Disable the SAR ADC block in Active Power Mode */
    LIGHT_SENS_ADC_PWRMGR_SAR_REG &= (uint8)~LIGHT_SENS_ADC_ACT_PWR_SAR_EN;
    /* Disable the SAR ADC in Standby Power Mode */
    LIGHT_SENS_ADC_STBY_PWRMGR_SAR_REG &= (uint8)~LIGHT_SENS_ADC_STBY_PWR_SAR_EN;

    /* This is only valid if there is an internal clock */
    #if(LIGHT_SENS_ADC_DEFAULT_INTERNAL_CLK)
        LIGHT_SENS_ADC_PWRMGR_CLK_REG &= (uint8)~LIGHT_SENS_ADC_ACT_PWR_CLK_EN;
        LIGHT_SENS_ADC_STBY_PWRMGR_CLK_REG &= (uint8)~LIGHT_SENS_ADC_STBY_PWR_CLK_EN;
    #endif /* End LIGHT_SENS_ADC_DEFAULT_INTERNAL_CLK */

    CyExitCriticalSection(enableInterrupts);

}


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_SetPower
********************************************************************************
*
* Summary:
*  Sets the operational power of the ADC. You should use the higher power
*  settings with faster clock speeds.
*
* Parameters:
*  power:  Power setting for ADC
*  0 ->    Normal
*  1 ->    Medium power
*  2 ->    1.25 power
*  3 ->    Minimum power.
*
* Return:
*  None.
*
*******************************************************************************/
void LIGHT_SENS_ADC_SetPower(uint8 power)
{
    uint8 tmpReg;

    /* mask off invalid power settings */
    power &= LIGHT_SENS_ADC_SAR_API_POWER_MASK;

    /* Set Power parameter  */
    tmpReg = LIGHT_SENS_ADC_SAR_CSR0_REG & (uint8)~LIGHT_SENS_ADC_SAR_POWER_MASK;
    tmpReg |= (uint8)(power << LIGHT_SENS_ADC_SAR_POWER_SHIFT);
    LIGHT_SENS_ADC_SAR_CSR0_REG = tmpReg;
}


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_SetResolution
********************************************************************************
*
* Summary:
*  Sets the Relution of the SAR.
*
* Parameters:
*  resolution:
*  12 ->    RES12
*  10 ->    RES10
*  8  ->    RES8
*
* Return:
*  None.
*
* Side Effects:
*  The ADC resolution cannot be changed during a conversion cycle. The
*  recommended best practice is to stop conversions with
*  ADC_StopConvert(), change the resolution, then restart the
*  conversions with ADC_StartConvert().
*  If you decide not to stop conversions before calling this API, you
*  should use ADC_IsEndConversion() to wait until conversion is complete
*  before changing the resolution.
*  If you call ADC_SetResolution() during a conversion, the resolution will
*  not be changed until the current conversion is complete. Data will not be
*  available in the new resolution for another 6 + "New Resolution(in bits)"
*  clock cycles.
*  You may need add a delay of this number of clock cycles after
*  ADC_SetResolution() is called before data is valid again.
*  Affects ADC_CountsTo_Volts(), ADC_CountsTo_mVolts(), and
*  ADC_CountsTo_uVolts() by calculating the correct conversion between ADC
*  counts and the applied input voltage. Calculation depends on resolution,
*  input range, and voltage reference.
*
*******************************************************************************/
void LIGHT_SENS_ADC_SetResolution(uint8 resolution)
{
    uint8 tmpReg;

    /* Set SAR ADC resolution and sample width: 18 conversion cycles at 12bits + 1 gap */
    switch (resolution)
    {
        case (uint8)LIGHT_SENS_ADC__BITS_12:
            tmpReg = LIGHT_SENS_ADC_SAR_RESOLUTION_12BIT | LIGHT_SENS_ADC_SAR_SAMPLE_WIDTH;
            break;
        case (uint8)LIGHT_SENS_ADC__BITS_10:
            tmpReg = LIGHT_SENS_ADC_SAR_RESOLUTION_10BIT | LIGHT_SENS_ADC_SAR_SAMPLE_WIDTH;
            break;
        case (uint8)LIGHT_SENS_ADC__BITS_8:
            tmpReg = LIGHT_SENS_ADC_SAR_RESOLUTION_8BIT | LIGHT_SENS_ADC_SAR_SAMPLE_WIDTH;
            break;
        default:
            tmpReg = LIGHT_SENS_ADC_SAR_RESOLUTION_12BIT | LIGHT_SENS_ADC_SAR_SAMPLE_WIDTH;
            /* Halt CPU in debug mode if resolution is out of valid range */
            CYASSERT(0u != 0u);
            break;
    }
    LIGHT_SENS_ADC_SAR_CSR2_REG = tmpReg;

     /* Calculate gain for convert counts to volts */
    LIGHT_SENS_ADC_CalcGain(resolution);
}


#if(LIGHT_SENS_ADC_DEFAULT_CONV_MODE != LIGHT_SENS_ADC__HARDWARE_TRIGGER)


    /*******************************************************************************
    * Function Name: LIGHT_SENS_ADC_StartConvert
    ********************************************************************************
    *
    * Summary:
    *  Forces the ADC to initiate a conversion. In free-running mode, the ADC runs
    *  continuously. In software trigger mode, the function also acts as a software
    *  version of the SOC and every conversion must be triggered by
    *  LIGHT_SENS_ADC_StartConvert(). This function is not available when the
    *  Hardware Trigger sample mode is selected.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Forces the ADC to initiate a conversion. In Free Running mode, the ADC will
    *  run continuously. In a software trigger mode the function also acts as a
    *  software version of the SOC. Here every conversion has to be triggered by
    *  the routine. This writes into the SOC bit in SAR_CTRL reg.
    *
    * Side Effects:
    *  In a software trigger mode the function switches source for SOF from the
    *  external pin to the internal SOF generation. Application should not call
    *  StartConvert if external source used for SOF.
    *
    *******************************************************************************/
    void LIGHT_SENS_ADC_StartConvert(void)
    {
        #if(LIGHT_SENS_ADC_DEFAULT_CONV_MODE != LIGHT_SENS_ADC__FREE_RUNNING)  /* If software triggered mode */
            LIGHT_SENS_ADC_SAR_CSR0_REG &= (uint8)~LIGHT_SENS_ADC_SAR_MX_SOF_UDB;   /* source: SOF bit */
        #endif /* End LIGHT_SENS_ADC_DEFAULT_CONV_MODE */

        /* Start the conversion */
        LIGHT_SENS_ADC_SAR_CSR0_REG |= LIGHT_SENS_ADC_SAR_SOF_START_CONV;
    }


    /*******************************************************************************
    * Function Name: LIGHT_SENS_ADC_StopConvert
    ********************************************************************************
    *
    * Summary:
    *  Forces the ADC to stop conversions. If a conversion is currently executing,
    *  that conversion will complete, but no further conversions will occur. This
    *  function is not available when the Hardware Trigger sample mode is selected.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Stops ADC conversion in Free Running mode.
    *
    * Side Effects:
    *  In Software Trigger sample mode, this function sets a software version of the
    *  SOC to low level and switches the SOC source to hardware SOC input.
    *
    *******************************************************************************/
    void LIGHT_SENS_ADC_StopConvert(void)
    {
        /* Stop all conversions */
        LIGHT_SENS_ADC_SAR_CSR0_REG &= (uint8)~LIGHT_SENS_ADC_SAR_SOF_START_CONV;

        #if(LIGHT_SENS_ADC_DEFAULT_CONV_MODE != LIGHT_SENS_ADC__FREE_RUNNING)  /* If software triggered mode */
            /* Return source to UDB for hardware SOF signal */
            LIGHT_SENS_ADC_SAR_CSR0_REG |= LIGHT_SENS_ADC_SAR_MX_SOF_UDB;    /* source: UDB */
        #endif /* End LIGHT_SENS_ADC_DEFAULT_CONV_MODE */

    }

#endif /* End LIGHT_SENS_ADC_DEFAULT_CONV_MODE != LIGHT_SENS_ADC__HARDWARE_TRIGGER */


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_IsEndConversion
********************************************************************************
*
* Summary:
*  Immediately returns the status of the conversion or does not return
*  (blocking) until the conversion completes, depending on the retMode
*  parameter.
*
* Parameters:
*  retMode:  Check conversion return mode.
*   LIGHT_SENS_ADC_RETURN_STATUS: Immediately returns the status. If the
*     value returned is zero, the conversion is not complete, and this function
*     should be retried until a nonzero result is returned.
*   LIGHT_SENS_ADC_WAIT_FOR_RESULT: Does not return a result until the ADC
*     conversion is complete.
*
* Return:
*  (uint8)  0 =>  The ADC is still calculating the last result.
*           1 =>  The last conversion is complete.
*
* Side Effects:
*  This function reads the end of conversion status, which is cleared on read.
*
*******************************************************************************/
uint8 LIGHT_SENS_ADC_IsEndConversion(uint8 retMode)
{
    uint8 status;

    do
    {
        status = LIGHT_SENS_ADC_SAR_CSR1_REG & LIGHT_SENS_ADC_SAR_EOF_1;
    } while ((status != LIGHT_SENS_ADC_SAR_EOF_1) && (retMode == LIGHT_SENS_ADC_WAIT_FOR_RESULT));
    /* If convertion complete, wait until EOF bit released */
    if(status == LIGHT_SENS_ADC_SAR_EOF_1)
    {
        /* wait one ADC clock to let the EOC status bit release */
        CyDelayUs(1u);
        /* Do the unconditional read operation of the CSR1 register to make sure the EOC bit has been cleared */
        CY_GET_REG8(LIGHT_SENS_ADC_SAR_CSR1_PTR);
    }

    return(status);
}


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_GetResult8
********************************************************************************
*
* Summary:
*  Returns the result of an 8-bit conversion. If the resolution is set greater
*  than 8 bits, the function returns the LSB of the result.
*  LIGHT_SENS_ADC_IsEndConversion() should be called to verify that the data
*   sample is ready.
*
* Parameters:
*  None.
*
* Return:
*  The LSB of the last ADC conversion.
*
* Global Variables:
*  LIGHT_SENS_ADC_shift - used to convert the ADC counts to the 2s
*  compliment form.
*
* Side Effects:
*  Converts the ADC counts to the 2s complement form.
*
*******************************************************************************/
int8 LIGHT_SENS_ADC_GetResult8( void )
{
    return( (int8)LIGHT_SENS_ADC_SAR_WRK0_REG - (int8)LIGHT_SENS_ADC_shift);
}


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_GetResult16
********************************************************************************
*
* Summary:
*  Returns a 16-bit result for a conversion with a result that has a resolution
*  of 8 to 12 bits.
*  LIGHT_SENS_ADC_IsEndConversion() should be called to verify that the data
*   sample is ready
*
* Parameters:
*  None.
*
* Return:
*  The 16-bit result of the last ADC conversion
*
* Global Variables:
*  LIGHT_SENS_ADC_shift - used to convert the ADC counts to the 2s
*  compliment form.
*
* Side Effects:
*  Converts the ADC counts to the 2s complement form.
*
*******************************************************************************/
int16 LIGHT_SENS_ADC_GetResult16( void )
{
    uint16 res;

    res = CY_GET_REG16(LIGHT_SENS_ADC_SAR_WRK_PTR);

    return( (int16)res - LIGHT_SENS_ADC_shift );
}


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_SetOffset
********************************************************************************
*
* Summary:
*  Sets the ADC offset, which is used by LIGHT_SENS_ADC_CountsTo_Volts(),
*  LIGHT_SENS_ADC_CountsTo_mVolts(), and LIGHT_SENS_ADC_CountsTo_uVolts()
*  to subtract the offset from the given reading before calculating the voltage
*  conversion.
*
* Parameters:
*  int16: This value is measured when the inputs are shorted or connected to
   the same input voltage.
*
* Return:
*  None.
*
* Global Variables:
*  The LIGHT_SENS_ADC_offset variable modified. This variable is used for
*  offset calibration purpose.
*  Affects the LIGHT_SENS_ADC_CountsTo_Volts,
*  LIGHT_SENS_ADC_CountsTo_mVolts, LIGHT_SENS_ADC_CountsTo_uVolts functions
*  by subtracting the given offset.
*
*******************************************************************************/
void LIGHT_SENS_ADC_SetOffset(int16 offset)
{
    LIGHT_SENS_ADC_offset = offset;
}


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_CalcGain
********************************************************************************
*
* Summary:
*  This function calculates the ADC gain in counts per 10 volt.
*
* Parameters:
*  uint8: resolution
*
* Return:
*  None.
*
* Global Variables:
*  LIGHT_SENS_ADC_shift variable initialized. This variable is used to
*  convert the ADC counts to the 2s compliment form.
*  LIGHT_SENS_ADC_countsPer10Volt variable initialized. This variable is used
*  for gain calibration purpose.
*
*******************************************************************************/
static void LIGHT_SENS_ADC_CalcGain( uint8 resolution )
{
    int32 counts;
    #if(!((LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSS_TO_VREF) || \
         (LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSSA_TO_VDDA) || \
         (LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSSA_TO_VDAC)) )
        uint16 diff_zero;
    #endif /* End LIGHT_SENS_ADC_DEFAULT_RANGE */

    switch (resolution)
    {
        case (uint8)LIGHT_SENS_ADC__BITS_12:
            counts = (int32)LIGHT_SENS_ADC_SAR_WRK_MAX_12BIT;
            #if(!((LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSS_TO_VREF) || \
                 (LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSSA_TO_VDDA) || \
                 (LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSSA_TO_VDAC)) )
                diff_zero = LIGHT_SENS_ADC_SAR_DIFF_SHIFT;
            #endif /* End LIGHT_SENS_ADC_DEFAULT_RANGE */
            break;
        case (uint8)LIGHT_SENS_ADC__BITS_10:
            counts = (int32)LIGHT_SENS_ADC_SAR_WRK_MAX_10BIT;
            #if(!((LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSS_TO_VREF) || \
                 (LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSSA_TO_VDDA) || \
                 (LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSSA_TO_VDAC)) )
                diff_zero = LIGHT_SENS_ADC_SAR_DIFF_SHIFT >> 2u;
            #endif /* End LIGHT_SENS_ADC_DEFAULT_RANGE */
            break;
        case (uint8)LIGHT_SENS_ADC__BITS_8:
            counts = (int32)LIGHT_SENS_ADC_SAR_WRK_MAX_8BIT;
            #if(!((LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSS_TO_VREF) || \
                 (LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSSA_TO_VDDA) || \
                 (LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSSA_TO_VDAC)) )
                diff_zero = LIGHT_SENS_ADC_SAR_DIFF_SHIFT >> 4u;
            #endif /* End LIGHT_SENS_ADC_DEFAULT_RANGE */
            break;
        default: /* Halt CPU in debug mode if resolution is out of valid range */
            counts = 0;
            #if(!((LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSS_TO_VREF) || \
                 (LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSSA_TO_VDDA) || \
                 (LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSSA_TO_VDAC)) )
                diff_zero = 0u;
            #endif /* End LIGHT_SENS_ADC_DEFAULT_RANGE */
            CYASSERT(0u != 0u);
            break;
    }
    LIGHT_SENS_ADC_countsPerVolt = 0; /* Clear obsolete variable */
    /* Calculate gain in counts per 10 volts with rounding */
    LIGHT_SENS_ADC_countsPer10Volt = (((counts * LIGHT_SENS_ADC_10MV_COUNTS) +
                        LIGHT_SENS_ADC_DEFAULT_REF_VOLTAGE_MV) / (LIGHT_SENS_ADC_DEFAULT_REF_VOLTAGE_MV * 2));

    #if( (LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSS_TO_VREF) || \
         (LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSSA_TO_VDDA) || \
         (LIGHT_SENS_ADC_DEFAULT_RANGE == LIGHT_SENS_ADC__VSSA_TO_VDAC) )
        LIGHT_SENS_ADC_shift = 0;
    #else
        LIGHT_SENS_ADC_shift = diff_zero;
    #endif /* End LIGHT_SENS_ADC_DEFAULT_RANGE */
}


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_SetGain
********************************************************************************
*
* Summary:
*  Sets the ADC gain in counts per volt for the voltage conversion functions
*  that follow. This value is set by default by the reference and input range
*  settings. It should only be used to further calibrate the ADC with a known
*  input or if the ADC is using an external reference.
*
* Parameters:
*  int16 adcGain counts per volt
*
* Return:
*  None.
*
* Global Variables:
*  LIGHT_SENS_ADC_countsPer10Volt variable modified. This variable is used
*  for gain calibration purpose.
*
*******************************************************************************/
void LIGHT_SENS_ADC_SetGain(int16 adcGain)
{
    LIGHT_SENS_ADC_countsPer10Volt = (int32)adcGain * 10;
}


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_SetScaledGain
********************************************************************************
*
* Summary:
*  Sets the ADC gain in counts per 10 volt for the voltage conversion functions
*  that follow. This value is set by default by the reference and input range
*  settings. It should only be used to further calibrate the ADC with a known
*  input or if the ADC is using an external reference.
*
* Parameters:
*  int32 adcGain  counts per 10 volt
*
* Return:
*  None.
*
* Global Variables:
*  LIGHT_SENS_ADC_countsPer10Volt variable modified. This variable is used
*  for gain calibration purpose.
*
*******************************************************************************/
void LIGHT_SENS_ADC_SetScaledGain(int32 adcGain)
{
    LIGHT_SENS_ADC_countsPer10Volt = adcGain;
}


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_CountsTo_mVolts
********************************************************************************
*
* Summary:
*  Converts the ADC output to millivolts as a 16-bit integer.
*
* Parameters:
*  int16 adcCounts:  Result from the ADC conversion
*
* Return:
*  int16 Result in mVolts
*
* Global Variables:
*  LIGHT_SENS_ADC_offset variable used.
*  LIGHT_SENS_ADC_countsPer10Volt variable used.
*
*******************************************************************************/
int16 LIGHT_SENS_ADC_CountsTo_mVolts(int16 adcCounts)
{
    int16 mVolts;
    int32 countsPer10Volt;

    if(LIGHT_SENS_ADC_countsPerVolt != 0)
    {   /* Support obsolete method */
        countsPer10Volt = (int32)LIGHT_SENS_ADC_countsPerVolt * 10;
    }
    else
    {
        countsPer10Volt = LIGHT_SENS_ADC_countsPer10Volt;
    }

    /* Subtract ADC offset */
    adcCounts -= LIGHT_SENS_ADC_offset;
    /* Convert to millivolts with rounding */
    mVolts = (int16)( (( (int32)adcCounts * LIGHT_SENS_ADC_10MV_COUNTS ) + ( (adcCounts > 0) ?
                       (countsPer10Volt / 2) : (-(countsPer10Volt / 2)) )) / countsPer10Volt);

    return( mVolts );
}


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_CountsTo_uVolts
********************************************************************************
*
* Summary:
*  Converts the ADC output to microvolts as a 32-bit integer.
*
* Parameters:
*  int16 adcCounts: Result from the ADC conversion
*
* Return:
*  int32 Result in micro Volts
*
* Global Variables:
*  LIGHT_SENS_ADC_offset variable used.
*  LIGHT_SENS_ADC_countsPer10Volt used to convert ADC counts to uVolts.
*
*******************************************************************************/
int32 LIGHT_SENS_ADC_CountsTo_uVolts(int16 adcCounts)
{

    int64 uVolts;
    int32 countsPer10Volt;

    if(LIGHT_SENS_ADC_countsPerVolt != 0)
    {   /* Support obsolete method */
        countsPer10Volt = (int32)LIGHT_SENS_ADC_countsPerVolt * 10;
    }
    else
    {
        countsPer10Volt = LIGHT_SENS_ADC_countsPer10Volt;
    }

    /* Subtract ADC offset */
    adcCounts -= LIGHT_SENS_ADC_offset;
    /* To convert adcCounts to microVolts it is required to be multiplied
    *  on 10 million and later divide on gain in counts per 10V.
    */
    uVolts = (( (int64)adcCounts * LIGHT_SENS_ADC_10UV_COUNTS ) / countsPer10Volt);

    return((int32) uVolts );
}


/*******************************************************************************
* Function Name: LIGHT_SENS_ADC_CountsTo_Volts
********************************************************************************
*
* Summary:
*  Converts the ADC output to volts as a floating-point number.
*
* Parameters:
*  int16 adcCounts: Result from the ADC conversion
*
* Return:
*  float Result in Volts
*
* Global Variables:
*  LIGHT_SENS_ADC_offset variable used.
*  LIGHT_SENS_ADC_countsPer10Volt used to convert ADC counts to Volts.
*
*******************************************************************************/
float32 LIGHT_SENS_ADC_CountsTo_Volts(int16 adcCounts)
{
    float32 volts;
    int32 countsPer10Volt;

    if(LIGHT_SENS_ADC_countsPerVolt != 0)
    {   /* Support obsolete method */
        countsPer10Volt = (int32)LIGHT_SENS_ADC_countsPerVolt * 10;
    }
    else
    {
        countsPer10Volt = LIGHT_SENS_ADC_countsPer10Volt;
    }

    /* Subtract ADC offset */
    adcCounts -= LIGHT_SENS_ADC_offset;

    volts = ((float32)adcCounts * LIGHT_SENS_ADC_10V_COUNTS) / (float32)countsPer10Volt;

    return( volts );
}


/* [] END OF FILE */
