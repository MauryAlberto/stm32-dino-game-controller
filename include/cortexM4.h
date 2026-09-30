#ifndef CORTEXM4_H
#define CORTEXM4_H
#include <stdint.h>

/* NVIC register definition */
typedef struct
{
    volatile uint32_t ISER[8];          /* Interrupt set-enable register */
             uint32_t RESERVERD0[24];
    volatile uint32_t ICER[8];          /* Interrupt clear enable register */
             uint32_t RESERVERD1[24];
    volatile uint32_t ISPR[8];          /* Interrupt set pending register */
             uint32_t RESERVERD2[24];
    volatile uint32_t ICPR[8];          /* Interrupt clear pending register */
             uint32_t RESERVERD3[24];
    volatile uint32_t IABR[8];          /* Interrupt active bit register */
             uint32_t RESERVERD4[56];
    volatile uint32_t IPR[60];          /* Interrupt priority register */
             uint32_t RESERVERD5[644];
    volatile uint32_t STIR;         /* Software trigger interrupt register */
} NVIC_RegDef_t;

/* NVIC base address */
#define NVIC    ((NVIC_RegDef_t*) (0xE000E100UL))

/* Interrupt request number */
#define IRQ_NO_EXTI0        6U
#define IRQ_NO_EXTI1        7U
#define IRQ_NO_EXTI2        8U
#define IRQ_NO_EXTI3        9U
#define IRQ_NO_EXTI4        10U
#define IRQ_NO_EXTI9_5      23U
#define IRQ_NO_USART3       39U
#define IRQ_NO_EXTI15_10    40U

#define NULL ((void*)0)

void NVIC_SetPriority(uint8_t IRQNumber, uint8_t Priority);
void NVIC_EnableIRQ(uint8_t IRQNumber);

#endif