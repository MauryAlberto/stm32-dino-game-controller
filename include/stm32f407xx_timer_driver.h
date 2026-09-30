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
} TIM_Base_Conf_t;

/* TIM_AutoReloadPreload */
#define TIM_AUTORELOAD_PRELOAD_DISABLE      0U  /* TIMx_ARR register is not buffered */
#define TIM_AUTORELOAD_PRELOAD_ENABLE       1U  /* TIMx_ARR register buffered */

/* TIMx CR1 register bit */
#define TIM_CR1_ARPE    7U  /* ARPE: Auto-reload preload enable bit */
#define TIM_CR1_CEN     0U  /* CEN: Counter enable bit */

/* TIMx EGR register bit */
#define TIM_EGR_UG      0U  /* EGR: Update generation bit */

/* TIMx SR register bit */
#define TIM_SR_UIF      0U  /* UIF: Update interrupt flag bit */

/* Macros handle update event status */
#define TIM6_UEV_STS()          ((TIM6->SR >> TIM_SR_UIF) & 0x01U)      /* Timer 6 update event status */
#define TIM6_UEV_STS_CLR()      (TIM6->SR &= ~(0x01U << TIM_SR_UIF))    /* Timer 7 clear update event status */

void TIM_Base_Init(TIM_RegDef_t* TIMx, TIM_Base_Conf_t TIM_BaseConf);
void TIM_Base_Start(TIM_RegDef_t* TIMx);
void TIM_Base_Stop(TIM_RegDef_t* TIMx);

#endif