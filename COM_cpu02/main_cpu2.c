//###########################################################################
//
// FILE:   blinky_cpu01.c
//
// TITLE:  LED Blink Example for F2837xD.
//
//! \addtogroup dual_example_list
//! <h1> Blinky </h1>
//!
//! Dual Core Blinky Example.  This example demonstrates how to implement
//! and run a standalone application on both cores.
//!
//
//###########################################################################
// $TI Release: F2837xD Support Library v210 $
// $Release Date: Tue Nov  1 14:46:15 CDT 2016 $
// $Copyright: Copyright (C) 2013-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Included Files
//
#include "F28x_Project.h"
#include "F2837xD_Ipc_drivers.h"
#include "Inc_Drivers.h"

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
//  Habilitar las Interrupciones
//
    Hablitar_ISR ();

//
// Bucle Infinito
//
    for(;;)
    {
//
// Turn on LED
//
    ON_LED9() ;
//
// Delay for a bit.
//
    DELAY_US(1000 * 250);

//
// Turn off LED
//
    OFF_LED9() ;
//
// Delay for a bit.
//
    DELAY_US(1000 * 250);
    }

}

//
// End of file
//
