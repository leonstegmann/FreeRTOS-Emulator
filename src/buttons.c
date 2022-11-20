#include "buttons.h"

buttons_buffer_t buttons = { 0 };

void xGetButtonInput(void)
{
	if (xSemaphoreTake(buttons.lock, 0) == pdTRUE) {
		xQueueReceive(buttonInputQueue, &buttons.buttons, 0);
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

void drawButton(button_t* this_button){
    char string_tmp[100];
    sprintf(string_tmp,"%c: %d", this_button->id, this_button->counter);
    tumDrawText(string_tmp, this_button->pos.x, 
                this_button->pos.y, Black);
}

button_t createButton(char id, coord_t pos){

    button_t *ret = calloc(1, sizeof(button_t));

    if (!ret) {
        fprintf(stderr, "Creating ball failed\n");
        exit(EXIT_FAILURE);
    }

    ret->id = id;
    ret->pos = pos;
    ret->counter = 0;
    
    return *ret;
}
