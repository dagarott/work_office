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
\file           CONFIG_GPIO.c
\brief          Modulo de configuracion de los GPIO del microcontrolador
                TMS320F2877s.

\author         Jesus Nieto Hervas
\version        V0.0
\date           15/05/2018
**************************************************************************/

//
// Included
//
#include "F28x_Project.h"
#include "Inc_Drivers.h"

/**
********************************************************************************
 *  CPU01 :
 *  | GPIO | I/O|   Nombre    |  Descripcion
 *  ----------------------------------------------------------------------------
 *  | 02   | I  | E_Tierra2   | Entrada errores del check tierra Chademo
 *  ----------------------------------------------------------------------------
 *  | 03   | I  | E_Tierra1   | Entrada errores del check tierra Chademo
 *  ----------------------------------------------------------------------------
 *  | 17   | I  | VerifCL     | Entrada verifiaciones del Conector Lock
 *  ----------------------------------------------------------------------------
 *  | 20   | I  | CANB        | RX del CAN B para protcolo Cahdemo
 *  ----------------------------------------------------------------------------
 *  | 21   | O  | CANB        | TX del CAN B para protcolo Cahdemo
 *  ----------------------------------------------------------------------------
 *  | 41   | O  | CL          | Salida Conector Lock protocolo Chademo
 *  ----------------------------------------------------------------------------
 *  | 58   | O  | D2          | Salida D2 protocolo Chademo
 *  ----------------------------------------------------------------------------
 *  | 59   | O  | D1          | Salida D1 protocolo Chademo
 *  ----------------------------------------------------------------------------
 *  | 61   | 0  | Ventilador  | Salida Rele forzar refirgeracion por aire
 *  ----------------------------------------------------------------------------
 *  | 62   | 0  | S_Diodo     | Salida Rele para salida de potencia por diodo
 *  ----------------------------------------------------------------------------
 *  | 63   | 0  | S_V2G       | Salida Rele para entrada de potencia directa
 *  ----------------------------------------------------------------------------
 *  | 64   | 0  | S_Precarga  | Salida Rele para precargar del Bus
 *  ----------------------------------------------------------------------------
 *  | 65   | 0  | S_Masa      | Salida Rele para conectar masa del Bus
 *  ----------------------------------------------------------------------------
 *  | 89   | 0  | S_Tierra2   | Salida Rele activar check tierra Chademo
 *  ----------------------------------------------------------------------------
 *  | 91   | 0  | S_Tierra1   | Salida Rele activar check tierra Chademo
 *  ----------------------------------------------------------------------------
 *  | 99   | I  | j           | Entrada J protocolo Chademo
 *  ----------------------------------------------------------------------------
 */
//

/**
***************************************************************************
\fn         INIT_GPIO
\brief      Funcion principal de configuracion de los GPIOSs. Esta funcion
            es llamada desde el "main".
            Los GPIOS estan divididos en 6 Grupos (A,B,C,D,E,F) donde esta
            repartidos e la siguiente manera :
                - GRUPO A = GPIO00  a GPIO31
                - GRUPO B = GPIO32  a GPIO63
                - GRUPO C = GPIO64  a GPIO95
                - GRUPO D = GPIO96  a GPIO127
                - GRUPO E = GPIO128 a GPIO159
                - GRUPO F = GPIO160 a GPIO168

            NOTA IMPORTANTE : Se han implementado los modulos necesarios
            y los más importantes de configuracion. para más resigtros
            consular el PDF de TI "spruhx5e.pdf".

\param[in]  void
\return     void

**************************************************************************/
void Config_GPIO ()
{
    //
    //  pin = Num GPIO
    //  cpu = Num CPU
    //  peripheral = Cod funcion especial (tms320f28377s.pdf -> Table 4-3)
    // GPIO_SetupPinMux(pin, cpu, peripheral);
    //
    //  pin    = Num GPIO
    //  output = GPIO_OUTPUT
    //           GPIO_INPUT
    //  peripheral = GPIO_PUSHPULL
    //               GPIO_PULLUP
    //               GPIO_ASYNC
    //GPIO_SetupPinOptions(pin, output, flags)

    InitGpio();

 // Step 2.1 Inicializar GPIO para CPU1:
     GPIO_SetupPinMux(CL, GPIO_MUX_CPU1, 0);
     GPIO_SetupPinOptions(CL, GPIO_OUTPUT, GPIO_PUSHPULL);
     GPIO_SetupPinMux(D2, GPIO_MUX_CPU1, 0);
     GPIO_SetupPinOptions(D2, GPIO_OUTPUT, GPIO_PUSHPULL);
     GPIO_SetupPinMux(D1, GPIO_MUX_CPU1, 0);
     GPIO_SetupPinOptions(D1, GPIO_OUTPUT, GPIO_PUSHPULL);
     GPIO_SetupPinMux(Ventilador, GPIO_MUX_CPU1, 0);
     GPIO_SetupPinOptions(Ventilador, GPIO_OUTPUT, GPIO_PUSHPULL);
     GPIO_SetupPinMux(S_Diodo, GPIO_MUX_CPU1, 0);
     GPIO_SetupPinOptions(S_Diodo, GPIO_OUTPUT, GPIO_PUSHPULL);
     GPIO_SetupPinMux(S_V2G, GPIO_MUX_CPU1, 0);
     GPIO_SetupPinOptions(S_V2G, GPIO_OUTPUT, GPIO_PUSHPULL);
     GPIO_SetupPinMux(S_Precarga, GPIO_MUX_CPU1, 0);
     GPIO_SetupPinOptions(S_Precarga, GPIO_OUTPUT, GPIO_PUSHPULL);
     GPIO_SetupPinMux(S_Masa, GPIO_MUX_CPU1, 0);
     GPIO_SetupPinOptions(S_Masa, GPIO_OUTPUT, GPIO_PUSHPULL);
     GPIO_SetupPinMux(S_Tierra1, GPIO_MUX_CPU1, 0);
     GPIO_SetupPinOptions(S_Tierra2, GPIO_OUTPUT, GPIO_PUSHPULL);
     GPIO_SetupPinMux(LED10, GPIO_MUX_CPU1, 0);
     GPIO_SetupPinOptions(LED10, GPIO_OUTPUT, GPIO_PUSHPULL);
     GPIO_SetupPinMux(E_Tierra2, GPIO_MUX_CPU1, 0);
     GPIO_SetupPinOptions(E_Tierra2, GPIO_INPUT, GPIO_ASYNC);
     GPIO_SetupPinMux(E_Tierra1, GPIO_MUX_CPU1, 0);
     GPIO_SetupPinOptions(E_Tierra1, GPIO_INPUT, GPIO_ASYNC);
     GPIO_SetupPinMux(VerifCL, GPIO_MUX_CPU1, 0);
     GPIO_SetupPinOptions(VerifCL, GPIO_INPUT, GPIO_ASYNC);
     GPIO_SetupPinMux(j, GPIO_MUX_CPU1, 0);
     GPIO_SetupPinOptions(j, GPIO_INPUT, GPIO_ASYNC);

     // CANB_RX
     GPIO_SetupPinMux(17, GPIO_MUX_CPU1, 2);
     GPIO_SetupPinOptions(17, GPIO_INPUT, GPIO_ASYNC);
     // CANB_TX
     GPIO_SetupPinMux(12, GPIO_MUX_CPU1, 2);
     GPIO_SetupPinOptions(12, GPIO_OUTPUT, GPIO_PUSHPULL);
/*
    // ePWM 2A
    GPIO_SetupPinMux(2, GPIO_MUX_CPU1, 1);
    GPIO_SetupPinOptions(2, GPIO_OUTPUT, GPIO_PUSHPULL);
    // ePWM 2B
    GPIO_SetupPinMux(3, GPIO_MUX_CPU1, 1);
    GPIO_SetupPinOptions(3, GPIO_OUTPUT, GPIO_PUSHPULL);
    // ePWM 6A
    GPIO_SetupPinMux(10, GPIO_MUX_CPU1, 1);
    GPIO_SetupPinOptions(10, GPIO_OUTPUT, GPIO_PUSHPULL);
    // ePWM 6B
    GPIO_SetupPinMux(11, GPIO_MUX_CPU1, 1);
    GPIO_SetupPinOptions(11, GPIO_OUTPUT, GPIO_PUSHPULL);
    // ePWM 10A
    GPIO_SetupPinMux(18, GPIO_MUX_CPU1, 5);
    GPIO_SetupPinOptions(18, GPIO_OUTPUT, GPIO_PUSHPULL);
    // ePWM 10B
    GPIO_SetupPinMux(19, GPIO_MUX_CPU1, 5);
    GPIO_SetupPinOptions(19, GPIO_OUTPUT, GPIO_PUSHPULL);
    // CANRXA
    GPIO_SetupPinMux(70, GPIO_MUX_CPU1, 5);
    GPIO_SetupPinOptions(70, GPIO_INPUT, GPIO_ASYNC);
    // CANTXA
    GPIO_SetupPinMux(71, GPIO_MUX_CPU1, 5);
    GPIO_SetupPinOptions(71, GPIO_OUTPUT, GPIO_PUSHPULL);
    */
}

//
// FIN DEL ARCHIVO
//

