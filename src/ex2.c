/* Library includes */
#include <stdio.h>
#include"math.h"

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
#include"main.h"
#include"shapes.h"
#include"buttons.h"
#include"ex2.h"

void vExercise2(void *pvParameters)
{   
    //for Synchroninzing
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    const TickType_t updatePeriod = 10;

    ///define Parameters of shapes
    /// Circle
    coord_t startingPoint_circle = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 };
    unsigned short radius = 30;

    ///Square
    coord_t startingPoint_square = {3 * SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 };
    signed short square_width = 60;
    signed short square_height = 60;

    ///Triangle
    coord_t startingPoint_triangle = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    coord_t corners[3] = {{-25,-23},{0,23},{25,-23}};

    ///CREATE OBJECTs
    circle_t *red_circle = createCircle(startingPoint_circle, radius, Red);
    square_t *blue_square = createSquare(startingPoint_square, square_width, square_height, TUMBlue );
    triangle_t *orange_triangle = createTriangle(startingPoint_triangle, corners, Orange);

    //Transfers the drawing ability to the calling thread/taskd
    tumDrawBindThread();


    static coord_t offset = {0,0};
    float rad=0;
    int ROTATION_RADIUS = abs(SCREEN_CENTER.x - startingPoint_circle.x);

    static char string_static[20] = "Random Text";
	static int string_static_width = 0;
    static char string_dynamic[20]= "Moving Text";
	static int string_dynamic_width = 0;
    static char string_mouse_position[100];
    static coord_t mouse_location;

    // Button Objects for GUI
    int button_keycodes[4] = {KEYCODE(A),KEYCODE(B),KEYCODE(C),KEYCODE(D)};
    for (int i=0; i < 4 ; i++){
        setButtonColour(Black,button_keycodes[i]);
        setButtonPosition((coord_t) {i*SCREEN_WIDTH/8, SCREEN_HEIGHT/10},button_keycodes[i]);
        resetCounter(button_keycodes[i]);
    }
    
    setDisplayedButtonName('A',button_keycodes[0]);
    setDisplayedButtonName('B',button_keycodes[1]);
    setDisplayedButtonName('C',button_keycodes[2]);
    setDisplayedButtonName('D',button_keycodes[3]);

    while (1) {
        if(DrawSignal)
            /* so no other task can draw at the same time */
            if(xSemaphoreTake(DrawSignal, 10) == pdTRUE);

            tumEventFetchEvents(FETCH_EVENT_NONBLOCK); // Query events backend for new events, ie. button presses

            xGetButtonInput(); // Update global input 

            if (xSemaphoreTake(buttons.lock, 0) == pdTRUE) {
                if (buttons.currentState[KEYCODE(Q)]) { // Equiv to SDL_SCANCODE_Q
                    exit(EXIT_SUCCESS);
                }
                for (int i=0; i < 4 ; i++){
                    checkButton(button_keycodes[i]);
                }
                xSemaphoreGive(buttons.lock);
            }

            if (tumEventGetMouseLeft()){
                for (int i=0; i<4; i++){
                    buttons.counter[button_keycodes[i]] = 0;
                }
            }

            mouse_location = (coord_t) {tumEventGetMouseX(), tumEventGetMouseY()};            

            tumDrawSetGlobalXOffset	( mouse_location.x - SCREEN_CENTER.x );
            tumDrawSetGlobalYOffset	( mouse_location.y - SCREEN_CENTER.y );

            //Calculate rotational Offset
            offset.x = (int) (ROTATION_RADIUS * sin(rad));
            offset.y = (int) (ROTATION_RADIUS * cos(rad));
        
            //Increment Rotation
            if(rad >= 2*M_PI)
                    rad=0;
                else
                    rad += 0.03;

            /* take Screenlock while drawing*/
            xSemaphoreTake(ScreenLock, portMAX_DELAY);

            tumDrawClear(White);
            
            if(!drawCircle(red_circle))

            if(!drawSquare(blue_square))

            if(!drawTriangle(orange_triangle))

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
                        SCREEN_HEIGHT/4 - DEFAULT_FONT_SIZE / 2,
                        TUMBlue);

            updateLocation(&(red_circle->shape), offset);
            updateLocation(&(blue_square->shape), (coord_t) {-offset.x, -offset.y});
            
            //Draw Buttons 
            for (int i=0; i<4; i++){
            drawButton(button_keycodes[i]);
            }
            
            //Print Mouse Coordinates
            sprintf(string_mouse_position, "Mouse position: X: %d | Y: %d", mouse_location.x, mouse_location.y); 
                tumDrawText(string_mouse_position, 20, 10, Black);

            tumDrawUpdateScreen();

            /* Give back Screenlock Semaphore*/
            xSemaphoreGive(ScreenLock);

            //Update last synch time
            vTaskDelayUntil(&xLastWakeTime, updatePeriod);
                    
    }
}

void Exercise2EnterFunction(void){
    printf("Resume Tasks 2");
    vTaskResume(Ex2_handle);
	
}

void Exercise2ExitFunction(void){
    printf("Exiting Tasks 2");
    vTaskSuspend(Ex2_handle);

}

