#ifndef __MAIN__ 
#define __MAIN__

/* Library includes */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include <SDL2/SDL_scancode.h> //for reading Keyboard Input
#include "AsyncIO.h"

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

/* TUM_Library includes  */
#include "TUM_Ball.h"
#include "TUM_Print.h"
#include "TUM_Draw.h"
#include "TUM_Event.h"
#include "TUM_Sound.h"
#include "TUM_Utils.h"
#include "TUM_Font.h"
#include "TUM_FreeRTOS_Utils.h"

/* Project includes  */
#include "defines.h"
#include "buttons.h"
#include "ex2.h"
#include "ex3.h"

/* RTOS Taskhandles -> Instantiating: each Task has his own Reference as taskhandle. Needed to Delete Tasks */
extern TaskHandle_t BufferSwap; // FreeRTOS intern: Used to pass a handle to the created task out of the xTaskCreate() function.
extern TaskHandle_t ex2_handle; // FreeRTOS intern: Used to pass a handle to the created task out of the xTaskCreate() function.
extern TaskHandle_t ex3_t1_handle; // FreeRTOS intern: Used to pass a handle to the created task out of the xTaskCreate() function.

/* RTOS Semaphorehandles -> Instantiating  */
extern SemaphoreHandle_t DrawSignal;
extern SemaphoreHandle_t ScreenLock;

#endif // _MAIN_
