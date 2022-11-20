#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include <SDL2/SDL_scancode.h>

#include "FreeRTOS.h"
#include "semphr.h"
#include"task.h"

#include"TUM_Draw.h"
#include "TUM_Event.h"
#include "TUM_Print.h"

#define KEYCODE(CHAR) SDL_SCANCODE_##CHAR
#define  DEBOUNCEDELAY (TickType_t) 50      // the debounce time

typedef struct buttons_buffer {

    unsigned char prevState[SDL_NUM_SCANCODES];
    TickType_t lastTimePressed[SDL_NUM_SCANCODES];
    unsigned char currentState[SDL_NUM_SCANCODES];
    unsigned short counter[SDL_NUM_SCANCODES];
    char id[SDL_NUM_SCANCODES];
    coord_t pos[SDL_NUM_SCANCODES];
    unsigned int colour[SDL_NUM_SCANCODES]; /**< Hex RGB colour */
    SemaphoreHandle_t lock;

} buttons_buffer_t;

extern buttons_buffer_t buttons;

void xGetButtonInput(void);
int buttonsInit(void);
void buttonsExit(void);
void checkButton(int );

typedef struct button{

    char id;
    coord_t pos;

} button_t;

void drawButton(int keyvalue);

void createButtonObject(char id, coord_t pos, int keyvalue);

#endif //__BUTTONS_H__