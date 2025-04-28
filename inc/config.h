/**
 * @brief arquivo cabeçalho das funções de configuração
 */
#ifndef CONFIG_H
#define CONFIG_H
/***********************  Includes ***********************/
#include <stdio.h>
#include "pinout.h"
#include "ssd1306.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "funcoes_gpio.h"
#include "prefixos_uteis.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

/***********************  Defines ***********************/

/******************* Variáveis Globais *******************/

/******************* Protótipo Funções *******************/

void config_adc();
void config_i2c();
void config_pins_gpio();


#endif //CONFIG_H