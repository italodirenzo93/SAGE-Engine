#include "Game.h"
#include "GLRenderer.h"

#ifdef _WIN32
#include "D3DRenderer.h"
#include <SDL_syswm.h>
#endif

namespace SAGE
{
	cGame::cGame(int width, int height, bool fullscreen, std::string const& title) :
		m_pWindow(nullptr),
		m_pRenderer(nullptr),
		m_title(title)
	{
		// Init SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0)
		{
			throw std::exception("Could not initialize SDL.");
		}

		// Create window
		auto wndFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
		if (fullscreen)
			wndFlags |= SDL_WINDOW_FULLSCREEN;

		m_pWindow = SDL_CreateWindow(
			m_title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			wndFlags
		);

		if (!m_pWindow)
		{
			throw std::exception("Could not create SDL window.");
		}

		// Create renderer
#ifdef _WIN32
	//m_pRenderer = std::make_unique<cD3DRenderer>(m_pWindow, false);
		m_pRenderer = std::make_unique<cGLRenderer>(m_pWindow, 4, 3, false);	// OpenGL version 4.3
#else
		m_pRenderer = std::make_unique<cGLRenderer>(m_pWindow, 4, 3, false);	// OpenGL version 4.3
#endif
	}

	cGame::~cGame()
	{
		m_pRenderer.reset();	// Force the renderer to cleanup before the other subsystems
		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
	}

	void cGame::Run()
	{
		m_running = true;
		m_prevFrameTime = SDL_GetTicks();
		while (m_running)
		{
			while (SDL_PollEvent(&m_event))
			{
				ProcessEvents(m_event);
			}

			// Calculate delta time
			auto frameTime = SDL_GetTicks();
			float deltaTime = (frameTime - m_prevFrameTime) / 1000.0f;	// as seconds

			// Render frame
			Update(deltaTime);
			Draw();

			m_prevFrameTime = frameTime;
		} // end while
	}

	void cGame::ProcessEvents(SDL_Event const& ev)
	{
		if (ev.type == SDL_QUIT)
			m_running = false;
	}

	int cGame::GetWindowWidth() const
	{
		int w;
		SDL_GetWindowSize(m_pWindow, &w, NULL);
		return w;
	}

	int cGame::GetWindowHeight() const
	{
		int h;
		SDL_GetWindowSize(m_pWindow, NULL, &h);
		return h;
	}
}