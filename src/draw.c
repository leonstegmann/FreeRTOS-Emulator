#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "TUM_Draw.h"
#include "TUM_Ball.h"
#include "TUM_Event.h"
#include "TUM_Font.h"

#include"buttons.h"

void vDraw(void *pvParameters)
{

    // create local variables for Drawing Circle
    signed short x_c = SCREEN_WIDTH / 2;
    signed short y_c = SCREEN_HEIGHT / 2;
    signed short radius = 30;
	unsigned int colour_c = TUMBlue;

    // create local variables for Drawing Square
    signed short w = 60;
    signed short h = 60;
    signed short x_s = ((2 * SCREEN_WIDTH) / 3 ) - w / 2; 
    signed short y_s = (SCREEN_HEIGHT / 2) - w / 2;
	unsigned int colour_s = Red;

    //Transfers the drawing ability to the calling thread/taskd
    tumDrawBindThread();
    

    while (1) {
    
        tumEventFetchEvents(FETCH_EVENT_NONBLOCK); // Query events backend for new events, ie. button presses

        if(!tumDrawCircle( x_c, y_c, radius, colour_c))
            tumDrawCircle( x_c, y_c, radius, colour_c);
        
        if(!tumDrawFilledBox( x_s, y_s, w, h, colour_s))
            tumDrawFilledBox( x_s, y_s, w, h, colour_s);
        
        
        tumDrawUpdateScreen();
        vTaskDelay((TickType_t) 1000);

    }
    
}
