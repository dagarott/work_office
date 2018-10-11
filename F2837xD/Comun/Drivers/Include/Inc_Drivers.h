/*
 * Inc_Drivers.h
 *
 *  Created on: 18 abr. 2018
 *      Author: jeniher
 */

#ifndef DRIVERS_INCLUDE_INC_DRIVERS_H_
#define DRIVERS_INCLUDE_INC_DRIVERS_H_

#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "DEF_Global.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "Init_HW.h"
#include "Config_GPIO.h"
#include "Config_PWM.h"
#include "Config_ADC.h"
#include "MEM.h"
#include "Config_CAN.h"
#include "FIFO.h"

//
// Defines
//
// Definimos el modelo del Microcontrolador
//#define TMS320F28377s
//#define TMS320F2837xD
#define T_clk 100000000   //10 MHz


#define CSS_Protocol true  //Enable/Disable use of COMBO CAN commmands

//
// Definicion posiciones de memoria
//

//  ePWM
#define Start_Address_ePWMxRegs 0x4000
#define Size_ePWMxRegs          0x0100

// GPIO
#define Start_Address_GPIOs     0x7C00
#define Size__Address_ePWMxRegs 0x0040
#define Size_GPIOs              0x0020
#define Offset_PUD              0x000
#define Offset_MUX1             0x0006
#define Offset_MUX2             0x0008
#define Offset_GMUX1            0x0020
#define Offset_GMUX2            0x0022
#endif /* DRIVERS_INCLUDE_INC_DRIVERS_H_ */
