#include "../include/menu_test.h"
#include <stdio.h>
#include <stdlib.h>

void
scrollable_menu_init(ScrollableMenu* scrollable_menu,
					 char** arr,
					 int arr_size,
					 int font_size,
					 int line_gap,
					 int margin)
{
	scrollable_menu->arr = malloc(arr_size * sizeof(char*));
	if (scrollable_menu->arr == NULL) {
		fprintf(stderr, "Memory allocation failed: scrollable_menu->arr\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < arr_size; i++) {
		scrollable_menu->arr[i] = malloc(sizeof(char));
		if (scrollable_menu->arr[i] == NULL) {
			fprintf(stderr, "Memory allocation failed: scrollable_menu->arr[i]\n");
			exit(EXIT_FAILURE);
		}

        scrollable_menu->arr[i] = arr[i];
	}
}
