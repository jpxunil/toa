#include "defines.h"

void startTimer(Timer* timer, float lifetime){
		if( timer != NULL){ 
				timer->lifetime = lifetime; 
		}
}
void updateTimer(Timer* timer){ 
		if( timer != NULL && timer->lifetime > 0){ 
				timer->lifetime -= GetFrameTime();
		}
}

bool isDoneTimer(Timer* timer){
		if( timer != NULL ){ 
				return timer->lifetime <= 0; 
		}
		return false;
}
