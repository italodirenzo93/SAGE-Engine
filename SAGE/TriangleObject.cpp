#include "TriangleObject.h"

namespace SAGE
{
	cTriangleObject::cTriangleObject(iRenderer& renderer) : _numIndices(3), m_renderer(renderer) {
		const GLfloat vertexBufferData[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f,  1.0f, 0.0f
		};

		const GLfloat colorBufferData[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};

		glGenVertexArrays(1, &_vertexArrayID);
		glBindVertexArray(_vertexArrayID);

		// Vertex buffer
		glGenBuffers(1, &_vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

		// Color buffer
		glGenBuffers(1, &_colorBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, _colorBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);
	}

	cTriangleObject::~cTriangleObject() {}

	void cTriangleObject::OnRender() {
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
		glVertexAttribPointer(
			0,
			3,	// 3 point vertex
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		// Pass colors to shader
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, _colorBufferID);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//glDrawArrays(GL_TRIANGLES, 0, _numIndices);
		m_renderer.DrawPrimitives(TriangleList, 0, _numIndices);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
}