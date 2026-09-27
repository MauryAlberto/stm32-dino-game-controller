#include "stm32f407xx_gpio_driver.h"

/**
 * @brief This funtion initializes the GPIO peripheral according to the specified settings.
 * 
 * @param GPIOx Pointer to the GPIO port to be configured (e.g. GPIOA, GPIOB).
 * @param GPIOPinConf Structure that contains the configuration information of a specified GPIO pin.
 * 
 * @return None
 */
void GPIO_Init(GPIO_RegDef_t *GPIOx, GPIO_PinConf_t GPIOPinConf)
{
    /* Configure the pin mode */
    /* Clear the current pin mode configuration */
    GPIOx->MODER &= ~(0x03U << GPIOPinConf.PinNumber * 2);
    /* Set the current pin mode configuration */
    GPIOx->MODER |= (GPIOPinConf.PinMode << GPIOPinConf.PinNumber * 2);
    if(GPIOPinConf.PinMode == GPIO_MODE_OUTPUT || GPIOPinConf.PinMode == GPIO_MODE_ALT)
    {
        /* Configure the output type */
        GPIOx->OTYPER &= ~(0x01U << GPIOPinConf.PinNumber);
        GPIOx->OTYPER |= (GPIOPinConf.OutType << GPIOPinConf.PinNumber);
        /* Configure the output speed */
        GPIOx->OSPEEDR &= ~(0x02U << GPIOPinConf.PinNumber * 2);
        GPIOx->OSPEEDR |= (GPIOPinConf.OutSpeed << GPIOPinConf.PinNumber * 2);
    }
 
    /* Configure the pull-up/pull-down */
    GPIOx->PUPDR &= ~(0x03U << GPIOPinConf.PinNumber * 2);
    GPIOx->PUPDR |= (GPIOPinConf.PUPD << GPIOPinConf.PinNumber * 2);
    /* Configure the alternate function */
    if(GPIOPinConf.PinMode == GPIO_MODE_ALT) {
        if(GPIOPinConf.PinNumber < 8)
        {
            /* Configure for the alternate function low register */
            GPIOx->AFRL &= ~(0x0FU << GPIOPinConf.PinNumber * 4);
            GPIOx->AFRL |= (GPIOPinConf.AltFun << GPIOPinConf.PinNumber * 4);
        }
        else
        {
            /* Configure for the alternate function high register */
            GPIOx->AFRH &= ~(0x0FU << GPIOPinConf.PinNumber * 4);
            GPIOx->AFRH |= (GPIOPinConf.AltFun << GPIOPinConf.PinNumber * 4);
        }
    }

}

/**
 * @brief This function writes a high or low state to the specified GPIO pin.
 *        The value can be [GPIO_PIN_LOW, GPIO_PIN_HIGH].
 * 
 * @param GPIOx Pointer to the GPIO port to be configured (e.g. GPIOA, GPIOB).
 * @param PinNumber GPIO pin number to be written.
 * @param PinState Specifies the desired pin state.
 *                 - GPIO_PIN_LOW   : Reset the pin to 0
 *                 - GPIO_PIN_HIGH  : Set the pin to 1
 * 
 * @return None
 */
void GPIO_WritePin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber, GPIO_PinState_e PinState)
{
    if(PinState == GPIO_PIN_LOW)
    {
        /* Clear the output pin */
        GPIOx->ODR &= ~(0x01U << PinNumber);
    }
    else
    {
        /* Set the output pin */
        GPIOx->ODR |= (0x01U << PinNumber);
    }
}

/**
 * @brief This function reads the state of the specified GPIO input pin
 * 
 * @param GPIOx Pointer to the GPIO port to be configured (e.g. GPIOA, GPIOB).
 * @param PinNumber GPIO pin number to be written.
 * @return uint8_t Pin state
 *                 - GPIO_PIN_LOW   : if the pin is low
 *                 - GPIO_PIN_HIGH  : if the pin is high
 */
uint8_t GPIO_ReadPin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber)
{
    uint8_t ret;
    /* Read the value of the input pin */
    ret = (GPIOx->IDR >> PinNumber) & 0x01U;
    return ret;
}

/**
 * @brief This function toggles the GPIO pin state.
 *        The function toggles the pin state from HIGH to LOW or LOW to HIGH
 * 
 * @param GPIOx Pointer to the GPIO port to be configured (e.g. GPIOA, GPIOB).
 * @param PinNumber GPIO pin number to be written.
 * 
 * @return None 
 */
void GPIO_TogglePin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber)
{
    GPIOx->ODR ^= (0x01U << PinNumber);
}

/**
 * @brief This function writes a high or low state to a specificed GPIO pin.
 *        The operation can be done separately on an individual bit and not affects other bits.
 * 
 * @param GPIOx Pointer to the GPIO port to be configured (e.g. GPIOA, GPIOB).
 * @param PinNumber GPIO pin number to be written.
 * @param PinState Specifies the desired pin state.
 *                 - GPIO_PIN_LOW   : Reset the pin to 0
 *                 - GPIO_PIN_HIGH  : Set the pin to 1
 * 
 * @return None
 */
void GPIO_WritePinBit(GPIO_RegDef_t *GPIOx, uint8_t PinNumber, GPIO_PinState_e PinState)
{
    if(PinState == GPIO_PIN_LOW)
    {
        /* Reset the pin state to low */
        GPIOx->BSRR |= (0x01U << (PinNumber + 16U));
    }
    else
    {
        /* Set the state to high */
        GPIOx->BSRR |= (0x01U << PinNumber);
    }
}

/**
 * @brief This functions locks the specified GPIO pin configuration.
 * 
 * @param GPIOx Pointer to the GPIO port to be configured (e.g. GPIOA, GPIOB).
 * @param PinNumber GPIO pin number to be written.
 * 
 * @return None
 */
void GPIO_LockPinConf(GPIO_RegDef_t *GPIOx, uint8_t PinNumber)
{
    uint32_t temp1 = (0x01 << 16U);
    uint32_t temp2 = (0x01 << PinNumber);

    temp1 |= temp2;
    /* WR LCKR[16] = ‘1’ + LCKR[15:0] */
    GPIOx->LCKR = temp1;
    /* WR LCKR[16] = ‘0’ + LCKR[15:0] */
    GPIOx->LCKR = temp2;
    /* WR LCKR[16] = ‘1’ + LCKR[15:0] */
    GPIOx->LCKR = temp1;
    /* RD LCKR */
    temp1 = GPIOx->LCKR;
}
