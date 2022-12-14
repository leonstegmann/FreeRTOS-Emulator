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
#include"TUM_Print.h" // for calling PRINT_ERROR()

/* Project includes  */
#include"ex3.h"
#include"main.h"
#include"shapes.h"
#include"buttons.h"
#include"utility_functions.h"
#include"defines.h"


QueueHandle_t Queue_ex3_Handle = NULL;

TaskHandle_t Ex3_draw_handle = NULL;
TaskHandle_t Ex3_t1_handle = NULL;
TaskHandle_t ex3_t2_handle = NULL;

QueueHandle_t Queue_ButtonOne = NULL;
QueueHandle_t Queue_ButtonTwo = NULL;
SemaphoreHandle_t ButtonOneSemaphore = NULL;
TaskHandle_t buttonTrigger_handle = NULL;
TaskHandle_t buttonOne_handle = NULL;
TaskHandle_t buttonTwo_handle = NULL;

void vExercise3Draw(void *pvParameters){

    /* Create Left Blinkng Circle*/
    circle_t *left_circle = createCircle((coord_t) {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, (unsigned short) 30, Red);
    int leftCircle_State;

    circle_t *right_circle = createCircle((coord_t) {3*SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, (unsigned short) 30, Red);
    int rightCircle_State;

    char strButton[30];
    int strButtonWidth;
    int rxButton1;
    int rxButton2;

    while(1){
        if (DrawSignal)
            if (xSemaphoreTake(DrawSignal, portMAX_DELAY) == pdTRUE) {
            tumEventFetchEvents( FETCH_EVENT_NONBLOCK); // Query events backend for new events, ie. button presses
            
 
            /* Begin drawing with white Background */
            tumDrawClear(White);

            vDrawFPS();
            /*Check for new counter Button One*/
            if(xQueuePeek(Queue_ButtonOne, &rxButton1, 0) && xQueuePeek(Queue_ButtonTwo, &rxButton2, 0)){ // is always True as there is always ine element in the queue                
                sprintf(strButton,"pressed Button [N]: %d Button [M]: %d ",rxButton1 ,rxButton2);
                if (!tumGetTextSize((char *)strButton, &strButtonWidth, NULL))
                    tumDrawText(strButton, SCREEN_CENTER.x -
                                strButtonWidth / 2, 3*SCREEN_HEIGHT/4 - DEFAULT_FONT_SIZE / 2,
                                TUMBlue);
            }           

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
                    mainGENERIC_PRIORITY+5, &Ex3_draw_handle) != pdPASS) {
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
     ButtonOneSemaphore = xSemaphoreCreateBinary();
    if (!ButtonOneSemaphore) {
        PRINT_ERROR("Failed to create ButtonOneSemaphore semaphore");
        goto err_handleButtonOne;
    }
    Queue_ButtonOne = xQueueCreate(1, sizeof(unsigned int));
    if (!Queue_ButtonOne) {
        PRINT_ERROR("Failed to create Queue_ButtonOne queue");
        goto err_Queue_ButtonOne;
    }
    /* to set the counter (Queue Element) to Zero */
    int zero = 0;
    xQueueSend(Queue_ButtonOne, &zero ,0);

    if (xTaskCreate(vButtonTrigger, "Buuton Trigger", mainGENERIC_STACK_SIZE , NULL,
                    mainGENERIC_PRIORITY+1, &buttonTrigger_handle) != pdPASS) {
		goto err_buttonTrigger;
	}
    if (xTaskCreate(vButtonOne, "Buuton One", mainGENERIC_STACK_SIZE , NULL,
                    mainGENERIC_PRIORITY+1, &buttonOne_handle) != pdPASS) {
		goto err_buttonOne;
	}
    Queue_ButtonTwo = xQueueCreate(1, sizeof(unsigned int));
    if (!Queue_ButtonTwo) {
        PRINT_ERROR("Failed to create Queue_ButtonTwo queue");
        goto err_Queue_ButtonTwo;
    }
    /* to set the counter (Queue Element) to Zero */
    xQueueSend(Queue_ButtonTwo, &zero ,0);

    if (xTaskCreate(vButtonTwo, "Buuton Two", mainGENERIC_STACK_SIZE , NULL,
                    mainGENERIC_PRIORITY+1, &buttonTwo_handle) != pdPASS) {
		goto err_buttonTwo;
	}

    vTaskSuspend(Ex3_draw_handle);
	vTaskSuspend(Ex3_t1_handle);
	vTaskSuspend(ex3_t2_handle);
    vTaskSuspend(buttonTrigger_handle);
    vTaskSuspend(buttonOne_handle);
    vTaskSuspend(buttonTwo_handle);

    return 0;

err_buttonTwo:
    vQueueDelete(Queue_ButtonTwo);
err_Queue_ButtonTwo:
    vTaskDelete(buttonOne_handle);
err_buttonOne:
    vTaskDelete(buttonTrigger_handle);
err_buttonTrigger:
    vQueueDelete(Queue_ButtonOne);
err_Queue_ButtonOne:
    vSemaphoreDelete(ButtonOneSemaphore);
err_handleButtonOne:
    vTaskDelete(ex3_t2_handle);
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
    if (buttonTrigger_handle) {
        vTaskDelete(buttonTrigger_handle);
    }
    if (buttonOne_handle) {
        vTaskDelete(buttonOne_handle);
    }
    if (buttonTwo_handle) {
        vTaskDelete(buttonTwo_handle);
    }
}

void Exercise3ExitFunction(void){
    printf("Exiting Tasks 3\n");
    vTaskSuspend(Ex3_draw_handle);
	vTaskSuspend(Ex3_t1_handle);
	vTaskSuspend(ex3_t2_handle);
    vTaskSuspend(buttonTrigger_handle);
    vTaskSuspend(buttonOne_handle);
    vTaskSuspend(buttonTwo_handle);
}

void Exercise3EnterFunction(void){
    printf("Resume Tasks 3\n");
    vTaskResume(Ex3_draw_handle);
	vTaskResume(Ex3_t1_handle);
	vTaskResume(ex3_t2_handle);
    vTaskResume(buttonTrigger_handle);
    vTaskResume(buttonOne_handle);
    vTaskResume(buttonTwo_handle);
}

void vButtonTrigger(void* pvparameters){
    
    while (1) {
    
        xGetButtonInput();

        if (checkButton(KEYCODE(N))) {
            printf("Button One pressed\n");
            xSemaphoreGive(ButtonOneSemaphore);
        }
        if (checkButton(KEYCODE(M))) {
            printf("Button Two pressed\n");
            xTaskNotifyGive( buttonTwo_handle );
        }
    
        vTaskDelay(10);    
    }

}

void vButtonOne(void * pvparameters){

    unsigned int counter = 0;

    while(1) {
        if(xSemaphoreTake(ButtonOneSemaphore, 0) == pdTRUE) {
            counter++;
            //xQueueOverwrite is used, because the queue should be full at all times
            printf("Counter of Button One incremented\n");
            xQueueOverwrite(Queue_ButtonOne, &counter);
        }
        vTaskDelay(10);
    }
}


void vButtonTwo(void * pvparameters){

    unsigned int counter = 0;
 
    while(1)
    {
        if(ulTaskNotifyTake(pdTRUE, portMAX_DELAY) != 0){
            counter++;
            printf("Counter of Button Two incremented\n");
            xQueueOverwrite(Queue_ButtonTwo, &counter);
        }
        vTaskDelay(10);
    }
}