/*
Use the linear linked list code to store a randomly generated set of 100 integers.  
Now write a routine that will rearrange the list in sorted order of these values. 
Note you might want to use bubble sort to do this. Print these values in rows of 
5 on the screen.

How will this work? Compare two adjacent list elements and if they are out of order swap 
them. After a first pass the largest element will have bubbled to the end of the list. 
Each pass can look at one less element as the end of a list stays sorted.
*/

/* List Sort 
Steven Williams
May 16, 2021 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 1000
#define MIN 0
#define POPULATION 100

int *generate_random(void) {
    static int sample[POPULATION];
    int range = MAX - MIN;
    int i, deviation;

    srand(time(0));

    for ( i = 0; i < POPULATION; ++i) {
        deviation = rand() % range;
        sample[i] = MIN + deviation;
    }

    return sample;
}

typedef struct list {
    int data;
    struct list *next;
} list;

list *create_list(int d) {
	list *head = malloc(sizeof(list)); 
	head -> data = d; 
	head -> next = NULL;
	return head;
}

list *add_to_front(int d, list *h) {
	list* head = create_list(d);
	head -> next = h;
	return head;
}

list *array_to_list(int d[], int size) {
	list *head = create_list(d[0]);
	int i;
	for( i = 1; i < size; i++)
	{
		head = add_to_front(d[i], head);
	}
	return head;
}

void print_list( list *h, char *title) {   
    int i = 0;
	printf("%s\n", title);

	while (h != NULL) {
		printf("%d\t", h -> data);
		h = h -> next;

        if ((i + 1) % 5 == 0) 
            printf("\n");

        i++;
	}
}

void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int sort_list( list *h) {
    int i = 0, prev_i = 1;
    list * next_h = h -> next;

    while (h != NULL && next_h != NULL) {

        if (h->data > next_h->data) {
            swap( &h->data, &next_h->data);
            i++;
        }
        
        h = next_h;
        next_h = h -> next;
    }
    return i;
}

int main(void) {
    int *data = generate_random();
    int i = 999;
	list *head = NULL;

	head = array_to_list(data, POPULATION);
	print_list(head, "100 Random Integers:");
	printf("\n\n");

    while (i > 0) {
        i = sort_list(head);
    }
    print_list(head, "Sorted:");
	return 0;
}



