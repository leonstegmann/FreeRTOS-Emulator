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

        vDrawFPS();

        drawCircle(left_circle);
        tumDrawUpdateScreen();

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