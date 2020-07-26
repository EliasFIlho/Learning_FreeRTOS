/*

  Libs do framwork do arduino e do FreeRTOS

*/
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED1 2
#define LED2 15

/*
  Variaveis para armazenamento do Handle das tasks
*/
TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;
TaskHandle_t task3Handle = NULL;


/*

  Prototipos das Tasks

*/
void vTaskBlink(void *pvParametes);
void vTask2(void *pvParametes);

int value = 500;




void setup() {
  Serial.begin(9600);
  xTaskCreatePinnedToCore(vTaskBlink, "TASK1", configMINIMAL_STACK_SIZE, (void*)LED1, 1, &task1Handle,APP_CPU_NUM);
  xTaskCreatePinnedToCore(vTask2, "TASK2", configMINIMAL_STACK_SIZE+1024, (void*)value, 2, &task2Handle,PRO_CPU_NUM);
  xTaskCreatePinnedToCore(vTaskBlink, "TASK3", configMINIMAL_STACK_SIZE, (void*)LED2, 1, &task3Handle,APP_CPU_NUM);
  
}

void loop() {
  vTaskDelay(1000);
}

void vTaskBlink(void *pvParametes){
  UBaseType_t uxHighWaterMark;
  int pin = (int)pvParametes;
  pinMode(pin,OUTPUT);
  while (1){
    digitalWrite(pin, !digitalRead(pin));
    vTaskDelay(1000);
    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
    Serial.print(pcTaskGetTaskName(NULL));
    Serial.print(" : ");
    Serial.println(uxHighWaterMark);

  }
  

}


void vTask2(void *pvParametes){
  UBaseType_t uxHighWaterMark;
  int cont = (int)pvParametes;
  while(1){
    Serial.println("Task 2:" + String(cont++));
    vTaskDelay(1000);
    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
    Serial.print(pcTaskGetTaskName(NULL));
    Serial.print(" : ");
    Serial.println(uxHighWaterMark);
  }


}
