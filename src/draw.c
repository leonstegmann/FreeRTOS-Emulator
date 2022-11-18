#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "TUM_Draw.h"
#include "TUM_Ball.h"
#include "TUM_Event.h"
#include "TUM_Font.h"

#include"shapes.h"



void vDraw(void *pvParameters)
{
    //define Circle Object pramteters
    coord_t startingPoint_circle = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 };
    unsigned short radius = 30;

    //CREATE OBJECT
    circle_t *red_circle = createCircle(startingPoint_circle, radius, Red);

    //define Square Object pramteters
    coord_t startingPoint_square = {3 * SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 };
    signed short square_width = 60;
    signed short square_height = 60;

    //CREATE OBJECT
    square_t *blue_square = createSquare(startingPoint_square, square_width, square_height, TUMBlue );
    // signed short x_s = ((2 * SCREEN_WIDTH) / 3 ) - w / 2;
    // signed short y_s = (SCREEN_HEIGHT / 2) - w / 2;

    //define Triangle Object pramteters
    coord_t startingPoint_triangle = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    coord_t corners[3] = {{-25,-23},{0,23},{25,-23}};

    //CREATE OBJECT
    triangle_t *orange_triangle = createTriangle(startingPoint_triangle, corners, Orange);

    //Transfers the drawing ability to the calling thread/taskd
    tumDrawBindThread();


    while (1) {

        tumEventFetchEvents(FETCH_EVENT_NONBLOCK); // Query events backend for new events, ie. button presses

        if(!drawCircle(red_circle))
            drawCircle(red_circle);

        if(!drawSquare(blue_square))
            drawSquare(blue_square);

        if(!drawTriangle(orange_triangle))
           drawTriangle(orange_triangle);

        tumDrawUpdateScreen();
        vTaskDelay((TickType_t) 1000);

    }

}
