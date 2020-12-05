#define _GNU_SOURCE
#include <assert.h>
#include <gnu/libc-version.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Used to get time difference between start and end of a section
#define DIFFTIME(a, b) ((((b.tv_sec - a.tv_sec) * 1e6) + (b.tv_usec - a.tv_usec))* 1e-6)
struct linked{
	int val;
	char c;

	struct linked *next;

};

struct mylinks{
	struct linked *head;
};

void insert(struct mylinks* node, int val, char c){
	struct linked * tmp = malloc(sizeof(struct linked));

	tmp ->val = val;
	tmp ->c = c;
	tmp ->next = node->head;

	node->head = tmp;
	
}
struct mylinks *clearList(struct mylinks* node){
	struct linked *tmp = node->head, *next;
	
	if(tmp != NULL)
		while(tmp){
			next = tmp->next;
			free(tmp);
			tmp = next;
		}
	

	return NULL;
}

int main(int argc, char **argv){
	int i, count;
	struct timeval start, end;
	struct linked *tmp;
	struct mylinks *l = malloc(sizeof(struct mylinks));

	// Set random seed
	srand(42);

	printf("Glibc version is: %s\n", gnu_get_libc_version());

	l->head = NULL;

	if(argc < 2){
		printf("Usage: %s <number of nodes in linked list>\n", argv[0]);
		exit(1);
	}

	count = atoi(argv[1]);


	// Start malloc section
	gettimeofday(&start, NULL);
	for(i = 0; i < count; i++){
		insert(l, rand(), rand()%26 + 'A');
		// Uncomment if you want to see values as they are inserted to the front of the list.
		// printf("%d %c %p\n", l->head->val, l->head->c, l->head->next);
	}

	gettimeofday(&end, NULL);

	/* //print out the list
	tmp = l->head;

	while(tmp){
		printf("%d %c %p\n", tmp->val, tmp->c, tmp->next);
		tmp = tmp->next;
	}
	*/
	
	// End malloc section
	printf("Time elapsed on malloc(): %f\n", DIFFTIME(start, end));


	// Start full linked list traversal section
	gettimeofday(&start, NULL);

	for(i = 0; i < 1000; i++){
		tmp = l->head;

		while(tmp)
			tmp = tmp->next;
	}


	gettimeofday(&end, NULL);
	printf("Time elapsed on 1000 full linked list traversals: %f\n", DIFFTIME(start, end));
	// End linked list traversal section


	// Start free section	
	gettimeofday(&start, NULL);

	l = clearList(l);

	gettimeofday(&end, NULL);
	printf("Time elapsed on free(): %f\n", DIFFTIME(start, end));

	/*
	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	printf("Time elapsed on xyz(): %f\n", DIFFTIME(start, end));


	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	printf("Time elapsed on xyz(): %f\n", DIFFTIME(start, end));
	*/
}
