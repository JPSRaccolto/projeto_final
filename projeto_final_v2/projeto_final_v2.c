#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "font.h"

#define BOTAO_A 5
#define BOTAO_B 6
#define buzzer_1 10
#define buzzer_2 21
#define VERMELHO 13
#define SELEC 22
#define PWM_WRAP 4095
#define PWM_CLK_DIV 30.52f
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define ENDERECO_I2C 0x3C

int captura = 0;
absolute_time_t last_interrupt_time = 0;
bool buzzer_state = false; // Estado do buzzer (ligado/desligado)
bool rect_state = false;   // Estado do retângulo (visível/invisível)
bool cor = false;
uint32_t buzzer_timer = 0; // Contador para controlar o buzzer e o retângulo

void pwm_init_gpio(uint gpio, uint wrap, float clkdiv) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, wrap);
    pwm_config_set_clkdiv(&config, clkdiv);
    pwm_init(slice_num, &config, true);
}

void inicia_pinos() {
    gpio_init(VERMELHO);
    gpio_set_dir(VERMELHO, GPIO_OUT);

    gpio_init(SELEC);
    gpio_set_dir(SELEC, GPIO_IN);
    gpio_pull_up(SELEC);

    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);

    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_B);

    gpio_init(buzzer_1);
    gpio_set_dir(buzzer_1, GPIO_OUT);

    gpio_init(buzzer_2);
    gpio_set_dir(buzzer_2, GPIO_OUT);
}
ssd1306_t *ssd;
void gpio_callback(uint gpio, uint32_t event) {
    absolute_time_t now = get_absolute_time();
    if (absolute_time_diff_us(last_interrupt_time, now) < 250000) return;
    last_interrupt_time = now;

    if (gpio == SELEC && captura == 0) {
        captura = 1; // Só pode ativar se ainda não estiver no estado de captura
    } else if (gpio == BOTAO_A && captura == 1) {
        captura = 2; // Confirmação do alerta apenas se já estiver em modo de captura
    } else if (gpio == BOTAO_B) {
        captura = 0; // Reset apenas com o botão B
    }
}


void tocar_buzzer(uint pin, bool ligar) {
    uint slice = pwm_gpio_to_slice_num(pin);
    if (ligar) {
        pwm_set_gpio_level(pin, 2047); // 50% do duty cycle (som médio)
    } else {
        pwm_set_gpio_level(pin, 0); // Silencia o buzzer
    }
}

void invasao(ssd1306_t *ssd) {
    switch (captura) {
        case 0:
          // Modo normal (nada acontece)
          ssd1306_fill(ssd, false); // Limpa o display
          gpio_put(VERMELHO, 0);   // Desliga o LED vermelho
          tocar_buzzer(buzzer_1, false); // Desliga o buzzer
          tocar_buzzer(buzzer_2, false);
          break;
        case 1:
          // Modo de alerta
          ssd1306_fill(ssd, false); // Limpa o display
          ssd1306_draw_string(ssd, "ALERTA INTRUSO", 5, 5); // Desenha uma string
          ssd1306_draw_string(ssd, "CONFIRMA?", 35, 20); // Desenha uma string
          ssd1306_draw_string(ssd, "SIM", 7, 35);
          ssd1306_draw_string(ssd, "BOTAO A", 7, 45);
          ssd1306_draw_string(ssd, "NAO", 65, 35);
          ssd1306_draw_string(ssd, "BOTAO B", 65, 45);

          // Alterna o estado do buzzer e do retângulo a cada 300 ms
          if (to_ms_since_boot(get_absolute_time()) - buzzer_timer >= 300) {
              buzzer_state = !buzzer_state; // Alterna o estado do buzzer
              rect_state = !rect_state;     // Alterna o estado do retângulo
              cor = !cor;
              tocar_buzzer(buzzer_1, buzzer_state);
              tocar_buzzer(buzzer_2, buzzer_state);
              buzzer_timer = to_ms_since_boot(get_absolute_time()); // Reinicia o timer
          }

          // Desenha as bordas alternadas
          if (rect_state) {
              // Desenha a borda externa
              ssd1306_rect(ssd, 3, 3, 122, 60, true, false); // Borda externa
          } else {
              ssd1306_rect(ssd, 3, 3, 122, 58, true, false);
              ssd1306_rect(ssd, 4, 4, 120, 56, true, false); 
          }

          gpio_put(VERMELHO, cor); // Pisca o LED vermelho
          break;
        case 2:
          
          ssd1306_fill(ssd, false); // Limpa o display
          ssd1306_draw_string(ssd, "CONFIRMADO", 25, 5); // Desenha uma string
          ssd1306_draw_string(ssd, "EMITINDO UM", 20, 30); // Desenha uma string
          ssd1306_draw_string(ssd, "ALERTA PARA", 19, 40); // Desenha uma string
          ssd1306_draw_string(ssd, "A POLICIA", 20, 50); // Desenha uma string

                    // Alterna o estado do buzzer e do retângulo a cada 300 ms
          if (to_ms_since_boot(get_absolute_time()) - buzzer_timer >= 300) {
              buzzer_state = !buzzer_state; // Alterna o estado do buzzer
              rect_state = !rect_state;     // Alterna o estado do retângulo
              cor = !cor;
              tocar_buzzer(buzzer_1, buzzer_state);
              tocar_buzzer(buzzer_2, buzzer_state);
              buzzer_timer = to_ms_since_boot(get_absolute_time()); // Reinicia o timer
          }

          // Desenha as bordas alternadas
          if (rect_state) {
              // Desenha a borda externa
              ssd1306_rect(ssd, 3, 3, 122, 60, true, false); // Borda externa
          } else {
              ssd1306_rect(ssd, 3, 3, 122, 58, true, false);
              ssd1306_rect(ssd, 4, 4, 120, 56, true, false); 
          }

          gpio_put(VERMELHO, cor); // Pisca o LED vermelho
          break;
    }
}

int main() {
    stdio_init_all();
    inicia_pinos();
    gpio_set_irq_enabled_with_callback(SELEC, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    //I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);
    
    ssd1306_t ssd;
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ENDERECO_I2C, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_fill(&ssd, false); // Limpa o display

    pwm_init_gpio(buzzer_1, PWM_WRAP, PWM_CLK_DIV);
    pwm_init_gpio(buzzer_2, PWM_WRAP, PWM_CLK_DIV);

    while (true) {
        invasao(&ssd); // Atualiza o display, o buzzer e o retângulo
        ssd1306_send_data(&ssd); // Envia os dados para o display
        sleep_ms(10); // Pequena pausa para evitar uso excessivo da CPU
    }
}