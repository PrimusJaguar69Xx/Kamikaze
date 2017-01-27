#define SDL_MAIN_HANDLED


#include <SDL2/SDL.h>
#include <stdio.h>
#include <thread>

#include "Game_Controller.h"
#include "Resource_Image.h"
#include "Resource_Texture.h"
#include "Default_Level.h"


#define FRAME_RATE 60

int main(int argc, char* argv[]) {
	int quit = 1;
	int iResult = 0;

	Game_Controller* GameControl = new Game_Controller();
	iResult = GameControl->Init(1920, 1080);
	if (iResult < 0) {
		printf("call to gamecontroller->init() failed");
	}
	GameControl->LoadLevel(false, new Default_Level());

	SDL_Event eEvent;

	int time = 0;

	while (quit != 0) {
		time = SDL_GetTicks();

		while (SDL_PollEvent(&eEvent) != NULL) {
			if (eEvent.type == SDL_QUIT || eEvent.key.keysym.sym == SDLK_ESCAPE) 
				quit = 0;
		}



		SDL_RenderClear(GameControl->GetRenderer());
//runs level code

		GameControl->GetCurrLvl()->Update();

		GameControl->GetCurrLvl()->Render();

//bring the back buffer out
		SDL_RenderPresent(GameControl->GetRenderer());

		if (SDL_GetTicks() - time < 1000 / FRAME_RATE) {
			SDL_Delay(1000 / FRAME_RATE - (SDL_GetTicks() - time));
		}
	}

	

	GameControl->~Game_Controller();


	return 0;
}