/**
 * @file gd32f450ve-wing.h
 *
 */
/* Copyright (C) 2024 by Arjan van Vught mailto:info@gd32-dmx.org */

#ifndef BOARD_GD32F450VE_WING_H_
#define BOARD_GD32F450VE_WING_H_

#if !defined(BOARD_GD32F450VE)
# error This file should not be included
#endif

#if defined (MCU_GD32F450_MCU_H_)
# error This file should be included later
#endif

#include <stdint.h>

/**
 * I2C
 */

#define I2C0_REMAP
#define I2C_REMAP						GPIO_I2C0_REMAP
#define I2C_PERIPH						I2C0_PERIPH
#define I2C_RCU_I2Cx					I2C0_RCU_I2C0
#define I2C_GPIO_AFx					I2C0_GPIO_AFx
#define I2C_SCL_RCU_GPIOx				I2C0_SCL_RCU_GPIOx
#define I2C_SCL_GPIOx					I2C0_SCL_GPIOx
#define I2C_SCL_GPIO_PINx				I2C0_SCL_GPIO_PINx
#define I2C_SDA_RCU_GPIOx				I2C0_SDA_RCU_GPIOx
#define I2C_SDA_GPIOx					I2C0_SDA_GPIOx
#define I2C_SDA_GPIO_PINx				I2C0_SDA_GPIO_PINx

/**
 * I2C1
 */

#define I2C1_PERIPH						I2C1
#define I2C1_RCU_I2C1					RCU_I2C1
#define I2C1_GPIO_AFx					GPIO_AF_4
#define I2C1_SCL_RCU_GPIOx				RCU_GPIOB
#define I2C1_SCL_GPIOx					GPIOB
#define I2C1_SCL_GPIO_PINx				GPIO_PIN_10
#define I2C1_SDA_RCU_GPIOx				RCU_GPIOC
#define I2C1_SDA_GPIOx					GPIOC
#define I2C1_SDA_GPIO_PINx				GPIO_PIN_12

/**
 * SPI FLASH bitbang
 */

#define SPI_BITBANG_SCK_RCU_GPIOx		RCU_GPIOC
#define SPI_BITBANG_SCK_GPIOx			GPIOC
#define SPI_BITBANG_SCK_GPIO_PINx		GPIO_PIN_14
#define SPI_BITBANG_MISO_RCU_GPIOx		RCU_GPIOE
#define SPI_BITBANG_MISO_GPIOx			GPIOE
#define SPI_BITBANG_MISO_GPIO_PINx		GPIO_PIN_3
#define SPI_BITBANG_MOSI_RCU_GPIOx		RCU_GPIOC
#define SPI_BITBANG_MOSI_GPIOx			GPIOC
#define SPI_BITBANG_MOSI_GPIO_PINx		GPIO_PIN_15

#define SPI_BITBANG_FLASH_CS_GPIOx		GPIOE
#define SPI_BITBANG_FLASH_CS_GPIO_PINx	GPIO_PIN_2

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
#define GD32_BOARD_NAME			"USB-MiniWing"

#include "mcu/gd32f450_mcu.h"
#include "gd32_gpio.h"

/*
 * DEBUG
 */

#define LED_BLINK_GPIO_CLK	RCU_GPIOA
#define LED_BLINK_GPIO_PORT GPIOA
#define LED_BLINK_PIN       GPIO_PIN_3


/**
 * ST7735S LCD
 */

#define SPI_LCD_DC_GPIO		GD32_PORT_TO_GPIO(GD32_GPIO_PORTD, 7) // LCD_RS
#define SPI_LCD_BL_GPIO		GD32_PORT_TO_GPIO(GD32_GPIO_PORTA, 4) // Dummy
#if defined(SPI_LCD_HAVE_CS_GPIO)
# define SPI_LCD_CS_GPIO	GD32_PORT_TO_GPIO(GD32_GPIO_PORTD, 0) //
#endif
#define SPI_LCD_RST_GPIO	GD32_PORT_TO_GPIO(GD32_GPIO_PORTD, 4) //

#endif /* BOARD_GD32F450VE_WING_H_ */
