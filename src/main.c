#include "stm32f407xx.h"
#include <string.h>
#include <stdlib.h>

GPIO_PinConf_t Blinky_LED;
GPIO_PinConf_t UserButton;
USART_Conf_t USART3_Conf;
TIM_Base_Conf_t TIM6_Conf;
TIM_Base_Conf_t TIM4_Conf;
TIM_OC_Conf_t TIM4_OC_Conf;

#define RX_BUFFER_SIZE  8U
#define TX_BUFFER_SIZE  8U
#define BUTTON_DEBOUNCE_TIME    100U
volatile uint8_t ReceivedMsg[RX_BUFFER_SIZE];
volatile uint8_t SentMsg[RX_BUFFER_SIZE] = "J\n";
volatile uint8_t TxMsgSize  = 2U;
volatile uint8_t RxIndex    = 0U;
volatile uint8_t RxData     = 0U;
volatile uint8_t IsRxAvailable = FALSE;
volatile uint8_t Timer6DelayCounter = 0U;

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
    USART3_RXNEIE_ENB();
    NVIC_SetPriority(IRQ_NO_USART3, 0U);
    NVIC_EnableIRQ(IRQ_NO_USART3);
    USART_Init(USART3, USART3_Conf);
}

void TIM6_Init(void)
{
    TIM6_Conf.AutoReloadPreload = ENABLE;
    TIM6_Conf.Period = 999;                 /* 1ms period */
    TIM6_Conf.Prescaler = 15;               /* Counter clock is 1Mhz (with 16 Mhz timer clock) */
    TIM6_CLK_ENB();
    TIM_Base_Init(TIM6, TIM6_Conf);
}

void TIM6_Start(void)
{
    TIM_Base_Start(TIM6);
}

void TIM6_Stop(void)
{
    TIM_Base_Stop(TIM6);
}

void TIM6_IT_Init(void)
{
    uint8_t Priority = 1U;
    TIM_Base_IT_Init(TIM6, Priority);
}

void TIM4_OC_Init(void)
{
    GPIO_PinConf_t OC_Pin;

    OC_Pin.PinMode      = GPIO_MODE_ALT;
    OC_Pin.PUPD         = GPIO_NO_PUPD;
    OC_Pin.OutType      = GPIO_OUTPUT_PP;
    OC_Pin.OutSpeed     = GPIO_SPEED_VERY_HIGH;
    OC_Pin.PinNumber    = GPIO_PIN_NUM_15;
    OC_Pin.AltFun       = GPIO_ALT_AF2;
    GPIOD_CLK_ENB();
    GPIO_Init(GPIOD, OC_Pin);

    TIM4_Conf.AutoReloadPreload = ENABLE;
    TIM4_Conf.Period            = 999;
    TIM4_Conf.Prescaler         = 15;
    TIM4_Conf.CounterMode       = TIM_UPCOUNTING;
    TIM4_CLK_ENB();
    TIM_Base_Init(TIM4, TIM4_Conf);

    TIM4_OC_Conf.OCMode     = TIM_OCMODE_PWM1;
    TIM4_OC_Conf.OCPolarity = TIM_OCPOLARITY_HIGH;
    TIM4_OC_Conf.Pulse      = 0;
    TIM_OC_Init(TIM4, TIM4_OC_Conf, TIM_OC_CHANNEL_4);
}

void TIM4_Start(void)
{
    TIM_Base_Start(TIM4);
}

int main(void)
{
    uint8_t DutyCycle = 0;
    BlueLED_Init();
    UserButton_Init();
    USART3_Init();
    TIM6_Init();
    TIM6_IT_Init();
    TIM4_OC_Init();
    TIM4_Start();

    while(1)
    {
        /* Is new data available? */
        if(IsRxAvailable == TRUE)
        {
            /* Check overflow status and store data */
            if(RxIndex < RX_BUFFER_SIZE)
            {
                /* Store new data to the received message */
                ReceivedMsg[RxIndex] = RxData;
                /* Increase the index */
                RxIndex++;
            }
            else
            {
                RxIndex = 0; /* Overflow recovery */
            }

            /* Reset the Rx data available flag to FALSE */
            IsRxAvailable = FALSE;

            /* Check if the message is fully received */
            if(RxData == '\n')
            {
                /* Null-terminate the string/message */
                ReceivedMsg[RxIndex - 1] = '\0';
                DutyCycle = atoi((const char*) ReceivedMsg);
                /* Set duty cycle for timer 4 pwm channel 4 */
                TIM4_OC_PWM_SET_DUTY(TIM_OC_CHANNEL_4, (TIM4_Conf.Period * DutyCycle) / 100);
                /* Reset the index */
                RxIndex = 0;
            }
        }
        
    }

    return 0;
}

void EXTI0_IRQHandler(void)
{
    /* Start timer 6 */
    TIM6_Start();
    /* Is the corresponding bit in the EXTI_PR register set? */
    if((EXTI->PR >> UserButton.PinNumber) & 0x01U)
    {
        /* Clear the pending bit by writing 1 */
        EXTI->PR |= (0x01U << UserButton.PinNumber);
    }
}

void USART3_IRQHandler(void)
{
    /* Check if the receive register is not empty */
    if((USART3->SR >> USART_SR_RXNE) & 0x01U)
    {
        /* Read the received data */
        RxData = USART3->DR;
        /* Set the RX data available flag to TRUE */
        IsRxAvailable = TRUE;
    }
}

void TIM6_DAC_IRQHandler(void)
{
    /* Check if update event generated */
    if(TIM6_UEV_STS() == BIT_SET)
    {
        /* Clear the update event status */
        TIM6_UEV_STS_CLR();
        /* Increase the timer delay counter by 1 */
        Timer6DelayCounter++;
        /* Check if BUTTON_DEBOUNCE_TIME ms has elapsed */
        if(Timer6DelayCounter == BUTTON_DEBOUNCE_TIME)
        {
            /* Toggle the blue LED */
            USART_Transmit(USART3, (uint8_t*)SentMsg, TxMsgSize);
            /* Reset timer 6 delay counter */
            Timer6DelayCounter = 0;
            /* Stop timer 6 */
            TIM6_Stop();
        }
    }
}