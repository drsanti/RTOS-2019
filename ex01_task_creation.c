
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

	// vTaskDelete(NULL);
}

void system_init() {

	xTaskCreate(Task1, "Task_1", 64, NULL, tskIDLE_PRIORITY+1, NULL);

	vTaskStartScheduler();
}

void main(void) {
	vTraceEnable(TRC_INIT);
	system_init();
}
