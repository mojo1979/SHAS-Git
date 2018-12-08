/* ========================================
 *
 * Copyright J2DW, 2018
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF J2DW.
 *
 * File: stepctrl.c
 * Description: SHAS Area Controller Stepper Motor Functions
 * Author(s): Jamie Doan, John Mo, Dallas Crus, William Vuong
 * Revision Date: 2018-11-04
 * ========================================
*/
#include "stepctrl.h"
#include "project.h"
#include "stdlib.h"

void STEP_EN(uint8 num) {
    if (num == 0) {
       Step_Control_Write(Step_Control_Read() & 0x06); 
    } else {
       Step_Control_Write(Step_Control_Read() | 0x01); 
    }
}

void STEP_DIR(uint8 num) {
    if (num == 0) {
       Step_Control_Write(Step_Control_Read() & 0x03); 
    } else {
       Step_Control_Write(Step_Control_Read() | 0x04); 
    }
}

void STEP_RUN() {
    Step_Control_Write(Step_Control_Read() ^ 0x02); 
    Step_Control_Write(Step_Control_Read() ^ 0x02); 
}

/* [] END OF FILE */
