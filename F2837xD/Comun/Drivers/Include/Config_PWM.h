/*
 * Config_PWM.h
 *
 *  Created on: 18 abr. 2018
 *      Author: jeniher
 */

#ifndef DRIVERS_INCLUDE_CONFIG_PWM_H_
#define DRIVERS_INCLUDE_CONFIG_PWM_H_

#include "Inc_drivers.h"


extern volatile struct EPWM_REGS ePWM;

typedef enum eParam_ePWM {
        //MiembroParametro  //Offset Memora ePWMxRegs
        TiempoMuerto_RED    = 0x51,
        TiempoMuerto_FED    = 0x53,
        Desfase             = 0x60,
        Frecuencia          = 0x63,
        Duty                = 0x6A,

    } tParam_ePWM ;


void Config_EPwm          (void);
void Actualizar_ePWM      (uint16_t ePWM, uint32_t Param, tParam_ePWM MiembroEstructura);


#endif /* DRIVERS_INCLUDE_CONFIG_PWM_H_ */
