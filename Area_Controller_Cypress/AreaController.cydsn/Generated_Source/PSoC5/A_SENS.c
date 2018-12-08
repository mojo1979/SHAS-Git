/*******************************************************************************
* File Name: A_SENS.c
* Version 1.80
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "A_SENS.h"

static uint8 A_SENS_lastChannel = A_SENS_NULL_CHANNEL;


/*******************************************************************************
* Function Name: A_SENS_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void A_SENS_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < A_SENS_CHANNELS ; chan++)
    {
#if (A_SENS_MUXTYPE == A_SENS_MUX_SINGLE)
        A_SENS_Unset(chan);
#else
        A_SENS_CYAMUXSIDE_A_Unset(chan);
        A_SENS_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    A_SENS_lastChannel = A_SENS_NULL_CHANNEL;
}


#if (!A_SENS_ATMOSTONE)
/*******************************************************************************
* Function Name: A_SENS_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void A_SENS_Select(uint8 channel) 
{
    A_SENS_DisconnectAll();        /* Disconnect all previous connections */
    A_SENS_Connect(channel);       /* Make the given selection */
    A_SENS_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: A_SENS_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void A_SENS_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( A_SENS_lastChannel != A_SENS_NULL_CHANNEL)
    {
        A_SENS_Disconnect(A_SENS_lastChannel);
    }

    /* Make the new channel connection */
#if (A_SENS_MUXTYPE == A_SENS_MUX_SINGLE)
    A_SENS_Set(channel);
#else
    A_SENS_CYAMUXSIDE_A_Set(channel);
    A_SENS_CYAMUXSIDE_B_Set(channel);
#endif


    A_SENS_lastChannel = channel;   /* Update last channel */
}


#if (A_SENS_MUXTYPE == A_SENS_MUX_DIFF)
#if (!A_SENS_ATMOSTONE)
/*******************************************************************************
* Function Name: A_SENS_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void A_SENS_Connect(uint8 channel) 
{
    A_SENS_CYAMUXSIDE_A_Set(channel);
    A_SENS_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: A_SENS_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void A_SENS_Disconnect(uint8 channel) 
{
    A_SENS_CYAMUXSIDE_A_Unset(channel);
    A_SENS_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (A_SENS_ATMOSTONE)
/*******************************************************************************
* Function Name: A_SENS_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void A_SENS_DisconnectAll(void) 
{
    if(A_SENS_lastChannel != A_SENS_NULL_CHANNEL) 
    {
        A_SENS_Disconnect(A_SENS_lastChannel);
        A_SENS_lastChannel = A_SENS_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
