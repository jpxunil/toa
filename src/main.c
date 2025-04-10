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

	freopen("/dev/null","w",stderr);
	
	//typedef enum gameState {LOGO, TITLE, GAMEPLAY, ENDING} gameState;

	stringArray menu;
	stringArray options;

	initStringArray(&menu, 0, MENUOPTS);
	initStringArray(&options, 0, OPTIONS);

	puts(options.strings[0]);

	// Initialization

	gameData* data = initData("./res/gameData.xml");

	const char* title = TextFormat("%s %s", data->title, data->version);

	Image icon = LoadImage(TextFormat("%s%s", (char*)"./res/", (char*)data->icon));

	InitWindow(WIDTH, HEIGHT, title);

	SetWindowIcon(icon);

	SetTargetFPS(60);

	// LOAD -> RESIZE -> CONVERT
	Image rawBG = LoadImage("./res/media/bg.png");
	ImageResizeNN(&rawBG, 1280, 720);
	Texture2D menuBG = LoadTextureFromImage(rawBG);

	// Audio Backend Initialization
	//

	fluidDriver* bgm_driver = initFluidDriver(data->audiodriver);
	fluidDriver* sfx_driver = initFluidDriver(data->audiodriver);
	

	int sid = fluid_synth_sfload(bgm_driver->synth, "./res/soundfont/A320U.sf2", 1);
	int sfx_sid = fluid_synth_sfload(sfx_driver->synth, "./res/soundfont/A320U.sf2", 1);

	if(sid == FLUID_FAILED) {
		fprintf(stderr, "Erro ao carregar soundfont\n");
	}

	int menu_option = 0;
	float volume = 0.0f;

	Font font = LoadFont("./res/Arial.ttf");
	SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);

	bool quit = false;
	bool audio_fadein = false;
	int bg_alpha = 0;

	stringArray* active_menu = &menu;

	player = new_fluid_player(bgm_driver->synth);
	fluid_player_add(player, "./res/audio/bgm.mid");
	fluid_player_play(player);

	fluid_synth_set_gain(sfx_driver->synth, 3.0f);

	while(! ( WindowShouldClose() || quit )){

		bg_alpha < 125? bg_alpha++:125;

		// Logic

		switch(GetKeyPressed()){
			case KEY_Q:
				quit = true;
				break;
			case KEY_ENTER:
				fluid_synth_program_select(sfx_driver->synth, 0, sfx_sid, 5, 124);
				fluid_synth_noteon(sfx_driver->synth, 0, 15, 90);
				fluid_synth_noteoff(sfx_driver->synth, 0, 15);

				if(menu_option == 2 && active_menu == &menu){ 
					active_menu = &options; menu_option = 0;
				}else if(menu_option == 1 && active_menu == &options){ active_menu = &menu; menu_option = 0;}

				break;

			case KEY_ZERO:
				volume <1.0f?volume+=0.1f:1.0f;
				break;
			case KEY_NINE:
				volume > 0.0f?volume-=0.1f:0.0f; 
				break;
		}

		if(volume < 0.0f){ volume = 0.0f; } else if(volume > 1.0f){ volume = 1.0f;}

		// Fade in Intro

		if(! audio_fadein ){
			if (volume < data->volume ){ volume += 0.1f * GetFrameTime(); }
			else if(volume >= data->volume){ volume = data->volume; audio_fadein = true; }
		}
		
		fluid_synth_set_gain(bgm_driver->synth,volume);

		if(IsKeyPressed(KEY_DOWN)){
			menu_option++;
			if(menu_option >= active_menu->count){ menu_option = 0; }

		}else if(IsKeyPressed(KEY_UP)){
			menu_option--;
			if(menu_option < 0){ menu_option = active_menu->count - 1 ; }
		}

		if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP)){
			fluid_synth_program_select(sfx_driver->synth, 0, sfx_sid, 1, 121);
			fluid_synth_noteon(sfx_driver->synth, 0, 15, 80);
		}

		// Drawing

		BeginDrawing();
		ClearBackground(BLACK);


		DrawTexture(menuBG, 0, 0, (Color){255, 255, 255, bg_alpha});

		DrawTextEx(font, TextFormat("Volume: %.2f", volume), (Vector2){0 + PADX, 0 + PADY}, 14.0f, 1.0f, WHITE);

		for(int i = 0; i < active_menu->count; i++){
			DrawTextEx(font, TextFormat("%c. %s", 'a' + i, 
						active_menu->strings[i]), 
					(Vector2){50, 50 + ( 26 * i ) }, 14.0f, 1.0f, 
					(Color){255, 255, menu_option == i?50:255, 255});

			DrawRectangleGradientH(50 - 8, 
					(50 - 6 + (26 * menu_option) ), 
					12 * 8, 24, 
					(Color){255, 255, 255, 25}, 
					(Color){255, 255, 255, 5});
		}

		EndDrawing();

	}

	freeStringArray(&menu);
	freeStringArray(&options);

	unloadDriver(bgm_driver);
	unloadDriver(sfx_driver);

	/*
	delete_fluid_audio_driver(audio);
	delete_fluid_audio_driver(sfx_audio);
	delete_fluid_synth(synth);
	delete_fluid_synth(sfx_synth);
	delete_fluid_settings(settings);
	delete_fluid_player(player);
	*/

	UnloadFont(font);

	UnloadTexture(menuBG);
	UnloadImage(icon);

	CloseWindow();

	free(data);

	return 0;

}
