#include <Arduino.h>
#include <STM32FreeRTOS.h>

#define LED_NET PB3

HardwareSerial Serial2(PA3, PA2);

TaskHandle_t v2x_network_handler = NULL;
TaskHandle_t v2x_blink_handler = NULL;
