
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

QueueHandle_t  qFloat;
QueueHandle_t  qPerson;


typedef struct {
	char* name;
	int age;
}Person;

static void TaskSender(void* pvParameters) {

	//!! Ceate 5 items of floating point data
	qFloat = xQueueCreate(5, sizeof(float));


	//!! Ceate 8 items of Person data structure (pointers to the structures)
	qPerson = xQueueCreate(8, sizeof(struct Person*));

	float float_data = 0.0f;
	for (;;) {
		
		//!! Float data
		float_data += 0.01;
		printf("Sender: %f\r\n", float_data);
		if (xQueueSend(qFloat, (void*)& float_data, (TickType_t)10) != pdPASS)
		{
			printf("\tFailed to post the message, even after 10 ticks\r\n");
		}

		//!! Generate Person Data
		Person person;
		person.name = (char*)malloc(32);
		printf("Allocate: 0x%.8X\r\n", person.name);
		sprintf(person.name, "name-%d", (int)(float_data*100));
		person.age = (int)(float_data * 100.0f);

		Person* ptr_person = &person;
		//!! 
		if (xQueueSend(qPerson, (void*)& ptr_person, (TickType_t)10) != pdPASS)
		{
			printf("\tFailed to post the message, even after 10 ticks\r\n");
		}
		
		vTaskDelay(500);

	}
}

static void TaskReceiver(void* pvParameters) {

	float  receivedFloat;
	Person* ptr_person;
	for (;;) {
		if (qFloat != 0) {

			if ( xQueueReceive(qFloat, &receivedFloat, (TickType_t)10) ) {
				printf("Receiver: %f\r\n", receivedFloat);
				//vTaskDelay(2000);
			}
		}

		if (qPerson != 0) {

			if (xQueueReceive(qPerson, &(ptr_person), (TickType_t)10)) {
				printf("Receiver: %s %d\r\n", ptr_person->name, ptr_person->age);
				printf("Free 0x%.8X\r\n", ptr_person->name);
				
				//!! Comment this line and check the memory
				free(ptr_person->name); 
				//vTaskDelay(2000);
			}
		}
	}
}




void system_init() {


	xTaskCreate(TaskSender,   "Sender",   128, NULL, 1, NULL);
	xTaskCreate(TaskReceiver, "Receiver", 128, NULL, 1, NULL);

	



	vTaskStartScheduler();
}

void main(void) {
	vTraceEnable(TRC_INIT);
	system_init();
}
