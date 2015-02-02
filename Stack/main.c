
#include "stack.h"
#include <stdio.h>

#define DATA_TYPE char

int main (int argc, char *argv[]){

	unsigned i;
	stack_t s;
	DATA_TYPE *a = "HOLA AMIGO" ;
	DATA_TYPE b;

	stack_init(&s, sizeof(DATA_TYPE));

	for (i = 0; i < 10; ++i){
		stack_push(&s, &(a[i]));
	}


	while (!stack_empty(&s)){
		stack_pop(&s, &b);
		printf("%c, %u\n", b, stack_size(&s));
	}

	stack_destroy(&s);
	
	return 0;
}
