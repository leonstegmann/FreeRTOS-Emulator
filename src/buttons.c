#include "buttons.h"

buttons_buffer_t buttons = { 0 };

void xGetButtonInput(void)
{
	if (xSemaphoreTake(buttons.lock, 0) == pdTRUE) {
		xQueueReceive(buttonInputQueue, &buttons.currentState, 0);
		xSemaphoreGive(buttons.lock);
	}
}

int buttonsInit(void)
{
    buttons.lock = xSemaphoreCreateMutex(); // Locking mechanism
    if (!buttons.lock) {
        PRINT_ERROR("Failed to create buttons lock");
        return -1;
    }

    return 0;
}

void buttonsExit(void)
{
    vSemaphoreDelete(buttons.lock);
}

void drawButton(int keyvalue){
    char string_tmp[100];
    sprintf(string_tmp,"%c: %d", buttons.id[keyvalue], buttons.counter[keyvalue]);
    tumDrawText(string_tmp, buttons.pos[keyvalue].x, 
                buttons.pos[keyvalue].y, buttons.colour[keyvalue]);
}

void setDisplayedButtonName(char id, int keyvalue){
    buttons.id[keyvalue]= id;
}

void setButtonPosition(coord_t pos, int keyvalue){
    buttons.pos[keyvalue] = pos;
}

void setButtonColour(unsigned int colour, int keyvalue){
    buttons.colour[keyvalue] = colour;
}

void resetCounter(int keyvalue){
    buttons.counter[keyvalue] = 0;
}

void checkButton(int keyvalue){
    if (buttons.currentState[keyvalue]) { // Equiv to SDL_SCANCODE_Q
        TickType_t now = xTaskGetTickCount();
        if ( buttons.currentState[keyvalue] > 0 && buttons.prevState[keyvalue] == 0){
            if ((now - buttons.lastTimePressed[keyvalue]) > DEBOUNCEDELAY ){
                buttons.counter[keyvalue]++;
                buttons.lastTimePressed[keyvalue] = now;
            }
        }
    }
    buttons.prevState[keyvalue] = buttons.currentState[keyvalue];
}
