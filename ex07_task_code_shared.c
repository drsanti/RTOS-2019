
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "FreeRTOS.h"
#include "task.h"

#define NUM_TASKS	2
TaskHandle_t TaskHandles[NUM_TASKS];

static void Worker(void* pvParameters) {
	int cnt = 0;
	int id = (int)pvParameters;

	int addr = &cnt;

	TaskStatus_t xTaskDetails;
	TaskHandle_t handle = xTaskGetHandle("Dog");
	vTaskGetInfo(handle, &xTaskDetails, pdTRUE, eInvalid);

	for (;;) {
		cnt++;
		printf("%sWorker #%d value: %d addr: 0x%.8X\r\n", ((id==1)?"\t":""), id, cnt, addr);
		vTaskDelay(((id == 0) ? 200 : 1000));
	}
}


void system_init() {

	
	xTaskCreate(Worker, "Cat", 48, (void *)0, 1, &TaskHandles[0]);
	xTaskCreate(Worker, "Dog", 48, (void *)1, 1, &TaskHandles[1]);

	TaskStatus_t xTaskDetails;
	TaskHandle_t handle = xTaskGetHandle("Dog");
	vTaskGetInfo(handle, &xTaskDetails, pdTRUE, eInvalid);
	

	vTaskStartScheduler();
}

void main(void) {
	vTraceEnable(TRC_INIT);
	system_init();
}
