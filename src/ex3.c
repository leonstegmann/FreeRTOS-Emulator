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

/* Project includes  */
#include"ex3.h"
#include"main.h"
#include"shapes.h"
#include"buttons.h"
#include"utility_functions.h"


QueueHandle_t Queue_ex3_Handle = NULL;


void vExercise3Draw(void *pvParameters){

    /* Create Left Blinkng Circle*/
    circle_t *left_circle = createCircle((coord_t) {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, (unsigned short) 30, Red);
    int leftCircle_State;

    circle_t *right_circle = createCircle((coord_t) {3*SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, (unsigned short) 30, Red);
    int rightCircle_State;


    tumDrawBindThread();
    
    while(1){
        if (DrawSignal);
        if(xSemaphoreTake(DrawSignal, 10) == pdTRUE);

        tumEventFetchEvents( FETCH_EVENT_NONBLOCK); // Query events backend for new events, ie. button presses
		xGetButtonInput(); // Update global input

        tumDrawClear(White);

        vDrawFPS();

    	xQueueReceive(Queue_ex3_Handle,&leftCircle_State,20);
        xQueueReceive(Queue_ex3_Handle,&rightCircle_State,20);
		
        if (leftCircle_State == 1)
            drawCircle(left_circle);
            
        if (rightCircle_State == 1)
            drawCircle(right_circle);
            
        tumDrawUpdateScreen();
        
        xSemaphoreGive(DrawSignal);

    }
}

void vExercise3Task1(void *pvParameters){

    int leftCircle_State;

    while(1){
    leftCircle_State = 1;
    xQueueSend(Queue_ex3_Handle, &leftCircle_State, portMAX_DELAY);
    vTaskDelay((TickType_t) 50);

    leftCircle_State = 0;
    xQueueSend(Queue_ex3_Handle, &leftCircle_State, portMAX_DELAY);
    vTaskDelay((TickType_t) 50);

    }
}

void vExercise3Task2(void *pvParameters){
    
    int rightCircle_State;

    while(1){
    rightCircle_State = 1;
    xQueueSend(Queue_ex3_Handle, &rightCircle_State, portMAX_DELAY);
    vTaskDelay((TickType_t) 25);

    rightCircle_State = 0;
    xQueueSend(Queue_ex3_Handle, &rightCircle_State, portMAX_DELAY);
    vTaskDelay((TickType_t) 25);

    }
}