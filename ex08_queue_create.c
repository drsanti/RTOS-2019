
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


typedef struct {
	char* name;
	int age;
}Person;


static void TaskDog(void* pvParameters) {
	int cnt = 0;

	//!! Ceate 5 items of floating point data
	QueueHandle_t  qFloat;
	qFloat = xQueueCreate(5, sizeof(float));


	//!! Ceate 8 items of Person data structure (pointers to the structures)
	QueueHandle_t  qPerson;
	qPerson = xQueueCreate(8, sizeof(struct Person*));

	for (;;) {
		printf("Dog: %d\r\n", ++cnt);
		vTaskDelay( 500 );
	}
}




void system_init() {


	xTaskCreate(TaskDog, "Cat", 48, NULL, 1, NULL);

	vTaskStartScheduler();
}

void main(void) {
	vTraceEnable(TRC_INIT);
	system_init();
}
