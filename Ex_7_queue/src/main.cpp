#include <Arduino.h>
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/FreeRTOS.h"

#define LED 2

QueueHandle_t xFilaHandle;
TaskHandle_t xTask1Handle,xTask2Handle;

void vTask1(void *pvParametes);
void vTask2(void *pvParametes);


void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  xTaskCreate(vTask1,"TASK1",configMINIMAL_STACK_SIZE+1024,NULL,1, &xTask1Handle);
  xTaskCreate(vTask2,"TASK2",configMINIMAL_STACK_SIZE+1024,NULL,1, &xTask2Handle);
  xFilaHandle = xQueueCreate(1,sizeof(int));
  
  if(xFilaHandle == NULL){
    Serial.println("Erro ao criar queue");
    while(1);
  }
  
}

void loop() {
  digitalWrite(LED,!digitalRead(LED));
  vTaskDelay(pdMS_TO_TICKS(1000));
}

void vTask1(void *pvParametes){
  int count = 0;
  while(1){
    if(count < 10){
      xQueueSend(xFilaHandle,&count,portMAX_DELAY);
      count++;
    }else{
      count = 0;
      vTaskDelay(pdMS_TO_TICKS(5000));
    }
    vTaskDelay(pdMS_TO_TICKS(500));
      
  }


}

void vTask2(void *pvParametes){
  int recived_value = 0;
  while(1){
    if(xQueueReceive(xFilaHandle,&recived_value,pdMS_TO_TICKS(1000)) == pdTRUE){
      Serial.println("Valor Recebido: " + String(recived_value));
    }else{
      Serial.println("TIMEOUT");
    }
  }
  
}