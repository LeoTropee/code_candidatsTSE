
/*
 * Cheapeau_Led.h
 *
 *  Created on: 19 janv. 2019
 *      Author: Clement
 */
#include "stm32f7xx_hal.h"

#ifndef APPLICATION_INC_CHAPEAU_LED_H_
#define APPLICATION_INC_CHAPEAU_LED_H_

#define SPIx                             SPI2
#define SPIx_CLK_ENABLE()                __HAL_RCC_SPI2_CLK_ENABLE()
#define DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

#define SPIx_FORCE_RESET()               __HAL_RCC_SPI2_FORCE_RESET()
#define SPIx_RELEASE_RESET()             __HAL_RCC_SPI2_RELEASE_RESET()

/* Definition for SPIx Pins */
#define SPIx_SCK_PIN                     GPIO_PIN_12
#define SPIx_SCK_GPIO_PORT               GPIOA
#define SPIx_SCK_AF                      GPIO_AF5_SPI2
#define SPIx_MISO_PIN                    GPIO_PIN_14
#define SPIx_MISO_GPIO_PORT              GPIOB
#define SPIx_MISO_AF                     GPIO_AF5_SPI2
#define SPIx_MOSI_PIN                    GPIO_PIN_15
#define SPIx_MOSI_GPIO_PORT              GPIOB
#define SPIx_MOSI_AF                     GPIO_AF5_SPI2

/* Definition for SPIx's NVIC */
#define SPIx_IRQn                        SPI2_IRQn
#define SPIx_IRQHandler                  SPI2_IRQHandler

void led_spi_init(SPI_HandleTypeDef *hspi);
void led_start(uint8_t* leds);
void led_stop(uint8_t* leds);
void modify_led(uint8_t* leds, int led_number, uint8_t intensity, uint8_t red, uint8_t green, uint8_t blue);
void all_led_red(uint8_t* leds);
void all_led_blue(uint8_t* leds);
void all_led_green(uint8_t* leds);
void all_led_yellow(uint8_t* leds);


#endif /* APPLICATION_INC_CHAPEAU_LED_H_ */
