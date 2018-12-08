/* ========================================
 *
 * Copyright J2DW, 2018
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF J2DW.
 *
 * File: main.c
 * Description: SHAS Area Controller Main Firmware Template
 * Author(s): Jamie Doan, John Mo, Dallas Crus, William Vuong
 * Revision Date: 2018-11-04
 * ========================================
*/
#include "project.h"   //Cypress Project Headers
#include "stdlib.h"    //Standard C Library
#include "stdio.h"     //Standard C I/O Library
#include "stepctrl.h"  //Stepper Motor Control Functions
#include "devstruct.h" //Peripheral Structure Initializers
#include "devdef.h"    //Device Definitions


//Global Variables & Struct Declarations
// Vars
char commandBytes[16] = "";

uint8 k,getDir = 0,curCount = 0,readyStatus = 0,wmode = 0;
int8 curAct = -1;
uint16 counterVal = 0;

//Structs -> From devstructs.h
struct areacontroller mainAreacontroller;       //Initialize Area Controller ID Struct
struct actuators mainActuators[NUM_OF_ACTUATORS]; //Initialize Actuator Data Structs
struct sensors mainSensors[NUM_OF_SENSORS];

/* Function Prototypes */
void Area_Controller_Init( void );
void Check_Sens ( int id );

/* UART Interrupt Service Routine */
CY_ISR(Rx_ISR_Call) {
    char curChar = UART_GetChar();
    if (curChar == '!') {
        //UART_PutChar(curChar);
        wmode = 0;
        readyStatus = 1;
        //UART_PutString( commandBytes );
        //UART_PutString( "\r\n" );
    } else {
        if (curChar == 'W'){
            wmode = 1;
        } 
        if (wmode == 1) {
            if (curChar == ',') {
                mainActuators[curAct].val = atoi(commandBytes);
                for (k = 0; k < curCount;k++) {
                    commandBytes[k] = 0x00;
                }
                curCount = 0;
                curAct = -1;
            } else {
                if (curAct == -1) {
                    for (k = 0; k < NUM_OF_ACTUATORS; k++) {
                        if (mainActuators[k].id == curChar) {
                            curAct = k;
                            if (mainActuators[k].type == 0x00) {
                                getDir = 1;
                            }
                        }
                    }
                } else {
                    if (getDir == 1) {
                        if (curChar == 'A') {
                            mainActuators[curAct].dir = 0x00;
                        } else {
                            mainActuators[curAct].dir = 0x01;
                        }
                        getDir = 0; 
                    } else {
                        commandBytes[curCount] = curChar;
                        curCount++; 
                    }
                }
            }
        } else {
            if (curChar == 'R') {
                readyStatus = 2;   
            } else if (curChar == 'A') {
                readyStatus = 3;
            }
        }
    }
}

int main(void)
{
    /* Interrupt Inits */
    CyGlobalIntEnable; /* Enable global interrupts. */
    RxISR_StartEx(Rx_ISR_Call); /* Start UART ISR */
    
    /* Device Init & Vars*/
    Area_Controller_Init();
    ADC_Start();
    UART_Start(); //Start UART
    HCSR04_Start();
    
    
    UART_PutString( "Starting: " );
    UART_PutString( mainAreacontroller.description );
    UART_PutCRLF(0x00);
    RGB_OUT_Write(mainActuators[1].val);
    
    uint16 i= 0;
    
    /* Main Program Loop */
    for(;;)
    {
        Check_Sens(0);
        Check_Sens(1);
        Check_Sens(2);
        Check_Sens(3);
        if (readyStatus == 1) {
               
            // Change LED States
            RGB_OUT_Write(mainActuators[1].val);
            
            // Change Stepper State
            STEP_EN(1);
            STEP_DIR(mainActuators[0].dir);
            for(i = 1; i<=mainActuators[0].val; i++) {
                STEP_RUN();
                CyDelay(15);
            }
            mainActuators[0].val = 0;
            STEP_EN(0);
            readyStatus = 0;
        } else if (readyStatus == 2) {
            char sensorOutput[100];
            UART_PutChar('[');
            for (int i = 0; i < NUM_OF_SENSORS; i++) {
                snprintf(sensorOutput,100,"{ \"SensId\" : %d, \"SensType\" : %d, \"SensVal\" : %d }",
                    mainSensors[i].id,
                    mainSensors[i].type,
                    mainSensors[i].val
                );
                UART_PutString( sensorOutput );
                if ( i != 3 ) {
                    UART_PutChar(',');
                }
                UART_PutCRLF(0x00);
            }
            UART_PutChar(']');
            readyStatus = 0;
        } else if (readyStatus == 3) {
            char ACOutput[100];
            snprintf(ACOutput, 100, "{ \"ACId\" : %d, \"ACNumActs\" : %d, \"ACNumSens\" : %d, \"ACDesc\" : %s }",
                mainAreacontroller.id,
                mainAreacontroller.numActs,
                mainAreacontroller.numSens,
                mainAreacontroller.description
            );
            UART_PutString( ACOutput );
            UART_PutCRLF(0x00);
            readyStatus = 0;
        }
        CyDelay(1);
    }
}

void Area_Controller_Init ( void ) {
    //AreaController ID Init
    mainAreacontroller.id = DEV_ID;
    mainAreacontroller.numActs = NUM_OF_ACTUATORS;
    mainAreacontroller.numSens = NUM_OF_SENSORS;
    mainAreacontroller.description = DEV_DESC;
    
    //Sensor Init Structs
    //Light Sensor Init
    mainSensors[0].id = 'A';
    mainSensors[0].type = 0x00;
    mainSensors[0].val = 0x00;
    
    //SHARP Distance Sensor Init
    mainSensors[1].id = 'B';
    mainSensors[1].type = 0x02;
    mainSensors[1].val = 0x00;
    
    //TMP36 Sensor Init
    mainSensors[2].id = 'C';
    mainSensors[2].type = 0x03;
    mainSensors[2].val = 0x00;
    
    //ULTRASON Sensor Init
    mainSensors[3].id = 'D';
    mainSensors[3].type = 0x01;
    mainSensors[3].val = 0x00;
    
    //Actuator Init Structs
    //Stepper Init
    mainActuators[0].id = 'A';
    mainActuators[0].type = 0x00;
    mainActuators[0].dir = 0x00;
    mainActuators[0].val = 0x00;
    
    //RGBLED Init
    mainActuators[1].id = 'B';
    mainActuators[1].type = 0x01;
    mainActuators[1].val = 0x00;   
}

void Check_Sens( int id ) {
    if (mainSensors[id].type == 0x01) {
            TRIG_Write(1);
            CyDelay(10u);
            TRIG_Write(0);
            CyDelay(100);
            while (ECHO_PIN_Read()){
                //UART_PutString("in ECHO 1");
                //CyDelay(500);
            }
             mainSensors[id].val = 65536 - HCSR04_ReadCounter();
    } else {
        A_SENS_Select(id);
        ADC_StartConvert();
        CyDelay(10);
        mainSensors[id].val = ADC_GetResult16();
        ADC_StopConvert();
    }
}

/* [] END OF FILE */
