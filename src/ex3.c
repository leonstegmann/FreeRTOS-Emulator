#include"ex3.h"

void vExercise3Task1(void *pvParameters){

    /* Create Left Blinkng Circle*/
   // circle_t *left_circle = createCircle((coord_t) {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, (unsigned short) 30, Red);
    tumDrawBindThread();

    while(1){
        tumEventFetchEvents( FETCH_EVENT_NONBLOCK); // Query events backend for new events, ie. button presses
		xGetButtonInput(); // Update global input
    
        //printf("\nHello Task3_1 here");
    
        tumDrawClear(White);
        //drawCircle(left_circle);
        //vTaskDelay(500);

        tumDrawUpdateScreen();
        vTaskDelay((TickType_t) 1000);

    }
}

void vExercise3Task2(void *pvParameters){

    
    while(1){

    }
}