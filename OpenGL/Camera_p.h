#pragma once

#include <GL\freeglut.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\vector_angle.hpp>

class Camera_p
{
protected:

	float fov;
	float aspect;
	float znear;
	float zfar;

	glm::mat4 projection;
	glm::mat4 view;

	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 direction;

	glm::vec3 up;
	glm::vec3 front;
	glm::vec3 right;

	glm::vec3 glob_front;
	glm::vec3 glob_right;
	glm::vec3 glob_up;

	glm::vec3 angles;

	void LookAt(void);
	void Perspective(void);
	void Calculate(void);
	void Rotations(void);

public:
	Camera_p(void);
	~Camera_p(void);

	void Activate(void);
	glm::mat4 GetView(void);

	void SetLookAt(void);
	void SetLookAt(glm::vec3);
	void SetLookAt(glm::vec3, glm::vec3);
	void SetLookAt(glm::vec3, glm::vec3, glm::vec3);
	void SetPerspective(void);
	void SetPerspective(float, float, float, float);
	void SetAspect(float);
	void SetPosition(glm::vec3);
	void SetDirection(glm::vec3);
	void SetTarget(glm::vec3);

	glm::vec3 GetPosition(void);
	glm::vec3 GetDirection(void);
	glm::vec3 GetTarget(void);
	glm::vec3 GetUp(void);
	glm::vec3 GetFront(void);
	glm::vec3 GetRight(void);

	void Rotate(glm::vec3);
	void Translate(glm::vec3);

	void Render(void);
	void RenderDirections(void);

	void MoveFront(void);
	void MoveBack(void);
	void MoveRight(void);
	void MoveLeft(void);
	void MoveUp(void);
	void MoveDown(void);
};