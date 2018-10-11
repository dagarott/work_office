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
 \file           FIFO.c
 \brief          Modulo de configuracion de las colas FIFO del
 microcontrolador TMS320F2877s.

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
#include <stdlib.h>

void Init_FIFO(FIFO *fifo, uint16_t NumWords, uint16_t NumMsg)
{

    fifo->N_WORDS = NumWords;
    fifo->N_MSG = NumMsg;
    fifo->T_WORDS = NumWords * NumMsg;

    fifo->Datos_FIFO = (uint16_t *) calloc((fifo->T_WORDS + 1),
                                           sizeof(uint16_t));
    fifo->Datos_Recibidos = (uint16_t *) calloc(NumWords + 1, sizeof(uint16_t));
    fifo->New_Datos = (uint16_t *) calloc(NumWords + 1, sizeof(uint16_t));

    fifo->Estado_PILA = PILA_VACIA;
} // FIN CrearString

/**
 *******************************************************************************
 \fn         void Encolar Trama
 \brief      Funcion que introduce una trama a la cola FIFO
 \param[in]  FIFOEstado -> Estructura de la cola FIFO
 \return     void
 ******************************************************************************/
void Encolar_FIFO(FIFO *fifo)
{
    // Reset todos los punteros temporales
    fifo->Flags.all = 0x00;

    // Comprobamos el estado de la pila
    switch (fifo->Estado_PILA)
    {
    // Si esta vacia recibimos el mensaje
    case (PILA_VACIA):  //Correct state of FIFO, allowed to store data
    {
        fifo->Flags.bit.recibir++;
        break;
    }  // FIN case
        // Si esta OK, comprobamos que estamos por encima de la de leer
    case (PILA_OK):
    {
        if (fifo->Ptr_leer < fifo->Ptr_escribir)
            fifo->Flags.bit.recibir++;
        else
            fifo->Flags.bit.recibir = 0;
        break;
    }    // FIN case
        // Si esta RESET, hemos dado la vuelta y comprobamos que esta por detras
    case (PILA_RESET):
    {
        if (fifo->Ptr_leer > fifo->Ptr_escribir)
            fifo->Flags.bit.recibir++;
        else
            fifo->Flags.bit.recibir = 0;
        break;
    }    // FIN
        // Si esta llena o un error diferente forazamos a estado lleno y no
        // recibimos nada
    default:
    {
        fifo->Flags.bit.recibir = 0;
        break;
    }    // FIN default
    }    // FIN switch

    if (fifo->Flags.bit.recibir > 0)
    {
        // hacemos un barrido de los array de los datos recibidos
        for (fifo->Flags.bit.array = 0;
                fifo->Flags.bit.array <= (fifo->N_WORDS - 1);
                fifo->Flags.bit.array++)
        {
            memcpy((void *) (fifo->Datos_FIFO + fifo->Ptr_escribir),
                   (void *) (fifo->New_Datos + fifo->Flags.bit.array), 1);

            fifo->Ptr_escribir++;
        }

        fifo->Msg_pendientes++;

        if (fifo->Msg_pendientes >= fifo->N_MSG)
        {
            fifo->Estado_PILA = PILA_LLENA;  //
            if (fifo->Ptr_escribir >= fifo->T_WORDS)
            {
                fifo->Ptr_escribir = 0x00; //Pointer for write equal to maximum data allowed for the FIFO, then reset pointer
            }
        }
        else if (fifo->Ptr_escribir >= fifo->T_WORDS)
        {
            fifo->Ptr_escribir = 0x00;
            // Comprobamos que se han leido los primeros mensajes
            if (fifo->Ptr_leer > 0x00)
            {
                fifo->Estado_PILA = PILA_RESET;
            }
            else
                fifo->Estado_PILA = PILA_LLENA;
        }
        else if (fifo->Ptr_escribir > fifo->Ptr_leer)
        {
            fifo->Estado_PILA = PILA_OK;
        }
        else
        {
            fifo->Estado_PILA = PILA_RESET;
        }
    } // FIN if fifo->Flags.bit.

    else
        fifo->Estado_PILA = PILA_LLENA;

} // FIN Encolar_FIFO

/**
 *******************************************************************************
 \fn         void Desencolar FIFO
 \brief      Funcion que saca una trama a la cola FIFO
 \param[in]  FIFOEstado -> Estructura de la cola FIFO
 \return     void
 ******************************************************************************/
void Desencolar_FIFO(FIFO *fifo)
{
    // Reset todos los punteros temporales
    fifo->Flags.all = 0x00;

    // Comprobamos el estado de la pila
    switch (fifo->Estado_PILA)
    {
    // Si esta llena sacamos el mensaje
    case (PILA_LLENA):
    {
        fifo->Flags.bit.leer++;
        break;
    } // FIN case
        // Si esta OK, comprobamos que estamos por encima de la de leer
    case (PILA_OK):
    {
        if (fifo->Ptr_leer < fifo->Ptr_escribir)
            fifo->Flags.bit.leer++;
        else
            fifo->Flags.bit.leer = 0;
        break;
    }      // FIN case
        // Si esta RESET, hemos dado la vuelta y comprobamos que esta por detras
    case (PILA_RESET):
    {
        fifo->Flags.bit.leer++;
        break;
    }      // FIN
        // Si esta llena o un error diferente forazamos a estado lleno y no
        // recibimos nada
    default:
    {
        fifo->Flags.bit.leer = 0;
        break;
    }      // FIN default
    }      // FIN switch

    if (fifo->Flags.bit.leer > 0)
    {
        // hacemos un barrido de los array de los datos a leer
        for (fifo->Flags.bit.array = 0;
                fifo->Flags.bit.array <= (fifo->N_WORDS - 1);
                fifo->Flags.bit.array++)
        {
            memcpy((void *) (fifo->Datos_Recibidos + fifo->Flags.bit.array),
                   (void *) (fifo->Datos_FIFO + fifo->Ptr_leer), 1);
            fifo->Ptr_leer++;
        }
        fifo->Msg_pendientes--;

        // Actualizamos el estado de la cola FIFO
        if (fifo->Msg_pendientes == 0x00)
        {
            fifo->Estado_PILA = PILA_VACIA;
            if (fifo->T_WORDS <= fifo->Ptr_leer)
            {
                fifo->Ptr_leer = 0x00;
            }
        }

        else if (fifo->T_WORDS <= fifo->Ptr_leer)
        {
            fifo->Ptr_leer = 0x00;
            // Comprobamos que se han leido los primeros mensajes
            if (fifo->Ptr_escribir > 0x00)
            {
                fifo->Estado_PILA = PILA_OK;
            }
            else
            {
                fifo->Estado_PILA = PILA_VACIA;
            }
        }

        else if (fifo->Ptr_escribir > fifo->Ptr_leer)
        {
            fifo->Estado_PILA = PILA_OK;
        }

        else
        {
            fifo->Estado_PILA = PILA_RESET;
        }
    }
    else
    {
        fifo->Estado_PILA = PILA_VACIA;
    }      // FIN fifo->N_MSG <= fifo->Msg_leido

}      // FIN Desencolar_FIFO
