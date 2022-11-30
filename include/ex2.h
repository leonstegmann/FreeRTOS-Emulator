//include Guards to ensure  initialising Header files only once
#ifndef __EX_2__  
#define __EX_2__

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

#define  SCREEN_CENTER (coord_t) {SCREEN_WIDTH/2 , SCREEN_HEIGHT/2} 

/**
 * @brief Exercise 2: draw objects and handles logic
 * @param pvParameters A value that is passed as the paramater to the created task in FreeRTOS 
 */
void vExercise2(void *pvParameters);

#endif //__EX_2__