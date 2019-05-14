
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "FreeRTOS.h"
#include "task.h"

static void Task1(void* pvParameters) {
	int cnt = 0;
	for (;;) {

		printf("Task1 %d\r\n", cnt++);
		vTaskDelay(1000);
	}
}

void system_init() {

	TaskHandle_t handle;
	xTaskCreate(Task1, "Task_1", 8, NULL, 1, &handle);

	eTaskState state = eTaskGetState(handle);

	TaskStatus_t xTaskDetails;
	vTaskGetInfo(handle, &xTaskDetails, pdTRUE, eInvalid);


	vTaskStartScheduler();
}

void main(void) {
	vTraceEnable(TRC_INIT);
	system_init();
}
