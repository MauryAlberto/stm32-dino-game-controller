#include "stm32f407xx.h"
#include <string.h>

GPIO_PinConf_t Blinky_LED;
GPIO_PinConf_t UserButton;
USART_Conf_t USART3_Conf;

void SimDelay(void) {
    uint32_t DelayCount;
    for(DelayCount = 0; DelayCount < 50000; DelayCount++) {
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
    UserButton.EdgeTrigger  = GPIO_IT_EDGE_RT;

    GPIOA_CLK_ENB();
    GPIO_Init(GPIOA, UserButton);
    GPIO_IT_Init(GPIOA, UserButton, 1);
}

void USART3_Init(void)
{
    GPIO_PinConf_t USART_Pin;
    /* GPIO - USART pin configuration
    Configure GPIO (GPIOB pin10/Tx and pin11/Rx) pin to use in alternate function mode (USART3) */
    USART_Pin.PinMode   = GPIO_MODE_ALT;
    USART_Pin.PUPD      = GPIO_NO_PUPD;
    USART_Pin.OutType   = GPIO_OUTPUT_PP;
    USART_Pin.OutSpeed  = GPIO_SPEED_VERY_HIGH;
    USART_Pin.AltFun    = GPIO_ALT_AF7;
    GPIOB_CLK_ENB();
    USART_Pin.PinNumber = GPIO_PIN_NUM_10; /* Tx pin */
    GPIO_Init(GPIOB, USART_Pin);
    USART_Pin.PinNumber = GPIO_PIN_NUM_11; /* Rx pin */
    GPIO_Init(GPIOB, USART_Pin);

    /* USART3 configuration */
    USART3_Conf.Mode            = USART_MODE_TX_RX;         /* Transmit and receive mode */
    USART3_Conf.Parity          = USART_PARITY_NONE;        /* No parity control */
    USART3_Conf.StopBits        = USART_STOPBITS_1;         /* 1 stop bit */
    USART3_Conf.WordLength      = USART_WORDLENGTH_8B;      /* 8 bit word length */
    USART3_Conf.OverSampling    = USART_OVERSAMPLING_16;    /* Oversampling by 16 */
    USART3_Conf.BaudRate        = USART_BAUDRATE_9600;      /* Baudrate of 9600 */
    USART3_CLK_ENB();
    USART_Init(USART3, USART3_Conf);
}

int main(void)
{
    uint8_t ReceivedMsg[4] = {0};
    uint8_t ReceivedMsgSize = 3U;
    BlueLED_Init();
    UserButton_Init();
    USART3_Init();

    while(1)
    {
        /* Receive message */
        USART_Receive(USART3, ReceivedMsg, ReceivedMsgSize);
        /* Echo back the received message */
        USART_Transmit(USART3, ReceivedMsg, ReceivedMsgSize);
        /* Check if the recieved messaged is "ON_"*/
        if(strcmp((const char*)ReceivedMsg, "ON_") == 0)
        {
            /* Turn blue LED on */
            GPIO_WritePinBit(GPIOD, GPIO_PIN_NUM_15, GPIO_PIN_HIGH);
        }
        /* Check if th received message is "OFF" */
        if(strcmp((const char*)ReceivedMsg, "OFF") == 0)
        {
            /* Turn blue LED oFF */
            GPIO_WritePinBit(GPIOD, GPIO_PIN_NUM_15, GPIO_PIN_LOW);
        }
    }

    return 0;
}
void EXTI0_IRQHandler(void)
{
    EXTI->PR &= 0x01;
}