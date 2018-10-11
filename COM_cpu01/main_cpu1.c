//###########################################################################
//
// FILE:   COM_cpu01.c
//
// TITLE:  Comunicaciones con el Vehiculo Electrico mediante el protocolo de
// comunicaciones CAHDEMO v2.0 V2G con el microcontrolador de TI F2837xD.
//
//! \addtogroup Comunicaciones CHADEMO
//! <h1> Comunicaciones CHADEMO </h1>
//!
//!
//  CVS => v1.0 -> Inicio del SW.
//      => vX.X ->
//
//###########################################################################
// $TI Release: F2837xD Support Library v210 $
// $Release Date: 24/09/2018 $
//###########################################################################

//
// Included Files
//
#include "F28x_Project.h"
#include "F2837xD_Ipc_drivers.h"
#include "Inc_Drivers.h"
#include "DEF_Global.h"
#include "Chademo.h"

//
// Main
//
void main(void)
{
//
//  Iniciar C2000
//
    Init_HW ();

//
//  Iniciar protocolo Chademo
//
    Init_Chademo();

//
//  Habilitar las Interrupciones
//
    Hablitar_ISR ();


//
// Bucle Infinito
//
    for(;;)
    {
    Chademo ();
    }

}

//
// End of file
//
