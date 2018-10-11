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


#define LED9                34
#define Toggle_LED9()       GpioDataRegs.GPATOGGLE.bit.GPIO12 = 1
#define ON_LED9()           GPIO_WritePin(34,0)
#define OFF_LED9()          GPIO_WritePin(34,1)
#define LED10               31
#define Toggle_LED10()      GpioDataRegs.GPATOGGLE.bit.GPIO13 = 1
#define ON_LED10()          GPIO_WritePin(31,0)
#define OFF_LED10()         GPIO_WritePin(31,1)

#define E_Tierra2           2
#define Estado_E_Tierra2()  GPIO_ReadPin(E_Tierra2)
#define E_Tierra1           3
#define Estado_E_Tierra1()  GPIO_ReadPin(E_Tierra1)
#define VerifCL             17
#define Estado_VerifCL()    GPIO_ReadPin(Verif_CL)
#define CL                  41
#define ON_CL()             GPIO_WritePin(CL,1)
#define OFF_CL()            GPIO_WritePin(CL,0)
#define D2                  58
#define ON_D2()             GPIO_WritePin(D2,1)
#define OFF_D2()            GPIO_WritePin(D2,0)
#define D1                  59
#define ON_D1()             GPIO_WritePin(D1,1)
#define OFF_D1()            GPIO_WritePin(D1,0)
#define Ventilador          61
#define ON_Ventilador()     GPIO_WritePin(Ventilador,1)
#define OFF_ventilador()    GPIO_WritePin(Ventilador,0)
#define S_Diodo             62
#define ON_S_Diodo()        GPIO_WritePin(S_Diodo,1)
#define OFF_S_Diodo()       GPIO_WritePin(S_Diodo,0)
#define S_V2G               63
#define ON_S_V2G()          GPIO_WritePin(S_V2G,1)
#define OFF_S_V2G()         GPIO_WritePin(S_V2G,0)
#define S_Precarga          64
#define ON_S_Precarga()     GPIO_WritePin(S_Precarga,1)
#define OFF_S_Precarga()    GPIO_WritePin(S_Precarga,0)
#define S_Masa              65
#define ON_S_Masa()         GPIO_WritePin(S_Masa,1)
#define OFF_S_Masa()        GPIO_WritePin(S_Masa,0)
#define S_Tierra2           89
#define ON_S_Tierra2()      GPIO_WritePin(S_Tierra2,1)
#define OFF_S_Tierra2()     GPIO_WritePin(S_Tierra2,0)
#define S_Tierra1           91
#define ON_S_Tierra1()      GPIO_WritePin(S_Tierra1,1)
#define OFF_S_Tirra1()      GPIO_WritePin(S_Tierra1,0)
#define j                   99
#define ON_j()              GPIO_WritePin(j,1)
#define OFF_j()             GPIO_WritePin(j,0)

#endif /* DEF_GLOBAL_H_ */
