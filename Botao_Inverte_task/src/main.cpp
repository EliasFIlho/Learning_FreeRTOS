/*

  Libs do framwork do arduino e do FreeRTOS

*/
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED 2
#define BT  15
/*
  Variaveis para armazenamento do Handle das tasks
*/
TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;

int task_state_flag = 1;

/*

  Prototipos das Tasks

*/
void vTask1(void *pvParametes);
void vTask2(void *pvParametes);




void setup() {

  pinMode(LED, OUTPUT);
  pinMode(BT, INPUT);

  xTaskCreate(vTask1, "TASK1", configMINIMAL_STACK_SIZE, NULL, 1, &task1Handle);
  xTaskCreate(vTask2, "TASK2", configMINIMAL_STACK_SIZE+1024, NULL, 2, &task2Handle);
  
}

void loop() {
  vTaskDelay(1000);
}

void vTask1(void *pvParametes){
  while (1){
    digitalWrite(LED, !digitalRead(LED));
    vTaskDelay(200);
  }
  

}


void vTask2(void *pvParametes){

  while(1){
    
    int value = digitalRead(BT);
    if(value == 1 && task_state_flag == 1){
      if(task1Handle != NULL){
        vTaskSuspend(task1Handle);
        digitalWrite(LED, LOW);
        task_state_flag = 0;
      }
    }else if(value == 0 && task_state_flag == 0){
      vTaskResume(task1Handle);
      task_state_flag = 1;
    }
  }


}
