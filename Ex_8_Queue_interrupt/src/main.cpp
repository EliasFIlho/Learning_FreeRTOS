#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"


#define LED 2
#define BT 15

QueueHandle_t xFila;
TaskHandle_t xTask1Handle;

void vTask1(void *pvParametes);
void trataISR_BT(){
  static int valor;

  valor++;
  xQueueSendFromISR(xFila,&valor,NULL);

}


void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(BT,INPUT);
  attachInterrupt(digitalPinToInterrupt(BT),trataISR_BT,FALLING);

  xFila = xQueueCreate(5,sizeof(int));
  xTaskCreate(vTask1,"TASK1",configMINIMAL_STACK_SIZE+1024,NULL,1,&xTask1Handle);

}

void loop() {
  digitalWrite(LED,!digitalRead(LED));
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void vTask1(void *pvParametes){
  
  int valorrecebido;
  
  while(1){
    xQueueReceive(xFila,&valorrecebido,portMAX_DELAY);
    Serial.println("BT Pressionado: " + String(valorrecebido));
  }

}
