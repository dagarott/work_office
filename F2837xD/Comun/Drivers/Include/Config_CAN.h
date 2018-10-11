/*
 * Config_CAN.h
 *
 *  Created on: 16 may. 2018
 *      Author: jeniher
 */

#ifndef DRIVERS_INCLUDE_CONFIG_CAN_H_
#define DRIVERS_INCLUDE_CONFIG_CAN_H_

#include "can.h"

void    Config_CANB         (uint32_t BitRate, uint16_t ID);
void    Transmitir_CANB     (void);
void    Init_Buzones        (tCANMsgObject CANBuzon,tMsgObjType TipoMsg, uint32_t NumBuzon);




/* Parametros de comunicacion del BUS CAN   */
/** Direcciones del campo CAN-ID del protocolo CANpen */
#define EMCY_ID             0x80
#define TPDO1               0x180
#define RPDO1               0x200
#define TPDO2               0x280
#define RPDO2               0x300
#define TPDO3               0x480
#define RPDO3               0x400
#define TPDO4               0x580
#define RPDO4               0x500
#define TSDO                0x580
#define RSDO                0x600
#define MNT                 0x700

/** Modo de acceso a una entrada del diccionario de objetos, READ*/
#define OD_READ             0x40
#define OD_READ_4BYTES      0x43
#define OD_READ_2BYTES      0x4B
#define OD_READ_1BYTES      0x4F

/** Modo de acceso a una entrada del diccionario de objetos, WRITE*/
#define OD_WRITE            0x20
#define OD_WRITE_4BYTES     0x23
#define OD_WRITE_2BYTES     0x2B
#define OD_WRITE_1BYTES     0x2F

#define OD_ERROR            0x80

#endif /* DRIVERS_INCLUDE_CONFIG_CAN_H_ */
