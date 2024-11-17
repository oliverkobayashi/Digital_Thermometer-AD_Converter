// Configurações de pinos do LCD
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
    float temperature;
    char text[5];

    // Inicializa módulos
    ADC_Init();                        // Inicializa ADC com configuração padrão
    ADCON1 = 0b00110000;               // Configura Vref externa AN2 e AN3

    Lcd_Init();                        // Inicializa o LCD
    Lcd_Cmd(_LCD_CLEAR);               // Limpa o display
    Lcd_Cmd(_LCD_CURSOR_OFF);          // Desliga cursor

    while(1) {
        adc_value = ADC_Get_Sample(0);                  // Lê o valor do canal AN0
        
        temperature = (adc_value * 100.0) / 1023.0;     // Cálculo da temperatura

        // Formata o texto para exibição
        FloatToStr(temperature, text);  // Converte float para string
        text[4] = '\0';                 // Limita o text em 4 caracteres

        Lcd_Out(1, 1, text);            // Exibe a temperatura no LCD
        Lcd_Chr(1, 6, 0xDF);            // Exibe o símbolo de grau
        Lcd_Out(1, 7, "C");             // Exibe o C

        Delay_ms(20);                   // Aguarda 20 ms antes de nova leitura
    }
}