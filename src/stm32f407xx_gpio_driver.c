#include "stm32f407xx_gpio_driver.h"

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

uint8_t GPIO_ReadPin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber)
{
    uint8_t ret;
    /* Read the value of the input pin */
    ret = (GPIOx->IDR >> PinNumber) & 0x01U;
    return ret;
}

void GPIO_TogglePin(GPIO_RegDef_t *GPIOx, uint8_t PinNumber)
{
    GPIOx->ODR ^= (0x01U << PinNumber);
}

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
