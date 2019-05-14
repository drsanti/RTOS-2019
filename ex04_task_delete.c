
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

		if (cnt > 5) {
			TaskHandle_t handle = xTaskGetHandle("Task_2");
			if (handle != NULL) {
				vTaskDelete(handle);
				printf("Task_1 kills Task_2");
			}
		}
		
		if (cnt > 7) {
			TaskHandle_t handle = xTaskGetHandle("Task_1");
			if (handle != NULL) {
				printf("Task_1 is killing itself...");
				vTaskDelete(handle);
				printf("Never goes here");
			}
		}

		char buffer[128];
		vTaskList( buffer );
		printf("\r\n%s\r\n", buffer);
	}
}

static void Task2(void* pvParameters) {
	int cnt = 0;
	for (;;) {

		printf("\tTask2 %d\r\n", cnt++);
		vTaskDelay(200);
	}
}

void system_init() {

	TaskHandle_t handle;
	xTaskCreate(Task1, "Task_1", 48, NULL, 1, &handle);
	xTaskCreate(Task2, "Task_2", 48, NULL, 1, &handle);

	vTaskStartScheduler();
}

void main(void) {
	vTraceEnable(TRC_INIT);
	system_init();
}
