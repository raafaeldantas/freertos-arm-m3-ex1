/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "conf_board.h"
#include "conf_clock.h"
#include "conf_uart_serial.h"
#include "stdio_serial.h"

void config_uart(void);
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vApplicationMallocFailedHook(void);

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	
	board_init();
	
	config_uart();
	
	const signed char teste1 = "Task 1";
	const signed char teste2 = "Task 2";
	
	/* Insert application code here, after the board has been initialized. */
	xTaskCreate(vTask1, &teste1, 240, NULL, 2, NULL);
	xTaskCreate(vTask2, &teste2, 240, NULL, 2, NULL);
	
	vTaskStartScheduler();
	
	for(;;);
}

void config_uart(void){
	const usart_serial_options_t usart_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY,
		#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
		#endif
		#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
		#endif
	};
	
	/*Config Uart*/
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONSOLE_UART, &usart_options);
}

void vTask1(void *pvParameters){
	while(1){
		printf("Task1 Running\n");
		vTaskDelay( 500 / portTICK_RATE_MS);
	}
}

void vTask2(void *pvParameters){
	while(1){
		printf("Task2 Running\n");
		vTaskDelay( 500 / portTICK_RATE_MS);
	}
}

void vApplicationMallocFailedHook(void){
	for(;;);
}
