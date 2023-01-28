#include "GameManager.h"

GameManager::GameManager()
{
	//Empty.
}

GameManager::~GameManager()
{
	// Delete the main Renderer.
	m_windowManager.deleteRenderer(m_pMainRenderer);
	
	// Delete the main Window.
	m_windowManager.deleteWindow(m_pMainWindow);

	// Delete the main Camera.
	delete m_pMainCamera;
	m_pMainCamera = nullptr;
}

void GameManager::initSystems()
{
	// Initialize SDL.
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create the main Window and Renderer.
	m_pMainWindow = m_windowManager.createWindow(MAIN_WIDTH, MAIN_HEIGHT, "3D Engine");
	m_pMainRenderer = m_windowManager.createRenderer(m_pMainWindow);

	// Create the main Camera.
	m_pMainCamera = new Camera(MAIN_WIDTH, MAIN_HEIGHT);

	// Add the main mesh;
	Mesh* mesh = new Mesh("Mouse.obj");
	MeshManager::Instance().addMesh(mesh);

	// Start the main loop.
	mainLoop();
}

void GameManager::mainLoop()
{
	// Variables for framerate.
	Uint64 start, end;
	double deltaTime = 0;

	SDL_Event e;
	bool quit = false;

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}

		start = SDL_GetPerformanceCounter();


		// Clear the screen.
		SDL_SetRenderDrawColor(m_pMainRenderer, 0, 0, 0, 255);
		SDL_RenderClear(m_pMainRenderer);


		SDL_SetRenderDrawColor(m_pMainRenderer, 255, 255, 255, 255);
		MeshManager::Instance().renderMeshes(m_pMainRenderer, m_pMainCamera);

		end = SDL_GetPerformanceCounter();
		deltaTime = (end - start) / (double)SDL_GetPerformanceFrequency() * 1000.0f;
		SDL_Delay(floor(1000.0f / m_maxFps - deltaTime));
		
		SDL_RenderPresent(m_pMainRenderer);
	}
}