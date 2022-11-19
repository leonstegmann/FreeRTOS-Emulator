#include <stdio.h>
#include"math.h"

#include "FreeRTOS.h"
#include "task.h"

#include "TUM_Draw.h"
#include "TUM_Ball.h"
#include "TUM_Event.h"
#include "TUM_Font.h"

#include"shapes.h"


void vDraw(void *pvParameters)
{
    //for Synchroninzing
    TickType_t xLastWakeTime, prevWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    prevWakeTime = xLastWakeTime;
    const TickType_t updatePeriod = 10;

    ///define Parameters of shapes
    // Circle
    coord_t startingPoint_circle = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 };
    unsigned short radius = 30;

    //Square
    coord_t startingPoint_square = {3 * SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 };
    signed short square_width = 60;
    signed short square_height = 60;

    //Triangle
    coord_t startingPoint_triangle = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    coord_t corners[3] = {{-25,-23},{0,23},{25,-23}};

    //CREATE OBJECTs
    circle_t *red_circle = createCircle(startingPoint_circle, radius, Red);
    square_t *blue_square = createSquare(startingPoint_square, square_width, square_height, TUMBlue );
    triangle_t *orange_triangle = createTriangle(startingPoint_triangle, corners, Orange);

    //Transfers the drawing ability to the calling thread/taskd
    tumDrawBindThread();


    while (1) {

        tumEventFetchEvents(FETCH_EVENT_NONBLOCK); // Query events backend for new events, ie. button presses

        tumDrawClear(White);

        if(!drawCircle(red_circle))
            drawCircle(red_circle);

        if(!drawSquare(blue_square))
            drawSquare(blue_square);

        if(!drawTriangle(orange_triangle))
           drawTriangle(orange_triangle);

        moveShape(&(red_circle->shape), xLastWakeTime - prevWakeTime);
        
        setSpeed(&(red_circle->shape), 500*sin(2*M_PI * (red_circle->shape.dx+10) / 500), 0);// 500*cos(2*M_PI * (red_circle->shape.dy+10) / 500));

        tumDrawUpdateScreen();

        //Update last synch time
        prevWakeTime = xLastWakeTime;
        vTaskDelayUntil(&xLastWakeTime, updatePeriod);

    }

}
