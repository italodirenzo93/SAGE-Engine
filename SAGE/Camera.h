#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>

enum eCameraProjection
{
	Projection,
	Orthographic
};

class cCamera {
	GLuint		_mvpID;

	glm::mat4	_projection;
	glm::mat4	_view;
	glm::mat4	_model;

	float		_fov;
	float		_nearPlane;
	float		_farPlane;

	glm::vec3	_position;
	glm::vec3	_target;
public:
	cCamera(GLuint, GLsizei, GLsizei);
	~cCamera();

	void Update() const;

	void Translate(float, float, float);
	void Viewport(GLint, GLint, GLsizei, GLsizei);
};

#endif