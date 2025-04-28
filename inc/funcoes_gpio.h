/**
 * @brief Arquivo Cabeçalho das Funções de Entrada/Saída Digital
 */
#ifndef FUNCOES_GPIO_H
#define FUNCOES_GPIO_H
/***********************  Includes ***********************/
#include "uart.h"
#include <stdio.h>
#include "pinout.h"
#include "ssd1306.h"
#include "matriz_5x5.h"
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "figuras_ws2812.h"
#include "prefixos_uteis.h"

/***********************  Defines ***********************/

/******************* Variáveis Globais *******************/

extern volatile uint8_t func_bot_joy, botao_a_flag;

/******************* Protótipo Funções *******************/

void botoes_callback(uint gpio, uint32_t events);
void botao_B(ssd1306_t *ssd);
void botao_joy(ssd1306_t *ssd);
void som_buz(uint16_t freq, uint16_t duration_ms);

#endif //FUNCOES_GPIO_H