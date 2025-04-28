#include "main.h"

int main()
{
    //Definição de Variaveis
    ssd1306_t ssd;      // Inicializa a estrutura do display
    float R_x = 0.0, R_x_historico = 0.0;    // Resistor desconhecido
    bool cor = true;
    float resistor_conhecido = 9.93*KOhm; //Resistor conhecido

    //Inicialização de hardware e software
    init_sistema(&ssd);

    calibrar_ohmimtro(&ssd);
    uint16_t val_ref = valor_maximo - valor_minimo;
    
    while(1)
    {
        adc_select_input(2); // Seleciona o ADC para eixo X. O pino 28 como entrada analógica

        float soma = 0.0f;
        for (int i = 0; i < 5000; i++)
          soma += adc_read() - valor_minimo;
        float media = soma / 5000.0f;

        if ((val_ref - media) > 0.001f)
        {
            R_x = resistor_conhecido * (media) / (val_ref - media);
        }
        else
        {
            R_x = 0;
        }

        if(abs(R_x - R_x_historico)> R_x*0.10)
            printar_cores(R_x, &ssd);
        sleep_ms(700);
    }
}
