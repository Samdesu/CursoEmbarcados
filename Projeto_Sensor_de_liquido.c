//1- inicialização do codigo = indicar visualmente na placa que o software foi iniciado 
//2- fazer a detecção do sensor em loop
//3- liga o led vermelho enquanto n detenta nada no sensor
//4- se o sensor indentificar um liquido, liga o led verde 
#include <stdio.h>
#include "pico/stdlib.h"

#define LED_RGB_RED_PIN 13
#define LED_RGB_BLUE_PIN 12
#define LED_RGB_GREEN_PIN 11
#define SENSOR_PIN 17

bool sensor_situation = false;

void sensor_detection(uint gpio, uint32_t events){ // detecção o sinal do sensor
    sensor_situation = gpio_get(SENSOR_PIN);
    printf("Sensor ativado!\n");
}

int main()
{
    stdio_init_all();

    gpio_init(LED_RGB_GREEN_PIN);
    gpio_set_dir(LED_RGB_GREEN_PIN,GPIO_OUT);
    gpio_put(LED_RGB_GREEN_PIN, 0);

    gpio_init(LED_RGB_BLUE_PIN);
    gpio_set_dir(LED_RGB_BLUE_PIN,GPIO_OUT);
    gpio_put(LED_RGB_BLUE_PIN, 0);
    for (int i = 0; i < 2; i++){ // indica a inicialização do codigo
        gpio_put(LED_RGB_BLUE_PIN,1);
        sleep_ms(1000);
        gpio_put(LED_RGB_BLUE_PIN,0);
        sleep_ms(1000);
    }

    gpio_init(LED_RGB_RED_PIN);
    gpio_set_dir(LED_RGB_RED_PIN,GPIO_OUT);
    gpio_put(LED_RGB_RED_PIN,1); // liga o led vermelho por padrão 

    gpio_init(SENSOR_PIN);
    gpio_set_dir(SENSOR_PIN,GPIO_IN);
    gpio_pull_up(SENSOR_PIN);

    gpio_set_irq_enabled_with_callback(SENSOR_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, sensor_detection);

    while (true) {
        if (sensor_situation){ // liga o led verde quando detectar liquido
            gpio_put(LED_RGB_RED_PIN,0);
            gpio_put(LED_RGB_GREEN_PIN,1);
        }
        else{ // liga o led se n detectar nada
            gpio_put(LED_RGB_RED_PIN,1);
            gpio_put(LED_RGB_GREEN_PIN,0);
        }
        sleep_ms(500);
    }
}
