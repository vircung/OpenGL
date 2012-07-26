#include "Camera_p.h"
#include <iostream>

Camera_p::Camera_p(void)
{
	SetPerspective();
	
	eye = glm::vec3(0,0,1);
	target = glm::vec3(0,0,0);
	direction = glm::vec3(0,0,-1);

	up = glm::vec3(0,1,0);
	front = glm::vec3(0,0,1);
	right = glm::vec3(1,0,0);

	glob_up = up;
	glob_right = right;
	glob_front = front;
	
	Rotations();
	LookAt();
	Perspective();
}


Camera_p::~Camera_p(void)
{
}

void Camera_p::LookAt(void){
	view = glm::lookAt(eye, target, up);
}

void Camera_p::Perspective(void){
	projection = glm::perspective(fov, aspect, znear, zfar);
}

void Camera_p::Calculate(void){
	right = glm::normalize(glm::cross(direction, glob_up));
	up = glm::normalize(glm::cross(right, direction));
	front = glm::normalize(glm::cross(glob_up, right));

	target = eye + direction;
}

void Camera_p::Rotations(void){
	angles.x = glm::angle(direction, glob_front);
	angles.y = glm::angle(direction, -glob_front);
}

void Camera_p::Activate(void){
	Perspective();
	LookAt();

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&projection[0][0]);
	glMatrixMode(GL_MODELVIEW);
}

glm::mat4 Camera_p::GetView(void){
	return view;
}

void Camera_p::SetLookAt(void){
	SetLookAt(glm::vec3(0, 0, 2));
}

void Camera_p::SetLookAt(glm::vec3 _eye){
	SetLookAt(_eye, glm::vec3(0, 0, -1));
}

void Camera_p::SetLookAt(glm::vec3 _eye, glm::vec3 _direction){
	SetLookAt(_eye, _eye + _direction, glm::vec3(0,1,0));
}

void Camera_p::SetLookAt(glm::vec3 _eye, glm::vec3 _target, glm::vec3 _up){
	eye = _eye;
	target = _target;
	up = _up;
	direction = target - eye;

	Rotations();
	LookAt();
}

void Camera_p::SetPerspective(void){
	SetPerspective(45.0, 4.0/3.0, 0.01, 100.0);

	Perspective();
}

void Camera_p::SetPerspective(float _fov, float _aspect, float _znear, float _zfar){
	fov = _fov;
	aspect = _aspect;
	znear = _znear;
	zfar = _zfar;

	Perspective();
}

void Camera_p::SetAspect(float _aspect){
	aspect = _aspect;

	Perspective();
}

void Camera_p::SetPosition(glm::vec3 _position){
	eye = _position;
	target = eye + direction;
	
	Rotations();
	LookAt();
}

void Camera_p::SetDirection(glm::vec3 _direction){
	direction = _direction;
	target = eye + direction;

	LookAt();
}

void Camera_p::SetTarget(glm::vec3 _target){
	target = target;
	direction = target - eye;

	LookAt();
}

glm::vec3 Camera_p::GetPosition(void){
	return eye;
}

glm::vec3 Camera_p::GetDirection(void){
	return direction;
}

glm::vec3 Camera_p::GetTarget(void){
	return target;
}

glm::vec3 Camera_p::GetUp(void){
	return up;
}

glm::vec3 Camera_p::GetFront(void){
	return front;
}

glm::vec3 Camera_p::GetRight(void){
	return right;
}
void Camera_p::Rotate(glm::vec3 rotate){
	angles -= rotate;
	glm::quat yaw = glm::angleAxis(angles.y, glob_up);
	glm::quat pitch = glm::angleAxis(angles.x, glob_right);

	glm::quat res = yaw * pitch;
	
	direction = res * glob_front;
		
	/*
	// uwaga na gimbal lock
	direction = glm::rotate(direction, -rotate.y, up);
	direction = glm::rotate(direction, -rotate.x, right);
	*/
	
	Calculate();
	LookAt();
}

void Camera_p::Translate(glm::vec3 translate){
	eye = eye + translate;
	
	Calculate();
	LookAt();
}

void Camera_p::Render(void){
	glPushMatrix();

		glPointSize(4);

		glBegin(GL_POINTS);
			glColor3f(1.0, 1.0, 0.0); glVertex3f(target.x, target.y, target.z);
		glEnd();

	glPopMatrix();
}

void Camera_p::RenderDirections(void){
	glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0); glVertex3f(0.0, 0.0, 0.0); glVertex3fv(&right[0]);
			glColor3f(0.0, 1.0, 0.0); glVertex3f(0.0, 0.0, 0.0); glVertex3fv(&direction[0]);
			glColor3f(0.0, 0.0, 1.0); glVertex3f(0.0, 0.0, 0.0); glVertex3fv(&up[0]);
	glEnd();
}

void Camera_p::MoveFront(void){
	Translate(front);
}
void Camera_p::MoveBack(void){
	Translate(-front);
}
void Camera_p::MoveRight(void){
	Translate(right);
}
void Camera_p::MoveLeft(void){
	Translate(-right);
}
void Camera_p::MoveUp(void){
	Translate(glob_up);
}
void Camera_p::MoveDown(void){
	Translate(-glob_up);
}