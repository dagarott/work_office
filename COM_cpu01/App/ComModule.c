/*
 * ComModule.c
 *
 *  Created on: 11 oct. 2018
 *      Author: dagaro
 */

/* USER CODE BEGIN Includes */
#include "ComModule.h"
/* USER CODE END Includes */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
/* USER CODE END PFP */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#define MSG_DATA_LENGTH  8

FIFO PowerSupplyMsgTX; //FIFO Tx defined for Power Supply
FIFO PowerSupplyMsgRX; //FIFO Rx defined for Power Supply
FIFO PCMsgRX; //FIFO Tx defined for Industrial PC
FIFO PCMsgTX; //FIFO Rx defined for Industrial PC
extern tCanMsg Diccionario_CanOpen[];
tCANMsgObject sTXCANMsg;

//unsigned char txMsgData[MSG_DATA_LENGTH];
/* USER CODE END PV */

/**
 * @brief  Set a new data frame in the correct CANOpen Protocol and stack it in FIFO,
 *         ready to be transmitted by CAN peripheral
 * @param Indice_Diccionario_TPO 
 * @param ptrMsg 
 * @param ptrFIFO 
 * @return unsigned char 
 */
//uint16_t Set_CANOpenMsg_To_Tx(enum Indice_Diccionario_TPO Idx, uint16_t *ptrMsg)
uint16_t Set_CANOpenMsg_To_Tx(enum Indice_Diccionario_TPO Idx)
{

    uint32_t tmp = 0;
    uint16_t CANMsg[10];
    uint16_t *ptrMsg;

    ptrMsg=&CANMsg;

    if (ptrMsg == NULL) //For sanity, checking pointer
        return (0x00); //NULL pointer. Error

    *(ptrMsg++) = Diccionario_CanOpen[Idx].Modo_Acceso;
    *(ptrMsg++) = (uint16_t) ((Diccionario_CanOpen[Idx].ID) & 0x00FF); //Object Dictionary Index
    *(ptrMsg++) = (uint16_t) ((Diccionario_CanOpen[Idx].ID) >> 8); //Stored as little endian
    *(ptrMsg++)=((Diccionario_CanOpen[Idx].SubIndice)); //Stored SunIndex
    tmp = Diccionario_CanOpen[Idx].Buf;
    *(ptrMsg++) = (uint16_t) (tmp & 0x00FF);   //Buffer Data.Stored as little endian
    tmp = tmp >> 8;
    *(ptrMsg++) = (uint16_t) (tmp & 0x00FF);   //Buffer Data. Stored as little endian
    tmp = tmp >> 8;
    *(ptrMsg++) = (uint16_t) (tmp & 0x00FF);   //Buffer Data. Stored as little endian
    tmp = tmp >> 8;
    *(ptrMsg++) = (uint16_t) (tmp & 0x00FF);   //Buffer Data. Stored as little endian

    memcpy((void *)(PowerSupplyMsgTX.New_Datos), (void *)(ptrMsg), 1);  //Message in correct format
                                                                        //stored in one item of FIFO struct
    Encolar_FIFO(&PowerSupplyMsgTX);    //FInally CAN message is queued on the stack

    return(0x01); //All OK
}






