/* Library includes */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include <SDL2/SDL_scancode.h> //for reading Keyboard Input
#include "AsyncIO.h"

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

/* TUM_Library includes  */
#include "TUM_Ball.h"
#include "TUM_Print.h"
#include "TUM_Draw.h"
#include "TUM_Event.h"
#include "TUM_Sound.h"
#include "TUM_Utils.h"
#include "TUM_Font.h"

/* Project includes  */
#include "ex2.h"
#include"buttons.h"

/* Defines variables  */
#define mainGENERIC_PRIORITY (tskIDLE_PRIORITY)
#define mainGENERIC_STACK_SIZE ((unsigned short)2560)
#define KEYCODE(CHAR) SDL_SCANCODE_##CHAR // SDL_SCANCODE for te keybord use i buttons

/* Static variables  */
static TaskHandle_t ex2_handle = NULL; // FreeRTOS intern: Used to pass a handle to the created task out of the xTaskCreate() function.
