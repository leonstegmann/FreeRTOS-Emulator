#include "main.h"

/**
 * @brief Task to swap the buffer of the screen to have a smooth user experience
*/
void vSwapBuffers(void *pvParameters)
{
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    const TickType_t frameratePeriod = 1000 / FRAMERATE;

    //tumDrawBindThread(); // Setup Rendering handle with correct GL context

	printf("\nDebugPrint: bufferswap "); //DEBUG PRINT

    while (1) {
        tumDrawUpdateScreen();
        tumEventFetchEvents(FETCH_EVENT_BLOCK);
        xSemaphoreGive(DrawSignal);
        vTaskDelayUntil(&xLastWakeTime,
                        pdMS_TO_TICKS(frameratePeriod));
    }
}

/* RTOS Taskhandles -> initializing*/
TaskHandle_t BufferSwap = NULL;
TaskHandle_t ex2_handle = NULL;
TaskHandle_t ex3_draw_handle = NULL;
TaskHandle_t ex3_t1_handle = NULL;

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

	printf("\nInitialization SUCCESS!! \nMoving on to create tasks... \n");    

/*-----------------------------------------------------------------------------------------------*/	
	/* FreeRTOS Task creation*/
	if (xTaskCreate(vSwapBuffers, "BufferSwapTask",
                    mainGENERIC_STACK_SIZE * 2, NULL, configMAX_PRIORITIES,
                    &BufferSwap) != pdPASS) {
        goto err_bufferswap;
	}
	
	if (xTaskCreate(vExercise2, "Exercise_2", mainGENERIC_STACK_SIZE * 2, NULL,
                    mainGENERIC_PRIORITY, &ex2_handle) != pdPASS) {
		goto err_ex2;
	}
			
	if (xTaskCreate(vExercise3Draw, "Exercise_3_Draw", mainGENERIC_STACK_SIZE * 2, NULL,
                    mainGENERIC_PRIORITY, &ex3_draw_handle) != pdPASS) {
		goto err_ex3_draw;
	}

	if (xTaskCreate(vExercise3Task1, "Exercise_3_Task_1", mainGENERIC_STACK_SIZE * 2, NULL,
                    mainGENERIC_PRIORITY, &ex3_t1_handle) != pdPASS) {
		goto err_ex3_t1;
	}



	tumFUtilPrintTaskStateList();

	vTaskSuspend(BufferSwap); // Task Suspended for Debug purposes
	vTaskSuspend(ex2_handle);
	vTaskSuspend(ex3_t1_handle);
	
	tumFUtilPrintTaskStateList();

/*-----------------------------------------------------------------------------------------------*/	
	/* start FreeRTOS Sceduler: Should never get passed this function */

	vTaskStartScheduler(); 
	
	atexit(aIODeinit);

	return EXIT_SUCCESS; // Return State Main

/*-----------------------------------------------------------------------------------------------*/	
/* Error handling -> delete everything that has been initialized so far (Backwards the Init Order)*/
err_ex3_t1:
	vTaskDelete(ex3_draw_handle);
err_ex3_draw:
	vTaskDelete(ex2_handle);
err_ex2:
	vTaskDelete(BufferSwap); // Delete TaskHandle
err_bufferswap:
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
