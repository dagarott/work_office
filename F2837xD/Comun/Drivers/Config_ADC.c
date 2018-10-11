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
\file           CONFIG_ADC.c
\brief          Modulo de configuracion de los ADC del microcontrolador
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

//
// Funciones Privadas
//
void Config_ADC_A   (void);

/**
***************************************************************************
\fn         INIT_ADC
\brief      Funcion principal de configuracion de los ADCs. Esta funcion es
            llamada desde el "main", donde llamará a las funciones de
            configuracion de los distintos modulos.
                - Config_ADC_A (Implementada).
                - Config_ADC_B (Sin implementar)
                - Config_ADC_C (Sin implementar)
                - Config_ADC_D (Sin implementar)

            NOTA IMPORTANTE : Se han implementado los modulos necesarios
            y los más importantes de configuracion. para más resigtros
            consular el PDF de TI "spruhx5e.pdf".

\param[in]  void
\return     void

**************************************************************************/
void Init_ADC ()
{
    EALLOW;
#ifdef CPU1
    Config_ADC_A();
#endif

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;

    EDIS;
}// FIN Config ADC


/**
***************************************************************************
\fn         INIT_ADC
\brief      Funcion de configuracion del modulos del ADC A del TMS320F2877s

            NOTA IMPORTANTE : Se han implementado los modulos necesarios
            y los más importantes de configuracion. para más resigtros
            consular el PDF de TI "spruhx5e.pdf".

\param[in]  void
\return     void

**************************************************************************/
void Config_ADC_A ()
{
    // Activamos el CLK del ADC
    CpuSysRegs.PCLKCR13.bit.ADC_A   = 1;    //ADCCLK on
#ifdef CPU1
    // Reset the ADC.  This is good programming practice.
    DevCfgRegs.SOFTPRES13.bit.ADC_A = 1;    // ADC is reset
    DevCfgRegs.SOFTPRES13.bit.ADC_A = 0;    // ADC is released from reset
#endif
    //-------------------------------------------------------------------------
    //    Setup ADCCTL1
    //-------------------------------------------------------------------------
    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  ADCPWDNZ            | Registro que enciende    | 00h - Power Off.   |
     * |  (7)                 |el modulo ADC_A.          | 01h - Power On.    |
     * |----------------------|--------------------------|--------------------|
     *
     */
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ  =   0x01;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  INTPULSEPOS         | Posicion de pulso de     | 00h - Activado al  |
     * |  (2)                 |interrupcion del ADC.     |finalizar la adqui- |
     * |                      |                          |cion ventana.       |
     * |                      |                          | 01h - Activado al  |
     * |                      |                          |finalizar la conver-|
     * |                      |                          |sion del ADC.       |
     * |----------------------|--------------------------|--------------------|
     *
     */
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS  =   0x01;

    //-------------------------------------------------------------------------
    //    Setup ADCCTL2
    //-------------------------------------------------------------------------
    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  SIGNALMODE          | Registro seleeciona el   | 00h - Single-ended |
     * |  (7)                 |modo de entrada del       | 01h - Diferencial. |
     * |                      |convertidor.              |                    |
     * |----------------------|--------------------------|--------------------|
     *
     */
    AdcaRegs.ADCCTL2.bit.SIGNALMODE  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  RESOLUTION          | Registro seleeciona la   | 00h - 12 bits.     |
     * |  (6)                 |resolucion del SOC.       | 01h - 16 bits.     |
     * |                      |                          |                    |
     * |----------------------|--------------------------|--------------------|
     *
     */
    AdcaRegs.ADCCTL2.bit.RESOLUTION  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  PRESCALE            | Registro preescalado del | 00h - /1.0         |
     * |  (3 - 0)             |CLK del ADC.              | 01h - Invalido.    |
     * |                      |                          | 02h - /2.0         |
     * |                      |                          | 03h - /2.5         |
     * |                      |                          | 04h - /3.0         |
     * |                      |                          | 05h - /3.5         |
     * |                      |                          | 06h - /4.0         |
     * |                      |                          | 07h - /4.5         |
     * |                      |                          | 08h - /5.0         |
     * |                      |                          | 09h - /5.5         |
     * |                      |                          | 0Ah - /6.0         |
     * |                      |                          | 0Bh - /6.5         |
     * |                      |                          | 0Ch - /7.0         |
     * |                      |                          | 0Dh - /7.5         |
     * |                      |                          | 0Eh - /8.0         |
     * |                      |                          | 0Fh - /8.5         |
     * |----------------------|--------------------------|--------------------|
     *
     */
    AdcaRegs.ADCCTL2.bit.PRESCALE  =   0x06;

    //
    // Retardo de un 1ms para encender el ADC.
    //
    DELAY_US(1000);

    //-------------------------------------------------------------------------
    //    Setup ADCSOCxCTL
    //-------------------------------------------------------------------------
    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  TRIGSEL             | Registro que selecciona  | 00h - Software.    |
     * |  (24 - 20)           |la fuente disparo del ADC.| 01h - Timer 0.     |
     * |                      |                          | 02h - Timer 1.     |
     * |                      |                          | 03h - Timer 2.     |
     * |                      |                          | 04h - GPIO.        |
     * |                      |                          |ADCEXTSOC.          |
     * |                      |                          | 05h - ePWM1.SOCA.  |
     * |                      |                          | 06h - ePWM1.SOCB.  |
     * |                      |                          | 07h - ePWM2.SOCA.  |
     * |                      |                          | 08h - ePWM2.SOCB.  |
     * |                      |                          | 09h - ePWM3.SOCA.  |
     * |                      |                          | 0Ah - ePWM3.SOCB.  |
     * |                      |                          | 0Bh - ePWM4.SOCA.  |
     * |                      |                          | 0Ch - ePWM4.SOCB.  |
     * |                      |                          | 0Dh - ePWM5.SOCA.  |
     * |                      |                          | 0Eh - ePWM5.SOCB.  |
     * |                      |                          | 0Fh - ePWM6.SOCA.  |
     * |                      |                          | 10h - ePWM6.SOCB.  |
     * |                      |                          | 11h - ePWM7.SOCA.  |
     * |                      |                          | 12h - ePWM7.SOCB.  |
     * |                      |                          | 13h - ePWM8.SOCA.  |
     * |                      |                          | 14h - ePWM8.SOCB.  |
     * |                      |                          | 15h - ePWM9.SOCA.  |
     * |                      |                          | 16h - ePWM9.SOCB.  |
     * |                      |                          | 17h - ePWM10.SOCA. |
     * |                      |                          | 18h - ePWM10.SOCB. |
     * |                      |                          | 19h - ePWM11.SOCA. |
     * |                      |                          | 1Ah - ePWM11.SOCB. |
     * |                      |                          | 1Bh - ePWM12.SOCA. |
     * |                      |                          | 1Ch - ePWM12.SOCB. |
     * |----------------------|--------------------------|--------------------|
     *
     */
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL  =   0x05;  //trigger on ePWM1 SOCA/C

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  CHSEL               | Registro que selecciona  |Single Mode:        |
     * |  (18 - 15)           |canal para el SOCx.       | 00h - ADCIN0.      |
     * |                      |                          | 01h - ADCIN1.      |
     * |                      |                          | 02h - ADCIN2.      |
     * |                      |                          | 03h - ADCIN3.      |
     * |                      |                          | 04h - ADCIN4.      |
     * |                      |                          | 05h - ADCIN5.      |
     * |                      |                          | 06h - ADCIN6.      |
     * |                      |                          | 07h - ADCIN7.      |
     * |                      |                          | 08h - ADCIN8.      |
     * |                      |                          | 09h - ADCIN9.      |
     * |                      |                          | 0Ah - ADCIN10.     |
     * |                      |                          | 0Bh - ADCIN11.     |
     * |                      |                          | 0Ch - ADCIN12.     |
     * |                      |                          | 0Dh - ADCIN13.     |
     * |                      |                          | 0Eh - ADCIN14.     |
     * |                      |                          | 0Fh - ADCIN15.     |
     * |                      |                          | Diferencial mode:  |
     * |                      |                          | 00h - ADCIN0 +.    |
     * |                      |                          |       ADCIN1 -.    |
     * |                      |                          | 02h - ADCIN2 +.    |
     * |                      |                          |       ADCIN3 -.    |
     * |                      |                          | 04h - ADCIN4 +.    |
     * |                      |                          |       ADCIN5 -.    |
     * |                      |                          | 06h - ADCIN6 +.    |
     * |                      |                          |       ADCIN7 -.    |
     * |                      |                          | 08h - ADCIN8 +.    |
     * |                      |                          |       ADCIN9 -.    |
     * |                      |                          | 0Ah - ADCIN10 +.   |
     * |                      |                          |       ADCIN11 -.   |
     * |                      |                          | 0Ch - ADCIN12 +.   |
     * |                      |                          |       ADCIN13 -.   |
     * |                      |                          | 0Eh - ADCIN14 +.   |
     * |                      |                          |       ADCIN15 -.   |
     * |----------------------|--------------------------|--------------------|
     *
     */
    AdcaRegs.ADCSOC0CTL.bit.CHSEL  =   0x0D;  //trigger on ePWM1 SOCA/C

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  ACQPS               | Registro que selecciona  | Formula abajo      |
     * |  (8 - 0)             |preescalado para el SOCx. |                    |
     * |----------------------|--------------------------|--------------------|
     *
     */
    /* T(s+h) = (ACQPS + 1) · (1/SYSCLK) -> ACQPS = (T(s+h) · SYSCLK) - 1  */
    // T(s+h) = 700ns                    -> ACQPS = 6
    AdcaRegs.ADCSOC0CTL.bit.ACQPS  =   0x06;

    //-------------------------------------------------------------------------
    //    Setup ADCINTESEL1N2
    //-------------------------------------------------------------------------
    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  INT2CONT            | Registro que activa el   | 00h - Deshabilitar |
     * |  (14)                |modo continuo del ADC 2.  | 01h - Hablilitar   |
     * |----------------------|--------------------------|--------------------|
     *
     */
    AdcaRegs.ADCINTSEL1N2.bit.INT2CONT  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  INT2E               | Registro que activa la   | 00h - Deshabilitar |
     * |  (13)                |interrupcion del ADC 2.   | 01h - Hablilitar   |
     * |----------------------|--------------------------|--------------------|
     *
     */
    AdcaRegs.ADCINTSEL1N2.bit.INT2E  =   0x00;


    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  INT2SEL             | Registro que selecciona  | 00h - EOC0.        |
     * |  (11- 8)             |la fuente del ADC 2.      | 01h - EOC1.        |
     * |                      |                          | 02h - EOC2.        |
     * |                      |                          | 03h - EOC3.        |
     * |                      |                          | 04h - EOC4.        |
     * |                      |                          | 05h - EOC5.        |
     * |                      |                          | 06h - EOC6.        |
     * |                      |                          | 07h - EOC7.        |
     * |                      |                          | 08h - EOC8.        |
     * |                      |                          | 09h - EOC9.        |
     * |                      |                          | 0Ah - EOC10.       |
     * |                      |                          | 0Bh - EOC11.       |
     * |                      |                          | 0Ch - EOC12.       |
     * |                      |                          | 0Dh - EOC13.       |
     * |                      |                          | 0Eh - EOC14.       |
     * |                      |                          | 0Fh - EOC15.       |
     * |----------------------|--------------------------|--------------------|
     *
     */
    AdcaRegs.ADCINTSEL1N2.bit.INT2SEL  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  INT1CONT            | Registro que activa el   | 00h - Deshabilitar |
     * |  (6)                 |modo continuo del ADC 1.  | 01h - Hablilitar   |
     * |----------------------|--------------------------|--------------------|
     *
     */
    AdcaRegs.ADCINTSEL1N2.bit.INT1CONT  =   0x00;

    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  INT1E               | Registro que activa la   | 00h - Deshabilitar |
     * |  (5)                 |interrupcion del ADC 1.   | 01h - Hablilitar   |
     * |----------------------|--------------------------|--------------------|
     *
     */
    AdcaRegs.ADCINTSEL1N2.bit.INT2E  =   0x01;  // Activamos el INT1 del ADC


    /* |----------------------|--------------------------|--------------------|
     * |    NAME BIT (BITS)   |       Descripcion        |       Valores      |
     * |----------------------|--------------------------|--------------------|
     * |  INT1SEL             | Registro que selecciona  | 00h - EOC0.        |
     * |  (3 - 0)             |la fuente del ADC 1.      | 01h - EOC1.        |
     * |                      |                          | 02h - EOC2.        |
     * |                      |                          | 03h - EOC3.        |
     * |                      |                          | 04h - EOC4.        |
     * |                      |                          | 05h - EOC5.        |
     * |                      |                          | 06h - EOC6.        |
     * |                      |                          | 07h - EOC7.        |
     * |                      |                          | 08h - EOC8.        |
     * |                      |                          | 09h - EOC9.        |
     * |                      |                          | 0Ah - EOC10.       |
     * |                      |                          | 0Bh - EOC11.       |
     * |                      |                          | 0Ch - EOC12.       |
     * |                      |                          | 0Dh - EOC13.       |
     * |                      |                          | 0Eh - EOC14.       |
     * |                      |                          | 0Fh - EOC15.       |
     * |----------------------|--------------------------|--------------------|
     *
     */
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL  =   0x00; // Activa INT cuando terminel el SOC0

    /* RESET FLAGs ADC  */
    AdcaRegs.ADCINTFLGCLR.all = 0x0F;    // Reseteamos los flags de INT de los ADC
}// FIN Config_ADC_A

//
// FIN DEL ARCHIVO
//
