
#include "list.h"
#include <stdio.h>

#define DATA_TYPE char

int main (int argc, char *argv[]){

	unsigned i;
	list_t s;
	list_iterator_t it;
	DATA_TYPE *a = "Hi_my_friend" ;
	DATA_TYPE *c = "Other" ;
	DATA_TYPE b;
	DATA_TYPE k = 'O';

	list_init(&s, sizeof(DATA_TYPE));


	for (i = 0; i < 7; ++i){
		list_push_back(&s, &(a[i]));
	}
	
	for (i = 0; i < 5; ++i){
		list_push_front(&s, &(c[i]));
	}


	// Search test
	it = list_search(&s,&k);
	
	// Delete test
	list_delete(&s, it); 


	while (!list_empty(&s)){
		list_pop_front(&s, &b);
		printf("%c, %u\n", b, list_size(&s));
	}

	list_destroy(&s);
	
	return 0;
}
