// Configuração dos pinos do LCD
sbit LCD_RS at LATB4_bit;
sbit LCD_EN at LATB5_bit;
sbit LCD_D4 at LATB0_bit;
sbit LCD_D5 at LATB1_bit;
sbit LCD_D6 at LATB2_bit;
sbit LCD_D7 at LATB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;

void main() {
    unsigned int adc_value;
    unsigned long voltage;
    char text[16];

    // Inicialização
    ADC_Init();                     // Inicializa o módulo ADC
    Lcd_Init();                     // Inicializa o LCD
    Lcd_Cmd(_LCD_CLEAR);            // Limpa o display
    Lcd_Cmd(_LCD_CURSOR_OFF);       // Desliga o cursor

    while(1) {
        adc_value = ADC_Get_Sample(0);              // Lê o valor do canal AN0
        voltage = (adc_value * 5000UL) / 1023;      // Converte para milivolts (0-5000) [mV]
        voltage = voltage * 4;                      // Ajusta para a escala de (0-20) [mV]

        // Formatando o valor a ser exibido no LCD
        text[0] = (voltage / 10000) + '0';           // Dezena de volts
        text[1] = ((voltage / 1000) % 10) + '0';     // Unidade de volts
        text[2] = '.';                               // Ponto decimal
        text[3] = ((voltage / 100) % 10) + '0';      // Primeira casa decimal
        text[4] = ' ';                               // Espaço
        text[5] = 'V';                               // Unidade (Volts)
        text[6] = '\0';                              // Finaliza a string

        Lcd_Out(1, 1, text);  // Exibe a tensão no LCD

        Delay_ms(20);  // Aguarda 20 ms
    }
}
