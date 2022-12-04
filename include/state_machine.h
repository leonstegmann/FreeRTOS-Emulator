#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

unsigned char states_init(void);

unsigned char states_run(void);

unsigned char states_add(void (*probe)(void), void (*enter)(void),
                         void (*run)(void), void (*exit)(void), int ID,
                         char *name);

void states_set_callback(void (*callback)(void));

void states_set_data(void *data);

void states_set_input(unsigned char input);

unsigned char states_set_state(unsigned int state_id);

void *states_get_data(void);

char *states_get_state_name(void);

unsigned char states_get_input(void);

unsigned int states_get_state_id(void);

unsigned int states_get_state_count(void);

void states_clear_input(void);

void vStatesHandler(void *pvParameters);


#endif //__STATE_MACHINE_H__