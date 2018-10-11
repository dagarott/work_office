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
\file           CONFIG_PWM.c
\brief          Modulo de configuracion de los PWM del microcontrolador
                TMS320F2877s.

\author         Jesus Nieto Hervas
\version        V0.0
\date           15/05/2018
**************************************************************************/

//
// Included Files
//
#include "F28x_Project.h"
#include "Inc_Drivers.h"
#include "DEF_Global.h"
#include "string.h"

//
// Funciones Privadas
//
void config_GPIO_ePWM   (void);
void Config_ePWM1       (void);
void Config_ePWM2       (void);
void Config_ePWM6       (void);
void Config_ePWM10      (void);

//
// Estructuras
//

//
// Variables Publicas
//
uint32_t Direccion_ePWMxregs;


/**
***************************************************************************
\fn         Config_ePWM
\brief      Funcion principal de configuracion de los PWMs. Esta funcion es
            llamada desde el "main", donde llamará a las funciones de
            configuracion de los distintos modulos de ePWM.
                - Config_ePWM1  (Implementada).
                - Config_ePWM2  (Implementada).
                - Config_ePWM3  (Sin implementar).
                - Config_ePWM4  (Sin implementar).
                - Config_ePWM5  (Sin implementar).
                - Config_ePWM6  (Implementada).
                - Config_ePWM7  (Sin implementar).
                - Config_ePWM8  (Sin implementar).
                - Config_ePWM9  (Sin implementar).
                - Config_ePWM10 (Sin implementar).
                - Config_ePWM11 (Sin implementar).
                - Config_ePWM12 (Sin implementar).

            Otra configuracion que se realiza es la de los GPIO para la
            señal de PWM. Se activa mediante la estructura "ePWM_GPIOReg".

            NOTA IMPORTANTE : Se han implementado los modulos necesarios
            y los más importantes de configuracion. para más resigtros
            consular el PDF de TI "spruhx5e.pdf".

\param[in]  void
\return     void

**************************************************************************/
void Config_EPwm ()
{
    /**
     *  Configuracion ePWM1 para el ADC
     *   10 kHz
     *   50 % Duty
     *   sin ISR
     */
    Config_ePWM1 ();

    /**
     *  Configuracion ePWM2 para el ZVT
     *  20 kHz
     *  50 % Duty
     *  sin ISR
     */
    Config_ePWM2 ();

    /**
     *  Configuracion ePWM6 para el ZVT
     *   20 kHz
     *   50 % Duty
     *   sin ISR
     */
    Config_ePWM6 ();

    /**
     *  Configuracion ePWM10 para el ZVT
     *  20 kHz
     *  50 % Duty
     *  sin ISR
     */
    Config_ePWM10 ();

    EALLOW;
    //  Reset conteo de todos lo ePWM
    //  Descomentar segun se usen los ePWM
    //EPwm12Regs.TBCTR = 0x00;
    //EPwm11Regs.TBCTR = 0x00;
    EPwm10Regs.TBCTR = 0x00;
    //EPwm9Regs.TBCTR  = 0x00;
    //EPwm8Regs.TBCTR  = 0x00;
    //EPwm7Regs.TBCTR  = 0x00;
    EPwm6Regs.TBCTR  = 0x00;
    //EPwm5Regs.TBCTR  = 0x00;
    //EPwm4Regs.TBCTR  = 0x00;
    //EPwm3Regs.TBCTR  = 0x00;
    EPwm2Regs.TBCTR  = 0x00;
    EPwm1Regs.TBCTR  = 0x00;

        CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

}// FIN Config_EPwm

/**
***************************************************************************
\fn         Config_ePWM
\brief      Funcion publica para modificar los parametros en tiempo real.
            Actualmente los parametros para modificar son:
                - Duty.
                - Frecuencia.
                - Desfase.
                - Tiempo Muerto (Dead Band).

\param[in]  ePWM  : Numero de ePWM que se va a modificar el parametro.
                    valores comprendidos entre 1 - 12.

\param[in]  Param : El valor del nuevo paramaetro que se va a modificar.
            Valores del Param:
                    - Duty             : 0 - 1
                    - TiempoMuerto_XED : ns
                    - Frecuencia       : kHz
                    - Desfase          : 0 - 360 Grados

\param[in]  MiembroEstructura : Indica el parametro que se va a modificar.
                    Sus posibles valores estan identificados en el enum
                    "tParam_ePWM".
\return     void

**************************************************************************/
void  Actualizar_ePWM   (uint16_t ePWM, uint32_t Param, tParam_ePWM MiembroEstructura)
{
    uint16_t size;
    uint32_t temp, valor_final;
    void *Datos_Local;
    DATOS registro_actual;

    if (ePWM > 12)
    {
        while (1)
        {
            // Error en el parametro ePWM. Revisar codigo
        }
    }
    else
    {
    //                    |Inicio estructuras PWM   | Offset estructura PWM deseado  | Offset Registro deseado
    Direccion_ePWMxregs = ((Start_Address_ePWMxRegs + (Size_ePWMxRegs * (ePWM - 1))) + MiembroEstructura) ;

    switch (MiembroEstructura)
        {
        case (Duty):
            {
            // 32 bits
            size = 2;
            if (Param > 100)
                Param = 1;
            // Obtenemos el valor que hay actualmente
            registro_actual.DATOS_32bits = Obtener_Mem (Direccion_ePWMxregs);
            // Calculamos el nuevo Duty
            // Obtenemos el valor actual de TBPR
            temp = Obtener_Mem (Direccion_ePWMxregs - (Duty - Frecuencia)) ;
            // Calculamos el nuevo duty
            temp *= (1 - ((float)Param/100.0));
            // Aplicamos el nuevo duty. Aplicamos Little Endian
            registro_actual.DATOS_16bits.Parte_Alta = registro_actual.DATOS_16bits.Parte_Baja;
            registro_actual.DATOS_16bits.Parte_Baja = temp;
            valor_final = registro_actual.DATOS_32bits;
            break;
            }
        case (TiempoMuerto_FED):
        case (TiempoMuerto_RED):
            {
            // 16 bits
            size = 1;
            // Calculamos el nuevo tiempo muerto
            valor_final = (Param * 1.0e-9) * T_clk;
            break;
            }
        case (Frecuencia):
            {
            // 16 bits
            size = 1;
            // Calculamos el nuevo TBPR para obtener la frecuencia deseada
            valor_final = ((T_clk / ((uint32_t)Param * 1000)) - 1) ;
            break;
            }
        case (Desfase):
            {
            // 32 bits
            size = 2;
           // while (Param > 360)
             //       Param -= 360.0;

            // Obtenemos el valor que hay actualmente
            registro_actual.DATOS_32bits = Obtener_Mem (Direccion_ePWMxregs);
            // Obtenemos el valor actual de TBPR
            //temp = Obtener_Mem (Direccion_ePWMxregs + (Frecuencia - Desfase)) ;
            // Calculamos el desfase de grados
            //temp = (Param * temp) / 360;
            // Aplicamos el nuevo desfase. Aplicamos Little Endian
            registro_actual.DATOS_16bits.Parte_Alta = registro_actual.DATOS_16bits.Parte_Baja;
            registro_actual.DATOS_16bits.Parte_Baja = temp;
            valor_final = registro_actual.DATOS_32bits;
            //valor_final = Param;
            break;
            }
        }// FIN switch

    Datos_Local = &valor_final ;

    EALLOW;
    memcpy ((uint32_t *)Direccion_ePWMxregs, Datos_Local, size );
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
    }// FIN else
}// FIN Actualizar ePWM

void Config_ePWM1 (void)
{
  //
  // Calculos Previos
  //
    float       Duty = 0.5;
    uint16_t    TBPRD, DeadBand,CMPA,CMPB,CMPC,CMPD;

    //  TBRPD (Count up) = ( CLK / PWM ) - 1
    TBPRD = (T_clk / 10000) - 1;
    //  TBRPD (Count UpDown) = 2 *  ( CLK / PWM ) - 1
    //TBPRD = 2*(T_clk / 10000) - 1;

    CMPA = (1 - Duty) * (TBPRD);
    CMPB = CMPC = CMPD = 0x00;
    //DeadBand = (Tiempo_Muerto * 1.0e-9) * T_clk
    DeadBand = 0;


  //-------------------------------------------------------------------------
  //    Setup TBPRD
  //-------------------------------------------------------------------------
  /* |----------------------|--------------------------|--------------------|
   * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
   * |----------------------|--------------------------|--------------------|
   * |  TBPRDSOFT           | Registro que selecciona  | Calculado en       |
   * |  (15 - 0)            |el periodo de la base de  |"Calculos Previos"  |
   * |                      |tiempos.                  |                    |
   * |----------------------|--------------------------|--------------------|
   *
   */
        EPwm1Regs.TBPRD   =   TBPRD;

  //-------------------------------------------------------------------------
  //    Setup TBCTL
  //-------------------------------------------------------------------------
  /* |----------------------|--------------------------|--------------------|
   * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
   * |----------------------|--------------------------|--------------------|
   * |  FREE_SOFT           | Selecciona el compoarta- | 00h - Detener desp-|
   * |  (15 - 16)           |miento del contador ePWM  |es de que el sigue- |
   * |                      |durante los eventos de    |nte contador incre- |
   * |                      |emulacion                 |mente  disminuya    |
   * |                      |                          | 01h - Detener      |
   * |                      |                          |compeltado un ciclo |
   * |                      |                          |completo.           |
   * |                      |                          | 02h - ejecucion    |
   * |                      |                          |libre               |
   * |----------------------|--------------------------|--------------------|
   *
   */
        EPwm1Regs.TBCTL.bit.FREE_SOFT   =   0x02;

   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  PHSDIR              | Este bit solo se usa si  | 00h - Cuenta hacia |
    * |  (13)                |se ha confiugrado en modo |arriba              |
    * |                      |up-down. indica la dire-  |                    |
    * |                      |ccion del cuenteo de la   | 01h - Cuenta hacia |
    * |                      |base de tiempos.          |abajo               |
    * |----------------------|--------------------------|--------------------|
    *
    */
        EPwm1Regs.TBCTL.bit.PHSDIR  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  CLKDIV              | Preescalado de la base   | 00h - /1 (default) |
     * |  (12 - 10)           |de tiempos                | 01h - /2           |
     * |                      |                          | 02h - /4           |
     * |                      |                          | 03h - /8           |
     * |                      |                          | 04h - /16          |
     * |                      |                          | 05h - /32          |
     * |                      |                          | 06h - /64          |
     * |                      |                          | 07h - /128         |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.TBCTL.bit.CLKDIV  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  HSPCLKDIV           | Preescalado de la base   | 00h - /1           |
     * |  (9 - 7)             |de tiempos de alta        | 01h - /2 (default) |
     * |                      |velocidad                 | 02h - /4           |
     * |                      |                          | 03h - /6           |
     * |                      |                          | 04h - /8           |
     * |                      |                          | 05h - /10          |
     * |                      |                          | 06h - /12          |
     * |                      |                          | 07h - /14          |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.TBCTL.bit.HSPCLKDIV  =   0x02;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  SWFSYNC             | Forzar el pulso          | 00h - No tiene     |
     * |  (6)                 |de la sincronizacion      |efecto              |
     * |                      | Solo tiene efecto si     |                    |
     * |                      |SYNCOSEL = 00             | 04h - Forzamos la  |
     * |                      |                          |sincronizacion      |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.TBCTL.bit.SWFSYNC  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  SYNCOSEL            | Seleccion de la salida   | 00h - EPWMxSYNCI / |
     * |  (5 - 4)             |de la sincronizacion      | SWFSYNC            |
     * |                      |                          | 01h - CTR llega a 0|
     * |                      |                          |en base de tiempos  |
     * |                      |                          | 02h - CTR llega a  |
     * |                      |                          |CMPB base de tiempos|
     * |                      |                          | 03h - EPWMXSYNCO es|
     * |                      |                          |definido por TBCTL2 |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.TBCTL.bit.SYNCOSEL  =   0x01;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  PRDLD               | Carga de registro de     | 00h - Se carga     |
     * |  (3)                 |periodo activo de "Shadow |desde su registro de|
     * |                      |Select"                   |sombra cuando el    |
     * |                      |                          |contador es 0 o una |
     * |                      |                          |sincronizacion      |
     * |                      |                          | 01h - Modo         |
     * |                      |                          |inmediato, accede el|
     * |                      |                          |registro TBPRD      |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.TBCTL.bit.PRDLD   =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  PHSEN               | Registro del contador    | 00h - No cargar el |
     * |  (2)                 |de carga desde "Phase Reg"|contador de la base |
     * |                      |                          |de tiempos "TBCTR"  |
     * |                      |                          |de la base de tiempo|
     * |                      |                          |(TBPHS)             |
     * |                      |                          | 01h -  Permitir la |
     * |                      |                          |el contador se carge|
     * |                      |                          |desde el registro de|
     * |                      |                          |fase (TBPHS)        |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.TBCTL.bit.PHSEN  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  CTRMODE             | Seleccion del modo de    | 00h - Up mode      |
     * |  (1 - 0)             |conteo                    | 01h - Down mode    |
     * |                      |                          | 02h - UpDown mode  |
     * |                      |                          | 03h - Libre modo   |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.TBCTL.bit.CTRMODE  =   0x00;

    //-------------------------------------------------------------------------
    //      Setup TBCTL2
    //-------------------------------------------------------------------------
    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  PRDLDSYNC           | Sombra al periodo activo | 00h - TBCTR = 0    |
     * |  (15 - 14)           |cuando el registro de     | 01h - TBCTR = 0 y  |
     * |                      |carga en el evento SYNC.  |se a recibido un    |
     * |                      | Es valida cuando         |SYNC                |
     * |                      |PRDLD = 0.                | 02h - Se a recibido|
     * |                      |  Shadow to Active Load de|un SYNC             |
     * |                      |TBPRD ocurre cuando:      | 03h - Reservado    |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.TBCTL2.bit.PRDLDSYNC   =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  SYNCOSELX           | Ampliacion de los bits de| 00h - Desactivado  |
     * |  (13 - 12)           |SYNCOUT                   | 01h -              |
     * |                      |                          |EPWMxSYNCO = CMPC   |
     * |                      |                          | 02h -              |
     * |                      |                          |EPWMxSYNCO = CMPD   |
     * |                      |                          | 03h - Reservado    |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.TBCTL2.bit.PRDLDSYNC   =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  OSHTSYNC            | Bit de sincronizacion de | 00h - Sin efecto   |
     * |  (7)                 |Oneshot                   | 01h - Permite un   |
     * |                      |                          |pulso de sincroni-  |
     * |                      |                          |zacion se propague  |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.TBCTL2.bit.OSHTSYNC   =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  OSHTSYNCMODE        | Bit de activacion de     | 00h - Deshabilitado|
     * |  (6)                 |Oneshot                   | 01h - Habilitado   |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.TBCTL2.bit.OSHTSYNCMODE   =   0x00;

    //-------------------------------------------------------------------------
    //      Setup TBCTR
    //-------------------------------------------------------------------------
    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  TBCTR               | Registo de conteo de la  | Valor de conteo    |
     * |  (15 - 0)            |base de tiempos           |actual              |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.TBCTR   =   0x00;

    //-------------------------------------------------------------------------
    //      Setup TBPHS
    //-------------------------------------------------------------------------
    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  TBPHR               | Registo del desfase de   | Angulo de retardo  |
     * |  (31 - 16)           |fase                      |de la señal PWM     |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.TBPHS.bit.TBPHSHR  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  TBPHSHR             | Registo del desfase de   | Angulo de retardo  |
     * |  (15 - 0)            |fase. Alta resolucion     |de la señal PWM     |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.TBPRDHR  =   0x00;

    //-------------------------------------------------------------------------
    //      Setup CMPCTL
    //-------------------------------------------------------------------------
    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  LOADBSYNC           | Activamos la sombra      | 00h - La sombra    |
     * |  (13 - 12)           |cuando el registro CMPB   |activa CMPB cuando  |
     * |                      |genenra un SYNC           |se cumple LOADMODE  |
     * |                      |                          | 01h - La sombra    |
     * |                      |                          |activa CMPB cuando  |
     * |                      |                          |se cumple LOADMODE y|
     * |                      |                          |se produce un SYNC  |
     * |                      |                          | 02h - La sombra    |
     * |                      |                          |activa CMPB cuando  |
     * |                      |                          |se produce un SYNC  |
     * |                      |                          | 03h - Reservado    |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.CMPCTL.bit.LOADBSYNC  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  LOADASYNC           | Activamos la sombra      | 00h - La sombra    |
     * |  (11 - 10)           |cuando el registro CMPA   |activa CMPA cuando  |
     * |                      |genenra un SYNC           |se cumple LOADMODE  |
     * |                      |                          | 01h - La sombra    |
     * |                      |                          |activa CMPA cuando  |
     * |                      |                          |se cumple LOADMODE y|
     * |                      |                          |se produce un SYNC  |
     * |                      |                          | 02h - La sombra    |
     * |                      |                          |activa CMPA cuando  |
     * |                      |                          |se produce un SYNC  |
     * |                      |                          | 03h - Reservado    |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.CMPCTL.bit.LOADASYNC  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  SHDWBMODE           | Registro CMPB modo de    | 00h - Sombra       |
     * |  (6)                 |                          |Funciona como un    |
     * |                      |operacion.                |doble buffer.       |
     * |                      |                          |Escribe mediante CPU|
     * |                      |                          | 01h - Inmediato    |
     * |                      |                          |solo se usa el      |
     * |                      |                          |resgistro CMPB      |
     * |                      |                          |activo              |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.CMPCTL.bit.SHDWBMODE  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  SHDWAMODE           | Registro CMPA modo de    | 00h - Sombra       |
     * |  (4)                 |                          |Funciona como un    |
     * |                      |operacion.                |doble buffer.       |
     * |                      |                          |Escribe mediante CPU|
     * |                      |                          | 01h - Inmediato    |
     * |                      |                          |solo se usa el      |
     * |                      |                          |resgistro CMPA      |
     * |                      |                          |activo              |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.CMPCTL.bit.SHDWAMODE  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  LOADBMODE           | Registro modos de carga  | 00h - Carga cuando |
     * |  (3 - 2)             |la sombra.                |CTR = (TBCTR = 0).  |
     * |                      | Este bit no tiene efecto | 01h - Carga cuando |
     * |                      |en modo inmediato         |CTR = TBPRD.        |
     * |                      |                          | 02h - Carga cuando |
     * |                      |                          |CTR = 0 o CTR = PRD |
     * |                      |                          | 03h - Reservado    |
     * |                      |                          |                    |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.CMPCTL.bit.LOADBMODE  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  LOADAMODE           | Registro modos de carga  | 00h - Carga cuando |
     * |  (1 - 0)             |la sombra.                |CTR = (TBCTR = 0).  |
     * |                      | Este bit no tiene efecto | 01h - Carga cuando |
     * |                      |en modo inmediato         |CTR = TBPRD.        |
     * |                      |                          | 02h - Carga cuando |
     * |                      |                          |CTR = 0 o CTR = PRD |
     * |                      |                          | 03h - Reservado    |
     * |                      |                          |                    |
     * |----------------------|--------------------------|--------------------|
     *
     */
         EPwm1Regs.CMPCTL.bit.LOADAMODE  =   0x00;

    //-------------------------------------------------------------------------
    //      Setup CMPCTL2
    //-------------------------------------------------------------------------
    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  LOADCSYNC           | Activamos la sombra      | 00h - La sombra    |
     * |  (13 - 12)           |cuando el registro CMPD   |activa CMPD cuando  |
     * |                      |genenra un SYNC           |se cumple LOADMODE  |
     * |                      |                          | 01h - La sombra    |
     * |                      |                          |activa CMPD cuando  |
     * |                      |                          |se cumple LOADMODE y|
     * |                      |                          |se produce un SYNC  |
     * |                      |                          | 02h - La sombra    |
     * |                      |                          |activa CMPD cuando  |
     * |                      |                          |se produce un SYNC  |
     * |                      |                          | 03h - Reservado    |
     * |----------------------|--------------------------|--------------------|
     *
     */
         EPwm1Regs.CMPCTL2.bit.LOADDSYNC  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  LOADCSYNC           | Activamos la sombra      | 00h - La sombra    |
     * |  (11 - 10)           |cuando el registro CMPC   |activa CMPC cuando  |
     * |                      |genenra un SYNC           |se cumple LOADMODE  |
     * |                      |                          | 01h - La sombra    |
     * |                      |                          |activa CMPC cuando  |
     * |                      |                          |se cumple LOADMODE y|
     * |                      |                          |se produce un SYNC  |
     * |                      |                          | 02h - La sombra    |
     * |                      |                          |activa CMPC cuando  |
     * |                      |                          |se produce un SYNC  |
     * |                      |                          | 03h - Reservado    |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.CMPCTL2.bit.LOADCSYNC  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  SHDWDMODE           | Registro CMPD modo de    | 00h - Sombra       |
     * |  (6)                 |                          |Funciona como un    |
     * |                      |operacion.                |doble buffer.       |
     * |                      |                          |Escribe mediante CPU|
     * |                      |                          | 01h - Inmediato    |
     * |                      |                          |solo se usa el      |
     * |                      |                          |resgistro CMPD      |
     * |                      |                          |activo              |
     * |----------------------|--------------------------|--------------------|
     *
     */
       EPwm1Regs.CMPCTL2.bit.SHDWDMODE  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  SHDWCMODE           | Registro CMPC modo de    | 00h - Sombra       |
     * |  (4)                 |                          |Funciona como un    |
     * |                      |operacion.                |doble buffer.       |
     * |                      |                          |Escribe mediante CPU|
     * |                      |                          | 01h - Inmediato    |
     * |                      |                          |solo se usa el      |
     * |                      |                          |resgistro CMPC      |
     * |                      |                          |activo              |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.CMPCTL2.bit.SHDWCMODE  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  LOADDMODE           | Registro modos de carga  | 00h - Carga cuando |
     * |  (3 - 2)             |la sombra.                |CTR = (TBCTR = 0).  |
     * |                      | Este bit no tiene efecto | 01h - Carga cuando |
     * |                      |en modo inmediato         |CTR = TBPRD.        |
     * |                      |                          | 02h - Carga cuando |
     * |                      |                          |CTR = 0 o CTR = PRD |
     * |                      |                          | 03h - Reservado    |
     * |----------------------|--------------------------|--------------------|
     *
     */
         EPwm1Regs.CMPCTL2.bit.LOADDMODE  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  LOADCMODE           | Registro modos de carga  | 00h - Carga cuando |
     * |  (1 - 0)             |la sombra.                |CTR = (TBCTR = 0).  |
     * |                      | Este bit no tiene efecto | 01h - Carga cuando |
     * |                      |en modo inmediato         |CTR = TBPRD.        |
     * |                      |                          | 02h - Carga cuando |
     * |                      |                          |CTR = 0 o CTR = PRD |
     * |                      |                          | 03h - Reservado    |
     * |                      |                          |                    |
     * |----------------------|--------------------------|--------------------|
     *
     */
         EPwm1Regs.CMPCTL2.bit.LOADCMODE  =   0x00;

    //-------------------------------------------------------------------------
    //      Setup CMPA
    //-------------------------------------------------------------------------
    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  CMPA                | Registo de comparacion   | Calculado en       |
     * |  (31 - 16)           |A.                        |"Calculos Previos"  |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.CMPA.bit.CMPA  =   CMPA;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  CMPAHR              | Registo de comparacion   | Calculado en       |
     * |  (15 - 0)            |A. Alta resolucion        |"Calculos Previos"  |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.CMPA.bit.CMPAHR  =   0x00;

    //-------------------------------------------------------------------------
    //      Setup CMPB
    //-------------------------------------------------------------------------
    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  CMPB                | Registo de comparacion   | Calculado en       |
     * |  (31 - 16)           |B.                        |"Calculos Previos"  |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.CMPB.bit.CMPB  =   CMPB;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  CMPBHR              | Registo de comparacion   | Calculado en       |
     * |  (15 - 0)            |B. Alta resolucion        |"Calculos Previos"  |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.CMPB.bit.CMPBHR  =   0x00;

    //-------------------------------------------------------------------------
    //      Setup CMPC
    //-------------------------------------------------------------------------
    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  CMPC                | Registo de comparacion   | Calculado en       |
     * |  (15 - 0)            |C.                        |"Calculos Previos"  |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.CMPC = CMPC;

    //-------------------------------------------------------------------------
    //      Setup CMPD
    //-------------------------------------------------------------------------
    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  CMPD                | Registo de comparacion   | Calculado en       |
     * |  (15 - 0)            |D.                        |"Calculos Previos"  |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.CMPD =   CMPD;

    //-------------------------------------------------------------------------
    //      Setup AQCTL
    //-------------------------------------------------------------------------
    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  LDAQBSYNC           | Registro AQCTLB para     | 00h - Produce el   |
     * |  (11 - 10)           |activar el modo sombra en |evento SYNC acuerdo |
     * |                      |el evento SYNC.           |resgistro LDAQBMODE.|
     * |                      | Solo funciona si         | 01h - Produce el   |
     * |                      |AQCTLR = 1.               |evento SYNC acuerdo |
     * |                      |                          |resgistro LDAQBMODE |
     * |                      |                          |y si a producido un |
     * |                      |                          |SYNC.               |
     * |                      |                          | 02h - Produce el   |
     * |                      |                          |evento SYNC si se a |
     * |                      |                          |producido un SYNC.  |
     * |                      |                          | 03h - Reservado.   |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.AQCTL.bit.LDAQBSYNC  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  LDAQASYNC           | Registro AQCTLB para     | 00h - Produce el   |
     * |  (9 - 8)             |activar el modo sombra en |evento SYNC acuerdo |
     * |                      |el evento SYNC.           |resgistro LDAQAMODE.|
     * |                      | Solo funciona si         | 01h - Produce el   |
     * |                      |AQCTLR = 1.               |evento SYNC acuerdo |
     * |                      |                          |resgistro LDAQBMODE |
     * |                      |                          |y si a producido un |
     * |                      |                          |SYNC.               |
     * |                      |                          | 02h - Produce el   |
     * |                      |                          |evento SYNC si se a |
     * |                      |                          |producido un SYNC.  |
     * |                      |                          | 03h - Reservado.   |
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.AQCTL.bit.LDAQASYNC  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  SHDWAQBMODE         | Registro modo de         | 00h - Inmediato    |
     * |  (6)                 |operacion en la accion    |solo se usa el      |
     * |                      |calificado B.             |resgistro calificado|
     * |                      |                          |de accion activa.   |
     * |                      |                          | 01h - Sombra       |
     * |                      |                          |Funciona como un    |
     * |                      |                          |doble buffer.       |
     * |                      |                          |Escribe mediante CPU|
     * |----------------------|--------------------------|--------------------|
     *
     */
        EPwm1Regs.AQCTL.bit.SHDWAQBMODE  =   0x00;

   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  SHDWAQAMODE         | Registro modo de         | 00h - Inmediato    |
    * |  (4)                 |operacion en la accion    |solo se usa el      |
    * |                      |calificado A.             |resgistro calificado|
    * |                      |                          |de accion activa.   |
    * |                      |                          | 01h - Sombra       |
    * |                      |                          |Funciona como un    |
    * |                      |                          |doble buffer.       |
    * |                      |                          |Escribe mediante CPU|
    * |----------------------|--------------------------|--------------------|
    *
    */
        EPwm1Regs.AQCTL.bit.SHDWAQAMODE  =   0x00;

   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  LDAQBMODE           | Modo de activacion de la | 00h - Cargar cuando|
    * |  (3 - 2)             |carga de sombra del       |el conteo = 0.      |
    * |                      |registro calificado B.    | 01h - Cargar cuando|
    * |                      |                          |el conteo = TBPRD   |
    * |                      |                          | 02h - Cargar cuando|
    * |                      |                          |el conteo es = TBPRD|
    * |                      |                          |0 el conteo = 0.    |
    * |                      |                          | 03h - libre.       |
    * |----------------------|--------------------------|--------------------|
    *
    */
        EPwm1Regs.AQCTL.bit.LDAQBMODE = 0x00;

   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  LDAQAMODE           | Modo de activacion de la | 00h - Cargar cuando|
    * |  (1 - 0)             |carga de sombra del       |el conteo = 0.      |
    * |                      |registro calificado A.    | 01h - Cargar cuando|
    * |                      |                          |el conteo = TBPRD   |
    * |                      |                          | 02h - Cargar cuando|
    * |                      |                          |el conteo es = TBPRD|
    * |                      |                          |0 el conteo = 0.    |
    * |                      |                          | 03h - libre.       |
    * |----------------------|--------------------------|--------------------|
    *
    */
        EPwm1Regs.AQCTL.bit.LDAQAMODE = 0x00;

   //-------------------------------------------------------------------------
   //      Setup AQTSRCSEL
   //-------------------------------------------------------------------------
   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  T2SEL               | Registro de seleccion de | 00h - DCAEVT1.     |
    * |  (7 - 4)             |la fuente de los eventos  | 01h - DCAEVT2.     |
    * |                      |T2.                       | 02h - DCBEVT1.     |
    * |                      |                          | 03h - DCBEVT2.     |
    * |                      |                          | 04h - TZ1.         |
    * |                      |                          | 05h - TZ2.         |
    * |                      |                          | 06h - TZ3.         |
    * |                      |                          | 07h - EPWMxSYNCI.  |
    * |                      |                          | 08h - Reservado    |
    * |----------------------|--------------------------|--------------------|
    *
    */
        EPwm1Regs.AQTSRCSEL.bit.T2SEL  =   0x00;

   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  T1SEL               | Registro de seleccion de | 00h - DCAEVT1.     |
    * |  (3 - 0)             |la fuente de los eventos  | 01h - DCAEVT2.     |
    * |                      |T1.                       | 02h - DCBEVT1.     |
    * |                      |                          | 03h - DCBEVT2.     |
    * |                      |                          | 04h - TZ1.         |
    * |                      |                          | 05h - TZ2.         |
    * |                      |                          | 06h - TZ3.         |
    * |                      |                          | 07h - EPWMxSYNCI.  |
    * |                      |                          | 08h - Reservado    |
    * |----------------------|--------------------------|--------------------|
    *
    */
        EPwm1Regs.AQTSRCSEL.bit.T1SEL  =   0x00;

   //-------------------------------------------------------------------------
   //      Setup AQCTLA
   //-------------------------------------------------------------------------
   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  CBD                 | Registro de accionion    | 00h - Sin accion.  |
    * |  (11 - 10)           |cuando TBCTR = CMPB cuando| 01h - Clear.       |
    * |                      |la cuenta es hacia abajo. | 02h - Set.         |
    * |                      |                          | 03h - Toggle.      |
    * |----------------------|--------------------------|--------------------|
    *
    */
       EPwm1Regs.AQCTLA.bit.CBD  =   0x00;

   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  CBU                 | Registro de accionion    | 00h - Sin accion.  |
    * |  (9 - 8)             |cuando TBCTR = CMPB cuando| 01h - Clear.       |
    * |                      |la cuenta es hacia arriba.| 02h - Set.         |
    * |                      |                          | 03h - Toggle.      |
    * |----------------------|--------------------------|--------------------|
    *
    */
       EPwm1Regs.AQCTLA.bit.CBU  =   0x00;

   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  CAD                 | Registro de accionion    | 00h - Sin accion.  |
    * |  (7 - 6)             |cuando TBCTR = CMPA cuando| 01h - Clear.       |
    * |                      |la cuenta es hacia abajo. | 02h - Set.         |
    * |                      |                          | 03h - Toggle.      |
    * |----------------------|--------------------------|--------------------|
    *
    */
       EPwm1Regs.AQCTLA.bit.CAD  =   0x00;

   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  CAU                 | Registro de accionion    | 00h - Sin accion.  |
    * |  (5 - 4)             |cuando TBCTR = CMPA cuando| 01h - Clear.       |
    * |                      |la cuenta es hacia arriba.| 02h - Set.         |
    * |                      |                          | 03h - Toggle.      |
    * |----------------------|--------------------------|--------------------|
    *
    */
       EPwm1Regs.AQCTLA.bit.CAU  =   0x00;

   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  PRD                 | Registro de accionion    | 00h - Sin accion.  |
    * |  (3 - 2)             |cuando TBCTR = TBRP.      | 01h - Clear.       |
    * |                      |                          | 02h - Set.         |
    * |                      |                          | 03h - Toggle.      |
    * |----------------------|--------------------------|--------------------|
    *
    */
       EPwm1Regs.AQCTLA.bit.PRD  =   0x00;

   //-------------------------------------------------------------------------
   //      Setup AQCTLB
   //-------------------------------------------------------------------------
   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  CBD                 | Registro de accionion    | 00h - Sin accion.  |
    * |  (11 - 10)           |cuando TBCTR = CMPB cuando| 01h - Clear.       |
    * |                      |la cuenta es hacia abajo. | 02h - Set.         |
    * |                      |                          | 03h - Toggle.      |
    * |----------------------|--------------------------|--------------------|
    *
    */
       EPwm1Regs.AQCTLB.bit.CBD  =   0x00;

   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  CBU                 | Registro de accionion    | 00h - Sin accion.  |
    * |  (9 - 8)             |cuando TBCTR = CMPB cuando| 01h - Clear.       |
    * |                      |la cuenta es hacia arriba.| 02h - Set.         |
    * |                      |                          | 03h - Toggle.      |
    * |----------------------|--------------------------|--------------------|
    *
    */
       EPwm1Regs.AQCTLB.bit.CBU  =   0x00;

   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  CAD                 | Registro de accionion    | 00h - Sin accion.  |
    * |  (7 - 6)             |cuando TBCTR = CMPA cuando| 01h - Clear.       |
    * |                      |la cuenta es hacia abajo. | 02h - Set.         |
    * |                      |                          | 03h - Toggle.      |
    * |----------------------|--------------------------|--------------------|
    *
    */
       EPwm1Regs.AQCTLB.bit.CAD  =   0x00;

   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  CAU                 | Registro de accionion    | 00h - Sin accion.  |
    * |  (5 - 4)             |cuando TBCTR = CMPA cuando| 01h - Clear.       |
    * |                      |la cuenta es hacia arriba.| 02h - Set.         |
    * |                      |                          | 03h - Toggle.      |
    * |----------------------|--------------------------|--------------------|
    *
    */
       EPwm1Regs.AQCTLB.bit.CAU  =   0x00;

   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  PRD                 | Registro de accionion    | 00h - Sin accion.  |
    * |  (3 - 2)             |cuando TBCTR = TBRP.      | 01h - Clear.       |
    * |                      |                          | 02h - Set.         |
    * |                      |                          | 03h - Toggle.      |
    * |----------------------|--------------------------|--------------------|
    *
    */
       EPwm1Regs.AQCTLB.bit.PRD  =   0x00;

   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  ZRO                 | Registro de accionion    | 00h - Sin accion.  |
    * |  (1 - 0)             |cuando TBCTR = 0.         | 01h - Clear.       |
    * |                      |                          | 02h - Set.         |
    * |                      |                          | 03h - Toggle.      |
    * |----------------------|--------------------------|--------------------|
    *
    */
       EPwm1Regs.AQCTLB.bit.ZRO  =   0x00;

   //-------------------------------------------------------------------------
   //      Setup DBCTL
   // Vease la figura 13-33 de spruhx5e.pdf para enterder la columna de
   //valores
   //-------------------------------------------------------------------------
   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  HALFCYCLE           | Activamos el medio ciclo | 00h - Ciclo comple-|
    * |  (15)                |de reloj.                 |to activado. El     |
    * |                      |                          |tiempo muerto es el |
    * |                      |                          |conteo de TBCLK.    |
    * |                      |                          | 01h - Medio ciclo  |
    * |                      |                          |activado. El tiempo |
    * |                      |                          |mierto es el conteo |
    * |                      |                          |de TBCLK*2.         |
    * |----------------------|--------------------------|--------------------|
    *
    */
       EPwm1Regs.DBCTL.bit.HALFCYCLE  =   0x00;

   /* |----------------------|--------------------------|--------------------|
    * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
    * |----------------------|--------------------------|--------------------|
    * |  DEDB_MODE           | Tiempo muerto Dual-Edge B| 00h -  Retraso en  |
    * |  (14)                |control de modo.          |el flanco ascendente|
    * |                      |(interruptor S8)          |segun INMODE en la  |
    * |                      |                          |señal A. Retraso de |
    * |                      |                          |caida de borde segun|
    * |                      |                          |INMODE en la señal B|
    * |                      |                          | 00h -  Retraso en  |
    * |                      |                          |el flanco ascendente|
    * |                      |                          |y descendente       |
    * |                      |                          |segun INMODE en la  |
    * |                      |                          |señal B.            |
    * |----------------------|--------------------------|--------------------|
    *
    */
       EPwm1Regs.DBCTL.bit.DEDB_MODE  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  SHDWDBFEDMODE       | FED Tiempo muerto modo   | 00h - Inmediato    |
     * |  (11)                |de carga.                 |solo se usa el      |
     * |                      |                          |resgistro DBFED.    |
     * |                      |                          |activo              |
     * |                      |                          | 01h - Sombra       |
     * |                      |                          |Funciona como un    |
     * |                      |                          |doble buffer.       |
     * |                      |                          |Escribe mediante CPU|
     * |----------------------|--------------------------|--------------------|
     *
     */
       EPwm1Regs.DBCTL.bit.SHDWDBFEDMODE  =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  SHDWDBREDMODE       | RED Tiempo muerto modo   | 00h - Inmediato    |
      * |  (10)                |de carga.                 |solo se usa el      |
      * |                      |                          |resgistro DBRED.    |
      * |                      |                          |activo              |
      * |                      |                          | 01h - Sombra       |
      * |                      |                          |Funciona como un    |
      * |                      |                          |doble buffer.       |
      * |                      |                          |Escribe mediante CPU|
      * |----------------------|--------------------------|--------------------|
      *
      */
        EPwm1Regs.DBCTL.bit.SHDWDBREDMODE  =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  LOADFEDMODE         | Modo de activacion de la | 00h - Cargar cuando|
      * |  (9 - 8)             |carga de sombra del       |el conteo = 0.      |
      * |                      |registro DBFED            | 01h - Cargar cuando|
      * |                      |                          |el conteo = TBPRD   |
      * |                      |                          | 02h - Cargar cuando|
      * |                      |                          |el conteo es = TBPRD|
      * |                      |                          |0 el conteo = 0.    |
      * |                      |                          | 03h - libre.       |
      * |----------------------|--------------------------|--------------------|
      *
      */
        EPwm1Regs.DBCTL.bit.LOADFEDMODE =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  LOADREDMODE         | Modo de activacion de la | 00h - Cargar cuando|
      * |  (7 - 6)             |carga de sombra del       |el conteo = 0.      |
      * |                      |registro DBRED            | 01h - Cargar cuando|
      * |                      |                          |el conteo = TBPRD   |
      * |                      |                          | 02h - Cargar cuando|
      * |                      |                          |el conteo es = TBPRD|
      * |                      |                          |0 el conteo = 0.    |
      * |                      |                          | 03h - libre.       |
      * |----------------------|--------------------------|--------------------|
      *
      */
        EPwm1Regs.DBCTL.bit.LOADREDMODE =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  IN_MODE             | Modo de control de la    | 00h - EPWMxA       |
      * |  (5 - 4)             |entrada para el Tiempo    |flanco de subida y  |
      * |                      |muerto.                   |flanco de bajada.   |
      * |                      |                          | 01h - EPWMxA       |
      * |                      |                          |flanco de bajada,   |
      * |                      |                          |EPWMxB flanco de    |
      * |                      |                          |subida.             |
      * |                      |                          | 02h - EPWMxA       |
      * |                      |                          |flanco de subida,   |
      * |                      |                          |EPWMxB flanco de    |
      * |                      |                          |bajada.             |
      * |                      |                          | 03h - EPWMxB       |
      * |                      |                          |flanco de subida y  |
      * |                      |                          |flanco de bajda     |
      * |----------------------|--------------------------|--------------------|
      *
      */
        EPwm1Regs.DBCTL.bit.IN_MODE =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  POLSEL              | Modo de control de la    | 00h - Modo Activo  |
      * |  (3 - 2)             |polaridad de la señal.    |Alto. EPWMxA ni     |
      * |                      |                          |EPWMxB es invertida |
      * |                      |                          | 01h - Modo Activo  |
      * |                      |                          |Bajo complementario.|
      * |                      |                          |EPWMxA es invertido.|
      * |                      |                          | 02h - Modo Activo  |
      * |                      |                          |Alto complementario.|
      * |                      |                          |EPWMxB es invertido.|
      * |                      |                          | 03h - Modo activo  |
      * |                      |                          |Bajo. EPWMxA y      |
      * |                      |                          |EPWMxB es invertido.|
      * |----------------------|--------------------------|--------------------|
      *
      */
        EPwm1Regs.DBCTL.bit.POLSEL =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  OUT_MODE            | Modo de control de la    | 00h - Desactivado  |
      * |  (1 - 0)             |salida del Tiempo Muerto. |el Tiempo Muerto.   |
      * |                      |                          | 01h - Camino A es  |
      * |                      |                          |retardo A y camino B|
      * |                      |                          |es FED.             |
      * |                      |                          | 02h - Camino A es  |
      * |                      |                          |RED y camino B es   |
      * |                      |                          |retardo B.          |
      * |                      |                          | 03h - Activado el  |
      * |                      |                          |Tiempo Muerto.      |
      * |----------------------|--------------------------|--------------------|
      *
      */
        EPwm1Regs.DBCTL.bit.OUT_MODE =   0x00;

     //-------------------------------------------------------------------------
     //      Setup DBCTL2
     //-------------------------------------------------------------------------
     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  SHDWDBCTLMODE       | DBCTL Tiempo muerto modo | 00h - Inmediato    |
      * |  (2)                 |de carga.                 |solo se usa el      |
      * |                      |                          |resgistro DBFED.    |
      * |                      |                          |activo              |
      * |                      |                          | 01h - Sombra       |
      * |                      |                          |Funciona como un    |
      * |                      |                          |doble buffer.       |
      * |                      |                          |Escribe mediante CPU|
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.DBCTL2.bit.SHDWDBCTLMODE  =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  LOADDBCTLMODE       | Modo de activacion de la | 00h - Cargar cuando|
      * |  (1 - 0)             |carga de sombra del       |el conteo = 0.      |
      * |                      |registro DBCTL            | 01h - Cargar cuando|
      * |                      |                          |el conteo = TBPRD   |
      * |                      |                          | 02h - Cargar cuando|
      * |                      |                          |el conteo es = TBPRD|
      * |                      |                          |0 el conteo = 0.    |
      * |                      |                          | 03h - libre.       |
      * |----------------------|--------------------------|--------------------|
      *
      */
        EPwm1Regs.DBCTL2.bit.LOADDBCTLMODE =   0x00;

     //-------------------------------------------------------------------------
     //      Setup DBRED
     //-------------------------------------------------------------------------
     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  DBRED               | Rising edge delay value. | Calculado en       |
      * |  (13 - 0)            |Retraso en ciclo a flanco |"Calculos previos"  |
      * |                      |nivel alto.               |                    |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.DBRED.bit.DBRED  =   DeadBand;

     //-------------------------------------------------------------------------
     //      Setup DBFED
     //-------------------------------------------------------------------------
     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  DBFED               | Rising edge delay value. | Calculado en       |
      * |  (13 - 0)            |Retraso en ciclo a flanco |"Calculos previos"  |
      * |                      |nivel bajo.               |                    |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.DBFED.bit.DBFED  =   DeadBand;

     //-------------------------------------------------------------------------
     //      Setup DBFED
     //-------------------------------------------------------------------------
     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  DBFED               | Rising edge delay value. | Calculado en       |
      * |  (13 - 0)            |Retraso en ciclo a flanco |"Calculos previos"  |
      * |                      |nivel bajo.               |                    |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.DBFED.bit.DBFED  =   DeadBand;

     //-------------------------------------------------------------------------
     //      Setup ETSEL
     //-------------------------------------------------------------------------
     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  SOCBEN              | Activar la conversion del| 00h - Deshabilitado|
      * |  (15)                |ADC al pulso del SOC B.   | 01h - Hablilitado. |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETSEL.bit.SOCBEN  =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  SOCBSEL             | Opciones de EPWMxSOCB.   | 00h - SOC evento   |
      * |  (14 - 12)           |Acciones cuando genera un |DCBEVT1.            |
      * |                      |genera un puslo.          | 01h - SOC evento   |
      * |                      |                          |TBCTR = 0x00.       |
      * |                      |                          | 02h - SOC evento   |
      * |                      |                          |TBCTR = TBPRD.      |
      * |                      |                          | 03h - SOC evento   |
      * |                      |                          |TBCTR = TBPRD o     |
      * |                      |                          |TBCTR = 0x00.       |
      * |                      |                          | 04h - SOC evento   |
      * |                      |                          |TBCTR = CMPA cuando |
      * |                      |                          |contea incrementa o |
      * |                      |                          |CMPC el tiempo esta |
      * |                      |                          |incrementando.      |
      * |                      |                          | 05h - SOC evento   |
      * |                      |                          |TBCTR = CMPA cuando |
      * |                      |                          |contea decrementa o |
      * |                      |                          |CMPC el tiempo esta |
      * |                      |                          |decrementando.      |
      * |                      |                          | 06h - SOC evento   |
      * |                      |                          |TBCTR = CMPB cuando |
      * |                      |                          |contea incrementa o |
      * |                      |                          |CMPD el tiempo esta |
      * |                      |                          |incrementando.      |
      * |                      |                          | 07h - SOC evento   |
      * |                      |                          |TBCTR = CMPB cuando |
      * |                      |                          |contea decrementa o |
      * |                      |                          |CMPD el tiempo esta |
      * |                      |                          |decrementando.      |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETSEL.bit.SOCBSEL  =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  SOCAEN              | Activar la conversion del| 00h - Deshabilitado|
      * |  (11)                |ADC al pulso del SOC A.   | 01h - Hablilitado. |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETSEL.bit.SOCAEN  =   0x01;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  SOCASEL             | Opciones de EPWMxSOCA.   | 00h - SOC evento   |
      * |  (10 - 8)            |Acciones cuando genera un |DCBEVT1.            |
      * |                      |genera un puslo.          | 01h - SOC evento   |
      * |                      |                          |TBCTR = 0x00.       |
      * |                      |                          | 02h - SOC evento   |
      * |                      |                          |TBCTR = TBPRD.      |
      * |                      |                          | 03h - SOC evento   |
      * |                      |                          |TBCTR = TBPRD o     |
      * |                      |                          |TBCTR = 0x00.       |
      * |                      |                          | 04h - SOC evento   |
      * |                      |                          |TBCTR = CMPA cuando |
      * |                      |                          |contea incrementa o |
      * |                      |                          |CMPC el tiempo esta |
      * |                      |                          |incrementando.      |
      * |                      |                          | 05h - SOC evento   |
      * |                      |                          |TBCTR = CMPA cuando |
      * |                      |                          |contea decrementa o |
      * |                      |                          |CMPC el tiempo esta |
      * |                      |                          |decrementando.      |
      * |                      |                          | 06h - SOC evento   |
      * |                      |                          |TBCTR = CMPB cuando |
      * |                      |                          |contea incrementa o |
      * |                      |                          |CMPD el tiempo esta |
      * |                      |                          |incrementando.      |
      * |                      |                          | 07h - SOC evento   |
      * |                      |                          |TBCTR = CMPB cuando |
      * |                      |                          |contea decrementa o |
      * |                      |                          |CMPD el tiempo esta |
      * |                      |                          |decrementando.      |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETSEL.bit.SOCASEL  =   0x04;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  INTSELCMP           | Seleccion de registro de | 00h - CMPA y CMPB. |
      * |  (6)                 |generacion de la INTSEL   | 01h - CMPC y CMPD. |
      * |                      |segun el evento CMPx.     |                    |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETSEL.bit.INTSELCMP  =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  SOCBSELCMP          | Seleccion de registro de | 00h - CMPA y CMPB. |
      * |  (5)                 |generacion de la INTSEL   | 01h - CMPC y CMPD. |
      * |                      |del SOCB segun el evento  |                    |
      * |                      |CMPx.                     |                    |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETSEL.bit.SOCBSELCMP  =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  SOCASELCMP          | Seleccion de registro de | 00h - CMPA y CMPB. |
      * |  (4)                 |generacion de la INTSEL   | 01h - CMPC y CMPD. |
      * |                      |del SOCA segun el evento  |                    |
      * |                      |CMPx.                     |                    |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETSEL.bit.SOCASELCMP  =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  INTSLEL             | Habilitar las            | 00h - Deshabilitar.|
      * |  (3)                 |interrupciones del ePWM.  | 01h - Habilitar.   |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETSEL.bit.INTEN  =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  INTSEL              | Seleccion de la opcion   | 01h - TBCTR = 0x00.|
      * |  (2 - 0)             |de accion que genera la   | 02h - TBCTR = TBPRD|
      * |                      |interrupciones del ePWM.  | 03h - TBCTR = 0x00 |
      * |                      |                          |o TBCTR = TBPRD.    |
      * |                      |                          | 04h = CMPA empieza |
      * |                      |                          |incrementar o CMPC  |
      * |                      |                          |empieza a incementar|
      * |                      |                          | 05h = CMPA empieza |
      * |                      |                          |decrementar o CMPC  |
      * |                      |                          |empieza a decementar|
      * |                      |                          | 06h = CMPB empieza |
      * |                      |                          |incrementar o CMPD  |
      * |                      |                          |empieza a incementar|
      * |                      |                          | 07h = CMPB empieza |
      * |                      |                          |decrementar o CMPD  |
      * |                      |                          |empieza a decementar|
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETSEL.bit.INTSEL  =   0x01;

     //-------------------------------------------------------------------------
     //      Setup ETPS
     //-------------------------------------------------------------------------
     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  SOCBCNT             | Activar la conversion del| 00h - Deshabilitado|
      * |  (15 - 14)           |ADC al pulso del SOC B.   | 01h - Hablilitado. |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETPS.bit.SOCBCNT  =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  SOCBPRD             | Seleccion el evento donde| 00h - Deshabilitar |
      * |  (13 - 12)           |se producira la           |la interrupcion.    |
      * |                      |interrupcion (INT) del    | 01h - 1er evento.  |
      * |                      |SOCB.                     | 02h - 2do evento.  |
      * |                      |                          | 03h - 3er evento.  |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETPS.bit.SOCBPRD  =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  SOCACNT             | Activar la conversion del| 00h - Deshabilitado|
      * |  (11 - 10)           |ADC al pulso del SOC A.   | 01h - Hablilitado. |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETPS.bit.SOCACNT  =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  SOCAPRD             | Seleccion el evento donde| 00h - Deshabilitar |
      * |  (13 - 12)           |se producira la           |la interrupcion.    |
      * |                      |interrupcion (INT) del    | 01h - 1er evento.  |
      * |                      |SOCA.                     | 02h - 2do evento.  |
      * |                      |                          | 03h - 3er evento.  |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETPS.bit.SOCAPRD  =   0x01;


     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  SOCPSSEL            | Seleccion del bit de     | 00h - Seleccionas  |
      * |  (5)                 |preescalar EPWMxSOC A/B.  |el preescalado del  |
      * |                      |                          |registro ETPS.      |
      * |                      |                          | 01h - Seleccionas  |
      * |                      |                          |el preescalado del  |
      * |                      |                          |registro ETSOCPS.   |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETPS.bit.SOCPSSEL  =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  INTPSSEL            | Seleccion del bit de     | 00h - Seleccionas  |
      * |  (4)                 |preescalar EPWMxINT A/B.  |el preescalado del  |
      * |                      |                          |registro ETPS.      |
      * |                      |                          | 01h - Seleccionas  |
      * |                      |                          |el preescalado del  |
      * |                      |                          |registro ETSOCPS.   |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETPS.bit.INTPSSEL  =   0x00;

     /* |----------------------|--------------------------|--------------------|
      * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
      * |----------------------|--------------------------|--------------------|
      * |  INTPRD              | Seleccion el evento donde| 00h - Deshabilitar |
      * |  (1 - 0)             |se producira la           |la interrupcion.    |
      * |                      |interrupcion (INT).       | 01h - 1er evento.  |
      * |                      |                          | 02h - 2do evento.  |
      * |                      |                          | 03h - 3er evento.  |
      * |----------------------|--------------------------|--------------------|
      *
      */
         EPwm1Regs.ETPS.bit.INTPRD  =   0x01;
}// FIN Config_ePWM1



void Config_ePWM2 ( )
{
    //
    // Calculos Previos
    //
      float       Duty = 0.5;
      uint16_t    TBPRD, DeadBand,CMPA,CMPB,CMPC,CMPD;

      //  TBRPD (Count up) = ( 10 MHz / PWM ) - 1
      TBPRD = (T_clk / 20000) - 1;

      CMPA = (1 - Duty) * (TBPRD);
      CMPB = CMPC = CMPD = 0x00;
      //DeadBand = (Tiempo_Muerto * 1.0e-9) * T_clk
      DeadBand = 0;
     //-------------------------------------------------------------------------
     //    Setup TBPRD
     //-------------------------------------------------------------------------
        EPwm2Regs.TBPRD                   =   TBPRD;   // Periodo de la señal PWM
     //-------------------------------------------------------------------------
     //    Setup TBCTL
     //-------------------------------------------------------------------------
        EPwm2Regs.TBCTL.bit.FREE_SOFT     =   0x02;
        EPwm2Regs.TBCTL.bit.PHSDIR        =   0x00;
        EPwm2Regs.TBCTL.bit.CLKDIV        =   0x00;    // Preescalado Clock /1
        EPwm2Regs.TBCTL.bit.HSPCLKDIV     =   0x00;    // Preescalado Clock /1
        EPwm2Regs.TBCTL.bit.SWFSYNC       =   0x00;
        EPwm2Regs.TBCTL.bit.SYNCOSEL      =   0x01;
        EPwm2Regs.TBCTL.bit.PRDLD         =   0x00;
        EPwm2Regs.TBCTL.bit.PHSEN         =   0x00;    // Deshabilitar el desfase
        EPwm2Regs.TBCTL.bit.CTRMODE       =   0x00;    // Modo up-mode
     //-------------------------------------------------------------------------
     //      Setup TBCTL2
     //-------------------------------------------------------------------------
        EPwm2Regs.TBCTL2.bit.PRDLDSYNC    =   0x00;
        EPwm2Regs.TBCTL2.bit.PRDLDSYNC    =   0x00;
        EPwm2Regs.TBCTL2.bit.OSHTSYNC     =   0x00;
        EPwm2Regs.TBCTL2.bit.OSHTSYNCMODE =   0x00;
        EPwm2Regs.TBCTR                   =   0x00;    // Reset conteo
        EPwm2Regs.TBPHS.bit.TBPHSHR       =   0x00;    // Desfase a 0º
        EPwm2Regs.TBPRDHR                 =   0x00;
     //-------------------------------------------------------------------------
     //      Setup CMPCTL
     //-------------------------------------------------------------------------
        EPwm2Regs.CMPCTL.bit.LOADBSYNC    =   0x00;
        EPwm2Regs.CMPCTL.bit.LOADASYNC    =   0x00;
        EPwm2Regs.CMPCTL.bit.SHDWBMODE    =   0x00;    // Modo Sombra
        EPwm2Regs.CMPCTL.bit.SHDWAMODE    =   0x00;    // Modo Sombra
        EPwm2Regs.CMPCTL.bit.LOADBMODE    =   0x00;    // Activar la sombra cunado CTR = 0
        EPwm2Regs.CMPCTL.bit.LOADAMODE    =   0x00;    // Activar la sombra cunado CTR = 0
        EPwm2Regs.CMPCTL2.bit.LOADDSYNC   =   0x00;
        EPwm2Regs.CMPCTL2.bit.LOADCSYNC   =   0x00;
        EPwm2Regs.CMPCTL2.bit.SHDWDMODE   =   0x00;
        EPwm2Regs.CMPCTL2.bit.SHDWCMODE   =   0x00;
        EPwm2Regs.CMPCTL2.bit.LOADDMODE   =   0x00;
        EPwm2Regs.CMPCTL2.bit.LOADCMODE   =   0x00;
     //-------------------------------------------------------------------------
     //      Setup CMPA
     //-------------------------------------------------------------------------
        EPwm2Regs.CMPA.bit.CMPA           =   CMPA;    // Definimos el Duty
        EPwm2Regs.CMPA.bit.CMPAHR         =   0x00;
     //-------------------------------------------------------------------------
     //      Setup CMPB
     //-------------------------------------------------------------------------
        EPwm2Regs.CMPB.bit.CMPB           =   CMPB;
        EPwm2Regs.CMPB.bit.CMPBHR         =   0x00;
     //-------------------------------------------------------------------------
     //      Setup CMPC
     //-------------------------------------------------------------------------
        EPwm2Regs.CMPC                    =   CMPC;
     //-------------------------------------------------------------------------
     //      Setup CMPD
     //-------------------------------------------------------------------------
        EPwm2Regs.CMPD                    =   CMPD;
     //-------------------------------------------------------------------------
     //      Setup AQCTL
     //-------------------------------------------------------------------------
        EPwm2Regs.AQCTL.bit.LDAQBSYNC     =   0x00;
        EPwm2Regs.AQCTL.bit.LDAQASYNC     =   0x00;
        EPwm2Regs.AQCTL.bit.SHDWAQBMODE   =   0x00;
        EPwm2Regs.AQCTL.bit.SHDWAQAMODE   =   0x00;
        EPwm2Regs.AQCTL.bit.LDAQBMODE     =   0x00;
        EPwm2Regs.AQCTL.bit.LDAQAMODE     =   0x00;
     //-------------------------------------------------------------------------
     //      Setup AQTSRCSEL
     //-------------------------------------------------------------------------
        EPwm2Regs.AQTSRCSEL.bit.T2SEL     =   0x00;
        EPwm2Regs.AQTSRCSEL.bit.T1SEL     =   0x00;
     //-------------------------------------------------------------------------
     //      Setup AQCTLA
     //-------------------------------------------------------------------------
        EPwm2Regs.AQCTLA.bit.CBD          =   0x00;
        EPwm2Regs.AQCTLA.bit.CBU          =   AQ_CLEAR;// Clear cuando TBCTR = CMPB
        EPwm2Regs.AQCTLA.bit.CAD          =   0x00;
        EPwm2Regs.AQCTLA.bit.CAU          =   AQ_SET;  // Set cuando TBCTR = CMPA
        EPwm2Regs.AQCTLA.bit.PRD          =   0x00;
     //-------------------------------------------------------------------------
     //      Setup AQCTLB
     //-------------------------------------------------------------------------
        EPwm2Regs.AQCTLB.bit.CBD         =   0x00;
        EPwm2Regs.AQCTLB.bit.CBU         =   AQ_SET;   // Set cuando TBCTR = CMPB
        EPwm2Regs.AQCTLB.bit.CAD         =   0x00;
        EPwm2Regs.AQCTLB.bit.CAU         =   AQ_CLEAR; // Clear cuando TBCTR = CMPA
        EPwm2Regs.AQCTLB.bit.PRD         =   0x00;
        EPwm2Regs.AQCTLB.bit.ZRO         =   0x00;
     //-------------------------------------------------------------------------
     //      Setup DBCTL
     // Vease la figura 13-33 de spruhx5e.pdf para enterder la columna de
     //valores
     //-------------------------------------------------------------------------
        EPwm2Regs.DBCTL.bit.HALFCYCLE    =   0x00;
        EPwm2Regs.DBCTL.bit.DEDB_MODE    =   0x00;
        EPwm2Regs.DBCTL.bit.SHDWDBFEDMODE=   0x00;
        EPwm2Regs.DBCTL.bit.LOADFEDMODE  =   0x00;
        EPwm2Regs.DBCTL.bit.LOADREDMODE  =   0x00;
        EPwm2Regs.DBCTL.bit.IN_MODE      =   0x00;     // PWMxA is source for RED and FED
        EPwm2Regs.DBCTL.bit.POLSEL       =   0x02;     // Activo high complemeentario (FED)
        EPwm2Regs.DBCTL.bit.OUT_MODE     =   0x03;     // RED & FED (DBM fully enabled)
     //-------------------------------------------------------------------------
     //      Setup DBRED
     //-------------------------------------------------------------------------
        EPwm2Regs.DBRED.bit.DBRED        =   DeadBand;
     //-------------------------------------------------------------------------
     //      Setup DBFED
     //-------------------------------------------------------------------------
        EPwm2Regs.DBFED.bit.DBFED        =   DeadBand;
     //-------------------------------------------------------------------------
     //      Setup DBFED
     //-------------------------------------------------------------------------
        EPwm2Regs.DBFED.bit.DBFED        =   DeadBand;
     //-------------------------------------------------------------------------
     //      Setup ETSEL
     //-------------------------------------------------------------------------
        EPwm2Regs.ETSEL.bit.SOCBEN       =   0x01;     // Habilitamos el SOCA
        EPwm2Regs.ETSEL.bit.SOCBSEL      =   0x00;
        EPwm2Regs.ETSEL.bit.SOCAEN       =   0x01;     // Habilitamos el SOCB
        EPwm2Regs.ETSEL.bit.SOCASEL      =   0x04;
        EPwm2Regs.ETSEL.bit.INTSELCMP    =   0x00;
        EPwm2Regs.ETSEL.bit.SOCBSELCMP   =   0x00;
        EPwm2Regs.ETSEL.bit.SOCASELCMP   =   0x00;
        EPwm2Regs.ETSEL.bit.INTEN        =   0x00;     //Deshabilitamos INT
        EPwm2Regs.ETSEL.bit.INTSEL       =   0x01;
     //-------------------------------------------------------------------------
     //      Setup ETPS
     //-------------------------------------------------------------------------
        EPwm2Regs.ETPS.bit.SOCBCNT       =   0x00;
        EPwm2Regs.ETPS.bit.SOCBPRD       =   0x00;
        EPwm2Regs.ETPS.bit.SOCACNT       =   0x00;
        EPwm2Regs.ETPS.bit.SOCAPRD       =   0x00;
        EPwm2Regs.ETPS.bit.SOCPSSEL      =   0x00;
        EPwm2Regs.ETPS.bit.INTPSSEL      =   0x00;
        EPwm2Regs.ETPS.bit.INTPRD        =   0x00;
}//FIN Config_ePWM2


void Config_ePWM6 ( )
{
    //
    // Calculos Previos
    //
      float       Duty = 0.5;
      uint16_t    TBPRD, DeadBand,CMPA,CMPB,CMPC,CMPD;

      //  TBRPD (Count up) = ( 10 MHz / PWM ) - 1
      TBPRD = (T_clk / 20000) - 1;

      CMPA = (1 - Duty) * (TBPRD);
      CMPB = CMPC = CMPD = 0x00;
      //DeadBand = (Tiempo_Muerto * 1.0e-9) * T_clk
      DeadBand = 0;
     //-------------------------------------------------------------------------
     //    Setup TBPRD
     //-------------------------------------------------------------------------
        EPwm6Regs.TBPRD                   =   TBPRD;   // Periodo de la señal PWM
     //-------------------------------------------------------------------------
     //    Setup TBCTL
     //-------------------------------------------------------------------------
        EPwm6Regs.TBCTL.bit.FREE_SOFT     =   0x02;
        EPwm6Regs.TBCTL.bit.PHSDIR        =   0x00;
        EPwm6Regs.TBCTL.bit.CLKDIV        =   0x00;    // Preescalado Clock /1
        EPwm6Regs.TBCTL.bit.HSPCLKDIV     =   0x00;    // Preescalado Clock /1
        EPwm6Regs.TBCTL.bit.SWFSYNC       =   0x00;
        EPwm6Regs.TBCTL.bit.SYNCOSEL      =   0x01;
        EPwm6Regs.TBCTL.bit.PRDLD         =   0x00;
        EPwm6Regs.TBCTL.bit.PHSEN         =   0x00;    // Deshabilitar el desfase
        EPwm6Regs.TBCTL.bit.CTRMODE       =   0x00;    // Modo up-mode
     //-------------------------------------------------------------------------
     //      Setup TBCTL2
     //-------------------------------------------------------------------------
        EPwm6Regs.TBCTL2.bit.PRDLDSYNC    =   0x00;
        EPwm6Regs.TBCTL2.bit.PRDLDSYNC    =   0x00;
        EPwm6Regs.TBCTL2.bit.OSHTSYNC     =   0x00;
        EPwm6Regs.TBCTL2.bit.OSHTSYNCMODE =   0x00;
        EPwm6Regs.TBCTR                   =   0x00;    // Reset conteo
        EPwm6Regs.TBPHS.bit.TBPHSHR       =   0x00;    // Desfase a 0º
        EPwm6Regs.TBPRDHR                 =   0x00;
     //-------------------------------------------------------------------------
     //      Setup CMPCTL
     //-------------------------------------------------------------------------
        EPwm6Regs.CMPCTL.bit.LOADBSYNC    =   0x00;
        EPwm6Regs.CMPCTL.bit.LOADASYNC    =   0x00;
        EPwm6Regs.CMPCTL.bit.SHDWBMODE    =   0x00;    // Modo Sombra
        EPwm6Regs.CMPCTL.bit.SHDWAMODE    =   0x00;    // Modo Sombra
        EPwm6Regs.CMPCTL.bit.LOADBMODE    =   0x00;    // Activar la sombra cunado CTR = 0
        EPwm6Regs.CMPCTL.bit.LOADAMODE    =   0x00;    // Activar la sombra cunado CTR = 0
        EPwm6Regs.CMPCTL2.bit.LOADDSYNC   =   0x00;
        EPwm6Regs.CMPCTL2.bit.LOADCSYNC   =   0x00;
        EPwm6Regs.CMPCTL2.bit.SHDWDMODE   =   0x00;
        EPwm6Regs.CMPCTL2.bit.SHDWCMODE   =   0x00;
        EPwm6Regs.CMPCTL2.bit.LOADDMODE   =   0x00;
        EPwm6Regs.CMPCTL2.bit.LOADCMODE   =   0x00;
     //-------------------------------------------------------------------------
     //      Setup CMPA
     //-------------------------------------------------------------------------
        EPwm6Regs.CMPA.bit.CMPA           =   CMPA;    // Definimos el Duty
        EPwm6Regs.CMPA.bit.CMPAHR         =   0x00;
     //-------------------------------------------------------------------------
     //      Setup CMPB
     //-------------------------------------------------------------------------
        EPwm6Regs.CMPB.bit.CMPB           =   CMPB;
        EPwm6Regs.CMPB.bit.CMPBHR         =   0x00;
     //-------------------------------------------------------------------------
     //      Setup CMPC
     //-------------------------------------------------------------------------
        EPwm6Regs.CMPC                    =   CMPC;
     //-------------------------------------------------------------------------
     //      Setup CMPD
     //-------------------------------------------------------------------------
        EPwm6Regs.CMPD                    =   CMPD;
     //-------------------------------------------------------------------------
     //      Setup AQCTL
     //-------------------------------------------------------------------------
        EPwm6Regs.AQCTL.bit.LDAQBSYNC     =   0x00;
        EPwm6Regs.AQCTL.bit.LDAQASYNC     =   0x00;
        EPwm6Regs.AQCTL.bit.SHDWAQBMODE   =   0x00;
        EPwm6Regs.AQCTL.bit.SHDWAQAMODE   =   0x00;
        EPwm6Regs.AQCTL.bit.LDAQBMODE     =   0x00;
        EPwm6Regs.AQCTL.bit.LDAQAMODE     =   0x00;
     //-------------------------------------------------------------------------
     //      Setup AQTSRCSEL
     //-------------------------------------------------------------------------
        EPwm6Regs.AQTSRCSEL.bit.T2SEL     =   0x00;
        EPwm6Regs.AQTSRCSEL.bit.T1SEL     =   0x00;
     //-------------------------------------------------------------------------
     //      Setup AQCTLA
     //-------------------------------------------------------------------------
        EPwm6Regs.AQCTLA.bit.CBD          =   0x00;
        EPwm6Regs.AQCTLA.bit.CBU          =   AQ_CLEAR;// Clear cuando TBCTR = CMPB
        EPwm6Regs.AQCTLA.bit.CAD          =   0x00;
        EPwm6Regs.AQCTLA.bit.CAU          =   AQ_SET;  // Set cuando TBCTR = CMPA
        EPwm6Regs.AQCTLA.bit.PRD          =   0x00;
     //-------------------------------------------------------------------------
     //      Setup AQCTLB
     //-------------------------------------------------------------------------
        EPwm6Regs.AQCTLB.bit.CBD         =   0x00;
        EPwm6Regs.AQCTLB.bit.CBU         =   AQ_SET;   // Set cuando TBCTR = CMPB
        EPwm6Regs.AQCTLB.bit.CAD         =   0x00;
        EPwm6Regs.AQCTLB.bit.CAU         =   AQ_CLEAR; // Clear cuando TBCTR = CMPA
        EPwm6Regs.AQCTLB.bit.PRD         =   0x00;
        EPwm6Regs.AQCTLB.bit.ZRO         =   0x00;
     //-------------------------------------------------------------------------
     //      Setup DBCTL
     // Vease la figura 13-33 de spruhx5e.pdf para enterder la columna de
     //valores
     //-------------------------------------------------------------------------
        EPwm6Regs.DBCTL.bit.HALFCYCLE    =   0x00;
        EPwm6Regs.DBCTL.bit.DEDB_MODE    =   0x00;
        EPwm6Regs.DBCTL.bit.SHDWDBFEDMODE=   0x00;
        EPwm6Regs.DBCTL.bit.LOADFEDMODE  =   0x00;
        EPwm6Regs.DBCTL.bit.LOADREDMODE  =   0x00;
        EPwm6Regs.DBCTL.bit.IN_MODE      =   0x00;     // PWMxA is source for RED and FED
        EPwm6Regs.DBCTL.bit.POLSEL       =   0x02;     // Activo high complemeentario (FED)
        EPwm6Regs.DBCTL.bit.OUT_MODE     =   0x03;     // RED & FED (DBM fully enabled)
     //-------------------------------------------------------------------------
     //      Setup DBRED
     //-------------------------------------------------------------------------
        EPwm6Regs.DBRED.bit.DBRED        =   DeadBand;
     //-------------------------------------------------------------------------
     //      Setup DBFED
     //-------------------------------------------------------------------------
        EPwm6Regs.DBFED.bit.DBFED        =   DeadBand;
     //-------------------------------------------------------------------------
     //      Setup DBFED
     //-------------------------------------------------------------------------
        EPwm6Regs.DBFED.bit.DBFED        =   DeadBand;
     //-------------------------------------------------------------------------
     //      Setup ETSEL
     //-------------------------------------------------------------------------
        EPwm6Regs.ETSEL.bit.SOCBEN       =   0x01;     // Habilitamos el SOCA
        EPwm6Regs.ETSEL.bit.SOCBSEL      =   0x00;
        EPwm6Regs.ETSEL.bit.SOCAEN       =   0x01;     // Habilitamos el SOCB
        EPwm6Regs.ETSEL.bit.SOCASEL      =   0x04;
        EPwm6Regs.ETSEL.bit.INTSELCMP    =   0x00;
        EPwm6Regs.ETSEL.bit.SOCBSELCMP   =   0x00;
        EPwm6Regs.ETSEL.bit.SOCASELCMP   =   0x00;
        EPwm6Regs.ETSEL.bit.INTEN        =   0x00;     //Deshabilitamos INT
        EPwm6Regs.ETSEL.bit.INTSEL       =   0x01;
     //-------------------------------------------------------------------------
     //      Setup ETPS
     //-------------------------------------------------------------------------
        EPwm6Regs.ETPS.bit.SOCBCNT       =   0x00;
        EPwm6Regs.ETPS.bit.SOCBPRD       =   0x00;
        EPwm6Regs.ETPS.bit.SOCACNT       =   0x00;
        EPwm6Regs.ETPS.bit.SOCAPRD       =   0x00;
        EPwm6Regs.ETPS.bit.SOCPSSEL      =   0x00;
        EPwm6Regs.ETPS.bit.INTPSSEL      =   0x00;
        EPwm6Regs.ETPS.bit.INTPRD        =   0x00;

}//FIN Config_ePWM6

void Config_ePWM10 ( )
{
    //
    // Calculos Previos
    //
      float       Duty = 0.5;
      uint16_t    TBPRD, DeadBand,CMPA,CMPB,CMPC,CMPD;

      //  TBRPD (Count up) = ( 10 MHz / PWM ) - 1
      TBPRD = (T_clk / 20000) - 1;

      CMPA = (1 - Duty) * (TBPRD);
      CMPB = CMPC = CMPD = 0x00;
      //DeadBand = (Tiempo_Muerto * 1.0e-9) * T_clk
      DeadBand = 0;
     //-------------------------------------------------------------------------
     //    Setup TBPRD
     //-------------------------------------------------------------------------
        EPwm10Regs.TBPRD                   =   TBPRD;   // Periodo de la señal PWM
     //-------------------------------------------------------------------------
     //    Setup TBCTL
     //-------------------------------------------------------------------------
        EPwm10Regs.TBCTL.bit.FREE_SOFT     =   0x02;
        EPwm10Regs.TBCTL.bit.PHSDIR        =   0x01;
        EPwm10Regs.TBCTL.bit.CLKDIV        =   0x00;    // Preescalado Clock /1
        EPwm10Regs.TBCTL.bit.HSPCLKDIV     =   0x00;    // Preescalado Clock /1
        EPwm10Regs.TBCTL.bit.SWFSYNC       =   0x00;
        EPwm10Regs.TBCTL.bit.SYNCOSEL      =   0x02;
        EPwm10Regs.TBCTL.bit.PRDLD         =   0x00;
        EPwm10Regs.TBCTL.bit.PHSEN         =   0x01;    // Deshabilitar el desfase
        EPwm10Regs.TBCTL.bit.CTRMODE       =   0x00;    // Modo up-mode
     //-------------------------------------------------------------------------
     //      Setup TBCTL2
     //-------------------------------------------------------------------------
        EPwm10Regs.TBCTL2.bit.PRDLDSYNC    =   0x00;
        EPwm10Regs.TBCTL2.bit.PRDLDSYNC    =   0x00;
        EPwm10Regs.TBCTL2.bit.OSHTSYNC     =   0x00;
        EPwm10Regs.TBCTL2.bit.OSHTSYNCMODE =   0x00;
        EPwm10Regs.TBCTR                   =   0x00;    // Reset conteo
        EPwm10Regs.TBPHS.bit.TBPHSHR       =   TBPRD / 4;    // Desfase a 0º
        EPwm10Regs.TBPRDHR                 =   0x00;
     //-------------------------------------------------------------------------
     //      Setup CMPCTL
     //-------------------------------------------------------------------------
        EPwm10Regs.CMPCTL.bit.LOADBSYNC    =   0x00;
        EPwm10Regs.CMPCTL.bit.LOADASYNC    =   0x00;
        EPwm10Regs.CMPCTL.bit.SHDWBMODE    =   0x00;    // Modo Sombra
        EPwm10Regs.CMPCTL.bit.SHDWAMODE    =   0x00;    // Modo Sombra
        EPwm10Regs.CMPCTL.bit.LOADBMODE    =   0x00;    // Activar la sombra cunado CTR = 0
        EPwm10Regs.CMPCTL.bit.LOADAMODE    =   0x00;    // Activar la sombra cunado CTR = 0
        EPwm10Regs.CMPCTL2.bit.LOADDSYNC   =   0x00;
        EPwm10Regs.CMPCTL2.bit.LOADCSYNC   =   0x00;
        EPwm10Regs.CMPCTL2.bit.SHDWDMODE   =   0x00;
        EPwm10Regs.CMPCTL2.bit.SHDWCMODE   =   0x00;
        EPwm10Regs.CMPCTL2.bit.LOADDMODE   =   0x00;
        EPwm10Regs.CMPCTL2.bit.LOADCMODE   =   0x00;
     //-------------------------------------------------------------------------
     //      Setup CMPA
     //-------------------------------------------------------------------------
        EPwm10Regs.CMPA.bit.CMPA           =   CMPA;    // Definimos el Duty
        EPwm10Regs.CMPA.bit.CMPAHR         =   0x00;
     //-------------------------------------------------------------------------
     //      Setup CMPB
     //-------------------------------------------------------------------------
        EPwm10Regs.CMPB.bit.CMPB           =   CMPB;
        EPwm10Regs.CMPB.bit.CMPBHR         =   0x00;
     //-------------------------------------------------------------------------
     //      Setup CMPC
     //-------------------------------------------------------------------------
        EPwm10Regs.CMPC                    =   CMPC;
     //-------------------------------------------------------------------------
     //      Setup CMPD
     //-------------------------------------------------------------------------
        EPwm10Regs.CMPD                    =   CMPD;
     //-------------------------------------------------------------------------
     //      Setup AQCTL
     //-------------------------------------------------------------------------
        EPwm10Regs.AQCTL.bit.LDAQBSYNC     =   0x00;
        EPwm10Regs.AQCTL.bit.LDAQASYNC     =   0x00;
        EPwm10Regs.AQCTL.bit.SHDWAQBMODE   =   0x00;
        EPwm10Regs.AQCTL.bit.SHDWAQAMODE   =   0x00;
        EPwm10Regs.AQCTL.bit.LDAQBMODE     =   0x02;
        EPwm10Regs.AQCTL.bit.LDAQAMODE     =   0x02;
     //-------------------------------------------------------------------------
     //      Setup AQTSRCSEL
     //-------------------------------------------------------------------------
        EPwm10Regs.AQTSRCSEL.bit.T2SEL     =   0x00;
        EPwm10Regs.AQTSRCSEL.bit.T1SEL     =   0x00;
     //-------------------------------------------------------------------------
     //      Setup AQCTLA
     //-------------------------------------------------------------------------
        EPwm10Regs.AQCTLA.bit.CBD          =   0x00;
        EPwm10Regs.AQCTLA.bit.CBU          =   AQ_CLEAR;// Clear cuando TBCTR = CMPB
        EPwm10Regs.AQCTLA.bit.CAD          =   0x00;
        EPwm10Regs.AQCTLA.bit.CAU          =   AQ_SET;  // Set cuando TBCTR = CMPA
        EPwm10Regs.AQCTLA.bit.PRD          =   0x00;
     //-------------------------------------------------------------------------
     //      Setup AQCTLB
     //-------------------------------------------------------------------------
        EPwm10Regs.AQCTLB.bit.CBD         =   0x00;
        EPwm10Regs.AQCTLB.bit.CBU         =   AQ_SET;   // Set cuando TBCTR = CMPB
        EPwm10Regs.AQCTLB.bit.CAD         =   0x00;
        EPwm10Regs.AQCTLB.bit.CAU         =   AQ_CLEAR; // Clear cuando TBCTR = CMPA
        EPwm10Regs.AQCTLB.bit.PRD         =   0x00;
        EPwm10Regs.AQCTLB.bit.ZRO         =   0x00;
     //-------------------------------------------------------------------------
     //      Setup DBCTL
     // Vease la figura 13-33 de spruhx5e.pdf para enterder la columna de
     //valores
     //-------------------------------------------------------------------------
        EPwm10Regs.DBCTL.bit.HALFCYCLE    =   0x00;
        EPwm10Regs.DBCTL.bit.DEDB_MODE    =   0x00;
        EPwm10Regs.DBCTL.bit.SHDWDBFEDMODE=   0x00;
        EPwm10Regs.DBCTL.bit.LOADFEDMODE  =   0x00;
        EPwm10Regs.DBCTL.bit.LOADREDMODE  =   0x00;
        EPwm10Regs.DBCTL.bit.IN_MODE      =   0x00;     // PWMxA is source for RED and FED
        EPwm10Regs.DBCTL.bit.POLSEL       =   0x02;     // Activo high complemeentario (FED)
        EPwm10Regs.DBCTL.bit.OUT_MODE     =   0x03;     // RED & FED (DBM fully enabled)
     //-------------------------------------------------------------------------
     //      Setup DBRED
     //-------------------------------------------------------------------------
        EPwm10Regs.DBRED.bit.DBRED        =   DeadBand;
     //-------------------------------------------------------------------------
     //      Setup DBFED
     //-------------------------------------------------------------------------
        EPwm10Regs.DBFED.bit.DBFED        =   DeadBand;
     //-------------------------------------------------------------------------
     //      Setup DBFED
     //-------------------------------------------------------------------------
        EPwm10Regs.DBFED.bit.DBFED        =   DeadBand;
     //-------------------------------------------------------------------------
     //      Setup ETSEL
     //-------------------------------------------------------------------------
        EPwm10Regs.ETSEL.bit.SOCBEN       =   0x01;     // Habilitamos el SOCA
        EPwm10Regs.ETSEL.bit.SOCBSEL      =   0x00;
        EPwm10Regs.ETSEL.bit.SOCAEN       =   0x01;     // Habilitamos el SOCB
        EPwm10Regs.ETSEL.bit.SOCASEL      =   0x04;
        EPwm10Regs.ETSEL.bit.INTSELCMP    =   0x00;
        EPwm10Regs.ETSEL.bit.SOCBSELCMP   =   0x00;
        EPwm10Regs.ETSEL.bit.SOCASELCMP   =   0x00;
        EPwm10Regs.ETSEL.bit.INTEN        =   0x00;     //Deshabilitamos INT
        EPwm10Regs.ETSEL.bit.INTSEL       =   0x01;
     //-------------------------------------------------------------------------
     //      Setup ETPS
     //-------------------------------------------------------------------------
        EPwm10Regs.ETPS.bit.SOCBCNT       =   0x00;
        EPwm10Regs.ETPS.bit.SOCBPRD       =   0x00;
        EPwm10Regs.ETPS.bit.SOCACNT       =   0x00;
        EPwm10Regs.ETPS.bit.SOCAPRD       =   0x00;
        EPwm10Regs.ETPS.bit.SOCPSSEL      =   0x00;
        EPwm10Regs.ETPS.bit.INTPSSEL      =   0x00;
        EPwm10Regs.ETPS.bit.INTPRD        =   0x00;

}//FIN Config_ePWM10

//
// FIN DEL ARCHIVO
//
