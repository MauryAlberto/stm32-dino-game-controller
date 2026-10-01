# STM32 Game Controller

A bare-metal C project for the **STM32F407 Discovery** board featuring register-level GPIO, USART, timer, and NVIC drivers. The board can connect to a compatible PC game over UART: pressing the onboard button triggers a jump, and height feedback from the game controls the blue LED's brightness.

## What I Implemented

- **GPIO driver:** pin configuration, read/write/toggle operations, alternate functions, and external interrupts.
- **USART driver:** baud rate and frame configuration, plus polling transmit and receive functions.
- **Timer driver:** timer initialization, start/stop control, update interrupts, and output compare/PWM configuration.
- **NVIC functions:** interrupt enabling and priority configuration.
- **Application firmware:** button handling, serial message processing, and PWM LED feedback.

The MCU firmware uses direct register access without HAL peripheral APIs or an RTOS.

## How It Works

1. The PA0 user button triggers an external interrupt and starts TIM6.
2. TIM6 counts approximately 100 ms before the firmware transmits `J\n` over USART3.
3. A connected game interprets the message as a jump command.
4. The game returns a jump-height percentage from 0 to 100.
5. The firmware converts that percentage into a PWM duty cycle on PD15, making the blue LED brighten as the character rises.

TIM6 uses 1 ms update interrupts. TIM4 channel 4 generates approximately 1 kHz PWM. Both timings assume a 16 MHz timer clock with `PSC = 15` and `ARR = 999`.

## Hardware

- STM32F407 Discovery board
- USB-to-UART adapter with 3.3 V logic
- USB cable and jumper wires

| Board pin | Connection |
|---|---|
| PA0 | Onboard user button |
| PD15 | Onboard blue LED / TIM4 channel 4 |
| PB10 / USART3 TX | Adapter RX |
| PB11 / USART3 RX | Adapter TX |
| GND | Adapter GND |

Power and flash the board through its USB/ST-LINK connection. Game communication uses the external UART adapter.

## Serial Interface

**9600 baud · 8 data bits · no parity · 1 stop bit · no flow control**

| Direction | Message | Purpose |
|---|---|---|
| Board → game | `J\n` | Jump command |
| Game → board | `0\n` through `100\n` | Height percentage for LED brightness |

`\n` represents an actual newline byte. The receive interrupt passes incoming bytes to the main loop, which assembles newline-terminated messages and updates the PWM output.

## Build and Run

1. Create a Keil uVision project targeting **STM32F407VGTx** with the appropriate device support pack and startup files.
2. Add the C files from `src/` and add `include/` to the compiler include paths. Include one device system initialization source.
3. Keep the 16 MHz HSI clock configuration used by the timer settings.
4. Build and flash through ST-LINK, then wire the UART adapter as shown above.
5. Run a compatible game, select the adapter's serial port at **9600 baud**, and connect.
6. Press the board button to play and watch the LED follow the jump height.

Close other programs using the serial port before connecting the game.

## Lunar Hopper Download

Lunar Hopper is a Python game with a jumping lunar rover, obstacles, and serial support for this controller.

**[Download Lunar Hopper](../../releases/latest/download/Lunar_Hopper.zip)**

Extract the download, open a terminal in its `lunar_hopper` folder, and run with Python 3.10+ and Tkinter installed:

```bash
python -m pip install -r requirements.txt
python lunar_hopper.py
```

Select your serial port, choose **9600**, and click **Connect**. The game also supports Space for keyboard play.

**Lunar Hopper is an AI-generated game written in Python.**

## Source Files

| Location | Contents |
|---|---|
| `src/main.c` | Application initialization, message handling, and interrupt handlers |
| `src/stm32f407xx_gpio_driver.c` | GPIO and external interrupt driver |
| `src/stm32f407xx_usart_driver.c` | USART driver |
| `src/stm32f407xx_timer_driver.c` | Timer and PWM driver |
| `src/cortexM4.c` | NVIC functions |
| `include/` | Register definitions and driver headers |
