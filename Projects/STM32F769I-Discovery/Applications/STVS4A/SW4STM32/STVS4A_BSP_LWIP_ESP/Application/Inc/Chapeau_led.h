#include <stm32f7xx_hal_gpio.h>
#include <stm32f7xx_hal_spi.h>


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

SPI_HandleTypeDef initSPI(){

		hspi2.Instance               = SPI2;
		hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
		hspi2.Init.Direction         = SPI_DIRECTION_1LINE;
		hspi2.Init.CLKPhase          = SPI_PHASE_1EDGE;
		hspi2.Init.CLKPolarity       = SPI_POLARITY_HIGH;
		hspi2.Init.DataSize          = SPI_DATASIZE_8BIT;
		hspi2.Init.FirstBit          = SPI_FIRSTBIT_MSB;
		hspi2.Init.TIMode            = SPI_TIMODE_DISABLE;
		hspi2.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
		hspi2.Init.CRCPolynomial     = 7;
		hspi2.Init.NSS               = SPI_NSS_SOFT;

		void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
		{
		GPIO_InitTypeDef  GPIO_InitStruct;

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
		}

		HAL_SPI_MspInit(&hspi2);

		hspi2.Init.Mode = SPI_MODE_MASTER;

		HAL_SPI_Init(&hspi2);
		return hspi2;
}


