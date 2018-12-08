/*******************************************************************************
* File Name: HCSR04.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_HCSR04_H)
#define CY_TIMER_HCSR04_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 HCSR04_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define HCSR04_Resolution                 16u
#define HCSR04_UsingFixedFunction         1u
#define HCSR04_UsingHWCaptureCounter      0u
#define HCSR04_SoftwareCaptureMode        0u
#define HCSR04_SoftwareTriggerMode        0u
#define HCSR04_UsingHWEnable              1u
#define HCSR04_EnableTriggerMode          0u
#define HCSR04_InterruptOnCaptureCount    0u
#define HCSR04_RunModeUsed                0u
#define HCSR04_ControlRegRemoved          0u

#if defined(HCSR04_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define HCSR04_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (HCSR04_UsingFixedFunction)
    #define HCSR04_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define HCSR04_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End HCSR04_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!HCSR04_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (HCSR04_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!HCSR04_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}HCSR04_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    HCSR04_Start(void) ;
void    HCSR04_Stop(void) ;

void    HCSR04_SetInterruptMode(uint8 interruptMode) ;
uint8   HCSR04_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define HCSR04_GetInterruptSource() HCSR04_ReadStatusRegister()

#if(!HCSR04_UDB_CONTROL_REG_REMOVED)
    uint8   HCSR04_ReadControlRegister(void) ;
    void    HCSR04_WriteControlRegister(uint8 control) ;
#endif /* (!HCSR04_UDB_CONTROL_REG_REMOVED) */

uint16  HCSR04_ReadPeriod(void) ;
void    HCSR04_WritePeriod(uint16 period) ;
uint16  HCSR04_ReadCounter(void) ;
void    HCSR04_WriteCounter(uint16 counter) ;
uint16  HCSR04_ReadCapture(void) ;
void    HCSR04_SoftwareCapture(void) ;

#if(!HCSR04_UsingFixedFunction) /* UDB Prototypes */
    #if (HCSR04_SoftwareCaptureMode)
        void    HCSR04_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!HCSR04_UsingFixedFunction) */

    #if (HCSR04_SoftwareTriggerMode)
        void    HCSR04_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (HCSR04_SoftwareTriggerMode) */

    #if (HCSR04_EnableTriggerMode)
        void    HCSR04_EnableTrigger(void) ;
        void    HCSR04_DisableTrigger(void) ;
    #endif /* (HCSR04_EnableTriggerMode) */


    #if(HCSR04_InterruptOnCaptureCount)
        void    HCSR04_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (HCSR04_InterruptOnCaptureCount) */

    #if (HCSR04_UsingHWCaptureCounter)
        void    HCSR04_SetCaptureCount(uint8 captureCount) ;
        uint8   HCSR04_ReadCaptureCount(void) ;
    #endif /* (HCSR04_UsingHWCaptureCounter) */

    void HCSR04_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void HCSR04_Init(void)          ;
void HCSR04_Enable(void)        ;
void HCSR04_SaveConfig(void)    ;
void HCSR04_RestoreConfig(void) ;
void HCSR04_Sleep(void)         ;
void HCSR04_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define HCSR04__B_TIMER__CM_NONE 0
#define HCSR04__B_TIMER__CM_RISINGEDGE 1
#define HCSR04__B_TIMER__CM_FALLINGEDGE 2
#define HCSR04__B_TIMER__CM_EITHEREDGE 3
#define HCSR04__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define HCSR04__B_TIMER__TM_NONE 0x00u
#define HCSR04__B_TIMER__TM_RISINGEDGE 0x04u
#define HCSR04__B_TIMER__TM_FALLINGEDGE 0x08u
#define HCSR04__B_TIMER__TM_EITHEREDGE 0x0Cu
#define HCSR04__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define HCSR04_INIT_PERIOD             65535u
#define HCSR04_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << HCSR04_CTRL_CAP_MODE_SHIFT))
#define HCSR04_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << HCSR04_CTRL_TRIG_MODE_SHIFT))
#if (HCSR04_UsingFixedFunction)
    #define HCSR04_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << HCSR04_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << HCSR04_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define HCSR04_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << HCSR04_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << HCSR04_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << HCSR04_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (HCSR04_UsingFixedFunction) */
#define HCSR04_INIT_CAPTURE_COUNT      (2u)
#define HCSR04_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << HCSR04_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (HCSR04_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define HCSR04_STATUS         (*(reg8 *) HCSR04_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define HCSR04_STATUS_MASK    (*(reg8 *) HCSR04_TimerHW__SR0 )
    #define HCSR04_CONTROL        (*(reg8 *) HCSR04_TimerHW__CFG0)
    #define HCSR04_CONTROL2       (*(reg8 *) HCSR04_TimerHW__CFG1)
    #define HCSR04_CONTROL2_PTR   ( (reg8 *) HCSR04_TimerHW__CFG1)
    #define HCSR04_RT1            (*(reg8 *) HCSR04_TimerHW__RT1)
    #define HCSR04_RT1_PTR        ( (reg8 *) HCSR04_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define HCSR04_CONTROL3       (*(reg8 *) HCSR04_TimerHW__CFG2)
        #define HCSR04_CONTROL3_PTR   ( (reg8 *) HCSR04_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define HCSR04_GLOBAL_ENABLE  (*(reg8 *) HCSR04_TimerHW__PM_ACT_CFG)
    #define HCSR04_GLOBAL_STBY_ENABLE  (*(reg8 *) HCSR04_TimerHW__PM_STBY_CFG)

    #define HCSR04_CAPTURE_LSB         (* (reg16 *) HCSR04_TimerHW__CAP0 )
    #define HCSR04_CAPTURE_LSB_PTR       ((reg16 *) HCSR04_TimerHW__CAP0 )
    #define HCSR04_PERIOD_LSB          (* (reg16 *) HCSR04_TimerHW__PER0 )
    #define HCSR04_PERIOD_LSB_PTR        ((reg16 *) HCSR04_TimerHW__PER0 )
    #define HCSR04_COUNTER_LSB         (* (reg16 *) HCSR04_TimerHW__CNT_CMP0 )
    #define HCSR04_COUNTER_LSB_PTR       ((reg16 *) HCSR04_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define HCSR04_BLOCK_EN_MASK                     HCSR04_TimerHW__PM_ACT_MSK
    #define HCSR04_BLOCK_STBY_EN_MASK                HCSR04_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define HCSR04_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define HCSR04_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define HCSR04_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define HCSR04_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define HCSR04_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define HCSR04_CTRL_ENABLE                        ((uint8)((uint8)0x01u << HCSR04_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define HCSR04_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define HCSR04_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << HCSR04_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define HCSR04_CTRL_MODE_SHIFT                 0x01u
        #define HCSR04_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << HCSR04_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define HCSR04_CTRL_RCOD_SHIFT        0x02u
        #define HCSR04_CTRL_ENBL_SHIFT        0x00u
        #define HCSR04_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define HCSR04_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << HCSR04_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define HCSR04_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << HCSR04_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define HCSR04_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << HCSR04_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define HCSR04_CTRL_RCOD       ((uint8)((uint8)0x03u << HCSR04_CTRL_RCOD_SHIFT))
        #define HCSR04_CTRL_ENBL       ((uint8)((uint8)0x80u << HCSR04_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define HCSR04_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define HCSR04_RT1_MASK                        ((uint8)((uint8)0x03u << HCSR04_RT1_SHIFT))
    #define HCSR04_SYNC                            ((uint8)((uint8)0x03u << HCSR04_RT1_SHIFT))
    #define HCSR04_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define HCSR04_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << HCSR04_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define HCSR04_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << HCSR04_SYNCDSI_SHIFT))

    #define HCSR04_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << HCSR04_CTRL_MODE_SHIFT))
    #define HCSR04_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << HCSR04_CTRL_MODE_SHIFT))
    #define HCSR04_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << HCSR04_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define HCSR04_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define HCSR04_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define HCSR04_STATUS_TC_INT_MASK_SHIFT        (HCSR04_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define HCSR04_STATUS_CAPTURE_INT_MASK_SHIFT   (HCSR04_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define HCSR04_STATUS_TC                       ((uint8)((uint8)0x01u << HCSR04_STATUS_TC_SHIFT))
    #define HCSR04_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << HCSR04_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define HCSR04_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << HCSR04_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define HCSR04_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << HCSR04_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define HCSR04_STATUS              (* (reg8 *) HCSR04_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define HCSR04_STATUS_MASK         (* (reg8 *) HCSR04_TimerUDB_rstSts_stsreg__MASK_REG)
    #define HCSR04_STATUS_AUX_CTRL     (* (reg8 *) HCSR04_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define HCSR04_CONTROL             (* (reg8 *) HCSR04_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(HCSR04_Resolution <= 8u) /* 8-bit Timer */
        #define HCSR04_CAPTURE_LSB         (* (reg8 *) HCSR04_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define HCSR04_CAPTURE_LSB_PTR       ((reg8 *) HCSR04_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define HCSR04_PERIOD_LSB          (* (reg8 *) HCSR04_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define HCSR04_PERIOD_LSB_PTR        ((reg8 *) HCSR04_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define HCSR04_COUNTER_LSB         (* (reg8 *) HCSR04_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define HCSR04_COUNTER_LSB_PTR       ((reg8 *) HCSR04_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(HCSR04_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define HCSR04_CAPTURE_LSB         (* (reg16 *) HCSR04_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define HCSR04_CAPTURE_LSB_PTR       ((reg16 *) HCSR04_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define HCSR04_PERIOD_LSB          (* (reg16 *) HCSR04_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define HCSR04_PERIOD_LSB_PTR        ((reg16 *) HCSR04_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define HCSR04_COUNTER_LSB         (* (reg16 *) HCSR04_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define HCSR04_COUNTER_LSB_PTR       ((reg16 *) HCSR04_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define HCSR04_CAPTURE_LSB         (* (reg16 *) HCSR04_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define HCSR04_CAPTURE_LSB_PTR       ((reg16 *) HCSR04_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define HCSR04_PERIOD_LSB          (* (reg16 *) HCSR04_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define HCSR04_PERIOD_LSB_PTR        ((reg16 *) HCSR04_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define HCSR04_COUNTER_LSB         (* (reg16 *) HCSR04_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define HCSR04_COUNTER_LSB_PTR       ((reg16 *) HCSR04_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(HCSR04_Resolution <= 24u)/* 24-bit Timer */
        #define HCSR04_CAPTURE_LSB         (* (reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define HCSR04_CAPTURE_LSB_PTR       ((reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define HCSR04_PERIOD_LSB          (* (reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define HCSR04_PERIOD_LSB_PTR        ((reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define HCSR04_COUNTER_LSB         (* (reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define HCSR04_COUNTER_LSB_PTR       ((reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define HCSR04_CAPTURE_LSB         (* (reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define HCSR04_CAPTURE_LSB_PTR       ((reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define HCSR04_PERIOD_LSB          (* (reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define HCSR04_PERIOD_LSB_PTR        ((reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define HCSR04_COUNTER_LSB         (* (reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define HCSR04_COUNTER_LSB_PTR       ((reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define HCSR04_CAPTURE_LSB         (* (reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define HCSR04_CAPTURE_LSB_PTR       ((reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define HCSR04_PERIOD_LSB          (* (reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define HCSR04_PERIOD_LSB_PTR        ((reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define HCSR04_COUNTER_LSB         (* (reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define HCSR04_COUNTER_LSB_PTR       ((reg32 *) HCSR04_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define HCSR04_COUNTER_LSB_PTR_8BIT       ((reg8 *) HCSR04_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (HCSR04_UsingHWCaptureCounter)
        #define HCSR04_CAP_COUNT              (*(reg8 *) HCSR04_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define HCSR04_CAP_COUNT_PTR          ( (reg8 *) HCSR04_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define HCSR04_CAPTURE_COUNT_CTRL     (*(reg8 *) HCSR04_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define HCSR04_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) HCSR04_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (HCSR04_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define HCSR04_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define HCSR04_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define HCSR04_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define HCSR04_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define HCSR04_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define HCSR04_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << HCSR04_CTRL_INTCNT_SHIFT))
    #define HCSR04_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << HCSR04_CTRL_TRIG_MODE_SHIFT))
    #define HCSR04_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << HCSR04_CTRL_TRIG_EN_SHIFT))
    #define HCSR04_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << HCSR04_CTRL_CAP_MODE_SHIFT))
    #define HCSR04_CTRL_ENABLE                    ((uint8)((uint8)0x01u << HCSR04_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define HCSR04_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define HCSR04_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define HCSR04_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define HCSR04_STATUS_TC_INT_MASK_SHIFT       HCSR04_STATUS_TC_SHIFT
    #define HCSR04_STATUS_CAPTURE_INT_MASK_SHIFT  HCSR04_STATUS_CAPTURE_SHIFT
    #define HCSR04_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define HCSR04_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define HCSR04_STATUS_FIFOFULL_INT_MASK_SHIFT HCSR04_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define HCSR04_STATUS_TC                      ((uint8)((uint8)0x01u << HCSR04_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define HCSR04_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << HCSR04_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define HCSR04_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << HCSR04_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define HCSR04_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << HCSR04_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define HCSR04_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << HCSR04_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define HCSR04_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << HCSR04_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define HCSR04_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << HCSR04_STATUS_FIFOFULL_SHIFT))

    #define HCSR04_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define HCSR04_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define HCSR04_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define HCSR04_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define HCSR04_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define HCSR04_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_HCSR04_H */


/* [] END OF FILE */
