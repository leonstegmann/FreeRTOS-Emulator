#include"ex3.h"

extern SemaphoreHandle_t DrawSignal;

void vExercise3Draw(void *pvParameters){

    /* Create Left Blinkng Circle*/
    circle_t *left_circle = createCircle((coord_t) {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, (unsigned short) 30, Red);
    tumDrawBindThread();
    
    while(1){
        if (DrawSignal);
        if(xSemaphoreTake(DrawSignal, 10) == pdTRUE);

        tumEventFetchEvents( FETCH_EVENT_NONBLOCK); // Query events backend for new events, ie. button presses
		xGetButtonInput(); // Update global input
        
        tumDrawClear(White);

        drawCircle(left_circle);
        tumDrawUpdateScreen();
        vTaskDelay((TickType_t) 500);

        tumDrawClear(White);
        tumDrawUpdateScreen();
        vTaskDelay((TickType_t) 500);

    }
}

void vExercise3Task1(void *pvParameters){


    while(1){

    }
}

void vExercise3Task2(void *pvParameters){

    
    while(1){

    }
}