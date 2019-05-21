
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/* Example 1 -- address and value */

short global_var = 12;
void main(void) {

	printf("addr: 0x%.8X\tvalue: %d\r\n", &global_var, global_var);

	short local_var = 25;
	printf("addr: 0x%.8X\tvalue: %d\r\n", &local_var, local_var);

	static short static_local_var = 34;
	printf("addr: 0x%.8X\tvalue: %d\r\n", &static_local_var, static_local_var);

}

/* Example 2 -- address and size */
/*
void main(void) {
	char char_var = 'A';
	printf("char\taddr: 0x%.8x\tsize: %d\r\n", &char_var, sizeof(char_var));


	short short_var = 13;
	printf("short\taddr: 0x%.8x\tsize: %d\r\n", &short_var, sizeof(short_var));

	int int_var = 24;
	printf("int\taddr: 0x%.8p\tsize: %d\r\n", &int_var, sizeof(int_var));

	long long_var = 36;
	printf("long\taddr: 0x%.8p\tsize: %d\r\n", &long_var, sizeof(long_var));


	float float_var = 3.14f;
	printf("float\taddr: 0x%.8p\tsize: %d\r\n", &float_var, sizeof(float_var));


	double double_var = 0.123;
	printf("double\taddr: 0x%.8p\tsize: %d\r\n", &double_var, sizeof(double_var));
}
*/

/* Example 3 -- memory location */
/*
void main(void) {
	static char		v1 = 1;
	static short	v2 = 2;
	static long		v3 = 3;
	static char		v4 = 4;
	static int		v5 = 5;
	printf("addr: 0x%.8p\tsize: %d\r\n", &v1, sizeof(v1));
	printf("addr: 0x%.8p\tsize: %d\r\n", &v2, sizeof(v2));
	printf("addr: 0x%.8p\tsize: %d\r\n", &v3, sizeof(v3));
	printf("addr: 0x%.8p\tsize: %d\r\n", &v4, sizeof(v4));
	printf("addr: 0x%.8p\tsize: %d\r\n", &v5, sizeof(v5));
}
*/

/* Example 4 -- pointer */
/*
void main(void) {
	char vx = 25;
	printf("vx  addr: 0x%p\tsize: %d\tval: %d\r\n", &vx, sizeof(vx), vx);

	char * ptr = &vx;
	printf("ptr addr: 0x%p\tsize: %d\tpointAddr: 0x%p\tpointVal: %d\r\n", &ptr, sizeof(ptr), ptr, *ptr);
}
*/

/* Example 5 -- pointer and array */
/*
void main(void) {
	short arr[] = {9, 5, 2, 3, 7};
	printf("arr addr: 0x%p\tsize: %d\r\n", arr, sizeof(arr));

	short* ptr = arr;
	printf("ptr addr: 0x%p\tsize: %d\tpointAddr: 0x%p\tpointVal: %d\r\n", &ptr, sizeof(ptr), ptr, *ptr);

	for (int i = 0; i < 5; i++) {
		*ptr *= 2;
		ptr++;
	}

	printf("\r\n\r\n");
	for (int i = 0; i < 5; i++) {
		printf("%d ", arr[i]);
	}
	printf("\r\nptr addr: 0x%p\tsize: %d\tpointAddr: 0x%p\tpointVal: %d\r\n", &ptr, sizeof(ptr), ptr, *ptr);
}
*/


/* Example 6 -- pointer and structure */
/*
typedef struct {
	char  name[32];
	long  ram;
}MCU;

void main(void) {
	MCU mcu;
	memcpy(mcu.name, "nrf52\0", 6);
	mcu.ram = 1024*4;

	printf("mcu addr: 0x%p\tsize: %d\r\n", &mcu, sizeof(mcu));

	MCU* ptr = &mcu;
	printf("ptr addr: 0x%p\tsize: %d\tpointAddr: 0x%p\r\n", &ptr, sizeof(ptr), ptr);
	printf("name: %s\tram: %d\r\n", ptr->name, ptr->ram);
}
*/

/* Example 7 -- pointer to pointer */
/*
void main(void) {

	static int   arr[] = {5, 7, 9};
	static int*  ptr   = arr;
	static int** pptr  = &ptr;

	printf("arr  addr: 0x%p\tsize: %d\tval: %d\r\n", &arr, sizeof(arr), arr[0]);
	printf("ptr  addr: 0x%p\tsize: %d\tpointAddr: 0x%p\tpointVal: %d\r\n", &ptr, sizeof(ptr), ptr, *ptr);
	printf("pptr addr: 0x%p\tsize: %d\tpointAddr: 0x%p\tpointVal: 0x%p\tpointPointVal: %d\r\n", &pptr, sizeof(pptr), pptr, *pptr, **pptr);
}
*/


/* Example 9 -- pointer and memory allocation */
/*
void main(void) {

	#define VAR_TYPE char
	for (int i = 0; i < 5; i++) {
		VAR_TYPE* pMem = (VAR_TYPE*)malloc(32 * sizeof(VAR_TYPE));
		printf("pMem addr: 0x%p\tsize: %d\tpointAddr: 0x%p\r\n", &pMem, sizeof(pMem), pMem);

		free(pMem); //!! Comment this line to make the "memory leak"
		
		//!! OR
		//free((void *)pMem);
	}
}
*/

/* Example 10 -- free the memory in function */
/*
void freeMem(void *pm) {
	free(pm);
	pm = NULL;
}

void freeMem2(void** ppm) {
	free(*ppm);
	ppm = NULL;
}

#define VAR_TYPE char
void main(void) {
	for (int i = 0; i < 5; i++) {
		VAR_TYPE* pMem = (VAR_TYPE*)malloc(32 * sizeof(VAR_TYPE));
		printf("pMem addr: 0x%p\tsize: %d\tpointAddr: 0x%p\r\n", &pMem, sizeof(pMem), pMem);
		// freeMem((void*)pMem);
		freeMem2((void **)&pMem);
	}
}
*/
