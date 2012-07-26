#include "Camera_o.h"

Camera_o::Camera_o(void)
{
	SetOrtho();

	projection = glm::mat4(1.0);
	view = glm::mat4(1.0);
}

Camera_o::~Camera_o(void)
{
}

void Camera_o::Ortho(void){
	projection = glm::ortho(left, right, bottom, top, znear, zfar);
}

void Camera_o::Activate(void){
	Ortho();

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&projection[0][0]);
	glMatrixMode(GL_MODELVIEW);
}

glm::mat4 Camera_o::GetView(void){
	return view;
}

void Camera_o::SetOrtho(void){
	SetOrtho(-1.0, 1.0, -1.0, 1.0);
}

void Camera_o::SetOrtho(float _left, float _right, float _bottom, float _top){
	SetOrtho(_left, _right, _bottom, _top, -1.0, 1.0);
}

void Camera_o::SetOrtho(float _left, float _right, float _bottom, float _top, float _znear, float _zfar){
	left = _left;
	right = _right;
	top = _top;
	bottom = _bottom;
	znear = _znear;
	zfar = _zfar;
}