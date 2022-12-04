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
#include"TUM_FreeRTOS_Utils.h"

/* Project includes  */
#include"main.h"
#include"buttons.h"
#include"utility_functions.h"
#include"state_machine.h"
#include "ex2.h"
#include "ex3.h"


/**
 * @brief Task to swap the buffer of the screen to have a smooth user experience
*/

/* RTOS Taskhandles -> initializing*/
TaskHandle_t BufferSwap_handle  = NULL;
TaskHandle_t Ex2_handle  = NULL;
TaskHandle_t StatesHandler = NULL;

/* RTOS Semaphorehandles -> initializing  */
SemaphoreHandle_t DrawSignal = NULL;
SemaphoreHandle_t ScreenLock = NULL;

int main(int argc, char *argv[])
{
	char *bin_folder_path = tumUtilGetBinFolderPath(argv[0]);

	printf("Initializing: ");

	if (tumDrawInit(bin_folder_path)) {
		PRINT_ERROR("Failed to initialize drawing");
		goto err_init_drawing;
	}

	if (tumEventInit()) {
		PRINT_ERROR("Failed to initialize events");
		goto err_init_events;
	}

	if (tumSoundInit(bin_folder_path)) {
		PRINT_ERROR("Failed to initialize audio");
		goto err_init_audio;
	}

	atexit(aIODeinit); // standart C library: passed function pointer gets calles when function exits -> ensures to clean sockets, Queues etc 

	buttons.lock = xSemaphoreCreateMutex(); // Locking mechanism
	if (!buttons.lock) {
		PRINT_ERROR("Failed to create buttons lock");
		goto err_buttons_lock;
	}

	DrawSignal = xSemaphoreCreateBinary();
    if (!DrawSignal) {
        PRINT_ERROR("Failed to create draw signal");
        goto err_draw_signal;
    }

    ScreenLock = xSemaphoreCreateMutex(); //Locks Screen 
    if (!ScreenLock) {
        PRINT_ERROR("Failed to create screen lock");
        goto err_screen_lock;
    }

	Queue_ex3_Handle = xQueueCreate(10,sizeof(int));
	if (!Queue_ex3_Handle) {
        PRINT_ERROR("Failed to create queue");
        goto err_queue_ex3_handle;
	}
	
	/* State Maschine confiuration*/
	states_add(NULL,Exercise2EnterFunction,NULL,Exercise2ExitFunction,1,"ex2");
	states_add(NULL,Exercise3EnterFunction,NULL,Exercise3ExitFunction,2,"ex3");
	states_init();
	states_set_state(1);

	printf("\nInitialization SUCCESS!! \nMoving on to create tasks... \n");    

/*-----------------------------------------------------------------------------------------------*/	
	/* FreeRTOS Task creation*/
	if (xTaskCreate(vSwapBuffers, "BufferSwapTask",
                    mainGENERIC_STACK_SIZE * 2, NULL, configMAX_PRIORITIES,
                    &BufferSwap_handle) != pdPASS) {
        goto err_bufferswap;
	}

	 if (xTaskCreate(vStatesHandler, "StatesHandler", 
                    mainGENERIC_STACK_SIZE * 2, NULL, configMAX_PRIORITIES-2,
                    &StatesHandler) != pdPASS) {
        goto err_statesHandler;
    }
	
	if (xTaskCreate(vExercise2, "Exercise_2", mainGENERIC_STACK_SIZE * 2, NULL,
                    mainGENERIC_PRIORITY, &Ex2_handle) != pdPASS) {
		goto err_ex2;
	}
			
	if (createExercise3Tasks())
		goto err_Exercise3;

	tumFUtilPrintTaskStateList();

	vTaskSuspend(BufferSwap_handle);
	vTaskSuspend(Ex2_handle);
	
/*-----------------------------------------------------------------------------------------------*/	
	/* start FreeRTOS Sceduler: Should never get passed this function */

	tumFUtilPrintTaskStateList();

	vTaskStartScheduler(); 
	
	atexit(aIODeinit);

	return EXIT_SUCCESS; // Return State Main

/*-----------------------------------------------------------------------------------------------*/	
/* Error handling -> delete everything that has been initialized so far (Backwards the Init Order)*/
	deleteExercise3Tasks();
err_Exercise3:
	vTaskDelete(Ex2_handle);
err_ex2:
	vTaskDelete(StatesHandler);
err_statesHandler:
	vTaskDelete(BufferSwap_handle); // Delete TaskHandle
err_bufferswap:
	vQueueDelete(Queue_ex3_Handle);
err_queue_ex3_handle:
	vSemaphoreDelete(ScreenLock);
err_screen_lock:
	vSemaphoreDelete(DrawSignal);
err_draw_signal:
	vSemaphoreDelete(buttons.lock);
err_buttons_lock:
	tumSoundExit();
err_init_audio:
	tumEventExit();
err_init_events:
	tumDrawExit();
err_init_drawing:

	return EXIT_FAILURE; // Return State Main
}

/*-----------------------------------------------------------------------------------------------*/	
// cppcheck-suppress unusedFunction
__attribute__((unused)) void vMainQueueSendPassed(void)
{
	/* This is just an example implementation of the "queue send" trace hook. */
}

// cppcheck-suppress unusedFunction
__attribute__((unused)) void vApplicationIdleHook(void)
{
#ifdef __GCC_POSIX__
	struct timespec xTimeToSleep, xTimeSlept;
	/* Makes the process more agreeable when using the Posix simulator. */
	xTimeToSleep.tv_sec = 1;
	xTimeToSleep.tv_nsec = 0;
	nanosleep(&xTimeToSleep, &xTimeSlept);
#endif
}
