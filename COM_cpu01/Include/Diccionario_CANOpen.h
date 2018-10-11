/*
 * Diccionario_CANOpen.h
 *
 *  Created on: 17 sept. 2018
 *      Author: jeniher
 */

#ifndef INCLUDE_DICCIONARIO_CANOPEN_H_
#define INCLUDE_DICCIONARIO_CANOPEN_H_

#include <stdint.h>

#define CCS_Protocol 0  /**/

/**
 *******************************************************************************
 \typedef        tCanMsg
 \brief          Tipo definido  para mensaje CAN
 \struct         sCanMsg
 \brief          Estructura para mensaje CAN
 ******************************************************************************/
typedef struct sCanMsg
{
    /** Modo Acceso al dato READ o WRITE*/
    char Modo_Acceso;
    /** Identificador mensaje*/
    uint16_t ID;
    /** Subindice mensaje*/
    char SubIndice;
    /** Longitud de datos (0 - 8)*/
    char Len;
    /** Buffer de datos*/
    uint32_t Buf;
} tCanMsg;

/**
 ********************************************************************************
 \typedef        enum Indice_Diccionario_TPO
 \brief          Enumeramos el indice del Diccionario de los mensajes TPO
 *******************************************************************************/
enum Indice_Diccionario_TPO
{
//  0x100x
    Nombre_dispositivo,
    Hardware_dispositivo,
    Software_dispositivo,

//  0x101x
    Identity,

//  0x210x
    Module_Enable,
    Module_Status,
    Module_Temperature,
    Uac_Input,
    Iac_Input,
    Udc_Out,
    Idc_Out,
    Udc_Out_Setpoint,
    Idc_Out_Setpoint,
    Udc_Bus,
    I_Solar_Out,

//  0x212x
    Uac_Input_Average,
    Uac_Input_L1,
    Uac_Input_L2,
    Uac_Input_L3,
    Iac_Input_L1,
    Iac_Input_L2,
    Iac_Input_L3,
    UBus,
    UBus_OVP,

    //  0x213x
    Warning_Status,
    Error_Source,
    Temp_Ambient,
    Temp_Sec,
    Temp_Prim,
    Temp_Trafo,
//  0x214x,
    Udc_Setpoint_Real,
    Idc_Setpoint_Real,
//  0x215x
    Switch_OFF_Reason,
//  0x2FFx
    Set_Node_ID,
    Restart_Module,
#ifdef 0
//  0x600x
    Enable,
    Enable_ZVT1,
    Enable_ZVT2,
    Enable_ZVT3,
    Enable_ZVT4,

    Io,
    Io_ZVT1,
    Io_ZVT2,
    Io_ZVT3,
    Io_ZVT4,

    Io_Max,
    Io_Max_ZVT1,
    Io_Max_ZVT2,
    Io_Max_ZVT3,
    Io_Max_ZVT4,

    Vo,
    Vo_ZVT1,
    Vo_ZVT2,
    Vo_ZVT3,
    Vo_ZVT4,

    Vo_Max,
    Vo_Max_ZVT1,
    Vo_Max_ZVT2,
    Vo_Max_ZVT3,
    Vo_Max_ZVT4,

    Vi,
    Vi_ZVT1,
    Vi_ZVT2,
    Vi_ZVT3,
    Vi_ZVT4,
//  0x601x
    Io_ADC_ZVT1,
    Io_ADC_ZVT2,
    Io_ADC_ZVT3,
    Io_ADC_ZVT4,
    Io_Estacion,

    Vo_ADC_ZVT1,
    Vo_ADC_ZVT2,
    Vo_ADC_ZVT3,
    Vo_ADC_ZVT4,
    Vo_Estacion,
//  0x610x
    Temp_IGBTBA_ZVT1,
    Temp_IGBTA_ZVT2,
    Temp_IGBTA_ZVT3,
    Temp_IGBTA_ZVT4,

    Temp_IGBTB_ZVT1,
    Temp_IGBTB_ZVT2,
    Temp_IGBTB_ZVT3,
    Temp_IGBTB_ZVT4,
//  0x700x
    Estado_IGBT_ZVT1,
    Estado_IGBT_ZVT2,
    Estado_IGBT_ZVT3,
    Estado_IGBT_ZVT4,

    Forzar_Refrigeracion,
    Forzar_Refrigeracion_ZVT1,
    Forzar_Refrigeracion_ZVT2,
    Forzar_Refrigeracion_ZVT3,
    Forzar_Refrigeracion_ZVT4,

    Descargar_BUS,
    Descargar_BUS_ZVT1,
    Descargar_BUS_ZVT2,
    Descargar_BUS_ZVT3,
    Descargar_BUS_ZVT4,
//  0x710x
    Estado_Actual_ZVT1,
    Estado_Actual_ZVT2,
    Estado_Actual_ZVT3,
    Estado_Actual_ZVT4,

    Cambiar_Estado,
    Cambiar_Estado_ZVT1,
    Cambiar_Estado_ZVT2,
    Cambiar_Estado_ZVT3,
    Cambiar_Estado_ZVT4,
//  0x720x
    Insolation_Test_ZVT1,
    Insolation_Test_ZVT2,
    Insolation_Test_ZVT3,
    Insolation_Test_ZVT4,
//  0x800x
    Errores_ZVT1,
    Errores_ZVT2,
    Errores_ZVT3,
    Errores_ZVT4,
#endif
//  0x9000
    Vo_Chademo,         //Voltage value read by ADC from Power Supply
    Io_Chademo,         //Current value read by ADC from Power Supply
    TempPos_Chademo,    //Positive Temperature value read by ADC
    TempNeg_Chademo,    //Negative Temperature value read by ADC
#if CCS_Protocol
//  0x9001
    Vo_CCS,             //Voltage value read by ADC from Power Supply
    Io_CCS,             //Current value read by ADC from Power Supply
    TempPos_CCS,        //Positive Temperature value read by ADC
    TempNeg_CCS,        //Negative Temperature value read by ADC
#endif
//  0xFFFF
    FIN_Diccionario,
};
#endif /* INCLUDE_DICCIONARIO_CANOPEN_H_ */
