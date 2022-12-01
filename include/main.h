#ifndef __MAIN__ 
#define __MAIN__
/*Libraries*/
#include "task.h"
#include"semaphore.h"

/* Defines variables  */
#define mainGENERIC_PRIORITY    (tskIDLE_PRIORITY)
#define mainGENERIC_STACK_SIZE  ((unsigned short)2560)
#define KEYCODE(CHAR)           SDL_SCANCODE_##CHAR     // SDL_SCANCODE for te keybord use i buttons
#define FRAMERATE               50

/* RTOS Taskhandles -> Instantiating
* Each Task has his own Reference as taskhandle. Needed to Delete Tasks 
* FreeRTOS intern: Used to pass a handle to the created task out of the xTaskCreate() function.
*/
extern TaskHandle_t Ex2_handle;

/* RTOS Semaphorehandles -> Instantiating  */
extern SemaphoreHandle_t DrawSignal;
extern SemaphoreHandle_t ScreenLock;

#endif // _MAIN_
