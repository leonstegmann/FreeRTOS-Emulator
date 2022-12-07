#include "state_machine.h"
#include"math.h"

#include"FreeRTOS.h"
#include"task.h"

#include"TUM_Event.h"
#include"TUM_FreeRTOS_Utils.h"

#include"buttons.h"
#include"states.h"
#include"ex2.h"
#include"ex3.h"

void vStatesMachineTask(void *pvParameters)
{
    printf("StatesHandler started \n");

	/* State Maschine confiuration*/	
	states_add(Exercise3EnterFunction,Exercise3EnterFunction,NULL,Exercise3ExitFunction,0,"ex3");
	states_add(NULL,Exercise2EnterFunction,NULL,Exercise2ExitFunction,1,"ex2");
	states_init();
	states_set_state(0);

	int total_stages = states_get_state_count();
	

	while (1) {
		states_run();
		tumEventFetchEvents(FETCH_EVENT_NONBLOCK);
		xGetButtonInput(); // Update global input
		//Button E is used to switch between states
		if (xSemaphoreTake(buttons.lock, 0) == pdTRUE) {
					if (buttons.currentState[KEYCODE(Q)]){
						printf("\nButton Q pressed -> EXITING ---------------------------------------------------\n");
						exit(EXIT_SUCCESS);
					}
					else if (buttons.currentState[KEYCODE(E)]){
						printf("\nButton E pressed ---------------------------------------------------\\n");
						int current_state = states_get_state_id();
						states_set_state((current_state+1) % total_stages);
					}
			xSemaphoreGive(buttons.lock);
		}
		//Delay as specified in STATE_MACHINE_INTERVAL
		printf("DebugPrint in StatesMachine\n");
		tumFUtilPrintTaskStateList();

		vTaskDelay((TickType_t) 500);
	}
}
