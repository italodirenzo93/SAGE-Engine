#include "Camera.h"

namespace SAGE
{
	cCamera::cCamera(cGLBasicShaderProgram& program, GLsizei width, GLsizei height) :
		m_shaderProgram(program),
		_fov(45.0f),
		_nearPlane(0.1f),
		_farPlane(100.0f),
		_position(0, 0, 3)
	{
		_projection = glm::perspective(
			glm::radians(_fov),
			4.0f / 3.0f,
			_nearPlane,
			_farPlane
		);

		_view = glm::lookAt(
			_position,
			_target,
			glm::vec3(0, 1.0f, 0)
		);

		_model = glm::mat4(1.0f);

		this->Viewport(0, 0, width, height);
	}

	cCamera::~cCamera() {

	}

	void cCamera::Update() const
	{
		m_shaderProgram.SetProjectionMatrix(_projection);
		m_shaderProgram.SetViewMatrix(_view);
		m_shaderProgram.SetWorldMatrix(_model);
	}

	void cCamera::Translate(float x, float y, float z) {
		glm::vec3 newPos(
			_position.x + x,
			_position.y + y,
			_position.z + z
		);
		_view = glm::lookAt(
			newPos,
			_target,
			glm::vec3(0, 1.0f, 0)
		);
		_position = newPos;
	}

	void cCamera::Viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
		glViewport(x, y, width, height);
	}
}