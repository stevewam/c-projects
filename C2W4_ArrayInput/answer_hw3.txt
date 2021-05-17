/* Array Input Processor 
Steven Williams
May 17, 2021 */

#include <stdio.h>
#include <stdlib.h>



/* Get size by reading the first number */
int get_size(FILE *ptr)
{
	int size = 0;
	fscanf(ptr, "%d", &size);

    return size;
}

/* Put data into array. Size not required as it is known. */
void read_data(FILE *ptr, int d[])
{
	int size = 0;
	while(fscanf(ptr, "%d", &d[size]) == 1)
		(size)++;
}


void print_data(int d[], int size)
{
	int i;
	for (i = 0; i < size; i++){
		printf("%d\t", d[i]);
		if ((i + 1) % 10 == 0) printf("\n");
	}
}

double average(int d[], int size)
{
	int i;
	double avg = 0.0;
	
	for (i = 0; i < size; i++)
		avg += d[i];
	return( avg/size);
}

/* Find max by comparing each value with the next */
int max(int d[], int size)
{
    int i, mx = 0;
    for (i = 0; i < size; i++)
    {
        // If value bigger than the current max, assign it as max
        if (d[i] > mx) mx = d[i];
    }
    return mx;
}

int main(int argc, char *argv[])
{
	FILE *ptr;
    int size;

	if (argc != 2) {
		printf("Need executable inputfile \n");
		exit(1);
	}

	ptr = fopen(argv[1], "r"); 
    size = get_size( ptr);
    
    int data[size];
    read_data(ptr, data);

    printf("Data (Size %d):\n", size);
    print_data(data, size);
    printf("\n\n");

    printf("Average value:\n");
    printf("%f", average(data, size));
    printf("\n\n");

    printf("Max. value:\n");
    printf("%d", max(data, size));
    printf("\n\n");
    
	fclose(ptr);
	return 0;
}