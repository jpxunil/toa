#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include <fluidsynth.h>


fluidDriver* initFluidDriver(char* audiodriver){

	fluidDriver* driver = malloc(sizeof(fluidDriver));

	driver->settings = new_fluid_settings();

	fluid_settings_setnum(driver->settings, "synth.sample-rate", 44100);
	fluid_settings_setint(driver->settings, "audio.period-size", 512);
	fluid_settings_setstr(driver->settings, "audio.driver", audiodriver);

	driver->synth = new_fluid_synth(driver->settings);

	fluid_synth_set_gain(driver->synth, 0.0f);

	driver->audio_driver = new_fluid_audio_driver(driver->settings, driver->synth);

	return driver;

}

void unloadDriver(fluidDriver* driver){
	delete_fluid_audio_driver(driver->audio_driver);
	delete_fluid_synth(driver->synth);
	delete_fluid_settings(driver->settings);
	free(driver);
}
