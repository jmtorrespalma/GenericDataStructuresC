
#include "queue.h"
#include <stdio.h>

#define DATA_TYPE char

int main (int argc, char *argv[]){

	unsigned i;
	queue_t s;
	DATA_TYPE *a = "Hi_my_friend" ;
	DATA_TYPE *c = "Other" ;
	DATA_TYPE b;

	queue_init(&s, sizeof(DATA_TYPE));

	//Force resize
	for (i = 0; i < 7; ++i){
		queue_push_back(&s, &(a[i]));
	}

	queue_pop_front(&s, NULL); 
	queue_pop_front(&s, NULL);

	
	//Force resize
	for (i = 0; i < 3; ++i){  //"i myMi" H=0, T=5 
		queue_push_back(&s, &(c[i]));
	}

	while (!queue_empty(&s)){
		queue_pop_front(&s, &b);
		printf("%c, %u\n", b, queue_size(&s));
	}


	queue_destroy(&s);
	
	return 0;
}
