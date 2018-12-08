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
 * Description: SHAS Area Controller Peripheral Data Structures
 * Author(s): Jamie Doan, John Mo, Dallas Crus, William Vuong
 * Revision Date: 2018-11-04
 * ========================================
*/
#ifndef DEVSTRUCT_H
#define DEVSTRUCT_H
    
#include "project.h"

struct areacontroller {
    uint8   id; // 0xAA Front door, 0xBB Living Room, 0xCC Bathroom, 0xDD Bedroom
    uint8   numActs;
    uint8   numSens;
    char*   description;
};
    
struct actuators {
    char    id; // Keep this unique, 26 should be enough... maybe
    uint8   type; // 0 stepper, 1 LEDs, 2 Speaker/Piezo ... Might include others
    uint16  val;
    uint8   dir; // Stepper (type 0) use only
    
};

struct sensors {
    char    id;   // Keep this unique, 26 should be enough... maybe
    uint8   type; // 0 light sensor (TEMT6000), 1 HC_SR04 Ultra, 2 SHARP IR DIST, 3 TMP36/MAX Temp
    uint16  val;
};

    
#endif
/* [] END OF FILE */
