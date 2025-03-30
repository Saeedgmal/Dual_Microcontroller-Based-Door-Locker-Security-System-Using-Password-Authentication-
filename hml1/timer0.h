/*
 * timer1.h
 *
 *  Created on: Oct 28, 2024
 *      Author: saeed
 */
#include <avr/io.h>
#include "Std_Types.h"
#ifndef TIMER0_H_
#define TIMER0_H_

#define IS_TIMER0_OVF() (TIFR & (1 << TOV0))

typedef enum {
    TIMER0,
    TIMER1,
    TIMER2
} Timer_ID_Type;

typedef enum {
    NO_CLOCK,
    F_CPU_1,
    F_CPU_8,
    F_CPU_64,
    F_CPU_256,
    F_CPU_1024
} Timer_ClockType;

typedef enum {
    NORMAL_MODE,
    CTC_MODE,
    FAST_PWM_MODE,
    PWM_MODE
} Timer_ModeType;

typedef void (*CallbackFunction)(void);

typedef struct {
    uint16_t timer_InitialValue;
    uint16_t timer_compare_MatchValue; // Used in compare mode only
    Timer_ID_Type timer_ID;
    Timer_ClockType timer_clock;
    Timer_ModeType timer_mode;
} Timer_ConfigType;

// Function prototypes
void Timer_init(const Timer_ConfigType *Config_Ptr);
void Timer_deInit(Timer_ID_Type timer_type);
void Timer_setCallBack(CallbackFunction a_ptr, Timer_ID_Type a_timer_ID);

// ISR Prototypes
void Timer0_Compare_ISR(void);
void Timer0_Overflow_ISR(void);
void Timer1_Compare_ISR(void);
void Timer1_Overflow_ISR(void);
void Timer2_Compare_ISR(void);
void Timer2_Overflow_ISR(void);

#endif /* TIMER0_H_ */
