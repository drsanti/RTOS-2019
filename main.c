
/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"


static void Task2(void* pvParameters) {
	for (;;) {
		vTaskDelay(1000);
		char buffer[48];
		vTaskList(buffer);
		printf("%s", buffer);
	}
}
int add(a, b) {
	return a + b;
}

TaskHandle_t xHandle;
TaskStatus_t xTaskDetails;

static void Task1(void* pvParameters)
{

	xHandle = xTaskGetCurrentTaskHandle();
	vTaskGetInfo(xHandle, &xTaskDetails, pdFALSE, eInvalid);

	

	int a = 10;
	int b = 20;
	add(a, b);

	int arr[8] = { 0 };
	long addr2 = &arr[0];

	long* ptr_addr = (long*)pvParameters;
	long data = *ptr_addr;

	//!! OR
	//long data = *((long*)pvParameters);

	long addr = (long*)pvParameters;
	for (;;)
	{
		
		vTaskDelay(1000);
		printf("Task1 0x%.8X\r\n", data);
	}
}


#define VAR_TYPE double

VAR_TYPE global_var = 123;
const VAR_TYPE const_var1 = 123;
const VAR_TYPE const_var2 = 123;

int main( void )
{
	VAR_TYPE local_var = 345;
	VAR_TYPE static static_var = 678;

	printf("size of var : %d byte\r\n", sizeof(VAR_TYPE));
	printf("global addr : 0x%.8X\r\n", (long)&global_var);
	printf("const1 addr : 0x%.8X\r\n", (long)& const_var1);
	printf("const2 addr : 0x%.8X\r\n", (long)& const_var2);
	printf("static addr : 0x%.8X\r\n", (long)&static_var);
	printf("local  addr : 0x%.8X\r\n", (long)&local_var);





	vTraceEnable( TRC_INIT );

	TaskHandle_t xHandle = NULL; // typedef struct tskTaskControlBlock* TaskHandle_t;
	static long vx = 15;
	printf("addr = 0x%.8X\r\n", (long int)&vx);
	xTaskCreate(Task1, "Task_One", 0xA0, (void *)(&vx), 1, (TaskHandle_t*)&xHandle);
	xTaskCreate(Task2, "Task_Two", 0xA0, NULL, 1, NULL);

	

	/*TaskStatus_t xTaskDetails;
	vTaskGetInfo(  xHandle, &xTaskDetails, pdFALSE, eInvalid );*/

	vTaskStartScheduler();


	return 0;
}
