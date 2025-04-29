#include "ohmimetro.h"

/************************ Declaração de Variaveis ************************/

volatile uint16_t valor_maximo = 4095, valor_minimo = 0;

/*********************** Implementação das funções **********************/

/**
 * @brief função para iniciar o sistema
 */
void init_sistema(ssd1306_t *ssd)
{
    bool cor = true;    //Estado LEDs display
    set_sys_clock_khz(125*MHz,false); //Cofigura o clock
    stdio_init_all();
    config_pins_gpio(); //Inicia os pinos GPIO
    init_matriz(); //Inicia a matriz de LEDs 5x5 WS2812
    config_i2c_display(ssd); //Inicia o I2C para o diplay
    config_adc();

    gpio_set_irq_enabled_with_callback(bot_B, GPIO_IRQ_EDGE_FALL, true, botoes_callback); //Interrupção botão B

    ssd1306_fill(ssd, !cor); // Limpa o display
    ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
    ssd1306_draw_string(ssd, "  EMBARCATECH", 5, 15); // Desenha uma string
    ssd1306_draw_string(ssd, "RESTIC 37", 26, 29); // Desenha uma string  
    ssd1306_draw_string(ssd, "  FASE 2", 26, 43); // Desenha uma string      
    ssd1306_send_data(ssd); // Atualiza o display

    sleep_ms(2000);
    ssd1306_fill(ssd, !cor); // Limpa o display
    ssd1306_draw_image(ssd, fig_principal);     
    ssd1306_send_data(ssd); // Atualiza o display

    sleep_ms(2000);

    gpio_set_irq_enabled_with_callback(bot_A, GPIO_IRQ_EDGE_FALL, true, botoes_callback);
}

/**
 * @brief função para executar a rotina de calibração
 */
void rotina_de_calibracao(ssd1306_t *ssd)
{
    bool cor = true, aux = 0; //Estado LEDs display
    uint16_t delay_telas = 3500;
    uint32_t soma = 0;
    uint16_t media = 0;
    char str_x[5]; // Buffer para armazenar a string

    ssd1306_fill(ssd, !cor); // Limpa o display
    ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
    ssd1306_draw_string(ssd, "    ATENCAO", 4, 15); // Desenha uma string
    ssd1306_draw_string(ssd, "  PROCESSO DE", 4, 29); // Desenha uma string  
    ssd1306_draw_string(ssd, "  CALIBRACAO", 4, 43); // Desenha uma string      
    ssd1306_send_data(ssd); // Atualiza o display
    sleep_ms(2000);

    //Calibrar valor máximo
    while(!botao_a_flag)
    {
        if(!aux)
        {
            ssd1306_fill(ssd, !cor); // Limpa o display
            ssd1306_draw_string(ssd, "Conecte um cabo", 4, 15); // Desenha uma string
            ssd1306_draw_string(ssd, "do pino 28 ao", 4, 29); // Desenha uma string  
            ssd1306_draw_string(ssd, "pino 3V3", 4, 43); // Desenha uma string      
            ssd1306_send_data(ssd); // Atualiza o display
        }
        else
        {
            ssd1306_fill(ssd, !cor); // Limpa o display
            ssd1306_draw_string(ssd, "  Feito isso", 4, 15); // Desenha uma string
            ssd1306_draw_string(ssd, "aperte o botao", 4, 29); // Desenha uma string  
            ssd1306_draw_string(ssd, "       A", 4, 43); // Desenha uma string      
            ssd1306_send_data(ssd); // Atualiza o display
        }
        sleep_ms(delay_telas);
        aux = !aux;
    }
    aux = 0, botao_a_flag = 0, soma = 0;
    while(!botao_a_flag)
    {
        adc_select_input(2); // Seleciona o ADC para eixo X. O pino 28 como entrada analógica
        soma = 0;
        for (int i = 0; i < 500; i++)
        {
            soma += adc_read();
            sleep_ms(1);
        }
        media = soma / 500;
        sprintf(str_x, "%d", media); // Converte o inteiro em string
    
        if(!aux)
        {
            ssd1306_fill(ssd, !cor); // Limpa o display
            ssd1306_draw_string(ssd, "Se val. proximo", 4, 15); // Desenha uma string
            ssd1306_draw_string(ssd, "de 4095 tecle", 4, 29); // Desenha uma string 
            ssd1306_draw_string(ssd, "       A", 4, 43); // Desenha uma string        
            ssd1306_send_data(ssd); // Atualiza o display
        }
        else
        {
    
            ssd1306_fill(ssd, !cor); // Limpa o display
            ssd1306_draw_string(ssd, "Valor medido", 4, 15); // Desenha uma string
            ssd1306_draw_string(ssd,     str_x, 4, 29); // Desenha uma string  
            ssd1306_send_data(ssd); // Atualiza o display
        }
        sleep_ms(delay_telas-500);
        aux = !aux;
    }
    valor_maximo = media;

    //Calibrar valor minimo
    aux = 0, botao_a_flag = 0;
    while(!botao_a_flag)
    {
        if(!aux)
        {
            ssd1306_fill(ssd, !cor); // Limpa o display
            ssd1306_draw_string(ssd, "Agora conecte o", 4, 15); // Desenha uma string
            ssd1306_draw_string(ssd, "cabo ao GND", 4, 29); // Desenha uma string   
            ssd1306_send_data(ssd); // Atualiza o display
        }
        else
        {
            ssd1306_fill(ssd, !cor); // Limpa o display
            ssd1306_draw_string(ssd, "  Feito isso", 4, 15); // Desenha uma string
            ssd1306_draw_string(ssd, "aperte o botao", 4, 29); // Desenha uma string  
            ssd1306_draw_string(ssd, "       A", 4, 43); // Desenha uma string      
            ssd1306_send_data(ssd); // Atualiza o display
        }
        sleep_ms(delay_telas);
        aux = !aux;
    }
    aux = 0; botao_a_flag = 0; soma = 0; media = 0;       
    while(!botao_a_flag)
    {
        soma = 0;
        adc_select_input(2); // Seleciona o ADC para eixo X. O pino 28 como entrada analógica
        for (int i = 0; i < 500; i++)
        {
            soma += adc_read();
            sleep_ms(1);
        }
        media = soma / 500;
        sprintf(str_x, "%d", media); // Converte o inteiro em string
    
        if(!aux)
        {
            ssd1306_fill(ssd, !cor); // Limpa o display
            ssd1306_draw_string(ssd, "Se val. proximo", 4, 15); // Desenha uma string
            ssd1306_draw_string(ssd, " de 0 tecle", 4, 29); // Desenha uma string 
            ssd1306_draw_string(ssd, "       A", 4, 43); // Desenha uma string        
            ssd1306_send_data(ssd); // Atualiza o display
        }
        else
        {
    
            ssd1306_fill(ssd, !cor); // Limpa o display
            ssd1306_draw_string(ssd, "Valor medido", 4, 15); // Desenha uma string
            ssd1306_draw_string(ssd,     str_x, 4, 29); // Desenha uma string  
            ssd1306_send_data(ssd); // Atualiza o display
        }
        sleep_ms(delay_telas-500);
        aux = !aux;
    }
    valor_minimo = media;
}


/**
 * @brief função usada para calibrar o Ohmimetro
 */
void calibrar_ohmimtro(ssd1306_t *ssd)
{
    bool cor = true; //Estado LEDs display 
    uint32_t tempo = to_ms_since_boot(get_absolute_time()),
    agora = 0;
    char str_y[9]; // Buffer para armazenar a string

    ssd1306_fill(ssd, !cor);
    ssd1306_draw_image(ssd, msg_calibrar);
    ssd1306_send_data(ssd); // Atualiza o display
    sleep_ms(2500);

    ssd1306_fill(ssd, !cor);
    ssd1306_draw_image(ssd, tecle_a);
    ssd1306_send_data(ssd); // Atualiza o display
    som_buz(1*KHz, 500);
    sleep_ms(3500);

    while((!botao_a_flag) && ((agora-tempo)<10000))
        agora = to_ms_since_boot(get_absolute_time());

    if(botao_a_flag)
    {
        botao_a_flag = 0;
        rotina_de_calibracao(ssd);

        som_buz(1*KHz, 500);
        gpio_put(LED_G, 1);
        ssd1306_fill(ssd, !cor); // Limpa o display
        ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
        ssd1306_draw_string(ssd, "CALIBRADO", 8, 15); // Desenha uma string
        sprintf(str_y, "Vmax %d", valor_maximo);
        ssd1306_draw_string(ssd,str_y, 8, 29); // Desenha uma string  
        sprintf(str_y, "Vmin %d", valor_minimo);
        ssd1306_draw_string(ssd,str_y, 8, 43); // Desenha uma string      
        ssd1306_send_data(ssd); // Atualiza o display
        sleep_ms(5000);
    }
    else
    {
        som_buz(1*KHz, 500);
        gpio_put(LED_G, 1);
        gpio_put(LED_R, 1);
        ssd1306_fill(ssd, !cor); // Limpa o display
        ssd1306_rect(ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
        ssd1306_draw_string(ssd, "NAO CALIBRADO", 8, 15); // Desenha uma string
        sprintf(str_y, "Vmax %d", valor_maximo);
        ssd1306_draw_string(ssd,str_y, 8, 29); // Desenha uma string  
        sprintf(str_y, "Vmin %d", valor_minimo);
        ssd1306_draw_string(ssd,str_y, 8, 43); // Desenha uma string      
        ssd1306_send_data(ssd); // Atualiza o display
        sleep_ms(5000);
    }

    gpio_put(LED_R, 0);
    gpio_put(LED_G, 0);
}

const float serie_e24[] = 
{
    1.0, 1.1, 1.2, 1.3, 1.5, 1.6, 1.8, 2.0, 2.2, 2.4, 
    2.7, 3.0, 3.3, 3.6, 3.9, 4.3, 4.7, 5.1, 5.6, 6.2, 
    6.8, 7.5, 8.2, 9.1, 10.0
};

#define TAMANHO_SERIE (sizeof(serie_e24) / sizeof(serie_e24[0]))

const char* cores[] = 
{
    "Preto",    // 0
    "Marrom",   // 1
    "Vermelho", // 2
    "Laranja",  // 3
    "Amarelo",  // 4
    "Verde",    // 5
    "Azul",     // 6
    "Violeta",  // 7
    "Cinza",    // 8
    "Branco"    // 9
};

float valor_compativel(float valor_float)
{
    if (valor_float > 9.1f && valor_float < 11.0f)
    {
        return 10.0f; // Se estiver entre 9.1 e 11, consideramos como 10
    }

    for (int i = 0; i < TAMANHO_SERIE; i++)
    {
        float tolerancia = serie_e24[i] * 0.05f; // 5% de tolerância
        if (valor_float >= (serie_e24[i] - tolerancia) && valor_float <= (serie_e24[i] + tolerancia))
        {
            return serie_e24[i];
        }
    }
    return -1.0f; // Não encontrado
}

/**
 * @brief Identificar posição dos dígitos e imprimir código de cores com multiplicador correto
 */
void printar_cores(uint16_t _valor_rx, ssd1306_t *ssd) 
{
    uint16_t valor = _valor_rx;
    uint8_t primeiro_digito = 0, segundo_digito = 0;
    int tamanho = 0;
    uint32_t temp = valor;
    char str_y[14]; // Buffer para armazenar a string
    bool cor = true;

    // Conta quantos dígitos tem o valor
    while (temp > 0) {
        temp /= 10;
        tamanho++;
    }

    if (tamanho < 2) {
        printf("Valor inválido para resistor.\n");
        return;
    }

    // Extrai o primeiro e segundo dígito
    uint32_t divisor = (uint32_t)pow(10, tamanho - 1);
    primeiro_digito = valor / divisor;
    valor = valor % divisor;
    divisor /= 10;
    segundo_digito = valor / divisor;

    // Valor base (ex: 4 + 3/10 = 4.3)
    float valor_base = primeiro_digito + (float)segundo_digito / 10.0f;

    float base_serie = valor_compativel(valor_base);
    if (base_serie < 0) {
        printf("Valor não compatível com série E24.\n");
        return;
    }

    // Agora calcula o multiplicador corretamente:
    // valor_rx / base_serie dá 10 elevado a multiplicador
    float fator = (float)_valor_rx / base_serie;
    int multiplicador = (int)roundf(log10f(fator));

    // Valor real corrigido
    float valor_real = base_serie * powf(10, multiplicador);

    // Mostra valor do resistor
    if (valor_real >= 1000000.0f)
        printf("Resistor: %.2fM ohms\n", valor_real / 1000000.0f);
    else if (valor_real >= 1000.0f)
        printf("Resistor: %.2fk ohms\n", valor_real / 1000.0f);
    else
        printf("Resistor: %.2f ohms\n", valor_real);

    // Primeira, segunda, e multiplicador
    int primeira_cor = (int)base_serie;
    int segunda_cor = (int)((base_serie - primeira_cor) * 10.0f + 0.5f);

    // Ajuste especial para 10.0
    if (base_serie == 10.0f) {
        primeira_cor = 1;
        segunda_cor = 0;
        multiplicador += 1; // compensa o 10
    }

    multiplicador = multiplicador-1;

    printf("Código de cores: %s, %s, %s\n", 
        cores[primeira_cor],
        cores[segunda_cor],
        cores[multiplicador]);

    
    sprintf(str_y, "Val. %0.2f", valor_real);   // Converte o float em string
    ssd1306_fill(ssd, !cor);                          // Limpa o display
    ssd1306_rect(ssd, 3, 3, 122, 60, cor, !cor);      // Desenha um retângulo
    ssd1306_draw_string(ssd, str_y,12,6);
    ssd1306_draw_string(ssd, cores[primeira_cor], 26,26);
    ssd1306_draw_string(ssd, cores[segunda_cor], 34,36);
    ssd1306_draw_string(ssd, cores[multiplicador], 43,48);
    ssd1306_send_data(ssd);

    uint32_t matriz_cores[25] = {0};    
    int i, pos = 0;

    // Copia primeira cor
    for(i = 0; i < 5; i++)
        matriz_cores[pos++] = cores_resistores[primeira_cor][i];

    // Copia segunda cor
    for(i = 0; i < 5; i++)
        matriz_cores[pos++] = cores_resistores[segunda_cor][i];

    // Copia multiplicador
    for(i = 0; i < 5; i++)
        matriz_cores[pos++] = cores_resistores[multiplicador][i];

    // Copia tolerância
    for(i = 0; i < 5; i++)
        matriz_cores[pos++] = 0x0000d7ff;

    // Copia 5 vezes 0xff000000
    for(i = 0; i < 5; i++)
        matriz_cores[pos++] = 0xff000000;

    desenhar_fig(apagado, 100);
    sleep_ms(50);
    desenhar_fig(matriz_cores, 10);
}