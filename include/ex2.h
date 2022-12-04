/*include Guards to ensure  initialising Header files only once*/
#ifndef __EX_2__  
#define __EX_2__

#define  SCREEN_CENTER (coord_t) {SCREEN_WIDTH/2 , SCREEN_HEIGHT/2} 

/**
 * @brief Exercise 2: draw objects and handles logic
 * @param pvParameters A value that is passed as the paramater to the created task in FreeRTOS 
 */
void vExercise2(void *pvParameters);

void Exercise2EnterFunction(void);
void Exercise2ExitFunction(void);


#endif //__EX_2__