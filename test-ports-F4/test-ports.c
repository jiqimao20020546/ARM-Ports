/* STM32F1 test of digital output ports

Ports are all set as outputs and pulsed to provide identification of pin
or soldering failure.

The ports alternate are set to inputs and the remaining outputs are pulsed with
a short pulse. The inputs should then show a single pulse while the outputs will
show a pulse followed by a shorter pulse. If a short exists between adjacent
pins then the input pin will show an apparent extra pulse.

This is based on the LQFP64 version of the STM32Fxxx pinout as used on the
STAMP board.

Initially tested with the ET-ARM-STAMP (STM32F103RET6).

Copyright K. Sarkies <ksarkies@internode.on.net>

10 February 2018
*/

/*
 * Copyright 2018 K. Sarkies <ksarkies@internode.on.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <stdint.h>
#include <stdbool.h>

/* Prototypes */

static void gpio_setup_outputs(void);
static void clock_setup(void);
static void delay(uint32_t period);

/* Globals */

/*--------------------------------------------------------------------------*/

int main(void)
{
    clock_setup();

    while (1)
    {
/* Start sequence by turning all on then all off.
PA10 is not exercised as it is connected to the receive output of the serial
device. It is always set as input and will always show high during the test. */
        gpio_setup_outputs();
        gpio_set(GPIOA,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7 |
            GPIO8 | GPIO9 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
        gpio_set(GPIOB,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7 |
            GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
        gpio_set(GPIOC,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7 |
            GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13);
        gpio_set(GPIOD,
            GPIO2);
        delay(3200000);
        gpio_clear(GPIOA,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7 |
            GPIO8 | GPIO9 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
        gpio_clear(GPIOB,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7 |
            GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
        gpio_clear(GPIOC,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7 |
            GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13);
        gpio_clear(GPIOD,
            GPIO2);
        delay(1600000);
    }

    return 0;
}

/*--------------------------------------------------------------------------*/
/** @brief Delay

*/

void delay(uint32_t period)
{
    uint32_t i;
    for (i = 0; i < period; i++)        /* Wait a bit. */
        __asm__("nop");
}

/*--------------------------------------------------------------------------*/
/** @brief Clock Setup

The processor system clock is established and the necessary peripheral
clocks are turned on.
*/

void clock_setup(void)
{
//    rcc_clock_setup_in_hse_8mhz_out_72mhz();
/* Enable all GPIO clocks. */
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_GPIOD);

}

/*--------------------------------------------------------------------------*/
/** @brief GPIO Setup Outputs

Setup all available GPIO Ports A, B, C, D as outputs.
*/

void gpio_setup_outputs(void)
{
    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7 |
            GPIO8 | GPIO9 |GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
    gpio_clear(GPIOA,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7 |
            GPIO8 | GPIO9 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);

    gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7 |
            GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);
    gpio_clear(GPIOB,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7 |
            GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15);

    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7 |
            GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13);
    gpio_clear(GPIOC,
            GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4 | GPIO5 | GPIO6 | GPIO7 |
            GPIO8 | GPIO9 | GPIO10 | GPIO11 | GPIO12 | GPIO13);

    gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
            GPIO2);
    gpio_clear(GPIOD, GPIO2);
}


