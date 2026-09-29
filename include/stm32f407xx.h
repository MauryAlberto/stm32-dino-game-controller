#ifndef STM32F407XX_H
#define STM32F407XX_H
#include <stdint.h>
#include "cortexM4.h"

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

/* SYSCFG register definition struct */
typedef struct
{
    volatile uint32_t MEMRMP;
    volatile uint32_t PMC;
    volatile uint32_t EXTICR[4];
    volatile uint32_t CMPCR;
} SYSCFG_RegDef_t;

/* EXTI register definition struct */
typedef struct
{
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
} EXTI_RegDef_t;

/* USART register definition struct */
typedef struct 
{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_Reg_Def_t;


/* Peripheral base addresses */
/* AHB1 base address */
#define AHB1_BASEADDR   (0x40020000UL)

/* APB1 base address */
#define APB1_BASEADDR   (0x40000000UL)

/* APB2 base address */
#define APB2_BASEADDR   (0x40010000UL)

/* GPIO base addresses */
#define GPIOA ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x0000UL))     /* GPIOA base address */
#define GPIOB ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x0400UL))     /* GPIOB base address */     
#define GPIOC ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x0800UL))     /* GPIOC base address */
#define GPIOD ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x0C00UL))     /* GPIOD base address */
#define GPIOE ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x1000UL))     /* GPIOE base address */
#define GPIOF ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x1400UL))     /* GPIOF base address */
#define GPIOG ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x1800UL))     /* GPIOG base address */
#define GPIOH ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x1C00UL))     /* GPIOH base address */
#define GPIOI ((GPIO_RegDef_t*) (AHB1_BASEADDR + 0x2000UL))     /* GPIOI base address */

/* USART/UART base addresses */
#define USART1  ((USART_Reg_Def_t*) (APB2_BASEADDR + 0x1000UL)) /* USART1 base address */
#define USART2  ((USART_Reg_Def_t*) (APB1_BASEADDR + 0x4400UL)) /* USART2 base address */
#define USART3  ((USART_Reg_Def_t*) (APB1_BASEADDR + 0x4800UL)) /* USART3 base address */ 
#define UART4   ((USART_Reg_Def_t*) (APB1_BASEADDR + 0x4C00UL)) /* UART4  base address */
#define UART5   ((USART_Reg_Def_t*) (APB1_BASEADDR + 0x5000UL)) /* UART5  base address */
#define USART6  ((USART_Reg_Def_t*) (APB2_BASEADDR + 0x1400UL)) /* USART6 base address */

/* RCC base address */
#define RCC   ((RCC_RegDeg_t *) (AHB1_BASEADDR + 0x3800UL))

/* SYSCFG base address */
#define SYSCFG ((SYSCFG_RegDef_t*) (APB2_BASEADDR + 0x3800UL))

/* EXTI base address */
#define EXTI ((EXTI_RegDef_t*) (APB2_BASEADDR + 0x3C00UL))

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

/* USART/UART clock enable */
#define USART1_CLK_ENB()    (RCC->APB2ENR |= 0x01U << 4)    /* USART1 peripheral clock enable */
#define USART2_CLK_ENB()    (RCC->APB1ENR |= 0x01U << 17)   /* USART2 peripheral clock enable */
#define USART3_CLK_ENB()    (RCC->APB1ENR |= 0x01U << 18)   /* USART3 peripheral clock enable */
#define UART4_CLK_ENB()     (RCC->APB1ENR |= 0x01U << 19)   /* UART4  peripheral clock enable */
#define UART5_CLK_ENB()     (RCC->APB1ENR |= 0x01U << 20)   /* UART5  peripheral clock enable */
#define USART6_CLK_ENB()    (RCC->APB2ENR |= 0x01U << 5)    /* USART6 peripheral clock enable */

/* SYSCFG clock enable */
#define SYSCFG_CLK_ENB()     (RCC->APB2ENR |= (0x01U << 14U)) /* SYSCFG peripheral clock enable */

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

/* USART/UART clock disable */
#define USART1_CLK_DIS()    (RCC->APB2ENR &= ~(0x01U << 4))    /* USART1 peripheral clock disable */
#define USART2_CLK_DIS()    (RCC->APB1ENR &= ~(0x01U << 17))   /* USART2 peripheral clock disable */
#define USART3_CLK_DIS()    (RCC->APB1ENR &= ~(0x01U << 18))   /* USART3 peripheral clock disable */
#define UART4_CLK_DIS()     (RCC->APB1ENR &= ~(0x01U << 19))   /* UART4  peripheral clock disable */
#define UART5_CLK_DIS()     (RCC->APB1ENR &= ~(0x01U << 20))   /* UART5  peripheral clock disable */
#define USART6_CLK_DIS()    (RCC->APB2ENR &= ~(0x01U << 5))    /* USART6 peripheral clock disable */

/* SYSCFG clock disable */
#define SYSCFG_CLK_DIS()     (RCC->APB2ENR &= ~(0x01U << 14U)) /* SYSCFG peripheral clock disable */

/* Common used macros */
#define DISABLE     0U
#define ENABLE      1U
#define BIT_RESET   0U
#define BIT_SET     1U

#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_usart_driver.h"
#endif