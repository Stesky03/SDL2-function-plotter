#pragma once
#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
using std::vector;
using std::pair;


class Game
{
public:

	//funzionamento
	bool Running;
	int windowx, windowy;

	//rendering
	SDL_Window* Window;
	SDL_Renderer* Renderer;

	//entità
	vector <pair<int,float>> P;

	//input
	bool lclick, rclick;


	Game() {}
	~Game() {}

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			std::cout << "SDL init success\n";
			Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
			if (Window != 0)
			{
				std::cout << "window creation success\n";
				Renderer = SDL_CreateRenderer(Window, -1, 0);
				if (Renderer != 0)
				{
					std::cout << "renderer creation success\n";
					SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
					SDL_GetRendererOutputSize(Renderer, &windowx, &windowy);
				}
				else
				{
					std::cout << "renderer init fail\n";
					return false;
				}
			}
			else
			{
				std::cout << "window init fail\n";
				return false;
			}
		}
		else
		{
			std::cout << "SDL init fail\n";
			return false;
		}
		std::cout << "init success\n";
		windowx=width;
		windowy=height;
		Running = true;
		init2();
		return true;
	};
	void init2(){
		P.resize(windowx);
	};

	void render() {
		SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
		SDL_RenderClear(Renderer);
		renderlines();
		SDL_RenderPresent(Renderer);
	};

	void renderlines(){
		SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
		for(int i=0;i<P.size()-1;i++){
			SDL_RenderDrawLineF(Renderer,P[i].first,(P[i].second*100)+(windowy/2),P[i+1].first,(P[i+1].second*100)+(windowy/2));
		}
	};

	void update() {
		points();
	};

	void points(){
		for(int i=0;i<windowx;i++){
			P[i].first=i;
			P[i].second=cos(float(i)/50);
		}
	};
	void handleEvents() {
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					Running = false;
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
						lclick=true;
						break;
					case SDL_BUTTON_RIGHT:
						rclick=true;
						break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
						lclick=false;
						break;
					case SDL_BUTTON_RIGHT:
						rclick=false;
						break;
				}
				break;
			case SDL_QUIT:
				Running = false;
				break;
			default:
				break;
			}
		}
	};
	void clean() {
		std::cout << "cleaning game\n";
		SDL_DestroyWindow(Window);
		SDL_DestroyRenderer(Renderer);
		SDL_Quit();
	};

	bool running() { return Running; }

};
#endif /* defined(__Game__) */