#pragma once
#include <SDL/SDL.h>
#include "MeshManager.h"
#include "WindowManager.h"
#include "Camera.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	void initSystems();

	const int MAIN_WIDTH = 1920;
	const int MAIN_HEIGHT = 1080;
private:
	WindowManager m_windowManager;
	//MeshManager m_meshManager; // This is without singleton class.

	SDL_Window* m_pMainWindow = nullptr;
	SDL_Renderer* m_pMainRenderer = nullptr;
	Camera* m_pMainCamera = nullptr;
	short m_maxFps = 30;

	void mainLoop();
};

