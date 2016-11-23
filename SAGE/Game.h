#ifndef __GAME_H__
#define __GAME_H__

#include <SDL.h>
#include <string>
#include <memory>

#include "Renderer.h"

class cGame
{
protected:
	using Super = cGame;

protected:
	cGame(int width, int height, bool fullscreen, std::string const& title);

	virtual void Update(float) = 0;
	virtual void Draw() = 0;
	virtual void ProcessEvents(SDL_Event const& ev);

	SDL_Window* GetWindow() const { return m_pWindow; }
	int GetWindowWidth() const;
	int GetWindowHeight() const;
	iRenderer& GetRenderer() const { return *m_pRenderer; }

	void Close() { m_running = false; }

public:
	virtual ~cGame();
	void Run();

private:
	SDL_Window*						m_pWindow;
	SDL_Event						m_event;
	std::string						m_title;
	bool							m_running;
	Uint32							m_prevFrameTime;
	std::unique_ptr<iRenderer>		m_pRenderer;
};

#endif