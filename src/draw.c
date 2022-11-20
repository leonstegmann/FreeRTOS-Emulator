#include <stdio.h>
#include"math.h"

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

#include "TUM_Draw.h"
#include "TUM_Ball.h"
#include "TUM_Event.h"
#include "TUM_Font.h"


#include"shapes.h"

static coord_t SCREEN_CENTER = {SCREEN_WIDTH/2 , SCREEN_HEIGHT/2}; 

extern SemaphoreHandle_t ScreenLock;

void rotateShape(shape_t* shape, coord_t origin){
    shape->location.x = SCREEN_CENTER.x + (origin.x-SCREEN_CENTER.x) * sin(2*M_PI * (shape->location.x +10) / 1000);
//    shape->location.y += origin.y; 
    shape->pixelLocation.x = round(shape->location.x);
    shape->pixelLocation.y = round(shape->location.y);
}

void updateLocation(shape_t* shape, coord_t offset){
    shape->location.x = SCREEN_CENTER.x + offset.x;
    shape->location.y = shape->starting_position.y + offset.y;
    shape->pixelLocation.x = round(shape->location.x);
    shape->pixelLocation.y = round(shape->location.y);
}

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


    coord_t offset = {0,0};
    float rad=0;
    int ROTATION_RADIUS = SCREEN_CENTER.x - startingPoint_circle.x;

    static char string_static[20]= "Random Text";
	static int string_static_width = 0;
    static char string_dynamic[20]= "Moving Text";
	static int string_dynamic_width = 0;
    

    while (1) {
        
        tumEventFetchEvents(FETCH_EVENT_NONBLOCK); // Query events backend for new events, ie. button presses

        tumDrawClear(White);
        
        if(!drawCircle(red_circle))
            drawCircle(red_circle);

        if(!drawSquare(blue_square))
            drawSquare(blue_square);

        if(!drawTriangle(orange_triangle))
           drawTriangle(orange_triangle);

        // Static Text 
        if (!tumGetTextSize((char *)string_static,
				    &string_static_width, NULL))
			tumDrawText(string_static,
				    SCREEN_CENTER.x -
					    string_static_width / 2,
				    3*SCREEN_HEIGHT/4 - DEFAULT_FONT_SIZE / 2,
				    TUMBlue);

        // Moving Text
        if (!tumGetTextSize((char *)string_dynamic,
				    &string_dynamic_width, NULL))
			tumDrawText(string_dynamic,
                    SCREEN_CENTER.x - string_dynamic_width / 2 + + offset.x,
				    1*SCREEN_HEIGHT/4 - DEFAULT_FONT_SIZE / 2,
				    TUMBlue);


        //Calculate rotational Offset
        offset.x = (int) (ROTATION_RADIUS * sin(rad));
        offset.y = (int) (ROTATION_RADIUS * cos(rad));
    
        //Increment Rotation
        if(rad >= 2*M_PI)
                rad=0;
            else
                rad += 0.03;

        updateLocation(&(red_circle->shape), offset);

        //rotateShape(&(red_circle->shape), startingPoint_circle);

        //moveShape(&(red_circle->shape), xLastWakeTime - prevWakeTime);
        
        //setSpeed(&(red_circle->shape), 500*sin(2*M_PI * (red_circle->shape.dx+10) / 500), 0);// 500*cos(2*M_PI * (red_circle->shape.dy+10) / 500));

        tumDrawUpdateScreen();

        //Update last synch time
        prevWakeTime = xLastWakeTime;
        vTaskDelayUntil(&xLastWakeTime, updatePeriod);

    }

}
