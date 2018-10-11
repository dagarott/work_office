/*
 * FIFO.h
 *
 *  Created on: 18 may. 2018
 *      Author: jeniher
 */

#ifndef DRIVERS_INCLUDE_FIFO_H_
#define DRIVERS_INCLUDE_FIFO_H_

#include <stdint.h>
#include <string.h>



typedef enum tEstadoFIFO {
/* Definicion de los distintos estados de la PILA   */
    PILA_VACIA  = 0x00,
    PILA_OK     ,//00x01
    PILA_RESET  ,//0x02 // Este estado indica que se ha escrito los primeros
                        //posiciones de la cola FIFO
    PILA_LLENA  ,//0x03
} sEstadoFIFO;


/**
*******************************************************************************
\typedef        FIFOEstado
\brief          Tipo definido  cola FIFO
\struct         sFIFOEstado
\brief          Estructura para cola FIFO
******************************************************************************/
typedef struct  sFIFO
{
    /** Definimos el numero me mensajes de la cola FIFO */
    uint16_t    N_MSG;
    /** Definimos el numero datos que compone cada trama */
    uint16_t    N_WORDS;
    /** Numero total de palabras*/
    uint16_t    T_WORDS;
    /** Datos donde se almacena en la cola FIFO */
    uint16_t    *Datos_FIFO ;
    /** Datos de mensaje que desencolamos de la FIFO*/
    uint16_t    *Datos_Recibidos;
    /** Datos de mensaje que encolaremos en la FIFO*/
    uint16_t    *New_Datos;
    /** Puntero del mensaje a leer de la cola FIFO */
    uint16_t    Ptr_leer;
    /** Puntero del mensaje a escribir de la cola FIFO*/
    uint16_t    Ptr_escribir;
    /** indica los mensajes que hay por tratar*/
    uint16_t    Msg_pendientes;
    /** Indica el estado de la PILA */
    sEstadoFIFO Estado_PILA;
    /** Variable temporal para realizar el barrido de los string*/
     union
        {
            uint32_t all;
            struct
            {
             uint32_t array:16;
             uint32_t leer:1;
             uint32_t recibir:1;
             uint32_t reservado:14;
            } bit;
        } Flags;
    /** Puntero para encolar en la cola FIFO    */
    void (*Encolar)();
    /** Puntero para encolar en la cola FIFO    */
    void (*Desencolar)();
} FIFO;

void Encolar_FIFO    (FIFO *fifo);
void Desencolar_FIFO       (FIFO *fifo);
void Init_FIFO             (FIFO *fifo, uint16_t NumWords, uint16_t NumMsg);

#endif /* DRIVERS_INCLUDE_FIFO_H_ */
