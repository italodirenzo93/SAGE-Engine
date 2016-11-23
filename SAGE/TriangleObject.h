#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <GL/glew.h>
#include "SceneNode.h"
#include "Renderer.h"

class cTriangleObject : public cSceneNode {
	GLuint	_vertexArrayID;
	GLuint	_vertexBufferID;
	GLint	_numIndices;
	GLuint _colorBufferID;
	iRenderer& m_renderer;
public:
	cTriangleObject(iRenderer& renderer);
	~cTriangleObject();

	void OnRender() override;
};

#endif