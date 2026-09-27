#ifndef STM32F407XX_H
#define STM32F407XX_H
#include <stdint.h>

/* GPIO register definition struct */
typedef struct
{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
} GPIO_RegDef_t;

/* RCC register definition struct */
typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
             uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
             uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    volatile uint32_t RESERVED2;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
             uint32_t RESERVED3[2];
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    volatile uint32_t RESERVED4;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
             uint32_t RESERVED5[2];
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
             uint32_t RESERVED6[2];
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
} RCC_RegDeg_t;

/* Peripheral base addresses */
#define AHB1_BASEADDR   (0x40020000UL)
#define GPIOA ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x0000UL))
#define GPIOB ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x0400UL))
#define GPIOC ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x0800UL))
#define GPIOD ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x0C00UL))
#define GPIOE ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x0100UL))
#define GPIOF ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x0140UL))
#define GPIOG ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x0180UL))
#define GPIOH ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x01C0UL))
#define GPIOI ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x0200UL))
#define GPIOJ ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x0240UL))
#define GPIOK ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x0280UL))

/* RCC base address */
#define RCC   ((RCC_RegDeg_t *) (AHB1_BASEADDR + 0x3800UL))

/* GPIO clock enable */
#define GPIOA_CLK_ENB()      (RCC->AHB1ENR |= 0x01U << 0U)  /* GPIOA peripheral clock enable */
#define GPIOB_CLK_ENB()      (RCC->AHB1ENR |= 0x01U << 1U)  /* GPIOB peripheral clock enable */
#define GPIOC_CLK_ENB()      (RCC->AHB1ENR |= 0x01U << 2U)  /* GPIOC peripheral clock enable */
#define GPIOD_CLK_ENB()      (RCC->AHB1ENR |= 0x01U << 3U)  /* GPIOD peripheral clock enable */
#define GPIOE_CLK_ENB()      (RCC->AHB1ENR |= 0x01U << 4U)  /* GPIOE peripheral clock enable */
#define GPIOF_CLK_ENB()      (RCC->AHB1ENR |= 0x01U << 5U)  /* GPIOF peripheral clock enable */
#define GPIOG_CLK_ENB()      (RCC->AHB1ENR |= 0x01U << 6U)  /* GPIOG peripheral clock enable */
#define GPIOH_CLK_ENB()      (RCC->AHB1ENR |= 0x01U << 7U)  /* GPIOH peripheral clock enable */
#define GPIOI_CLK_ENB()      (RCC->AHB1ENR |= 0x01U << 8U)  /* GPIOI peripheral clock enable */

/* GPIO clock disable */
#define GPIOA_CLK_DIS()      (RCC->AHB1ENR &= ~(0x01U << 0U))   /* GPIOA peripheral clock disable */ 
#define GPIOB_CLK_DIS()      (RCC->AHB1ENR &= ~(0x01U << 1U))   /* GPIOB peripheral clock disable */
#define GPIOC_CLK_DIS()      (RCC->AHB1ENR &= ~(0x01U << 2U))   /* GPIOC peripheral clock disable */
#define GPIOD_CLK_DIS()      (RCC->AHB1ENR &= ~(0x01U << 3U))   /* GPIOD peripheral clock disable */
#define GPIOE_CLK_DIS()      (RCC->AHB1ENR &= ~(0x01U << 4U))   /* GPIOE peripheral clock disable */
#define GPIOF_CLK_DIS()      (RCC->AHB1ENR &= ~(0x01U << 5U))   /* GPIOF peripheral clock disable */
#define GPIOG_CLK_DIS()      (RCC->AHB1ENR &= ~(0x01U << 6U))   /* GPIOG peripheral clock disable */
#define GPIOH_CLK_DIS()      (RCC->AHB1ENR &= ~(0x01U << 7U))   /* GPIOH peripheral clock disable */
#define GPIOI_CLK_DIS()      (RCC->AHB1ENR &= ~(0x01U << 8U))   /* GPIOI peripheral clock disable */

#include "stm32f407xx_gpio_driver.h"
#endif