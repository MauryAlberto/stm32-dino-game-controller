#ifndef STM32F407XX_GPIO_DRIVER_H
#define STM32F407XX_GPIO_DRIVER_H
#include "stm32f407xx.h"

/* GPIO pin configuration struct */
typedef struct
{
    uint8_t PinNumber; /* The GPIO pin to be configured */
    uint8_t PinMode;   /* Specifies the operating mode of the selected pin */
    uint8_t OutType;   /* Specifies the output type */
    uint8_t OutSpeed;  /* Specifies the output speed */
    uint8_t PUPD;      /* Specifies the pull-up/pull-down activation for the selected pin */
    uint8_t AltFun;    /* Specifies the peripheral to be connected to the pin */
} GPIO_PinConf_t;

/* GPIO pin state */
typedef enum
{
    GPIO_PIN_LOW = 0,
    GPIO_PIN_HIGH
} GPIO_PinState_e;

/* GPIO pin number*/
#define GPIO_PIN_NUM_0          0U
#define GPIO_PIN_NUM_1          1U
#define GPIO_PIN_NUM_2          2U
#define GPIO_PIN_NUM_3          3U
#define GPIO_PIN_NUM_4          4U
#define GPIO_PIN_NUM_5          5U
#define GPIO_PIN_NUM_6          6U
#define GPIO_PIN_NUM_7          7U
#define GPIO_PIN_NUM_8          8U
#define GPIO_PIN_NUM_9          9U
#define GPIO_PIN_NUM_10         10U
#define GPIO_PIN_NUM_11         11U
#define GPIO_PIN_NUM_12         12U
#define GPIO_PIN_NUM_13         13U
#define GPIO_PIN_NUM_14         14U
#define GPIO_PIN_NUM_15         15U

/* GPIO pin mode*/
#define GPIO_MODE_INPUT         0U
#define GPIO_MODE_OUTPUT        1U
#define GPIO_MODE_ALT           2U
#define GPIO_MODE_ANALOG        3U

/* GPIO output type */
#define GPIO_OUTPUT_PP          0U
#define GPIO_OUTPUT_OD          1U

/* GPIO output speed */
#define GPIO_SPEED_LOW          0U
#define GPIO_SPEED_MEDIUM       1U
#define GPIO_SPEED_HIGH         2U
#define GPIO_SPEED_VERY_HIGH    3U

/* GPIO pull-up/pull-down */
#define GPIO_NO_PUPD            0U
#define GPIO_PU                 1U
#define GPIO_PD                 2U

/* GPIO alternate function */
#define GPIO_ALT_AF0            0U
#define GPIO_ALT_AF1            1U
#define GPIO_ALT_AF2            2U
#define GPIO_ALT_AF3            3U
#define GPIO_ALT_AF4            4U
#define GPIO_ALT_AF5            5U
#define GPIO_ALT_AF6            6U
#define GPIO_ALT_AF7            7U
#define GPIO_ALT_AF8            8U
#define GPIO_ALT_AF9            9U
#define GPIO_ALT_AF10           10U
#define GPIO_ALT_AF11           11U
#define GPIO_ALT_AF12           12U
#define GPIO_ALT_AF13           13U
#define GPIO_ALT_AF14           14U
#define GPIO_ALT_AF15           15U

void GPIO_Init(GPIO_RegDef_t* GPIOx, GPIO_PinConf_t GPIOPinConf);
void GPIO_WritePin(GPIO_RegDef_t* GPIOx, uint8_t PinNumber, GPIO_PinState_e PinState);
uint8_t GPIO_ReadPin(GPIO_RegDef_t* GPIOx, uint8_t PinNumber);
void GPIO_TogglePin(GPIO_RegDef_t* GPIOx, uint8_t PinNumber);

#endif