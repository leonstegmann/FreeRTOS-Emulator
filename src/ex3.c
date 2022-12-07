/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

/* TUM_Library includes  */
#include "TUM_Draw.h"
#include "TUM_Ball.h"
#include "TUM_Event.h"
#include "TUM_Font.h"
#include"TUM_FreeRTOS_Utils.h"

/* Project includes  */
#include"ex3.h"
#include"main.h"
#include"shapes.h"
#include"buttons.h"
#include"utility_functions.h"


QueueHandle_t Queue_ex3_Handle = NULL;

TaskHandle_t Ex3_draw_handle = NULL;
TaskHandle_t Ex3_t1_handle = NULL;
TaskHandle_t ex3_t2_handle = NULL;



void vExercise3Draw(void *pvParameters){

    /* Create Left Blinkng Circle*/
    circle_t *left_circle = createCircle((coord_t) {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, (unsigned short) 30, Red);
    int leftCircle_State;

    circle_t *right_circle = createCircle((coord_t) {3*SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, (unsigned short) 30, Red);
    int rightCircle_State;

    
    while(1){
        if (DrawSignal)
            if (xSemaphoreTake(DrawSignal, portMAX_DELAY) == pdTRUE) {
            tumEventFetchEvents( FETCH_EVENT_NONBLOCK); // Query events backend for new events, ie. button presses
            
            tumDrawClear(White);

            vDrawFPS();

            xQueueReceive(Queue_ex3_Handle,&leftCircle_State,20);
            xQueueReceive(Queue_ex3_Handle,&rightCircle_State,20);
            
            if (leftCircle_State == 1)
                drawCircle(left_circle);
                
            if (rightCircle_State == 1)
                drawCircle(right_circle);
                        
            vTaskDelay(10);
            }
    }
}

void vExercise3Task1(void *pvParameters){

    int leftCircle_State;

    while(1){
    leftCircle_State = 1;
    xQueueSend(Queue_ex3_Handle, &leftCircle_State, portMAX_DELAY);
    vTaskDelay((TickType_t) 500);

    leftCircle_State = 0;
    xQueueSend(Queue_ex3_Handle, &leftCircle_State, portMAX_DELAY);
    vTaskDelay((TickType_t) 500);

    }
}

void vExercise3Task2(void *pvParameters){
    
    int rightCircle_State;

    while(1){
    rightCircle_State = 1;
    xQueueSend(Queue_ex3_Handle, &rightCircle_State, portMAX_DELAY);
    vTaskDelay((TickType_t) 250);

    rightCircle_State = 0;
    xQueueSend(Queue_ex3_Handle, &rightCircle_State, portMAX_DELAY);
    vTaskDelay((TickType_t) 250);

    }
}

int createExercise3Tasks(void){

    if (xTaskCreate(vExercise3Draw, "Exercise_3_Draw", mainGENERIC_STACK_SIZE, NULL,
                    mainGENERIC_PRIORITY+2, &Ex3_draw_handle) != pdPASS) {
		goto err_ex3_draw;
	}

	if (xTaskCreate(vExercise3Task1, "Exercise_3_Task_1", mainGENERIC_STACK_SIZE , NULL,
                    mainGENERIC_PRIORITY+1, &Ex3_t1_handle) != pdPASS) {
		goto err_ex3_t1;
	}

	if (xTaskCreate(vExercise3Task2, "Exercise_3_Task_2", mainGENERIC_STACK_SIZE , NULL,
                    mainGENERIC_PRIORITY+1, &ex3_t2_handle) != pdPASS) {
		goto err_ex3_t2;
	}

    vTaskSuspend(Ex3_draw_handle);
	vTaskSuspend(Ex3_t1_handle);
	vTaskSuspend(ex3_t2_handle);

    return 0;

err_ex3_t2:
	vTaskDelete(Ex3_t1_handle);
err_ex3_t1:
	vTaskDelete(Ex3_draw_handle);
err_ex3_draw:

    return -1;

}
    
void deleteExercise3Tasks(void)
{
    if (Ex3_draw_handle) {
        vTaskDelete(Ex3_draw_handle);
    }
    if (Ex3_t1_handle) {
        vTaskDelete(Ex3_t1_handle);
    }
    if (ex3_t2_handle) {
        vTaskDelete(ex3_t2_handle);
    }
}

void Exercise3ExitFunction(void){
    printf("\nExiting Tasks 3\n");
    vTaskSuspend(Ex3_draw_handle);
	vTaskSuspend(Ex3_t1_handle);
	vTaskSuspend(ex3_t2_handle);

}

void Exercise3EnterFunction(void){
    printf("\nResume Tasks 3\n");
    vTaskResume(Ex3_draw_handle);
	vTaskResume(Ex3_t1_handle);
	vTaskResume(ex3_t2_handle);
}


