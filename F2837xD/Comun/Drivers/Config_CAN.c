/**
***************************************************************************
\defgroup       DRIVERS

\brief          Modulo de inicializacion de los perifericos del
                TMS320F2877s

                Microcontroladores en los que se ha probado:
                TMS320F2877s

**************************************************************************/
/**
***************************************************************************
\file           CONFIG_CAN.c
\brief          Modulo de configuracion de los CAN del microcontrolador
                TMS320F2877s.

\author         Jesus Nieto Hervas
\version        V0.0
\date           16/05/2018
**************************************************************************/

//
// Included
//
#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "Inc_Drivers.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_can.h"
#include "can.h"

//
// Defines
//
#define MSG_DATA_LENGTH  8
#define TX_MSG_OBJ_ID    1
#define RX_MSG_OBJ_ID    2

//
// Estructuras
//
//extern FIFO FIFO_CANB;
// Buzones CAN RX para protocolo Chademo
    extern tCANMsgObject sRXCANMsg_100;
    extern unsigned char rxMsgData_100[MSG_DATA_LENGTH];
//
// Variables Globals
//
volatile unsigned long i;
volatile uint32_t errorFlag = 0;
unsigned char txMsgData[8];
unsigned char rxMsgData[8];
unsigned char rxMsgData2[8];
extern tCANMsgObject sTXCANMessage;
tCANMsgObject sRXCANMessage;
tCANMsgObject sRXCANMessage2;

/**
***************************************************************************
\fn         Config_CAN
\brief      Funcion principal de configuracion del CAN_A. Esta funcion
            es llamada desde el "main".

\param[in]  void
\return     void

**************************************************************************/
void Config_CANB (uint32_t BitRate, uint16_t ID)
{
//
// Initialize the CAN controllers
//
    CANInit(CANB_BASE);

//
// Setup CAN to be clocked off the PLL output clock
//
    CANClkSourceSelect(CANB_BASE, 0);   // 500kHz CAN-Clock

//
//               Num CAN | Frec de Reloj en Hz | BitRate en Bit/s
// CANBitRateSet(ui32Base, ui32SourceClock     , ui32BitRate)
//
    CANBitRateSet(CANB_BASE, (uint32_t)T_clk, BitRate*1000);

//
// Enable interrupts on the CAN B peripheral.
//
    CANIntEnable(CANB_BASE,CAN_INT_MASTER); // | CAN_INT_ERROR | CAN_INT_STATUS);

    CANGlobalIntEnable(CANB_BASE, CAN_GLB_INT_CANINT0);

    //
    // Initialize the transmit message object used for sending CAN messages.
    // Message Object Parameters:
    //      Message Identifier: 0x5555
    //      Message ID Mask: 0x0
    //      Message Object Flags: None
    //      Message Data Length: 4 Bytes
    //      Message Transmit data: txMsgData
    //
    sTXCANMessage.ui32MsgID = 0x5555;
    sTXCANMessage.ui32MsgIDMask = 0;
    sTXCANMessage.ui32Flags = 0;
    sTXCANMessage.ui32MsgLen = MSG_DATA_LENGTH;
    sTXCANMessage.pucMsgData = txMsgData;

    //
    // Initialize the receive message object used for receiving CAN messages.
    // Message Object Parameters:
    //      Message Identifier: 0x5555
    //      Message ID Mask: 0x0
    //      Message Object Flags: Receive Interrupt
    //      Message Data Length: 4 Bytes
    //      Message Receive data: rxMsgData
    //
    sRXCANMessage.ui32MsgID = 0x100;
    sRXCANMessage.ui32MsgIDMask = 0xFFFFFFFF;
    sRXCANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE  | MSG_OBJ_USE_ID_FILTER;
    sRXCANMessage.ui32MsgLen = MSG_DATA_LENGTH;
    sRXCANMessage.pucMsgData = rxMsgData;
    CANMessageSet(CANB_BASE, RX_MSG_OBJ_ID, &sRXCANMessage,
                  MSG_OBJ_TYPE_RX);
//
// Start CAN module A and B operations
//
    CANEnable(CANB_BASE);
}
// FIN Config_CANB

void Transmitir_CANB ()
{
    //uint16_t Datos_Temp[9];
    //
    // Transmit Message
    //
    //if (FIFO_CANB.Estado_PILA != PILA_VACIA)
    //{
    //    Desencolar_FIFO(&FIFO_CANB, Datos_Temp);

    //    sTXCANMessage.ui32MsgID = Datos_Temp[0];

    //    for (i=1 ; i < FIFO_CANB.MAXBUF ; i++)
     //       sTXCANMessage.pucMsgData[i-1] = Datos_Temp[i];

    //    CANMessageSet(CANB_BASE, TX_MSG_OBJ_ID, &sTXCANMessage,
    //                              MSG_OBJ_TYPE_TX);
    //}//FIN PILA_VACIA
}// FIN Transmitir CAN B

void Recibir_CANB ()
{

}

void Init_Buzones (tCANMsgObject CANBuzon, tMsgObjType TipoMsg, uint32_t NumBuzon)
{
    CANMessageSet(CANB_BASE, NumBuzon, &CANBuzon, TipoMsg);
}
//
// FIN DEL ARCHIVO
//
