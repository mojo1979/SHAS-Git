/* ========================================
 *
 * Copyright J2DW, 2018
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF J2DW.
 *
 * File: stepctrl.h
 * Description: SHAS Area Controller Stepper Motor Functions Header file
 * Author(s): Jamie Doan, John Mo, Dallas Crus, William Vuong
 * Revision Date: 2018-11-04
 * ========================================
*/

#ifndef STEPCTRL_H
#define STEPCTRL_H

#include "project.h"
    
void STEP_EN(uint8 num);

void STEP_DIR(uint8 num);

void STEP_RUN();

#endif

/* [] END OF FILE */
