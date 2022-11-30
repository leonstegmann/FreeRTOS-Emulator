//include Guards to ensure  initialising Header files only once
#ifndef __EX_3__  
#define __EX_3__

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
#include"shapes.h"
#include"buttons.h"

/**
 * @brief Exercise 3: 
 * @param pvParameters A value that is passed as the paramater to the created task in FreeRTOS 
 */
void vExercise3Task1(void *pvParameters);
void vExercise3Task2(void *pvParameters);

#endif //__EX_3__