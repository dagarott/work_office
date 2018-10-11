/*
 * Diccionario_CANOpen.c
 *
 *  Created on: 17 sept. 2018
 *      Author: jeniher
 */

#include "F28x_Project.h"
#include "F2837xD_Ipc_drivers.h"
#include "Diccionario_CANOpen.h"
#include "Config_CAN.h"

// Esctructura para sacar la inforamcion del diccionario del CANopen
tCanMsg *D2;

/*******************************************************************************
 Definimos los datos para lel diccionario del CANOpen
 IMPORTANTE : El protocolo CANopen utiliza el formato Little-endian
 *******************************************************************************/

/**
 ********************************************************************************
 \struct     Envio datos Diccionario CANOpen

 \brief      --------------------------------------------------------
 |   Indice  |   SubIndice   |   LEN | Valor por Defecto |
 --------------------------------------------------------
 *******************************************************************************/
/*  Para facilitar el acceso a esta tabla esta definida el incide en la
 "estrctura enum Indice_Diccionario_TPO" en Diccionario_CANopen_DS418.h    */

/*  IMPORTANTE : Si se modifica esta tabla, modificar
 enum Indice_Diccionario_TPO en Diccionario_CANopen_DS418.h                */

tCanMsg Diccionario_CanOpen[] = {

//  Indice                                           //Indice_Diccionario_TPO
//------------------------------------------------------------------------------
//  0x100x
//------------------------------------------------------------------------------
        { OD_READ, 0x1008, 0x00, 4, 0x00000000 }, //Nombre_dispositivo
        { OD_READ, 0x1009, 0x00, 4, 0x00000000 }, //Hardware_dispositivo
        { OD_READ, 0x100A, 0x00, 4, 0x00000000 }, //Software_dispositivo
//------------------------------------------------------------------------------
//  0x101x
//------------------------------------------------------------------------------
        { OD_READ, 0x1018, 0x00, 4, 0x00000000 }, //Identity
//------------------------------------------------------------------------------
//  0x210x
//------------------------------------------------------------------------------
        { OD_READ + OD_WRITE, 0x2100, 0x00, 4, 0x00000000 }, //Module_Enable
        { OD_READ, 0x2101, 0x00, 4, 0x00000000 }, //Module_Status
        { OD_READ, 0x2104, 0x00, 4, 0x00000000 }, //Module_Temperature
        { OD_READ + OD_WRITE, 0x2105, 0x00, 4, 0x00000000 }, //Uac_Input
        { OD_READ, 0x2106, 0x00, 4, 0x00000000 }, //Iac_Input
        { OD_READ, 0x2107, 0x00, 4, 0x00000000 }, //Udc_Out
        { OD_READ, 0x2108, 0x00, 4, 0x00000000 }, //Idc_Out
        { OD_READ + OD_WRITE, 0x2109, 0x00, 4, 0x00000000 }, //Udc_Out_Setpoint
        { OD_READ + OD_WRITE, 0x210A, 0x00, 4, 0x00000000 }, //Idc_Out_Setpoint
        { OD_READ, 0x210D, 0x00, 4, 0x00000000 }, //Udc_Bus
        { OD_READ, 0x210E, 0x00, 4, 0x00000000 }, //I_Solar_Out
//------------------------------------------------------------------------------
//  0x212x
//------------------------------------------------------------------------------
        { OD_READ, 0x2120, 0x00, 4, 0x00000000 }, //Uac_Input_Average
        { OD_READ, 0x2121, 0x00, 4, 0x00000000 }, //Uac_Input_L1
        { OD_READ, 0x2122, 0x00, 4, 0x00000000 }, //Uac_Input_L2
        { OD_READ, 0x2123, 0x00, 4, 0x00000000 }, //Uac_Input_L3
        { OD_READ, 0x2124, 0x00, 4, 0x00000000 }, //Iac_Input_L1
        { OD_READ, 0x2125, 0x00, 4, 0x00000000 }, //Iac_Input_L2
        { OD_READ, 0x2126, 0x00, 4, 0x00000000 }, //Iac_Input_L3
        { OD_READ, 0x212A, 0x00, 4, 0x00000000 }, //UBus
        { OD_READ, 0x212B, 0x00, 4, 0x00000000 }, //UBus_OVP
//------------------------------------------------------------------------------
//  0x213x
//------------------------------------------------------------------------------
        { OD_READ, 0x2130, 0x00, 4, 0x00000000 }, //Warning_Status
        { OD_READ, 0x2132, 0x00, 4, 0x00000000 }, //Error_Source
        { OD_READ, 0x2136, 0x00, 4, 0x00000000 }, //Temp_Ambient
        { OD_READ, 0x2137, 0x00, 4, 0x00000000 }, //Temp_Sec
        { OD_READ, 0x2138, 0x00, 4, 0x00000000 }, //Temp_Prim
        { OD_READ, 0x2139, 0x00, 4, 0x00000000 }, //Temp_Trafo
//------------------------------------------------------------------------------
//  0x214x
//------------------------------------------------------------------------------
        { OD_READ, 0x2149, 0x00, 4, 0x00000000 }, //Udc_Setpoint_Real
        { OD_READ, 0x214A, 0x00, 4, 0x00000000 }, //Idc_Setpoint_Real
//------------------------------------------------------------------------------
//  0x215x
//------------------------------------------------------------------------------
        { OD_READ, 0x2150, 0x00, 4, 0x00000000 }, //Switch_OFF_Reason
//------------------------------------------------------------------------------
//  0x2FFx
//------------------------------------------------------------------------------
        { OD_READ + OD_WRITE, 0x2FF0, 0x00, 4, 0x00000000 }, //Set_Node_ID
        { OD_READ + OD_WRITE, 0x2FFF, 0x00, 4, 0x00000000 }, //Restart_Module
#ifdef 0
//------------------------------------------------------------------------------
//  0x600x
//------------------------------------------------------------------------------
        {   OD_READ+OD_WRITE, 0x6000, 0x00, 4, 0x00000000}, //Enable
        {   OD_READ+OD_WRITE, 0x6000, 0x01, 4, 0x00000000}, //Enable_ZVT1
        {   OD_READ+OD_WRITE, 0x6000, 0x02, 4, 0x00000000}, //Enable_ZVT2
        {   OD_READ+OD_WRITE, 0x6000, 0x03, 4, 0x00000000}, //Enable_ZVT3
        {   OD_READ+OD_WRITE, 0x6000, 0x04, 4, 0x00000000}, //Enable_ZVT4

        {   OD_READ+OD_WRITE, 0x6001, 0x00, 4, 0x00000000}, //Io
        {   OD_READ+OD_WRITE, 0x6001, 0x01, 4, 0x00000000}, //Io_ZVT1
        {   OD_READ+OD_WRITE, 0x6001, 0x02, 4, 0x00000000}, //Io_ZVT2
        {   OD_READ+OD_WRITE, 0x6001, 0x03, 4, 0x00000000}, //Io_ZVT3
        {   OD_READ+OD_WRITE, 0x6001, 0x04, 4, 0x00000000}, //Io_ZVT4

        {   OD_READ+OD_WRITE, 0x6002, 0x00, 4, 0x00000000}, //Io_Max
        {   OD_READ+OD_WRITE, 0x6002, 0x01, 4, 0x00000000}, //Io_Max_ZVT1
        {   OD_READ+OD_WRITE, 0x6002, 0x02, 4, 0x00000000}, //Io_Max_ZVT2
        {   OD_READ+OD_WRITE, 0x6002, 0x03, 4, 0x00000000}, //Io_Max_ZVT3
        {   OD_READ+OD_WRITE, 0x6002, 0x04, 4, 0x00000000}, //Io_Max_ZVT4

        {   OD_READ+OD_WRITE, 0x6003, 0x00, 4, 0x00000000}, //Vo
        {   OD_READ+OD_WRITE, 0x6003, 0x01, 4, 0x00000000}, //Vo_ZVT1
        {   OD_READ+OD_WRITE, 0x6003, 0x02, 4, 0x00000000}, //Vo_ZVT2
        {   OD_READ+OD_WRITE, 0x6003, 0x03, 4, 0x00000000}, //Vo_ZVT3
        {   OD_READ+OD_WRITE, 0x6003, 0x04, 4, 0x00000000}, //Vo_ZVT4

        {   OD_READ+OD_WRITE, 0x6004, 0x00, 4, 0x00000000}, //Vo_Max
        {   OD_READ+OD_WRITE, 0x6004, 0x01, 4, 0x00000000}, //Vo_Max_ZVT1
        {   OD_READ+OD_WRITE, 0x6004, 0x02, 4, 0x00000000}, //Vo_Max_ZVT2
        {   OD_READ+OD_WRITE, 0x6004, 0x03, 4, 0x00000000}, //Vo_Max_ZVT3
        {   OD_READ+OD_WRITE, 0x6004, 0x04, 4, 0x00000000}, //Vo_Max_ZVT4

        {   OD_READ+OD_WRITE, 0x6005, 0x00, 4, 0x00000000}, //Vi
        {   OD_READ+OD_WRITE, 0x6005, 0x01, 4, 0x00000000}, //Vi_ZVT1
        {   OD_READ+OD_WRITE, 0x6005, 0x02, 4, 0x00000000}, //Vi_ZVT2
        {   OD_READ+OD_WRITE, 0x6005, 0x03, 4, 0x00000000}, //Vi_ZVT3
        {   OD_READ+OD_WRITE, 0x6005, 0x04, 4, 0x00000000}, //Vi_ZVT4
        //------------------------------------------------------------------------------
        //  0x601x
        //------------------------------------------------------------------------------
        {   OD_READ , 0x6010, 0x01, 4, 0x00000000}, //Io_ADC_ZVT1
        {   OD_READ , 0x6010, 0x02, 4, 0x00000000}, //Io_ADC_ZVT2
        {   OD_READ , 0x6010, 0x03, 4, 0x00000000}, //Io_ADC_ZVT3
        {   OD_READ , 0x6010, 0x04, 4, 0x00000000}, //Io_ADC_ZVT4
        {   OD_READ+OD_WRITE, 0x6010, 0x05, 4, 0x00000000}, //Io_Estacion

        {   OD_READ , 0x6011, 0x01, 4, 0x00000000}, //Vo_ADC_ZVT1
        {   OD_READ , 0x6011, 0x02, 4, 0x00000000}, //Vo_ADC_ZVT2
        {   OD_READ , 0x6011, 0x03, 4, 0x00000000}, //Vo_ADC_ZVT3
        {   OD_READ , 0x6011, 0x04, 4, 0x00000000}, //Vo_ADC_ZVT4
        {   OD_READ+OD_WRITE, 0x6011, 0x05, 4, 0x00000000}, //Vo_Estacion
        //------------------------------------------------------------------------------
        //  0x610x
        //------------------------------------------------------------------------------
        {   OD_READ , 0x6100, 0x01, 4, 0x00000000}, //Temp_IGBTBA_ZVT1
        {   OD_READ , 0x6100, 0x02, 4, 0x00000000}, //Temp_IGBTA_ZVT2
        {   OD_READ , 0x6100, 0x03, 4, 0x00000000}, //Temp_IGBTA_ZVT3
        {   OD_READ , 0x6100, 0x04, 4, 0x00000000}, //Temp_IGBTA_ZVT4

        {   OD_READ , 0x6101, 0x01, 4, 0x00000000}, //Temp_IGBTB_ZVT1
        {   OD_READ , 0x6101, 0x02, 4, 0x00000000}, //Temp_IGBTB_ZVT2
        {   OD_READ , 0x6101, 0x03, 4, 0x00000000}, //Temp_IGBTB_ZVT3
        {   OD_READ , 0x6101, 0x04, 4, 0x00000000}, //Temp_IGBTB_ZVT4
        //------------------------------------------------------------------------------
        //  0x700x
        //------------------------------------------------------------------------------
        {   OD_READ , 0x7000, 0x01, 4, 0x00000000}, //Estado_IGBT_ZVT1
        {   OD_READ , 0x7000, 0x02, 4, 0x00000000}, //Estado_IGBT_ZVT2
        {   OD_READ , 0x7000, 0x03, 4, 0x00000000}, //Estado_IGBT_ZVT3
        {   OD_READ , 0x7000, 0x04, 4, 0x00000000}, //Estado_IGBT_ZVT4

        {   OD_READ+OD_WRITE, 0x7001, 0x00, 4, 0x00000000}, //Forzar_Refrigeracion
        {   OD_READ+OD_WRITE, 0x7001, 0x01, 4, 0x00000000}, //Forzar_Refrigeracion_ZVT1
        {   OD_READ+OD_WRITE, 0x7001, 0x02, 4, 0x00000000}, //Forzar_Refrigeracion_ZVT2
        {   OD_READ+OD_WRITE, 0x7001, 0x03, 4, 0x00000000}, //Forzar_Refrigeracion_ZVT3
        {   OD_READ+OD_WRITE, 0x7001, 0x04, 4, 0x00000000}, //Forzar_Refrigeracion_ZVT4

        {   OD_READ+OD_WRITE, 0x7002, 0x00, 4, 0x00000000}, //Descargar_BUS
        {   OD_READ+OD_WRITE, 0x7002, 0x01, 4, 0x00000000}, //Descargar_BUS_ZVT1
        {   OD_READ+OD_WRITE, 0x7002, 0x02, 4, 0x00000000}, //Descargar_BUS_ZVT2
        {   OD_READ+OD_WRITE, 0x7002, 0x03, 4, 0x00000000}, //Descargar_BUS_ZVT3
        {   OD_READ+OD_WRITE, 0x7002, 0x04, 4, 0x00000000}, //Descargar_BUS_ZVT4
        //------------------------------------------------------------------------------
        //  0x710x
        //------------------------------------------------------------------------------
        {   OD_READ , 0x7100, 0x01, 4, 0x00000000}, //Estado_Actual_ZVT1
        {   OD_READ , 0x7100, 0x02, 4, 0x00000000}, //Estado_Actual_ZVT2
        {   OD_READ , 0x7100, 0x03, 4, 0x00000000}, //Estado_Actual_ZVT3
        {   OD_READ , 0x7100, 0x04, 4, 0x00000000}, //Estado_Actual_ZVT4

        {   OD_READ+OD_WRITE, 0x7101, 0x00, 4, 0x00000000}, //Cambiar_Estado
        {   OD_READ+OD_WRITE, 0x7101, 0x01, 4, 0x00000000}, //Cambiar_Estado_ZVT1
        {   OD_READ+OD_WRITE, 0x7101, 0x02, 4, 0x00000000}, //Cambiar_Estado_ZVT2
        {   OD_READ+OD_WRITE, 0x7101, 0x03, 4, 0x00000000}, //Cambiar_Estado_ZVT3
        {   OD_READ+OD_WRITE, 0x7101, 0x04, 4, 0x00000000}, //Cambiar_Estado_ZVT4
        //------------------------------------------------------------------------------
        //  0x720x
        //------------------------------------------------------------------------------
        {   OD_READ+OD_WRITE, 0x7200, 0x01, 4, 0x00000000}, //Insolation_Test_ZVT1
        {   OD_READ+OD_WRITE, 0x7200, 0x02, 4, 0x00000000}, //Insolation_Test_ZVT2
        {   OD_READ+OD_WRITE, 0x7200, 0x03, 4, 0x00000000}, //Insolation_Test_ZVT3
        {   OD_READ+OD_WRITE, 0x7200, 0x04, 4, 0x00000000}, //Insolation_Test_ZVT4
        //------------------------------------------------------------------------------
        //  0x800x
        //------------------------------------------------------------------------------
        {   OD_READ , 0x8000, 0x01, 4, 0x00000000}, //Errores_ZVT1
        {   OD_READ , 0x8000, 0x02, 4, 0x00000000}, //Errores_ZVT2
        {   OD_READ , 0x8000, 0x03, 4, 0x00000000}, //Errores_ZVT3
        {   OD_READ , 0x8000, 0x04, 4, 0x00000000}, //Errores_ZVT4
#endif
        //------------------------------------------------------------------------------
        //  0x9000  Used by ADC sensor PCB. Chademo Protocol
        //------------------------------------------------------------------------------
        { OD_READ, 0x9000, 0x01, 4, 0x00000000 }, //Vo_Chademo. Voltage value read by ADC from Power Supply
        { OD_READ, 0x9000, 0x02, 4, 0x00000000 }, //Io_Chademo. Current value read by ADC from Power Supply
        { OD_READ, 0x9000, 0x03, 4, 0x00000000 }, //TempPos_Chademo. Positive Temperature value read by ADC
        { OD_READ, 0x9000, 0x04, 4, 0x00000000 }, //TempNeg_Chademo. Negative Temperature value read by ADC

#if CCS_Protocol
        //------------------------------------------------------------------------------
        //  0x9001  Used by ADC sensor PCB. CCS Protocol
        //------------------------------------------------------------------------------
        {   OD_READ, 0x9001, 0x01, 4, 0x00000000}, //Vo_CCS. Voltage value read by ADC from Power Supply
        {   OD_READ, 0x9001, 0x02, 4, 0x00000000}, //Io_CCS. Current value read by ADC from Power Supply
        {   OD_READ, 0x9001, 0x03, 4, 0x00000000}, //TempPos_CCS. Positive Temperature value read by ADC
        {   OD_READ, 0x9001, 0x04, 4, 0x00000000}, //TempNeg_CCS. Negative Temperature value read by ADC
#endif
//------------------------------------------------------------------------------
//  0xFFFF
//------------------------------------------------------------------------------
        { 0xFF, 0xFFFF, 0xFF, 0, 0xFFFFFFFF }, //FIN_Diccionario
        };
/* FIN Diccionario  */
