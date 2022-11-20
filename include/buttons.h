#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include <SDL2/SDL_scancode.h>

#include "FreeRTOS.h"
#include "semphr.h"

#include"TUM_Draw.h"
#include "TUM_Event.h"
#include "TUM_Print.h"

#define KEYCODE(CHAR) SDL_SCANCODE_##CHAR

typedef struct buttons_buffer {
    unsigned char buttons[SDL_NUM_SCANCODES];
    SemaphoreHandle_t lock;
} buttons_buffer_t;

extern buttons_buffer_t buttons;

void xGetButtonInput(void);
int buttonsInit(void);
void buttonsExit(void);

typedef struct button{
    char id;
    coord_t pos;
    unsigned short counter;
} button_t;

void drawButton(button_t* );

button_t createButton(char , coord_t );

#endif //__BUTTONS_H__