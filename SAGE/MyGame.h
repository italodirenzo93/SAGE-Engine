#ifndef __MYGAME_H__
#define __MYGAME_H__

#include "Game.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "SceneNode.h"

#include <GL/glew.h>

class cMyGame : public cGame
{
public:
	cMyGame();
	virtual ~cMyGame();

protected:
	void Update(float) override;
	void Draw() override;
	void ProcessEvents(SDL_Event const& ev) override;

private:
	std::unique_ptr<cShaderManager>	m_pShaderManager;
	GLuint							m_shaderProgram;

	std::unique_ptr<cCamera>		m_pCamera;
	std::unique_ptr<cSceneNode>		m_pSceneGraph;
};

#endif