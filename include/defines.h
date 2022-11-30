/* Defines variables  */
#define mainGENERIC_PRIORITY    (tskIDLE_PRIORITY)
#define mainGENERIC_STACK_SIZE  ((unsigned short)2560)
#define KEYCODE(CHAR)           SDL_SCANCODE_##CHAR     // SDL_SCANCODE for te keybord use i buttons
#define FRAMERATE               50
#define SCREEN_CENTER (coord_t) {SCREEN_WIDTH/2 , SCREEN_HEIGHT/2} 
