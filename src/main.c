#include "main.h"

int main()
{
    //Definição de Variaveis
    ssd1306_t ssd;      // Inicializa a estrutura do display
    float R_x = 0.0;    // Resistor desconhecido

    //Inicialização de hardware e software
    init_sistema(&ssd);

    calibrar_ohmimtro(&ssd);
    
    while(1)
    {
        
    }
}
