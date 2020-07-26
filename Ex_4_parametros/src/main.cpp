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
  xTaskCreate(vTaskBlink, "TASK1", configMINIMAL_STACK_SIZE, (void*)LED1, 1, &task1Handle);
  xTaskCreate(vTask2, "TASK2", configMINIMAL_STACK_SIZE+1024, (void*)value, 2, &task2Handle);
  xTaskCreate(vTaskBlink, "TASK3", configMINIMAL_STACK_SIZE, (void*)LED2, 1, &task3Handle);
  
}

void loop() {
  vTaskDelay(1000);
}

void vTaskBlink(void *pvParametes){
  int pin = (int)pvParametes;
  pinMode(pin,OUTPUT);
  while (1){
    digitalWrite(pin, !digitalRead(pin));
    vTaskDelay(1000);
  }
  

}


void vTask2(void *pvParametes){

  int cont = (int)pvParametes;
  while(1){
    Serial.println("Task 2:" + String(cont++));
    vTaskDelay(1000);
  }


}
