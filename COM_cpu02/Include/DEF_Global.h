/*
 * DEF_Global.h
 *
 *  Created on: 20 abr. 2018
 *      Author: jeniher
 */

#ifndef DEF_GLOBAL_H_
#define DEF_GLOBAL_H_

//
// Included Files
//
#include "F28x_Project.h"

//
// Variables publicas
//
typedef enum { FALSE = 0, TRUE } BOOL;


typedef union
    {
    uint32_t DATOS_32bits;
    struct
        {
        uint32_t Parte_Alta:16;
        uint32_t Parte_Baja:16;
        } DATOS_16bits ;
    struct
        {
        uint32_t Parte_Alta2:8;
        uint32_t Parte_Alta1:8;
        uint32_t Parte_Baja2:8;
        uint32_t Parte_Baja1:8;
        } DATOS_8bits ;
    struct
        {
        uint32_t Parte_Alta2B:4;
        uint32_t Parte_Alta2A:4;
        uint32_t Parte_Alta1B:4;
        uint32_t Parte_Alta1A:4;
        uint32_t Parte_Baja2B:4;
        uint32_t Parte_Baja2A:4;
        uint32_t Parte_Baja1B:4;
        uint32_t Parte_Baja1A:4;
        } DATOS_4bits ;
    }DATOS;


#define LED9              34
#define Toggle_LED9()     GpioDataRegs.GPATOGGLE.bit.GPIO12 = 1
#define ON_LED9()         GPIO_WritePin(34,0)
#define OFF_LED9()        GPIO_WritePin(34,1)
#define LED10             31
#define Toggle_LED10()    GpioDataRegs.GPATOGGLE.bit.GPIO13 = 1
#define ON_LED10()        GPIO_WritePin(31,0)
#define OFF_LED10()       GPIO_WritePin(34,1)

#endif /* DEF_GLOBAL_H_ */
