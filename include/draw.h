//include Guards to ensure  initialising Header files only once
#ifndef __DRAW_H__  
#define __DRAW_H__

static coord_t SCREEN_CENTER = {SCREEN_WIDTH/2 , SCREEN_HEIGHT/2}; 

void vDraw(void *pvParameters);

#endif //__DRAW_H__