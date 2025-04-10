#ifndef DEFINES_H
#define DEFINES_H

#define MENUOPTS (char*[]){"New Game","Continue", "Options", "Exit", NULL}
//#define MENUOPTS (char*[]){"New Game","Continue", NULL}
#define OPTIONS (char*[]){"Audio", "Back", NULL}
#define WIDTH (int)1280
#define HEIGHT (int)720
#define PADX 10
#define PADY 10
#define SAMPLERATE 44100
#define PERIODSIZE 512

#include <fluidsynth.h>

typedef struct fluidDriver{
	fluid_synth_t* synth;
	fluid_settings_t* settings;
	fluid_audio_driver_t* audio_driver;
}fluidDriver;

fluidDriver* initFluidDriver(char* audiodriver);
void unloadDriver(fluidDriver* driver);


typedef struct stringArray{
	char** strings;
	int count;
	int capacity;
}stringArray;

int addString(stringArray* array, char* string);
void initStringArray(stringArray* array, int capacity, char** test);
int addString(stringArray* array, char* string);
void freeStringArray(stringArray* array);


#endif
