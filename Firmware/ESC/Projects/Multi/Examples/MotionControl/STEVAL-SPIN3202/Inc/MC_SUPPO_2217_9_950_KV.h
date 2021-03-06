/**
 ******************************************************************************
 * @file    MC_SUPPO_2217_9_950_KV.h
 * @author  Alex Bondarenko
 * @version V1.0.0
 * @date    JANUARY 24th, 2018
 * @brief   This header file provides all parameters to driver a motor with 6Step
            library
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/** @addtogroup MIDDLEWARES     MIDDLEWARES 
  * @brief  Middlewares Layer
  * @{ 
*/

/** @addtogroup MC_6-STEP_LIB       MC_6-STEP LIB 
  * @brief  Motor Control driver
  * @{ 
*/

/** @defgroup Main_Motor_parameters    Main_Motor_parameters
  *  @{
    * @brief All motor parameters for 6Step driving
*/
 
/* **************************************************************************** 
 ==============================================================================   
           ###### BASIC PARAMETERS ######
 ============================================================================== 
**************************************************************************** */   
#define NUM_POLE_PAIRS                       7      /*!< Number of Motor Pole pairs */
#define DIRECTION                            1      /*!< Set motor direction CW = 0 and CCW = 1*/
#define TARGET_SPEED_OPEN_LOOP            600      /*!< Target speed in open loop control */
#define TARGET_SPEED                      1000      /*!< Target speed in closed loop control */
//#define FIXED_HALL_DELAY
#ifdef VOLTAGE_MODE
/* **************************************************************************** 
 ==============================================================================   
           ###### ADVANCED PARAMETERS VOLTAGE MODE ######
 ============================================================================== 
**************************************************************************** */
/*!< ********************* Open loop control *********************************/
#define STARTUP_DUTY_CYCLE                  90     /*!< Tenths of percentage of PWM on time */

/*!< ********************* Closed Loop control *********************************/
#ifndef PID
#define KP_GAIN                            512     /*!< Kp parameter for PI regulator */
#define KI_GAIN                            484     /*!< Ki parameter for PI regulator */

#else
#define KP_GAIN                            512     /*!< Kp parameter for PID regulator */
#define KI_GAIN                            400     /*!< Ki parameter for PID regulator */
#define KD_GAIN                            100     /*!< Kd parameter for PID regulator */
#endif
#define K_GAIN_SCALING                      14     /*!< Kp, Ki, (Kd) scaling for PI(D) regulator */
#define LOWER_OUT_LIMIT                      0     /*!< Low Out value of PI regulator */
#define UPPER_OUT_LIMIT            HF_TIMX_ARR     /*!< High Out value of PI regulator */
#define MAX_POT_SPEED                    10000     /*!< Maximum Speed regulated by potentiometer */
#define MIN_POT_SPEED                     1200     /*!< Minimum Speed regulated by potentiometer */
#else
/* **************************************************************************** 
 ==============================================================================   
           ###### ADVANCED PARAMETERS CURRENT MODE ######
 ============================================================================== 
**************************************************************************** */
/*!< ********************* Open loop control *********************************/
#define STARTUP_PEAK_CURRENT               1000     /*!< mA, Startup Peak Current */
#define SENSE_RESISTOR                      10     /*!< mOhms, (RS) */
#define SENSE_RESISTOR_VOLTAGE      (STARTUP_PEAK_CURRENT*SENSE_RESISTOR)/1000  /*!< mV */
#define SENSE_GAIN                        6600     /*!< Thousandths, (RF/RB) */
#define SENSE_AMPLIFIED_VOLTAGE     (SENSE_RESISTOR_VOLTAGE*SENSE_GAIN)/1000    /*!< mV */
#define REFERENCE_PWM_HIGH_VOLTAGE        3300     /*!< mV, (VDD) */
#define REFERENCE_PWM_DIVIDER_RATIO       3200     /*!< Thousandths, ((RD+RLP)/RD) */
#define OC_THRESHOLD                      500     /*!< mV */
#define STARTUP_CURRENT_REF_THDS    (1000-(((2*OC_THRESHOLD-SENSE_AMPLIFIED_VOLTAGE)*REFERENCE_PWM_DIVIDER_RATIO)/REFERENCE_PWM_HIGH_VOLTAGE)) /*!< Thousandths */
#define STARTUP_CURRENT_REFERENCE   ((STARTUP_CURRENT_REF_THDS<<UPPER_OUT_SHIFT)/1000)

/*!< ********************* Closed Loop control *********************************/
#ifndef PID
//#define KP_GAIN                           2048     /*!< Kp parameter for PI regulator */
//#define KI_GAIN                           1960     /*!< Ki parameter for PI regulator */

#define KP_GAIN                            2048     /*!< Kp parameter for PI regulator */
#define KI_GAIN                            1960     /*!< Ki parameter for PI regulator */
#else
#define KP_GAIN                           2730     /*!< Kp parameter for PID regulator */
#define KI_GAIN                           1180     /*!< Ki parameter for PID regulator */
#define KD_GAIN                            295     /*!< Kd parameter for PID regulator */
#endif
#define K_GAIN_SCALING                      14     /*!< Kp, Ki, (Kd) scaling for PI(D) regulator */
#define LOWER_OUT_LIMIT                     30     /*!< Low Out value of PI regulator */
#define UPPER_OUT_SHIFT                     12     /*!< Integer value no greater than 16 */
#define UPPER_OUT_LIMIT   (1<<UPPER_OUT_SHIFT)     /*!< High Out value of PI regulator */
#define MAX_POT_SPEED                    10000     /*!< Maximum Speed regulated by potentiometer */
#define MIN_POT_SPEED                     1200     /*!< Minimum Speed regulated by potentiometer */
#endif

/* **************************************************************************** 
 ==============================================================================   
           ###### ADVANCED PARAMETERS COMMON ######
 ============================================================================== 
**************************************************************************** */
/*!< ********************* Gate driving **************************************/
#define GATE_DRIVING_PWM_FREQUENCY       50000     /*!< Hz */
#define SYSCLOCK_FREQUENCY               48000000  /*!< Hz */
#define LF_TIMX_PSC                      23
#define LF_TIMX_ARR                      24000
#define HF_TIMX_PSC                      0
#if defined(HALL_SENSORS)
#define HF_TIMX_ARR (SYSCLOCK_FREQUENCY/(GATE_DRIVING_PWM_FREQUENCY*(HF_TIMX_PSC+1))-1)
#else
#define HF_TIMX_ARR                      (SYSCLOCK_FREQUENCY/(2*GATE_DRIVING_PWM_FREQUENCY*(HF_TIMX_PSC+1))-1)
#endif
#define DEAD_TIME                        30
#define PULSE           ((4*HF_TIMX_ARR)/5)

/*!< ********************* Hall sensors **************************************/
#if defined(HALL_SENSORS)
#define START_COUNTER_STEPS_DECREMENTATION   8
#define NUMBER_OF_STARTS                     10
#define HALL_KO_SUCCESSIVE_MAX              60
#define MAX_SPEED                        20000      /*!< Motor rated max speed */
#define STEP_DURATION_MINIMUM 					((SYSCLOCK_FREQUENCY*10/((LF_TIMX_PSC+1)*NUM_POLE_PAIRS*MAX_SPEED))>>1)

#define LF_TIM_uS_TO_STEP(time) 				((int)(time/(1E6/(SYSCLOCK_FREQUENCY / (LF_TIMX_PSC+1)))))

#define HALL_RISE_TIME				(54) // uS 
#define HALL_FALL_TIME				(20) // uS 

#define HALL_OFFSET_HL				LF_TIM_uS_TO_STEP(HALL_RISE_TIME-HALL_FALL_TIME)
#define HALL_OFFSET_LH				LF_TIM_uS_TO_STEP(HALL_FALL_TIME-HALL_RISE_TIME)

#define HALL_OFFSET_H					LF_TIM_uS_TO_STEP(HALL_RISE_TIME)
#define HALL_OFFSET_L					LF_TIM_uS_TO_STEP(HALL_FALL_TIME)

#define HALL_PHASE_GAP 				 (-0.1)



//#define COMMUTATION_DELAY_HALL_RISE_STEP 	(138)
//#define COMMUTATION_DELAY_HALL_FALL_STEP 	(20)
//#define COMMUTATION_DELAY_SHIFT 					(220)
////#define COMMUTATION_DELAY_SHIFT_REVERSE 	(-102)
//#define COMMUTATION_DELAY_SHIFT_REVERSE 	(220)


//#define COMMUTATION_DELAY_RISE_TIME_STEP	(COMMUTATION_DELAY_HALL_RISE_STEP+COMMUTATION_DELAY_SHIFT)
//#define COMMUTATION_DELAY_FALL_TIME_STEP 	(COMMUTATION_DELAY_HALL_FALL_STEP+COMMUTATION_DELAY_SHIFT)
//#define COMMUTATION_DELAY_RISE_TIME_STEP_REVERSE	(COMMUTATION_DELAY_HALL_RISE_STEP+COMMUTATION_DELAY_SHIFT_REVERSE)
//#define COMMUTATION_DELAY_FALL_TIME_STEP_REVERSE 	(COMMUTATION_DELAY_HALL_FALL_STEP+COMMUTATION_DELAY_SHIFT_REVERSE)

//#define COMMUTATION_DELAY_WIDTH_ADJUST 	(COMMUTATION_DELAY_HALL_RISE_STEP-COMMUTATION_DELAY_HALL_FALL_STEP)
//#define COMMUTATION_DELAY_ADJUST_HL 	(COMMUTATION_DELAY_HALL_RISE_STEP-COMMUTATION_DELAY_HALL_FALL_STEP)
//#define COMMUTATION_DELAY_ADJUST_LH 	(COMMUTATION_DELAY_HALL_FALL_STEP-COMMUTATION_DELAY_HALL_RISE_STEP)

#if defined(FIXED_HALL_DELAY)
#define COMMUTATION_DELAY                  40
#endif
#endif

/*!< ********************* Open loop control *********************************/
#define ACC                              10000     /*!< Mechanical acceleration rate (setting available in manual mode, LOAD_TYPE = 0) */
#define MINIMUM_ACC                        500     /*!< Mechanical acceleration rate for BIG load application */
//#define NUMBER_OF_STEPS                  20000    /*!< Number of elements for motor start-UP (max value 65535)*///
#define NUMBER_OF_STEPS                  	100    /*!< Number of elements for motor start-UP (max value 65535)*/
#define TIME_FOR_ALIGN                     500     /*!< Time for alignment (msec)*/
#define BUTTON_DELAY                      1000     /*!< Delay time to enable push button for new command (1 = 1msec)*/
#define NUMBER_ZCR                          12     /*!< Number of zero crossing event during the startup for closed loop control begin */

/*!< ********************* Closed Loop control *******************************/
/*!< Zero Crossing parameters */
#define INITIAL_DEMAGN_DELAY                 4     /*!< Initial value for delay time during startup for Bemf detection */
#define DEMAG_TIME_STEP_RATIO              270     /*!< Tenths of percentage of step time allowed for demagnetization */
#define K_DEMAG (DEMAG_TIME_STEP_RATIO*GATE_DRIVING_PWM_FREQUENCY)/(100*NUM_POLE_PAIRS) /*!< Proportional parameter to compute the number of HF_TIMx periods before checking BEMF threshold */
#define DEMAG_SPEED_THRESHOLD            10500     /*!< Mechanical speed threshold above which the MINIMUM_DEMAGN_DELAY is used*/ 
#define MINIMUM_DEMAGN_DELAY                 0     /*!< Demagnetization delay applied above DEMAG_SPEED_THRESHOLD*/ 
#define BEMF_THRSLD_DOWN_OFF               200      /*!< Zero Crossing threshold during OFF time*/ 
#define BEMF_THRSLD_UP_OFF                 200      /*!< Zero Crossing threshold during OFF time*/
#ifdef PWM_ON_BEMF_SENSING
#define BEMF_THRSLD_DOWN_ON               1200      /*!< Zero Crossing threshold during ON time*/
#define BEMF_THRSLD_UP_ON                 1200      /*!< Zero Crossing threshold during ON time*/
#define DUTY_CYCLE_50   ((HF_TIMX_ARR + 1)>>1)
#endif

/*!< Speed parameters */
#define SPEED_LOOP_TIME                      1     /*!< Speed Loop time (1 = 1msec) */
#define FILTER_DEEP_SHIFT                    5
#define FILTER_DEEP     (1<<FILTER_DEEP_SHIFT)     /*!< Number of bits for digital filter */
#define POT_BUFFER_SIZE_SHIFT                4
#define POT_BUFFER_SIZE (2+(1<<POT_BUFFER_SIZE_SHIFT))
#define ADC_SPEED_TH                       250     /*!<Fixed treshold to change the target speed (t.b.f) */

/*!< Motor stall detection parameters */
#define BEMF_CONSEC_DOWN_MAX                10     /*!< Maximum value of BEMF Consecutive Threshold Falling Crossings Counter in closed loop */
#define BEMF_CNT_EVENT_MAX                 100     /*!< Maximum number of BEMF Counter in open loop */

/*!< ********************* Debug *********************************************/
/*!< Debug pin */
#define GPIO_ZERO_CROSS                      0     /*!< Enable (1) the GPIO toggling for zero crossing detection */
#define GPIO_COMM                            0     /*!< Enable (1) the GPIO toggling for commutation */
#ifdef PWM_ON_BEMF_SENSING
#define GPIO_ZCR_MODE                        1     /*!< Enable (1) the GPIO echo of TON/TOFF BEMF sensing method */
#endif

/*!< ********************* Demo **********************************************/
/*!< Demo mode parameters */
#define DEMO_START_TIME                  10000     /*!< Time (msec) to keep the motor in run mode */
#define DEMO_STOP_TIME                    5000     /*!< Time (msec) to keep the motor in stop mode */

/*!< ********************* General *******************************************/
#define TRUE                                 1     /*!< Define TRUE */
#define FALSE                                0     /*!< Define FALSE */

/**
  * @}   Main_Motor_parameters
  */


/**
  * @}  end MC_6-STEP_LIB 
  */

/**
  * @}  end MIDDLEWARES
  */
