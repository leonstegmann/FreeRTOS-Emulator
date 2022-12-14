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

void vButtonTrigger(void* pvparameters);
void vButtonOne(void * pvparameters);
/* Triggers Button by TaskNotification*/
void vButtonTwo(void * pvparameters);


int createExercise3Tasks(void);
void deleteExercise3Tasks(void);

void Exercise3EnterFunction(void);
void Exercise3ExitFunction(void);


extern QueueHandle_t Queue_ex3_Handle;

#endif //__EX_3__