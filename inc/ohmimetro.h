#ifndef OHMIMETRO_H
#define OHMIMETRO_H


#include "uart.h"
#include "font.h"
#include "math.h"
#include <stdio.h>
#include "pinout.h"
#include "config.h"
#include "ssd1306.h"
#include "matriz_5x5.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "funcoes_gpio.h"
#include "hardware/adc.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "figuras_ws2812.h"
#include "prefixos_uteis.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "figuras_ssd1306.h"
#include "InterfacePio.pio.h"

/***********************  Defines ***********************/

/******************* Variáveis Globais *******************/

extern volatile uint16_t valor_maximo, valor_minimo;

/******************* Protótipo Funções *******************/

void init_sistema(ssd1306_t *ssd);
void calibrar_ohmimtro(ssd1306_t *ssd);
void printar_cores(uint16_t _valor_rx, ssd1306_t *ssd);

#endif //OHMIMETRO_H