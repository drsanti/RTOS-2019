
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "FreeRTOS.h"
#include "task.h"

static void TaskCat(void* pvParameters) {
	int cnt = 0;
	for (;;) {
		printf("Cat %d\r\n", cnt++);
		//vTaskDelay(50);
	}
}

static void TaskDog(void* pvParameters) {
	int cnt = 0;
	for (;;) {

		printf("\tDog %d\r\n", cnt++);
		//vTaskDelay(50);
	}
}

void system_init() {

	const UBaseType_t CatPriority = tskIDLE_PRIORITY + 1;
	const UBaseType_t DogPriority = tskIDLE_PRIORITY + 1;

	xTaskCreate(TaskCat, "Cat", 64, NULL, CatPriority, NULL);
	xTaskCreate(TaskDog, "Dog", 64, NULL, DogPriority, NULL);

	vTaskStartScheduler();
}

void main(void) {
	vTraceEnable(TRC_INIT);
	system_init();
}
