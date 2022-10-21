/**
 * @brief Code to 2-way pipe data between the UART bus and USB Serial,
 * meant to test communcations between ESP-01s and PICO
 * also demonstrates how the two cores' programs will be organized
 * @author Shaqeeb Momen
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "pico/multicore.h"

#define UART0_TX_PIN 0
#define UART0_RX_PIN 1

// Main function to execute on core 1
void core1_main()
{

    uart_init(uart0, 115200); // Make sure this is consistent with the baud setup on the ESP-01s

    // Setting up GPIO pins
    gpio_set_function(UART0_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART0_RX_PIN, GPIO_FUNC_UART);
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    // Wait till usb connects
    while (!stdio_usb_connected())
        ;
    gpio_put(PICO_DEFAULT_LED_PIN, 1); // Trigger a status LED
    printf("started\n");

    // Buffers for data
    char uart_rx; // Incoming through uart buffer
    char uart_tx; // Outgoing through uart buffer
    printf("Core1 launch\n");

    while (true)
    {
        // NOTE: this is better done asynch with interrupts

        // UART -> USB Serial
        while (uart_is_readable(uart0))
        {
            // Read data from uart
            uart_read_blocking(uart0, &uart_rx, 1);
            printf("Received: %c from esp01\n", uart_rx);
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

    // Initialize UART bus
    stdio_usb_init();
    // ^That needs to happen on core0 it looks like, even if we actually print from core1
    multicore_launch_core1(core1_main); // Starts up the other core
    core0_main();
}
