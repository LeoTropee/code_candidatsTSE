/*
 * Chapeau_Led.c
 *
 *  Created on: 19 janv. 2019
 *      Author: Clement
 */

#include "../Inc/Chapeau_Led.h"
#include "stm32f7xx_hal.h"
#include "service.h"
#include "platform_init.h"

void led_spi_init(SPI_HandleTypeDef *hspi)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	hspi->Instance = SPI2;
	hspi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
	hspi->Init.Direction         = SPI_DIRECTION_2LINES;
	hspi->Init.CLKPhase          = SPI_PHASE_1EDGE;
	hspi->Init.CLKPolarity       = SPI_POLARITY_LOW;
	hspi->Init.DataSize          = SPI_DATASIZE_8BIT;
	hspi->Init.FirstBit          = SPI_FIRSTBIT_MSB;
	hspi->Init.TIMode            = SPI_TIMODE_DISABLE;
	hspi->Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
	hspi->Init.CRCPolynomial     = 7;
	hspi->Init.NSS               = SPI_NSS_SOFT;

	if (hspi->Instance == SPIx)
	{
		/*##-1- Enable peripherals and GPIO Clocks #################################*/
		/* Enable GPIO TX/RX clock */
		SPIx_SCK_GPIO_CLK_ENABLE();
		SPIx_MISO_GPIO_CLK_ENABLE();
		SPIx_MOSI_GPIO_CLK_ENABLE();
		/* Enable SPI2 clock */
		SPIx_CLK_ENABLE();
		/* Enable DMA clock */
		DMAx_CLK_ENABLE();

		/*##-2- Configure peripheral GPIO ##########################################*/
		/* SPI SCK GPIO pin configuration  */
		GPIO_InitStruct.Pin       = SPIx_SCK_PIN;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_PULLUP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
		GPIO_InitStruct.Alternate = SPIx_SCK_AF;
		HAL_GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);

		/* SPI MISO GPIO pin configuration  */
		GPIO_InitStruct.Pin = SPIx_MISO_PIN;
		GPIO_InitStruct.Alternate = SPIx_MISO_AF;
		HAL_GPIO_Init(SPIx_MISO_GPIO_PORT, &GPIO_InitStruct);

		/* SPI MOSI GPIO pin configuration  */
		GPIO_InitStruct.Pin = SPIx_MOSI_PIN;
		GPIO_InitStruct.Alternate = SPIx_MOSI_AF;
		HAL_GPIO_Init(SPIx_MOSI_GPIO_PORT, &GPIO_InitStruct);

	}

	hspi->Init.Mode = SPI_MODE_MASTER;

	HAL_SPI_Init(hspi);
}

void led_start(uint8_t* leds)
{
	int i = 0;

	leds[i++] = 0x00;
	leds[i++] = 0x00;
	leds[i++] = 0x00;
	leds[i++] = 0x00;
}

void led_stop(uint8_t* leds)
{
	int i = 84;

	leds[i++] = 0xFF;
	leds[i++] = 0xFF;
	leds[i++] = 0xFF;
	leds[i++] = 0xFF;
}

void modify_led(uint8_t* leds, int led_number, uint8_t intensity, uint8_t red, uint8_t green, uint8_t blue)
{
	int i = led_number * 4;

	leds[i++] = 0xE0 + (intensity & 0x1F);
	leds[i++] = blue;
	leds[i++] = green;
	leds[i++] = red;
}


void all_led_red(uint8_t* leds)
{
	led_start(leds);
	for (int i = 1 ; i < 21 ; i++)
	{
		modify_led(leds, i, 0x0A, 0xFF, 0x00, 0x00);
	}
	led_stop(leds);
}

void all_led_green(uint8_t* leds)
{
	led_start(leds);
	for (int i = 1 ; i < 21 ; i++)
	{
		modify_led(leds, i, 0x0A, 0x00, 0xFF, 0x00);
	}
	led_stop(leds);
}

void all_led_blue(uint8_t* leds)
{
	led_start(leds);
	for (int i = 1 ; i < 21 ; i++)
	{
		modify_led(leds, i, 0x0A, 0x00, 0x00, 0xFF);
	}
	led_stop(leds);
}

void all_led_yellow(uint8_t* leds)
{
	led_start(leds);
	for (int i = 1 ; i < 21 ; i++)
	{
		modify_led(leds, i, 0x0A, 0xFF, 0xFF, 0x00);
	}
	led_stop(leds);
}


