///
/// @file		ESC.h
/// @brief		Library header
/// @details	ST spin driver
/// @n
/// @n @b		Project SMC
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Alex Bondarenko
/// @author		Alex Bondarenko
///
/// @date		2018-02-28 5:57 PM
/// @version	<#version#>
///
/// @copyright	(c) Alex Bondarenko, 2018
/// @copyright	<#licence#>
///
/// @see		ReadMe.txt for references
///


// Core library for code-sense - IDE-based
// Help: http://bit.ly/2AdU7cu
#if defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
#elif defined(ROBOTIS) // Robotis specific
#include "libpandora_types.h"
#include "pandora.h"
#elif defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(LITTLEROBOTFRIENDS) // LittleRobotFriends specific
#include "LRF.h"
#elif defined(MICRODUINO) // Microduino specific
#include "Arduino.h"
#elif defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#elif defined(REDBEARLAB) // RedBearLab specific
#include "Arduino.h"
#elif defined(RFDUINO) // RFduino specific
#include "Arduino.h"
#elif defined(SPARK) // Spark specific
#include "application.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

#ifndef ESC____FILEEXTENSION___
///
/// @brief	Release
///
#define ESC____FILEEXTENSION___





#include "SPI.h"

#define ESC_PIN_FL A5
#define ESC_PIN_FR A4
#define ESC_PIN_FC A3
#define ESC_PIN_RL A1
#define ESC_PIN_RR A0
#define ESC_PIN_RC A2

#define ESC_INDEX_FL 0
#define ESC_INDEX_FR 1
#define ESC_INDEX_FC 2
#define ESC_INDEX_RL 3
#define ESC_INDEX_RR 4
#define ESC_INDEX_RC 5



typedef enum
{
    ESC_CMD_Stop,
    ESC_CMD_Start,
    ESC_CMD_GetTemperature,
    ESC_CMD_GetRunState,
    ESC_CMD_GetCurrent,
    ESC_CMD_GetSpeed,
    ESC_CMD_SetSpeed,
    ESC_CMD_SetCurrent,
    ESC_CMD_SetDirection,
    ESC_CMD_SetAcceleration,
    ESC_CMD_SetKP,
    ESC_CMD_SetKI,
    ESC_CMD_SetKD,
    ESC_CMD_RESET,
    ESC_CMD_GetStatusStruct
} ESC_COMMAND;

typedef enum
{
    IDLE,                               /* 0 */
    STARTUP,                            /* 1 */
    VALIDATION,                         /* 2 */
    STOP,                               /* 3 */
    START,                              /* 4 */
    RUN,                                /* 5 */
    ALIGNMENT,                          /* 6 */
    SPEEDFBKERROR,                      /* 7 */
    OVERCURRENT,                        /* 8 */
    STARTUP_FAILURE,                    /* 9 */
    STARTUP_BEMF_FAILURE,               /* 10 */
    LF_TIMER_FAILURE                    /* 11 */
} ESC_RUN_STATE;

typedef struct
{
    uint8_t pin;
    int16_t speedSetPoint;
    ESC_RUN_STATE runState;
    int32_t speedMeasured;
    int16_t currentMeasured;
    uint8_t temperature;
    uint8_t direction;
}ESC_Struct;

typedef struct
{
    int32_t speedSetPoint : 32;
    int32_t speedMeasured : 32;
    int16_t currentMeasured :16;
    uint8_t temperature:8;
    ESC_RUN_STATE runState : 7;
    uint8_t direction:1;
}ESC_StatusStruct;



typedef union
{
    ESC_StatusStruct statusStruct;
    uint8_t stuctRaw[sizeof(ESC_StatusStruct)];
} ESC_StatusStructUnion;





unsigned int ESC_init(ESC_Struct* ESC_hande,int pin);
unsigned int ESC_init_all(void);
unsigned int ESCStart(ESC_Struct* ESC_hande);
unsigned int ESCStop(ESC_Struct* ESC_hande);
unsigned int ESCSetSpeed(ESC_Struct* ESC_hande,int16_t speed);
unsigned int ESCSetDirection(ESC_Struct* ESC_hande,uint8_t direction);
unsigned int ESCSetAcceleration(ESC_Struct* ESC_hande,int16_t acceleration);
unsigned int ESCGetStatus(ESC_Struct* ESC_hande);
uint16_t ESCGetSpeed(ESC_Struct* ESC_hande);
uint16_t ESCGetCurrent(ESC_Struct* ESC_hande);
unsigned int ESCReset(ESC_Struct* ESC_hande);
ESC_StatusStruct ESCGetStatusStruct(ESC_Struct* ESC_hande);


#endif // ESC____FILEEXTENSION___


