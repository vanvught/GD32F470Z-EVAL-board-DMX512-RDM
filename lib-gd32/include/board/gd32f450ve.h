/**
 * @file gd32f450ve.h
 *
 */
/* Copyright (C) 2022-2023 by Arjan van Vught mailto:info@gd32-dmx.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef BOARD_GD32F450VE_H_
#define BOARD_GD32F450VE_H_

#if !defined(BOARD_GD32F450VE)
# error This file should not be included
#endif

#if defined (MCU_GD32F450_MCU_H_)
# error This file should be included later
#endif

#include <stdint.h>

/**
 * LEDs bit-banging 595
 */

#define LED595_DATA_GPIO_PINx	GPIO_PIN_2
#define LED595_DATA_RCU_GPIOx	RCU_GPIOE
#define LED595_DATA_GPIOx		GPIOE

#define LED595_CLK_GPIO_PINx	GPIO_PIN_3
#define LED595_CLK_RCU_GPIOx	RCU_GPIOE
#define LED595_CLK_GPIOx		GPIOE

#define LED595_LOAD_GPIO_PINx	GPIO_PIN_4
#define LED595_LOAD_RCU_GPIOx	RCU_GPIOE
#define LED595_LOAD_GPIOx		GPIOE

/**
 * Key
 */

#define KEY_BOOTLOADER_TFTP_RCU_GPIOx	RCU_GPIOD
#define KEY_BOOTLOADER_TFTP_GPIOx		GPIOD
#define KEY_BOOTLOADER_TFTP_GPIO_PINx	GPIO_PIN_3

/**
 * I2C
 */

#define I2C0_REMAP
#define I2C_REMAP			GPIO_I2C0_REMAP
#define I2C_PERIPH			I2C0_PERIPH
#define I2C_RCU_I2Cx		I2C0_RCU_I2C0
#define I2C_GPIO_AFx		I2C0_GPIO_AFx
#define I2C_SCL_RCU_GPIOx	I2C0_SCL_RCU_GPIOx
#define I2C_SCL_GPIOx		I2C0_SCL_GPIOx
#define I2C_SCL_GPIO_PINx	I2C0_SCL_GPIO_PINx
#define I2C_SDA_RCU_GPIOx	I2C0_SDA_RCU_GPIOx
#define I2C_SDA_GPIOx		I2C0_SDA_GPIOx
#define I2C_SDA_GPIO_PINx	I2C0_SDA_GPIO_PINx

/**
 * SPI
 */

#define SPI_PERIPH			SPI2_PERIPH
#define SPI_RCU_SPIx		SPI2_RCU_SPI2
#define SPI_RCU_GPIOx		SPI2_RCU_GPIOx
#define SPI_GPIO_AFx		SPI2_GPIO_AFx
#define SPI_GPIOx			SPI2_GPIOx
#define SPI_SCK_GPIO_PINx	SPI2_SCK_GPIO_PINx
#define SPI_MISO_GPIO_PINx	SPI2_MISO_GPIO_PINx
#define SPI_MOSI_GPIO_PINx	SPI2_MOSI_GPIO_PINx
#define SPI_NSS_GPIOx		SPI2_NSS_GPIOx
#define SPI_NSS_RCU_GPIOx	SPI2_NSS_RCU_GPIOx
#define SPI_NSS_GPIO_PINx	SPI2_NSS_GPIO_PINx
#define SPI_DMAx			SPI2_DMAx
#define SPI_DMA_CHx			SPI2_TX_DMA_CHx
#define SPI_DMA_SUBPERIx	SPI2_TX_DMA_SUBPERIx

/**
 * U(S)ART
 */

#define USART0_REMAP
#define USART1_REMAP
#define USART2_FULL_REMAP

/**
 * Panel LEDs
 */

#ifdef __cplusplus
namespace hal {
namespace panelled {
static constexpr uint32_t PORT_A_TX = (1U << 0);
static constexpr uint32_t PORT_A_RX = (1U << 8);
static constexpr uint32_t SACN		= (1U << 16);
static constexpr uint32_t ARTNET	= (1U << 17);

static constexpr uint32_t ACTIVITY = 0x00FC0000;
//
static constexpr uint32_t INVERTED = ACTIVITY;
}  // namespace panelled
}  // namespace hal
#endif

/**
 * SPI flash
 */

#define SPI_FLASH_CS_RCU_GPIOx	RCU_GPIOE
#define SPI_FLASH_CS_GPIOx		GPIOE
#define SPI_FLASH_CS_GPIO_PINx	GPIO_PIN_6

/**
 * EXT PHY
 */

#define LINK_CHECK_GPIO_CLK				RCU_GPIOB
#define LINK_CHECK_GPIO_PORT			GPIOB
#define LINK_CHECK_GPIO_PIN 			GPIO_PIN_0
#define LINK_CHECK_EXTI_LINE			EXTI_0
#define LINK_CHECK_EXTI_IRQn			EXTI0_IRQn
#define LINK_CHECK_IRQ_HANDLE			EXTI0_IRQHandler

#define LINK_CHECK_EXTI_CLK				RCU_SYSCFG
#define LINK_CHECK_EXTI_PORT_SOURCE		EXTI_SOURCE_GPIOB
#define LINK_CHECK_EXTI_PIN_SOURCE		EXTI_SOURCE_PIN0
#define LINK_CHECK_EXTI_SOURCE_CONFIG	syscfg_exti_line_config
#define LINK_CHECK_GPIO_CONFIG			gpio_mode_set(LINK_CHECK_GPIO_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, LINK_CHECK_GPIO_PIN);

/**
 * MCU and BOARD name
 */

#define GD32_MCU_NAME			"GD32F450VE"
#define GD32_BOARD_NAME			"OCTAL DMX"

#include "mcu/gd32f450_mcu.h"
#include "gd32_gpio.h"

/**
 * ST7789 LCD
 */

#define SPI_LCD_DC_GPIO		GD32_PORT_TO_GPIO(GD32_GPIO_PORTB, 1)
#define SPI_LCD_BL_GPIO		GD32_PORT_TO_GPIO(GD32_GPIO_PORTA, 3)
#if defined(SPI_LCD_HAVE_CS_GPIO)
# define SPI_LCD_CS_GPIO	GD32_PORT_TO_GPIO(GD32_GPIO_PORTE, 5)
#endif

/**
 * FT8xx LCD
 */

#define FT8XX_LCD_DC_GPIO	GD32_PORT_TO_GPIO(GD32_GPIO_PORTB, 1)
#define FT8XX_LCD_CS_GPIO	GD32_PORT_TO_GPIO(GD32_GPIO_PORTE, 5)

#endif /* BOARD_GD32F450VE_H_ */
