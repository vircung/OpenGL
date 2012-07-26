#pragma once

#include <GL\freeglut.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera_o
{
protected:
	float left;
	float right;
	float top;
	float bottom;
	float znear;
	float zfar;

	glm::mat4 projection;
	glm::mat4 view;

	void Ortho(void);

public:
	Camera_o(void);
	~Camera_o(void);

	void Activate(void);
	glm::mat4 GetView(void);

	void SetOrtho(void);
	void SetOrtho(float, float, float, float);
	void SetOrtho(float, float, float, float, float, float);
};

