#include "stm32f407xx.h"

GPIO_PinConf_t Blinky_LED;
GPIO_PinConf_t UserButton;

void SimDelay(void) {
    uint32_t DelayCount;
    for(DelayCount = 0; DelayCount < 200000; DelayCount++) {
        /* Do nothing */
    }
}

void BlueLED_Init(void)
{
    Blinky_LED.PinNumber    = GPIO_PIN_NUM_15;
    Blinky_LED.PinMode      = GPIO_MODE_OUTPUT;
    Blinky_LED.OutType      = GPIO_OUTPUT_PP;
    Blinky_LED.OutSpeed     = GPIO_SPEED_LOW;
    Blinky_LED.PUPD         = GPIO_NO_PUPD;

    GPIOD_CLK_ENB();
    GPIO_Init(GPIOD, Blinky_LED);
}

void UserButton_Init(void)
{
    UserButton.PinNumber    = GPIO_PIN_NUM_0;
    UserButton.PinMode      = GPIO_MODE_INPUT;
    UserButton.PUPD         = GPIO_NO_PUPD;

    GPIOA_CLK_ENB();
    GPIO_Init(GPIOA, UserButton);
}

int main(void)
{
    /* Initialize the blue LED */
    BlueLED_Init();
    /* Initialize the button */
    UserButton_Init();
    /* Lock the LED configuration */
    GPIO_LockPinConf(GPIOD, GPIO_PIN_NUM_15);

    /* Turn on the blue LED */
    GPIO_WritePinBit(GPIOD, GPIO_PIN_NUM_15, GPIO_PIN_HIGH);
    while(1)
    {
        /* Check the button state */
        if(GPIO_ReadPin(GPIOA, GPIO_PIN_NUM_0) == GPIO_PIN_HIGH)
        {
            /* Delay for some ms */
            SimDelay();
            /* Check the button state */
            if(GPIO_ReadPin(GPIOA, GPIO_PIN_NUM_0) == GPIO_PIN_HIGH)
            {
                /* Change the GPIOD pin number 15 mode from output to input mode */
                Blinky_LED.PinMode = GPIO_MODE_INPUT;
                /* Re-Init the GPIOD pin number 15 */
                GPIO_Init(GPIOD, Blinky_LED);
            }
        }
    }

    return 0;
}