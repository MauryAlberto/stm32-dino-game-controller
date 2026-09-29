#include "stm32f407xx_usart_driver.h"

uint16_t AHB_PreScaler[8] = {2, 4, 8, 16, 64, 128, 256, 512};
uint16_t APB_PreScaler[4] = {2, 4, 8, 16};

/**
 * @brief This function gets PLL clock frequency.
 *        It is a dummy function and always return 0.
 *        The implementation should be completed when PLL is applied in a project.
 * 
 * @return uint32_t 
 */
uint32_t RCC_GetPLLOutputClock(void)
{
    /* PLL clock is not used in this application */
    return 0;
}

/**
 * @brief This function is used to get APB1 frequency.
 *        Change the value of HSI and HSE with respect to the MCU.
 * 
 * @return uint32_t 
 */
uint32_t RCC_GetPCLK1Val(void)
{
    uint32_t P_Clk1, SYS_Clk;
    uint8_t Clk_Src, temp, AHB_Pre, APB1_Pre;

    /* Clock source in the MCU */
    Clk_Src = (RCC->CFGR >> 2) & 0x03;

    switch(Clk_Src)
    {
        case 0: /* HSI oscillator used as the system clock */
        {
            SYS_Clk = 16000000;
            break;
        }
        case 1: /* HSE oscillator used as the system clock */
        {
            SYS_Clk = 8000000;
            break;
        }
        case 2: /* PLL used as the system clock */
        {
            SYS_Clk = RCC_GetPLLOutputClock();
            break;
        }
        default:    /* Not applicable */
        {
            SYS_Clk = 0;
            break;
        }
    }

    /* Get the AHB PreScaler */
    temp = (RCC->CFGR >> 4) & 0x0F;
    if(temp < 8)
    {
        /* System clock is not divided */
        AHB_Pre = 1;
    }
    else
    {
        /* System clock is divided */
        AHB_Pre = AHB_PreScaler[temp - 8];
    }

    /* Get the APB1 PreScaler */
    temp = (RCC->CFGR >> 10) & 0x07;
    if(temp < 4)
    {
        /* AHB clock is not divided */
        APB1_Pre = 1;
    }
    else
    {
        /* AHB clock is divided */
        APB1_Pre = APB_PreScaler[temp - 4];
    }

    /* Set peripheral clock */
    P_Clk1 = (SYS_Clk / AHB_Pre) / APB1_Pre;

    return P_Clk1;
}

/**
 * @brief This function is used to get APB2 clock frequency.
 *        Change the value of HSI and HSE with respect to the MCU.
 * 
 * @return uint32_t 
 */
uint32_t RCC_GetPCLK2Val(void)
{
    uint32_t P_Clk2, SYS_Clk;
    uint8_t Clk_Src, temp, AHB_Pre, APB2_Pre;

    /* Clock source in the MCU */
    Clk_Src = (RCC->CFGR >> 2) & 0x03;

    switch(Clk_Src)
    {
        case 0: /* HSI oscillator used as the system clock */
        {
            SYS_Clk = 16000000;
            break;
        }
        case 1: /* HSE oscillator used as the system clock */
        {
            SYS_Clk = 8000000;
            break;
        }
        case 2: /* PLL used as the system clock */
        {
            SYS_Clk = RCC_GetPLLOutputClock();
            break;
        }
        default:    /* Not applicable */
        {
            SYS_Clk = 0;
            break;
        }
    }

    /* Get the AHB PreScaler */
    temp = (RCC->CFGR >> 4) & 0x0F;
    if(temp < 8)
    {
        /* System clock is not divided */
        AHB_Pre = 1;
    }
    else
    {
        /* System clock is divided */
        AHB_Pre = AHB_PreScaler[temp - 8];
    }

    /* Get the APB2 PreScaler */
    temp = (RCC->CFGR >> 13) & 0x07;
    if(temp < 4)
    {
        /* AHB clock is not divided */
        APB2_Pre = 1;
    }
    else
    {
        /* AHB clock is divided */
        APB2_Pre = APB_PreScaler[temp - 4];
    }

    /* Set peripheral clock */
    P_Clk2 = (SYS_Clk / AHB_Pre) / APB2_Pre;

    return P_Clk2;
}

/**
 * @brief This function initializes USART peripheral according to the specified settings.
 * 
 * @param USARTx Pointer to the USART port to be configuerd (e.g. USART1, USART2).
 * @param USART_Conf Structure that contains the configuration information of a specified USART.
 *
 * @return None
 */
void USART_Init(USART_Reg_Def_t *USARTx, USART_Conf_t USART_Conf)
{
    uint32_t USARTDIV;
    uint32_t Mantissa, Fraction, Remainder, Scaling;
    uint32_t USARTx_Clk;
    /* Set wordlength in CR1 register */
    USARTx->CR1 &= ~(0x01U << USART_CR1_M);
    USARTx->CR1 |=  (USART_Conf.WordLength << USART_CR1_M);
    /* Set parity in CR1 register */
    USARTx->CR1 &= ~(0x03 << USART_CR1_PS);
    USARTx->CR1 |=  (USART_Conf.Parity << USART_CR1_PS);
    /* Set USART mode in CR1 register */
    USARTx->CR1 &= ~(0x03U << USART_CR1_RE);
    USARTx->CR1 |=  (USART_Conf.Mode << USART_CR1_RE);
    /* Set oversampling in CR1 register */
    USARTx->CR1 &= ~(0x01U << USART_CR1_OVER8);
    USARTx->CR1 |=  (USART_Conf.OverSampling << USART_CR1_OVER8);
    /* Set stop bit in CR2 register */
    USARTx->CR2 &= ~(0x03U << USART_CR2_STOP);
    USARTx->CR2 |=  (USART_Conf.StopBits << USART_CR2_STOP);
    /* Set baudrate in BRR register */
    if(USARTx == USART1 || USARTx == USART6)
    {
        USARTx_Clk = RCC_GetPCLK2Val();
    }
    else
    {
        USARTx_Clk = RCC_GetPCLK1Val();
    }
    Scaling = 8 * (2 - USART_Conf.OverSampling);
    USARTDIV = (USARTx_Clk / (Scaling * USART_Conf.BaudRate));
    Mantissa = USARTDIV;
    Remainder = (USARTx_Clk % (Scaling * USART_Conf.BaudRate));
    Fraction = ((Remainder) + (USART_Conf.BaudRate / 2)) / USART_Conf.BaudRate; /* Round(Fraction) */
    USARTx->BRR &= ~(0x0FFF << USART_DIV_MANTISSA);
    USARTx->BRR &= ~(0x000F << USART_DIV_FRACTION);
    USARTx->BRR |=  (Mantissa << USART_DIV_MANTISSA);
    USARTx->BRR |=  (Fraction << USART_DIV_FRACTION);
    /* Enable the USART peripheral in CR1 register */
    USARTx->CR1 |= (ENABLE << USART_CR1_UE);
}

/**
 * @brief This function is used to transmit data via USART communication.
 * 
 * @note This implementation can only handle Asynchronous transmission.
 * 
 * @param USARTx Pointer to the USART port to be configuerd (e.g. USART1, USART2).
 * @param Msg Pointer to the message that is going to be sent.
 * @param MsgSize The size of the transmitted message.
 * 
 * @return None
 */
void USART_Transmit(USART_Reg_Def_t *USARTx, uint8_t *Msg, uint8_t MsgSize)
{
    uint8_t* pData8bit;
    uint16_t* pData16bit;
    uint8_t TxBufCounter;

    TxBufCounter = MsgSize;
    /* Check the wordlength. If it is 9 bit wordlength, then
       use the 16 bit data pointer to handle the transmission. */
    if((((USARTx->CR1 >> USART_CR1_M) & 0x01U) == USART_WORDLENGTH_9B)\
    && ((USARTx->CR1 >> USART_CR1_PCE) & 0x01U) == USART_PARITY_NONE)
    {
        /* 9 bit word length. No parity control. */
        pData8bit = NULL;
        pData16bit = (uint16_t*) Msg;
    }
    else
    {
        /* 9 bit word length. Parity control enabled */
        /* 8 bit word length. Parity control enabled */
        /* 8 bit word length. No parity control      */
        pData8bit = Msg;
        pData16bit = NULL;
    }

    /* Loop through all characters in the message */
    while(TxBufCounter > 0)
    {
        /* Check if transmit data register empty */
        if(((USARTx->SR >> USART_SR_TXE) & 0x01U) == BIT_SET)
        {
            if(pData8bit == NULL)
            {
                /* Handle 9 bit transmission */
                USARTx->DR = (uint16_t)(*pData16bit & 0x01FF);
                /* Move pointer to the next character */
                pData16bit++;
            }
            else
            {
                /* Handle 8 bit transmission */
                USARTx->DR = (uint8_t)(*pData8bit & 0x00FF);
                /* Move pointer to the next character */
                pData8bit++;
            }

            /* Reduce the buffer counter by 1 */
            TxBufCounter--;
        }
    }
}

/**
 * @brief This function is used to receive data via USART communication.
 * 
 * @note This implementation can only handle Asynchronous reception.
 * 
 * @param USARTx Pointer to the USART port to be configuerd (e.g. USART1, USART2).
 * @param Msg Pointer to the message buffer that is used to store the received message
 * @param MsgSize The size of the receieved message.
 * 
 * @return None
 */
void USART_Receive(USART_Reg_Def_t *USARTx, uint8_t *Msg, uint8_t MsgSize)
{
    uint8_t* pData8bit;
    uint16_t* pData16bit;
    uint8_t RxBufCounter;

    RxBufCounter = MsgSize;
    /* Check the wordlength. If it is 9 bit wordlength, then
       use the 16 bit data pointer to handle the reception. */
    if((((USARTx->CR1 >> USART_CR1_M) & 0x01U) == USART_WORDLENGTH_9B)\
    && ((USARTx->CR1 >> USART_CR1_PCE) & 0x01U) == USART_PARITY_NONE)
    {
        /* 9 bit word length. No parity control. */
        pData8bit = NULL;
        pData16bit = (uint16_t*) Msg;
    }
    else
    {
        /* 9 bit word length. Parity control enabled */
        /* 8 bit word length. Parity control enabled */
        /* 8 bit word length. No parity control      */
        pData8bit = Msg;
        pData16bit = NULL;
    }

    /* Loop through all characters in the message */
    while(RxBufCounter > 0)
    {
        /* Check if read data register not empty */
        if(((USARTx->SR >> USART_SR_RXNE) & 0x01U) == BIT_SET)
        {
            if(pData8bit == NULL)
            {
                /* Handle 9 bit reception */
                *pData16bit = (uint16_t) (USARTx->DR & 0x01FF);
                /* Move pointer to the next character */
                pData16bit++;
            }
            else
            {
                /* Handle 8 bit reception */
                /* Is 9 bit word length OR (8 bit word length AND no parity) */
                if(((USARTx->CR1 >> USART_CR1_M & 0x01U) == USART_WORDLENGTH_9B)\
                || (((USARTx->CR1 >> USART_CR1_M & 0x01U) == USART_WORDLENGTH_8B)\
                && (((USARTx->CR1 >> USART_CR1_PCE) & 0x01U) == USART_PARITY_NONE)))
                {
                    /* Handle 8 bit reception */
                    *pData8bit = (uint8_t) (USARTx->DR & 0x00FF);
                    /* Move pointer to the next buffer */
                    pData8bit++;
                }
                else
                {
                    /* Handle 8 bit reception. Parity control enabled */
                    *pData8bit = (uint8_t) (USARTx->DR & 0x007F);
                    /* Move pointer to the next buffer */
                    pData8bit++;
                }
            }

            /* Reduce the buffer counter by 1 */
            RxBufCounter--;
        }
    }
}
