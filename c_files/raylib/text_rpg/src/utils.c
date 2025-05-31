#include "../inc/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*
strdup_clone(const char* str)
{
    // duplicate string and return it

	if (str == NULL) {
		fprintf(stderr, "Empty array\n");
		exit(EXIT_FAILURE);
	}

	int size = strlen(str) + 1;

	char* copy = malloc(size * sizeof(char));
	if (copy == NULL) {
		fprintf(stderr, "Memory allocation falied\n");
		exit(EXIT_FAILURE);
	}

	strncpy(copy, str, size);

	return copy;
}