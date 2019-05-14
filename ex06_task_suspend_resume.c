
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "FreeRTOS.h"
#include "task.h"

#define NUM_TASKS	2
TaskHandle_t TaskHandles[NUM_TASKS];

static void TaskCat(void* pvParameters) {
	int cnt = 0;
	for (;;) {
		printf("Cat %d\r\n", cnt++);
		vTaskDelay(1000);

		if (cnt % 5 == 0) {
			//!! Resume TaskDog
			vTaskResume(TaskHandles[1]);
		}
	}
}

static void TaskDog(void* pvParameters) {
	int cnt = 0;
	for (;;) {

		printf("\tDog %d\r\n", cnt++);
		vTaskDelay(200);
		if (cnt % 10 == 0) {
			//!! Suspend itself
			vTaskSuspend(TaskHandles[1]);
		}
	}
}

void system_init() {

	TaskHandle_t handle;
	xTaskCreate(TaskCat, "Cat", 48, NULL, 1, &TaskHandles[0]);
	xTaskCreate(TaskDog, "Dog", 48, NULL, 1, &TaskHandles[1]);
	
	//!! Suspend TaskDog
	vTaskSuspend(TaskHandles[1]);

	vTaskStartScheduler();
}

void main(void) {
	vTraceEnable(TRC_INIT);
	system_init();
}
