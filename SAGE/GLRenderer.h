#ifndef __GLRENDERER_H__
#define __GLRENDERER_H__

#include "Renderer.h"

#include <SDL.h>

class cGLRenderer : public iRenderer
{
public:
	cGLRenderer(SDL_Window* window, int ctxMajor, int ctxMinor, bool vsync);
	virtual ~cGLRenderer();

	virtual void Clear(float r, float g, float b, float a) override;
	virtual void Present() override;
	virtual void Resize(int w, int h) override;
	virtual void DrawPrimitives(ePrimitiveType type, int start, int count) override;

private:
	SDL_Window*		m_pWindow;
	SDL_GLContext	m_glContext;
};

#endif