#ifndef __MYGAME_H__
#define __MYGAME_H__

#include "Game.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "SceneNode.h"
#include "GLBasicShaderProgram.h"

#include <GL/glew.h>

class cMyGame : public SAGE::cGame
{
public:
	cMyGame();
	virtual ~cMyGame();

protected:
	void Update(float) override;
	void Draw() override;
	void ProcessEvents(SDL_Event const& ev) override;

private:
	std::unique_ptr<SAGE::cGLBasicShaderProgram>	m_shaderProgram;

	std::unique_ptr<SAGE::cCamera>		m_pCamera;
	std::unique_ptr<SAGE::cSceneNode>		m_pSceneGraph;
};

#endif