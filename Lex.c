//------------------------
// Lex.c
//------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char* argv[]) {
	int count = 0;
	int n = 0;
	int i, j;
	FILE *in, *out;
	char line[MAX_LEN];
	char** strangs;
	char* temp; 
	char* f;
	char* b;

	//check command line for correct number of arguments
	if (argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	//open files for reading and writing
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if (in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}

	if (out == NULL) {
		printf("Unable to open file %s for reading\n", argv[2]);
		exit(1);
	}

	//read each line of input file, counting along the way
	while(fgets(line, MAX_LEN, in) != NULL) {
		count++;
	}
	//resets the in file to be read from the beginning
	rewind(in);

	//allocate memory for the string array as many times as we need
	strangs = malloc((count) * sizeof(char*));
	for (i = 0; i < count; i++) {
		strangs[i] = malloc((MAX_LEN) * sizeof(char));
	}


	//copies lines in array elements in original order
	while(fgets(line, MAX_LEN, in) != NULL) {
		strcpy(strangs[n], line);
		n++;
	}

	//create new list and sort it
	//using an insertion sort type of maniipulation
	List l = newList();

	append(l, 0);

	for (i = 1; i < count; i++) {
		moveFront(l);
		temp = strangs[i];
		f = strangs[front(l)];
		b = strangs[back(l)];
		
		if (strcmp(temp, f) < 0) {
			prepend(l, i);
		} else if (strcmp(temp, b) > 0) {
			append(l, i);
		} else {
			moveFront(l);
			j = length(l);
			while (j > 0) {
				if (strcmp(temp, strangs[get(l)]) < 0) {
					insertBefore(l, i);
					j = 0;
				} else {
					moveNext(l);
					j--;
				}
			}
		}
	}
	

	//prints sorted list to out.txt
	moveFront(l);
	while (index(l) >= 0) {
		fprintf(out, "%s", strangs[get(l)]);
		moveNext(l);
	}

	//close both files
	fclose(in);
	fclose(out);

	//free the list
	freeList(&l);

	for (i = 0; i < count; i++) {
		free(strangs[i]);
	}

	free(strangs);

	return 0;
}
