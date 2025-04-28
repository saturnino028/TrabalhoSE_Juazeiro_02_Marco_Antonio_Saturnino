/**
 * @brief Arquivo de implementação das funções de entrada/saida digital
 */
#include "funcoes_gpio.h"
volatile uint32_t passado = 0; //Usada para implementar o debouncing
volatile uint8_t func_bot_joy = 0, 
botao_a_flag = 0; //determina a função que será executada pelo Joystick
volatile bool control = true;

/**
 * @brief trata a interrupção gerada pelos botões A e B da BitDog
 * @param gpio recebe o pino que gerou a interrupção
 * @param events recebe o evento que causou a interrupção
 */
void botoes_callback(uint gpio, uint32_t events)
{
    printf("Interrupcao");
    // Obtém o tempo atual em microssegundos
    uint32_t agora = to_us_since_boot(get_absolute_time());
    // Verifica se passou tempo suficiente desde o último evento
    if (agora - passado > 500000) // 500 ms de debouncing
    {
        passado  = agora;
        if(gpio == bot_A)
            botao_a_flag = 1;
        else if(gpio == bot_B)
            modo_gravacao();
    }
}

void som_buz(uint16_t freq, uint16_t duration_ms)
{
    uint period = 1000000 / freq;  // Período do sinal em microssegundos
    uint cycles = (duration_ms * 1000) / period;  // Número de ciclos a gerar

    //Configuração do Buzzer A
    gpio_init(buz_A);
    gpio_set_dir(buz_A, GPIO_OUT);

    for (uint i = 0; i < cycles; i++) 
    {
        gpio_put(buz_A, 1);  // Liga o buzzer
        sleep_us(period / 2);  // Espera metade do período
        gpio_put(buz_A, 0);  // Desliga o buzzer
        sleep_us(period / 2);  // Espera metade do período
    }

}