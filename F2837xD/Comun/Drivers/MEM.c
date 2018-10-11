/*
 * MEM.c
 *
 *  Created on: 15 may. 2018
 *      Author: jeniher
 */


//
// Included Files
//
#include "F28x_Project.h"
#include "Inc_Drivers.h"
#include "DEF_Global.h"


/**
*******************************************************************************
\fn                         Obtener_Mem

\brief                  Funcion responsable de leer el valor de la poscion de memora

\param[in]          Pos_mem : el valor de la posicion de la memoria que deseamos
    leer
\return                 Valor : El nuevo valor del posicion de memoria


******************************************************************************/
uint32_t Obtener_Mem (uint32_t Pos_mem)
{
    uint32_t valor_return;
    DATOS valor;

    valor.DATOS_32bits  = *(uint32_t *)(Pos_mem);

    valor_return =  (valor.DATOS_16bits.Parte_Baja + valor.DATOS_16bits.Parte_Alta);

    return  valor_return;
}//FIN Obtener_Mem
