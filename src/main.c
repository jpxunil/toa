#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <raylib.h>

#include "defines.h"
#include "xmlParser.h"
#include "timer.h"



#include <fluidsynth.h>


// global variables

fluid_player_t* player = NULL;


int main(){

		enum gameState {INTRO, LOAD, MENU};

		// Initialization

		gameData* data = initData("./res/gameData.xml");

		const char* title = TextFormat("%s %s", data->title, data->version);

		InitWindow(WIDTH, HEIGHT, title);

		SetTargetFPS(60);

		char* menuItems[3] = {"New Game", "Continue", "Options"};


		// LOAD -> RESIZE -> CONVERT
		Image rawBG = LoadImage("./res/media/bg.png");
		ImageResizeNN(&rawBG, 1280, 720);
		Texture2D menuBG = LoadTextureFromImage(rawBG);


		/*
		InitAudioDevice();
		Music menu_bgm = LoadMusicStream("./res/audio/tears.ogg");
		SetAudioStreamBufferSizeDefault(4096);
		SetMasterVolume(0.1);

		Sound menu = LoadSound("res/sfx/menu_select.wav");
		Sound confirm = LoadSound("res/sfx/confirm.wav");

		PlayMusicStream(menu_bgm);

		*/

		// Audio Backend Initialization
		//

		fluid_settings_t* settings = new_fluid_settings();
		fluid_settings_setnum(settings, "synth.sample-rate", 44100);
		fluid_settings_setint(settings, "audio.period-size", 512);
		fluid_settings_setstr(settings, "audio.driver", "pipewire");

		fluid_synth_t* synth = new_fluid_synth(settings);
		fluid_audio_driver_t* audio = new_fluid_audio_driver(settings, synth);

		player = new_fluid_player(synth);

		if(fluid_synth_sfload(synth, "./res/soundfont/A320U.sf2", 1) == 0) {
			fprintf(stderr, "Erro ao carregar soundfont\n");
		}

		fluid_player_add(player, "./res/audio/bgm.mid");
		//fluid_player_seek(player, 3500);
		fluid_player_play(player);

		int menu_option = 0;
		float volume = 0.0f;

		Font font = LoadFont("./res/font.ttf");

		bool quit = false;

		bool audio_fadein = false;

		while(! ( WindowShouldClose() || quit )){

				// Logic

				switch(GetKeyPressed()){
						case KEY_Q:
								quit = true;
								break;
						case KEY_ENTER:
								//PlaySound(confirm);
								break;
				}

				// Fade in Intro
				
				if(! audio_fadein ){
					if (volume < data->volume ){ volume += 0.05f * GetFrameTime(); }
					else if(volume >= data->volume){ volume = data->volume; audio_fadein = true; }
				}
				SetMasterVolume(volume);

				//UpdateMusicStream(menu_bgm);

				if(IsKeyPressed(KEY_DOWN)){
						menu_option++;
						if(menu_option > 2){ menu_option = 0; }

				}else if(IsKeyPressed(KEY_UP)){
						menu_option--;
						if(menu_option < 0){ menu_option = 2; }
				}

				if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP)){
						//PlaySound(menu);
				}

				// Drawing

				BeginDrawing();
				ClearBackground(BLACK);
				

				DrawTexture(menuBG, 0, 0, (Color){255, 255, 255, 125});

				DrawTextEx(font, TextFormat("Volume: %.2f", volume), (Vector2){0 + PADX, 0 + PADY}, 12.0f, 1.0f, WHITE);

				for(int i = 0; i < 3; i++){
						DrawTextEx(font, TextFormat("%c. %s", 'a' + i, menuItems[i]), (Vector2){50, 50 + ( 26 * i ) }, 12.0f, 1.0f, (Color){255, 255, menu_option == i?50:255, 255});
						DrawRectangleGradientH(50 - 8, (50 - 6 + (26 * menu_option) ), 12 * 8, 24, (Color){255, 255, 255, 25}, (Color){255, 255, 255, 5});
				}

				EndDrawing();

		}

		delete_fluid_audio_driver(audio);
		delete_fluid_player(player);
		delete_fluid_synth(synth);
		delete_fluid_settings(settings);

		UnloadFont(font);
		CloseAudioDevice();
		
		//UnloadSound(confirm);
		//UnloadSound(menu);
		UnloadTexture(menuBG);
		
		CloseWindow();
		
		free(data);

		return 0;

}
