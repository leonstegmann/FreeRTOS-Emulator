/**
 * @file buttons.h
 * @author Leon Stegmann
 * @brief provides the Structs and Functions for the use of buttons
 */

#ifndef __BUTTONS_H__
#define __BUTTONS_H__

/* FreeRTOS includes  */
#include <SDL2/SDL_scancode.h>
#include"semphr.h"

/* TUM_Library includes  */
#include"TUM_Draw.h"

 /* Defines variables  */
#define KEYCODE(CHAR) SDL_SCANCODE_##CHAR
#define  DEBOUNCEDELAY (TickType_t) 50      // the debounce time

/**
 * @brief stores the currrent state of every button
 *      and has a SemaphoreHandle to be locked
 */
typedef struct buttons_buffer {
    unsigned char prevState[SDL_NUM_SCANCODES]; /**to be able to compare current with previous state*/
    TickType_t lastTimePressed[SDL_NUM_SCANCODES]; /** to ensure debounce time */
    unsigned char currentState[SDL_NUM_SCANCODES]; /** current button state */
    unsigned short counter[SDL_NUM_SCANCODES]; /**how often button got pressed */
    char id[SDL_NUM_SCANCODES]; /* the button name */
    coord_t pos[SDL_NUM_SCANCODES]; /* position of the button on the GUI */
    unsigned int colour[SDL_NUM_SCANCODES]; /**< Hex RGB colour */
    SemaphoreHandle_t lock; /* FreeRTOS Semaphore handle*/
} buttons_buffer_t;

extern buttons_buffer_t buttons; /* Instantiating the buttons as external object to access them from wherever needed*/

/**
 * @brief writes all current button values to the object "extern buttons_buffer_t buttons"
 */
void xGetButtonInput(void);

/**
 * @brief creates the locking Semaphore
 * @return returns 0 if successful and -1 if an error occured
 */
int buttonsInit(void);

/**
 * @brief deletes the Semaphore 
 */
void buttonsExit(void);

/**
 * @brief ensures the debounce of the buttons 
 * @param keyvalue intakes the "#define KEYCODE(CHAR)" from the "SDL_SCANCODE_##CHAR" as "int"
 */
void checkButton(int );

/**
 * @brief draws the button with the corresponding keyvalue 
 * @param keyvalue intakes the "#define KEYCODE(CHAR)" from the "SDL_SCANCODE_##CHAR" as "int"
 */
void drawButton(int keyvalue);

/**
 * @brief Setter for the Button Name displayed on the GUI 
 * @param id Button Name
 * @param keyvalue intakes the "#define KEYCODE(CHAR)" from the "SDL_SCANCODE_##CHAR" as "int"
 */ 
void setDisplayedButtonName(char , int );

/**
 * @brief Setter for the Button Position where it is displayed on the GUI 
 * @param position Button position  "coord_t"
 * @param keyvalue intakes the "#define KEYCODE(CHAR)" from the "SDL_SCANCODE_##CHAR" as "int"
 */ 
void setButtonPosition(coord_t , int );

/**
 * @brief Setter for the Button Colour displayed on the GUI 
 * @param colour Button Colour
 * @param keyvalue intakes the "#define KEYCODE(CHAR)" from the "SDL_SCANCODE_##CHAR" as "int"
 */ 
void setButtonColour(unsigned int , int );

/**
 * @brief sets/resets the countervalue of a button to 0
 * @param keyvalue intakes the "#define KEYCODE(CHAR)" from the "SDL_SCANCODE_##CHAR" as "int"
 */ 
void resetCounter(int );

#endif //__BUTTONS_H__