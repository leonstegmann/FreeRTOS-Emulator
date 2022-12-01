#ifndef __UTILITYFUN__ 
#define __UTILITYFUN__

/* FreeRTOS includes */
#include "task.h"
#include "FreeRTOS.h"

extern TaskHandle_t BufferSwap_handle; 

void vDrawFPS(void);

void vSwapBuffers(void *pvParameters);

#endif 