#include <fluidsynth.h>

#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <stddef.h>
#include <dirent.h>



int quit = 0;

fluid_player_t* player;

void sigHandler(int sig){
		printf("bye\n");
		fluid_player_stop(player);
}

int main(void){
		signal(SIGINT, sigHandler);

		char* dir_name = "./sakura/";

		fluid_settings_t* settings = new_fluid_settings();
		fluid_settings_setnum(settings, "synth.sample-rate", 44100);
		fluid_settings_setint(settings, "audio.period-size", 1024);
		fluid_settings_setstr(settings, "audio.driver", "pipewire");

		fluid_synth_t* synth = new_fluid_synth(settings);
		fluid_audio_driver_t* audio = new_fluid_audio_driver(settings, synth);
		
		player = new_fluid_player(synth);



				if(fluid_synth_sfload(synth, "A320U.sf2", 1) == 0) {
				fprintf(stderr, "Erro ao carregar soundfont\n");
				return -1;
		}
		
		fluid_player_add(player, "./sakura/opening_theme.mid");


		printf("Playing MIDI\n");
		
		fluid_player_seek(player, 3500);
		fluid_player_play(player);


		fluid_player_join(player);

		delete_fluid_audio_driver(audio);
		delete_fluid_player(player);
		delete_fluid_synth(synth);
		delete_fluid_settings(settings);

		printf("Cleanup Done\n");
		return 0;

}
