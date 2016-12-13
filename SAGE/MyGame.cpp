#include "MyGame.h"
#include "GLRenderer.h"
#include "CubeObject.h"
#include "TriangleObject.h"
using namespace SAGE;

#include <iostream>

cMyGame::cMyGame() : Super(800, 600, false, "SAGE Engine by Italo Di Renzo") // SAGE - Sweet....Another Game Engine
{
	// Load shaders
	m_shaderProgram = std::make_unique<cGLBasicShaderProgram>();

	// Set up camera
	m_pCamera = std::make_unique<cCamera>(*m_shaderProgram, GetWindowWidth(), GetWindowHeight());

	// Create game objects
	m_pSceneGraph = std::make_unique<cSceneNode>();
	m_pSceneGraph->AttachNode("Cube", std::make_shared<cCubeObject>(GetRenderer()));
	//m_pSceneGraph->AttachNode("Triangle Thing", std::make_shared<cTriangleObject>(GetRenderer()));
}

cMyGame::~cMyGame()
{
}

void cMyGame::Update(float deltaTime)
{
	m_pCamera->Update();
	float const camSpeed = 10.0f;
	auto keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_LEFT]) {
		m_pCamera->Translate(-camSpeed * deltaTime, 0, 0);
	}
	if (keyState[SDL_SCANCODE_RIGHT]) {
		m_pCamera->Translate(camSpeed * deltaTime, 0, 0);
	}
	if (keyState[SDL_SCANCODE_UP]) {
		m_pCamera->Translate(0, camSpeed * deltaTime, 0);
	}
	if (keyState[SDL_SCANCODE_DOWN]) {
		m_pCamera->Translate(0, -camSpeed * deltaTime, 0);
	}
	if (keyState[SDL_SCANCODE_PAGEUP]) {
		m_pCamera->Translate(0, 0, -camSpeed * deltaTime);
	}
	if (keyState[SDL_SCANCODE_PAGEDOWN]) {
		m_pCamera->Translate(0, 0, camSpeed * deltaTime);
	}
}

void cMyGame::Draw()
{
	iRenderer& renderer = GetRenderer();
	renderer.Clear(0.0f, 0.0f, 0.1f, 1.0f);

	// Draw stuff
	m_shaderProgram->Apply();
	m_pSceneGraph->RenderNodes();

	renderer.Present();
}

void cMyGame::ProcessEvents(SDL_Event const& ev)
{
	Super::ProcessEvents(ev);

	if (ev.type == SDL_WINDOWEVENT)
	{
		switch (ev.window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
			GetRenderer().Resize(ev.window.data1, ev.window.data2);
			break;
		}
	}
	else if (ev.type == SDL_KEYDOWN)
	{
		if (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			Close();
	}
}