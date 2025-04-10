#include <stdio.h>
#include <stdlib.h>

#include <fluidsynth.h>
#include <raylib.h>


fluid_player_t* player = NULL;

int main(void){

	// fluidsynth initialization
	//

	fluid_settings_t* settings = new_fluid_settings();
	fluid_settings_setnum(settings, "synth.sample-rate", 44100);
	fluid_settings_setint(settings, "audio.period-size", 512);
	fluid_settings_setstr(settings, "audio.driver", "pipewire");

	fluid_synth_t* synth = new_fluid_synth(settings);

	int sid = fluid_synth_sfload(synth, "example.sf2", 1);

	fluid_audio_driver_t* audio = new_fluid_audio_driver(settings, synth);

	InitWindow(1280, 720, (char*)"Fluidsynth");

	fluid_synth_program_select(synth, 0, sid, 1, 121);

	while(! WindowShouldClose()){

		if(IsKeyPressed(KEY_W)){
			fluid_synth_noteon(synth, 0, 15, 80);
		}

		BeginDrawing();

		ClearBackground(BLACK);

		EndDrawing();

	}


	delete_fluid_audio_driver(audio);
	delete_fluid_synth(synth);
	delete_fluid_settings(settings);
	delete_fluid_player(player);
	CloseWindow();

	return 0;

}
