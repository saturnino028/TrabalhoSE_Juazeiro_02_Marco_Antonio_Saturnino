/**
 * @brief implementa as funções do joystick
 */
#include "config.h"

/************************ Declaração de Variaveis ************************/

/*********************** Implementação das funções **********************/
/**
 * @brief Configura os pinos ADC
 */
void config_adc()
{
    adc_init();
    adc_gpio_init(adc_28); //Inicia o pino ADC 28
    adc_gpio_init(adc_jY);//Inicia pino ADC eixo y
    adc_gpio_init(adc_jX);//Inicia pino ADC eixo x
}

/**
 * @brief inicia os pinos de GPIO
 */
void config_pins_gpio()
{
    //Configuração do botao A
    gpio_init(bot_A);
    gpio_pull_up(bot_A);
    gpio_set_dir(bot_A, GPIO_IN);

    //Configuração do botao B
    gpio_init(bot_B);
    gpio_pull_up(bot_B);
    gpio_set_dir(bot_B, GPIO_IN);

    //Configuração do LED vermelho
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);

    //Configuração do LED verde
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);

    //Configuração do LED azul
    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
}