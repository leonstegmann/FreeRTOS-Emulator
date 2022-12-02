//include Guards to ensure  initialising Header files only once
#ifndef __EX_3__  
#define __EX_3__

#include"queue.h"

/**
 * @brief Exercise 3: 
 * @param pvParameters A value that is passed as the paramater to the created task in FreeRTOS 
 */
void vExercise3Draw(void *pvParameters);
void vExercise3Task1(void *pvParameters);
void vExercise3Task2(void *pvParameters);

int createExercise3Tasks(void);

extern QueueHandle_t Queue_ex3_Handle;

#endif //__EX_3__