#include "stm32f407xx.h"
#include <string.h>

GPIO_PinConf_t Blinky_LED;
GPIO_PinConf_t UserButton;
USART_Conf_t USART3_Conf;
TIM_Base_Conf_t TIM6_Conf;

#define RX_BUFFER_SIZE  8U
#define TX_BUFFER_SIZE  8U
volatile uint8_t ReceivedMsg[RX_BUFFER_SIZE];
volatile uint8_t SentMsg[RX_BUFFER_SIZE] = "J\n";
volatile uint8_t TxMsgSize  = 2U;
volatile uint8_t RxIndex    = 0U;
volatile uint8_t RxData     = 0U;
volatile uint8_t IsRxAvailable      = FALSE;

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

int main(void)
{
    uint16_t Timer6DelayCounter = 0U;

    BlueLED_Init();
    UserButton_Init();
    USART3_Init();
    TIM6_Init();
    TIM6_Start();

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
                /* Check if the received message is "ON" */
                if(strcmp((const char*)ReceivedMsg, "ON") == 0)
                {
                    /* Turn blue LED ON */
                    GPIO_WritePinBit(GPIOD, GPIO_PIN_NUM_15, GPIO_PIN_HIGH);
                }

                /* Check if the received message is "OFF" */
                if(strcmp((const char*)ReceivedMsg, "OFF") == 0)
                {
                    /* Turn blue LED OFF */
                    GPIO_WritePinBit(GPIOD, GPIO_PIN_NUM_15, GPIO_PIN_LOW);
                }

                /* Reset the index */
                RxIndex = 0U;
            }
        }
        
        /* Check if update event generated */
        if(TIM6_UEV_STS() == BIT_SET)
        {
            /* Clear the update event status */
            TIM6_UEV_STS_CLR();
            /* Increase the timer delay counter by 1 */
            Timer6DelayCounter++;
            /* Check if 1 second has elapsed */
            if(Timer6DelayCounter == 1000)
            {
                /* Toggle the blue LED */
                GPIO_TogglePin(GPIOD, GPIO_PIN_NUM_15);
                /* Reset timer 6 delay counter */
                Timer6DelayCounter = 0;
            }
        }
    }

    return 0;
}
void EXTI0_IRQHandler(void)
{
    SimDelay();
    /* Is the corresponding bit in the EXTI_PR register set? */
    if((EXTI->PR >> UserButton.PinNumber) & 0x01U)
    {
        /* Clear the pending bit by writing 1 */
        EXTI->PR |= (0x01U << UserButton.PinNumber);
    }

    /* Transmit data */
    USART_Transmit(USART3, (uint8_t*)SentMsg, TxMsgSize);
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