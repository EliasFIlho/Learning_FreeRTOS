/*

  Libs do framwork do arduino e do FreeRTOS

*/
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED 2

/*
  Variaveis para armazenamento do Handle das tasks
*/
TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;


/*

  Prototipos das Tasks

*/
void vTask1(void *pvParametes);
void vTask2(void *pvParametes);




void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);

  xTaskCreate(vTask1,"TASK1",configMINIMAL_STACK_SIZE,NULL,1,&task1Handle);
  xTaskCreate(vTask2,"TASK2",configMINIMAL_STACK_SIZE+1024,NULL,2,&task2Handle);
  
}

void loop() {
  vTaskDelay(1000);
}

void vTask1(void *pvParametes){
  while (1){
    digitalWrite(LED,!digitalRead(LED));
    vTaskDelay(200);
  }
  

}


void vTask2(void *pvParametes){

  int cont = 0;
  while(1){
    Serial.println("Task 2:" + String(cont++));
    vTaskDelay(1000);
  }


}
