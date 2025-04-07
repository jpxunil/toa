#ifndef GAMESTRUCTS_H
#define GAMESTRUCTS_H
#include <stdbool.h>

typedef struct Timer{
		int hits;
		float lifetime;
}Timer;


void startTimer(Timer* timer, float lifetime);
void updateTimer(Timer* timer);
bool isTimerDone(Timer* timer);


#endif
