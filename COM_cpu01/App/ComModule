/*
 * CAN.c
 *
 *  Created on: 25 sept. 2018
 *      Author: jeniher
 */

//
// Included Files
//
#include "F28x_Project.h"
#include "F2837xD_Ipc_drivers.h"
#include "Inc_Drivers.h"
#include "Diccionario_CANOpen.h"
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_can.h"
#include "can.h"
#include "systick.h"

#include "Chademo.h"
#include "Config_CAN.h"

//
//  Defines
//
#define MSG_DATA_LENGTH  8

//
// Funciones Privadas
//
    void Transmitir_CAN     (void);
    void Init_tramas_CAN    (void);

//
// Estructuras
//
    FIFO FIFO_CHADEMO;

// Buzones CAN TX para protocolo Chademo
    tCANMsgObject sTXCANMsg_108;
    unsigned char txMsgData_108[MSG_DATA_LENGTH];
    tCANMsgObject sTXCANMsg_109;
    unsigned char txMsgData_109[MSG_DATA_LENGTH];
    tCANMsgObject sTXCANMsg_208;
    unsigned char txMsgData_208[MSG_DATA_LENGTH];
    tCANMsgObject sTXCANMsg_209;
    unsigned char txMsgData_209[MSG_DATA_LENGTH];

// Buzones CAN RX para protocolo Chademo
    tCANMsgObject sRXCANMsg_100;
    unsigned char rxMsgData_100[MSG_DATA_LENGTH];
    tCANMsgObject sRXCANMsg_101;
    unsigned char rxMsgData_101[MSG_DATA_LENGTH];
    tCANMsgObject sRXCANMsg_102;
    unsigned char rxMsgData_102[MSG_DATA_LENGTH];
    tCANMsgObject sRXCANMsg_200;
    unsigned char rxMsgData_200[MSG_DATA_LENGTH];
    tCANMsgObject sRXCANMsg_201;
    unsigned char rxMsgData_201[MSG_DATA_LENGTH];

//
// Variables Globals
//
    uint16_t i_for;
    uint32_t timeout = 1000;
    extern uint32_t Tick;
    tCANMsgObject sTXCANMessage;

void Init_Chademo ()
{
//
//  Iniciar CAN_B
//
    Config_CANB (500, 1);

//
//  Iniciar Buzones CAN
//
    Init_tramas_CAN ();

//
//  FIFO CAN
//
    // BUF = 1 ID + 8 Data = 9 Datos
    // Num Msg = 5
    Init_FIFO(&FIFO_CHADEMO, MSG_DATA_LENGTH+1, 5);

    //Reset Tick
    Tick = 0;


}// FIN Init_Chademo

void Init_tramas_CAN ()
{
    volatile uint32_t NumMsg = 1;
    //
    // Initialize the receive message object used for receiving CAN messages.
    // Message Object Parameters:
    //      Message Identifier: 0xYYYY
    //      Message ID Mask: 0x0
    //      Message Object Flags: Receive Interrupt
    //      Message Data Length: 4 Bytes
    //      Message Receive data: rxMsgData
    //

    // Trama ID 100
    /*sRXCANMsg_100.ui32MsgID     = 0x100;
    sRXCANMsg_100.ui32MsgIDMask = 0xFFFFFFFF;
    sRXCANMsg_100.ui32Flags     = MSG_OBJ_RX_INT_ENABLE;
    sRXCANMsg_100.ui32MsgLen    = MSG_DATA_LENGTH;
    sRXCANMsg_100.pucMsgData    = rxMsgData_100;
    NumMsg = 1;
    //Init_Buzones (sRXCANMsg_100, MSG_OBJ_TYPE_RX, NumMsg);
    CANMessageSet(CANB_BASE, NumMsg, &sRXCANMsg_100, MSG_OBJ_TYPE_RX);*/
/*    // Trama ID 101
    sRXCANMsg_101.ui32MsgID     = 0x101;
    sRXCANMsg_101.ui32MsgIDMask = 0xFFFFFFFF;
    sRXCANMsg_101.ui32Flags     = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sRXCANMsg_101.ui32MsgLen    = MSG_DATA_LENGTH;
    sRXCANMsg_101.pucMsgData    = rxMsgData_101;
    NumMsg ++;
    Init_Buzones (sRXCANMsg_101, MSG_OBJ_TYPE_RX, NumMsg);
    // Trama ID 102
    sRXCANMsg_102.ui32MsgID     = 0x102;
    sRXCANMsg_102.ui32MsgIDMask = 0xFFFFFFFF;
    sRXCANMsg_102.ui32Flags     = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sRXCANMsg_102.ui32MsgLen    = MSG_DATA_LENGTH;
    sRXCANMsg_102.pucMsgData    = rxMsgData_102;
    NumMsg ++;
    Init_Buzones (sRXCANMsg_102, MSG_OBJ_TYPE_RX, NumMsg);
    // Trama ID 200
    sRXCANMsg_200.ui32MsgID     = 0x200;
    sRXCANMsg_200.ui32MsgIDMask = 0xFFFFFFFF;
    sRXCANMsg_200.ui32Flags     = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sRXCANMsg_200.ui32MsgLen    = MSG_DATA_LENGTH;
    sRXCANMsg_200.pucMsgData    = rxMsgData_200;
    NumMsg ++;
    Init_Buzones (sRXCANMsg_200, MSG_OBJ_TYPE_RX, NumMsg);
    // Trama ID 201
    sRXCANMsg_201.ui32MsgID     = 0x201;
    sRXCANMsg_201.ui32MsgIDMask = 0xFFFFFFFF;
    sRXCANMsg_201.ui32Flags     = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sRXCANMsg_201.ui32MsgLen    = MSG_DATA_LENGTH;
    sRXCANMsg_201.pucMsgData    = rxMsgData_201;
    NumMsg ++;
    Init_Buzones (sRXCANMsg_201, MSG_OBJ_TYPE_RX, NumMsg);*/
}

void Chademo ()
{

   if (Tick >= timeout)
    {

    Transmitir_CAN ();

    timeout = timeout + 10;
    }// FIN timeout
}// FIN Chademo


void Transmitir_CAN ()
{

 static uint16_t i_ID;


  CANMessageSet(CANB_BASE, 1, &sTXCANMessage, MSG_OBJ_TYPE_TX);

}// FIN Transmitir CAN B
