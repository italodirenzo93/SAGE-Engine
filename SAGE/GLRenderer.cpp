#include "GLRenderer.h"
#include <GL/glew.h>
#include <iostream>

cGLRenderer::cGLRenderer(SDL_Window* window, int ctxMajor, int ctxMinor, bool vsync) :
	m_pWindow(window),
	m_glContext(nullptr)
{
	// Create GL context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, ctxMajor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, ctxMinor);
	SDL_GL_SetSwapInterval(static_cast<int>(vsync));	// enable v-sync
	m_glContext = SDL_GL_CreateContext(m_pWindow);
	
	// TODO: Error checking

	// Init glew
	glewInit();

	// TODO: Error checking

	// Enable Z-buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

cGLRenderer::~cGLRenderer()
{
	SDL_GL_DeleteContext(m_glContext);
}

void cGLRenderer::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void cGLRenderer::Present()
{
	SDL_GL_SwapWindow(m_pWindow);
}

void cGLRenderer::Resize(int w, int h)
{
	glViewport(0, 0, w, h);
}

void cGLRenderer::DrawPrimitives(ePrimitiveType type, int start, int count)
{
	switch (type)
	{
	default:
	case TriangleList:
		glDrawArrays(GL_TRIANGLES, start, count);
		break;
	case TriangleStrip:
		glDrawArrays(GL_TRIANGLE_STRIP, start, count);
		break;
	}
}
