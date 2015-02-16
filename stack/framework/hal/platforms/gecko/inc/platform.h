#ifndef __PLATFORM_H_
#define __PLATFORM_H_

#include "platform_defs.h"

#ifndef PLATFORM_GECKO
    #error Mismatch between the configured platform and the actual platform. Expected PLATFORM_GECKO to be defined
#endif


#include "efm32gg_chip.h"

/********************
 * LED DEFINITIONS *
 *******************/

#define HW_NUM_LEDS 2


//INT_HANDLER


/********************
 * UART DEFINITIONS *
 *******************/

#define UART_BAUDRATE PLATFORM_GECKO_UART_BAUDRATE

#define UART_CHANNEL        UART0
#define UART_CLOCK          cmuClock_UART0
#define UART_ROUTE_LOCATION UART_ROUTE_LOCATION_LOC1

// UART0 location #1: PE0 and PE1
#define UART_PIN_TX         E0           // PE0
#define UART_PIN_RX         E1          // PE1


/********************
 * SPI DEFINITIONS *
 *******************/

/* SPI Channel configuration */
#define SPI_CHANNEL         USART1                      // SPI Channel
#define SPI_BAUDRATE        9600                    // SPI Frequency
#define SPI_CLOCK           cmuClock_USART1             // SPI Clock
#define SPI_ROUTE_LOCATION  USART_ROUTE_LOCATION_LOC1   // SPI GPIO Routing

/* SPI Ports and Pins for the selected route location above.
 * See the datasheet for the availiable routes and corresponding GPIOs */
#define SPI_PIN_MOSI        D0
#define SPI_PIN_MISO        D1
#define SPI_PIN_CLK         D2
#define SPI_PIN_CS          D3

#ifdef SPI_USE_DMA

    /* DMA Channel configuration */
    #define DMA_CHANNEL_TX      0
    #define DMA_CHANNEL_RX      1
    #define DMA_CHANNELS        2
    #define DMA_REQ_RX          DMAREQ_USART1_RXDATAV
    #define DMA_REQ_TX          DMAREQ_USART1_TXBL
#endif

/*************************
 * DEBUG PIN DEFINITIONS *
 ************************/

#define DEBUG_PIN_NUM 4
#define DEBUG0	D4
#define DEBUG1	D5
#define DEBUG2	D6
#define DEBUG3	D7

/**************************
 * USERBUTTON DEFINITIONS *
 *************************/

#define NUM_USERBUTTONS 	2
#define BUTTON0				B9
#define BUTTON1				B10


#endif
