#include "WindowManager.h"
#include <string>
#include "Error.h"

SDL_Window* WindowManager::createWindow(const int& width, const int& height, const char* windowName)
{
	SDL_Window* pWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (pWindow == nullptr)
	{
		std::string sdlErr = SDL_GetError();
		Error::fatalError("Failed to creat the required SDL Window. \nSDL Error: " + sdlErr, true);
	}

	return pWindow;
	// QUESTION Does this pointer delete itself? If not, how do we delete it?
}

SDL_Renderer* WindowManager::createRenderer(SDL_Window* pWindow)
{
	SDL_Renderer* pRen = SDL_CreateRenderer(pWindow, m_rendererIndex++, 0);
	
	if (pRen == nullptr)
	{
		std::string sdlErr = SDL_GetError();
		Error::fatalError("Failed to creat the required SDL Renderer. \nSDL Error: " + sdlErr, true);
	}

	return pRen;
	// QUESTION Again, does this delete itself?
}

void WindowManager::deleteWindow(SDL_Window* pWin)
{
	SDL_DestroyWindow(pWin);
}

void WindowManager::deleteRenderer(SDL_Renderer* pRen)
{
	SDL_DestroyRenderer(pRen);
}