
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "FreeRTOS.h"
#include "task.h"

static void Task1(void* pvParameters) {
	int cnt = 0;
	char *pstr = (char*)pvParameters;
	for (;;) {
		printf("%s %d\r\n", pstr, cnt++);
		vTaskDelay(1000);
	}
}

static void Task2(void* pvParameters) {
	int cnt = 0;
	double* pdbl = (double*)pvParameters;
	for (;;) {
		printf("Task_2, %f, %d\r\n", *pdbl, cnt++);
		vTaskDelay(1000);
	}
}


typedef struct {
	char* name;
	int age;
}Person;

static void Task3(void* pvParameters) {
	int cnt = 0;
	Person* pperson = (Person*)pvParameters;
	for (;;) {
		printf("Task_3, Name: %s, Age: %d, Cnt: %d\r\n", pperson->name, pperson->age, cnt++);
		vTaskDelay(1000);
	}
}

void system_init() {

	//!! Task_1
	xTaskCreate(Task1, "Task_1", 64, (void *)"Task #1", 1, NULL);

	//!! Task_2
	static double pi = 22.0 / 7.0;
	xTaskCreate(Task2, "Task_2", 64, (void*)(&pi), 1, NULL);


	//!! Task_3
	Person person;
	person.name = "Sawatdee";
	person.age = 25;
	xTaskCreate(Task3, "Task_3", 64, (void*)(&person), 1, NULL);

	//!! Start
	vTaskStartScheduler();
}

void main(void) {
	vTraceEnable(TRC_INIT);
	system_init();
}
