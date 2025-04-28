#include "main.h"

int main()
{
    //Definição de Variaveis
    ssd1306_t ssd;      // Inicializa a estrutura do display
    float R_x = 0.0, R_x_historico = 0.0;    // Resistor desconhecido
    bool cor = true;
    float resistor_conhecido = 9.93*KOhm; //Resistor conhecido
    char str_x[5]; // Buffer para armazenar a string
    char str_y[5]; // Buffer para armazenar a string
    bool aux = 1;

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
        {
            R_x_historico = R_x;
            
            sprintf(str_x, "%1.0f", media); // Converte o inteiro em string
            sprintf(str_y, "%1.0f", R_x);   // Converte o float em string

            //  Atualiza o conteúdo do display com animações
            ssd1306_fill(&ssd, !cor);                          // Limpa o display
            ssd1306_rect(&ssd, 3, 3, 122, 60, cor, !cor);      // Desenha um retângulo
            ssd1306_line(&ssd, 3, 25, 123, 25, cor);           // Desenha uma linha
            ssd1306_line(&ssd, 3, 37, 123, 37, cor);           // Desenha uma linha
            ssd1306_draw_string(&ssd, "CEPEDI   TIC37", 8, 6); // Desenha uma string
            ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 16);  // Desenha uma string
            ssd1306_draw_string(&ssd, "  Ohmimetro", 10, 28);  // Desenha uma string
            ssd1306_draw_string(&ssd, "ADC", 13, 41);          // Desenha uma string
            ssd1306_draw_string(&ssd, "Resisten.", 50, 41);    // Desenha uma string
            ssd1306_line(&ssd, 44, 37, 44, 60, cor);           // Desenha uma linha vertical
            ssd1306_draw_string(&ssd, str_x, 8, 52);           // Desenha uma string
            ssd1306_draw_string(&ssd, str_y, 59, 52);          // Desenha uma string
            ssd1306_send_data(&ssd); 
            sleep_ms(2000);  

            printar_cores(R_x, &ssd);
            sleep_ms(3000);
            aux = !aux;
        }
    }
}
