#pragma once
#include <SDL/SDL.h>

class WindowManager
{
public:
	SDL_Window* createWindow(const int& width, const int& height, const char* windowName);
	SDL_Renderer* createRenderer(SDL_Window* pWindow);

	void deleteWindow(SDL_Window* pWin);
	void deleteRenderer(SDL_Renderer* pRen);
private:
	int m_rendererIndex = -1;
};

