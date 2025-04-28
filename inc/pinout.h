/**
 * @brief Arquivo com a configuração dos pinos
 */
#ifndef PINOUT_H
#define PINOUT_H

/***********************  Includes ***********************/
#include <stdio.h>
#include "pico/stdlib.h"

/***********************  Defines ***********************/
#define bot_A       5 //Botão A
#define bot_B       6 //Botão B
#define mat_pin     7 //Matriz de LEDs
#define buz_B       10 //Buzzer B
#define LED_G       11 //LED verde
#define LED_B       12 //LED azul
#define LED_R       13 //LED vermelho
#define I2C1_SDA    14 //SDA Display
#define I2C1_SCL    15 //SCL Display
#define buz_A       21 //Buzzer A
#define bot_joy     22 //Botão Joystick
#define adc_jY      26 //Eixo Y do Joystick
#define adc_jX      27 //Eixo X do Joystick
#define adc_28      28 //ADC conectado ao pino 28

/******************* Variáveis Globais *******************/

/******************* Protótipo Funções *******************/

#endif //PINOUT_H