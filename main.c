/**
 * @brief Code to 2-way pipe data between the UART bus and USB Serial,
 * meant to test communcations between ESP-01s and PICO
 * also demonstrates how the two cores' programs will be organized
 * @author Shaqeeb Momen
 */

#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "pico/multicore.h"

// Defining Pin numbers
#define UART0_TX_PIN 0 // GPIO 0
#define UART0_RX_PIN 1 // GPIO 1

// Main function to execute on core 1
void core1_main()
{
    // Initialize UART bus
    uart_init(uart0, 115200); // Make sure this is consistent with the baud setup on the ESP-01s
    // Setting up GPIO pins
    gpio_set_function(UART0_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART0_RX_PIN, GPIO_FUNC_UART);

    // Buffers for data
    char uart_rx; // Incoming through uart buffer
    char uart_tx; // Outgoing through uart buffer

    while (true)
    {
        // NOTE: this is better done asynch with interrupts

        // UART -> USB Serial
        while (uart_is_readable(uart0))
        {
            // Read data from uart
            uart_read_blocking(uart0, &uart_rx, 1);
            printf("%c", uart_rx);
        }

        // USB Serial -> UART
        while (scanf("%c", &uart_tx) != EOF) // While reading from stdio (mapped to the USB port)
        {
            // Print the read value back through 
            uart_putc(uart0, uart_tx);
        }
    }
}

// Main function to execute on core 0
void core0_main()
{
    // Just for demonstration
    while (true)
        ;
}

int main()
{
    multicore_launch_core1(core1_main);
    core0_main();
}
