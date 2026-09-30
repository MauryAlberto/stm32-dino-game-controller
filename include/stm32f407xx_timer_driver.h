#ifndef STM32F407XX_TIMER_DRIVER_H
#define STM32F407XX_TIMER_DRIVER_H
#include "stm32f407xx.h"

/* Timer base unit configuration structure */
typedef struct
{
    uint32_t Period;            /* Specifies the period value to be loaded into the active
                                   Auto-Reload Register at the next update event.
                                   This parameter can be a number between Min_Data = 0x00000000 and Max_Data = 0xFFFFFFFF */
    uint16_t Prescaler;         /* Specifies the prescaler value of the timer base unit.
                                   This parameter can be a number between Minval = 0x0000 and Maxval = 0xFFFF */
    uint8_t AutoReloadPreload;  /* Specifies the auto reload Preload.
                                   This parameter can be a value of @ref TIM_AutoReloadPreload */
    uint8_t CounterMode;        /* Specifies the timer counting mode.
                                   This parameter can be a value of @ref TIM_CounterMode */
} TIM_Base_Conf_t;

/* Output compare configuration structure */
typedef struct
{
    uint32_t Pulse;         /* Specifies the pulse value to be loaded into the Capture Compare Register.
                               This parameter can be a number between Min_Data = 0x00000000 and Max_Data = 0xFFFFFFFF */
    uint8_t OCMode;         /* Specifies the TIM mode.
                               This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */
    uint8_t OCPolarity;     /* Specifies the output polarity.
                               This parameter can be a value of @ref TIM_Output_Compare_Polarity.*/
} TIM_OC_Conf_t;

/* Output compare channel */
#define TIM_OC_CHANNEL_1    0U  /* Output compare channel 1 */
#define TIM_OC_CHANNEL_2    1U  /* Output compare channel 2 */
#define TIM_OC_CHANNEL_3    2U  /* Output compare channel 3 */
#define TIM_OC_CHANNEL_4    3U  /* Output compare channel 4 */

/* TIM_AutoReloadPreload */
#define TIM_AUTORELOAD_PRELOAD_DISABLE      0U  /* TIMx_ARR register is not buffered */
#define TIM_AUTORELOAD_PRELOAD_ENABLE       1U  /* TIMx_ARR register buffered */

/* TIM_CounterMode */
#define TIM_UPCOUNTING      0U /* TIMx upcounting mode selection */
#define TIM_DOWNCOUNTING    1U /* TIMx downcounting mode selection */

/* TIM_Output_Compare_and_PWM_modes*/
/* TIM Output Compare and PWM modes */
#define TIM_OCMODE_TIMING               0U  /* Timing mode: compare match only sets the flag. Output pin is unchanged. */
#define TIM_OCMODE_ACTIVE               1U  /* Active mode: output becomes active when CNT matches CCRx. */
#define TIM_OCMODE_INACTIVE             2U  /* Inactive mode: output becomes inactive when CNT matches CCRx. */
#define TIM_OCMODE_TOGGLE               3U  /* Toggle mode: output toggles state whenever CNT matches CCRx. */
#define TIM_OCMODE_FORCED_INACTIVE      4U  /* Forced inactive: output is forced to its inactive level. */
#define TIM_OCMODE_FORCED_ACTIVE        5U  /* Forced active: output is forced to its active level. */
#define TIM_OCMODE_PWM1                 6U  /* PWM mode 1: output is active while CNT < CCRx and inactive afterward. */
#define TIM_OCMODE_PWM2                 7U  /* PWM mode 2: output is inactive while CNT < CCRx and active afterward. */

/* TIM_Output_Compare_Polarity */
#define TIM_OCPOLARITY_HIGH             0U  /* OC active high */
#define TIM_OCPOLARITY_LOW              1U  /* OC active low */

/* TIMx CR1 register bit */
#define TIM_CR1_ARPE    7U  /* ARPE: Auto-reload preload enable bit */
#define TIM_CR1_CEN     0U  /* CEN: Counter enable bit */
#define TIM_CR1_DIR     4U  /* DIR: Direction */

/* TIMx EGR register bit */
#define TIM_EGR_UG      0U  /* EGR: Update generation bit */

/* TIMx SR register bit */
#define TIM_SR_UIF      0U  /* UIF: Update interrupt flag bit */

/* TIMx DIER register bit */
#define TIM_DIER_UIE    0U  /* UIE: Enable update interrupt bit */

/* Macros handle update event status */
#define TIM6_UEV_STS()          ((TIM6->SR >> TIM_SR_UIF) & 0x01U)      /* Timer 6 update event status */
#define TIM6_UEV_STS_CLR()      (TIM6->SR &= ~(0x01U << TIM_SR_UIF))    /* Timer 7 clear update event status */

/* Macro handles output compare */
#define TIM4_OC_PWM_SET_DUTY(Channel, CCR_value)    (TIM4->CCR[(Channel)] = (CCR_value))

/* Macro to map IRQn to TIMx */
#define TIMx_TO_IRQ(TIMx)\
        ((TIMx == TIM6) ? IRQ_NO_TIM6_DAC :\
         (TIMx == TIM7) ? IRQ_NO_TIM7 : IRQ_NO_TIM6_DAC)

void TIM_Base_Init(TIM_RegDef_t* TIMx, TIM_Base_Conf_t TIM_BaseConf);
void TIM_Base_Start(TIM_RegDef_t* TIMx);
void TIM_Base_Stop(TIM_RegDef_t* TIMx);
void TIM_Base_IT_Init(TIM_RegDef_t* TIMx, uint8_t Priority);
void TIM_OC_Init(TIM_RegDef_t* TIMx, TIM_OC_Conf_t TIM_OCConf, uint8_t Channel);

#endif