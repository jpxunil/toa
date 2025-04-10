#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

void initStringArray(stringArray* array, int capacity, char** test){
	array->count = 0;
	array->capacity = 0;

	if(test != NULL){
		for(int i = 0; test[i] != NULL; i++){
			capacity++;
		}
		}

	array->capacity = capacity;

	array->strings = (char**)malloc(capacity * sizeof(char*));
	
	for(int i = 0; i < array->capacity; i++){ 
		addString(array, test[i]);
	}

}

int addString(stringArray* array, char* string){
	if(array->count >= array->capacity){ 
		printf("max capacity reached\n");
		return -1; 
	}

	array->strings[array->count] = (char*)malloc(strlen(string) + 1);
	strcpy(array->strings[array->count], string);
	array->count++;
	return 0;
}

void freeStringArray(stringArray* array){
	for(int i = 0; i < array->count; i++){
		free(array->strings[i]);
	}
	free(array->strings);
}
