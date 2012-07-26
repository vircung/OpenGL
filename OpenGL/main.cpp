#include <GL\freeglut.h>
#include <iostream>
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Camera.h"

#define  GLUT_KEY_LSHIFT    0x0070
#define  GLUT_KEY_RSHIFT    0x0071
#define  GLUT_KEY_LCTRL     0x0072
#define  GLUT_KEY_RCTRL     0x0073
#define  GLUT_KEY_LALT      0x0074
#define  GLUT_KEY_RALT      0x0075

std::vector<bool> keys(255,0);
std::vector<bool> specialKeys(128,0);
std::vector<bool> kouseKeys(3, 0);

glm::mat4 view;
glm::mat4 model;
glm::mat4 VM;
glm::vec2 mousePos;

int height = 500;
int width = 500;

Camera_p camera;
Camera_o hud;

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, width, height);
	camera.Activate();

	view = camera.GetView();
	model = glm::mat4(1.0f);
	
	VM = view * model;
	glLoadMatrixf(&VM[0][0]);

	camera.Render();
	
	camera.RenderDirections();

	glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, -0.1, 1.0);
		glVertex3f(-1.0, -0.1, 1.0);
		glVertex3f(1.0, -0.1, -1.0);
		glVertex3f(-1.0, -0.1, 1.0);
		glVertex3f(1.0, -0.1, -1.0);
		glVertex3f(-1.0, -0.1, -1.0);

	glEnd();

	glPushMatrix();
		hud.Activate();
		VM = glm::mat4(1);
		glLoadMatrixf(&VM[0][0]);

		glViewport(0, 0, 50, 50);
		camera.RenderDirections();

	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int _width, int _height){
	if(_width < 100)
		_width = 100;
	if(_height < 100)
		_height = 100;

	width = _width;
	height = _height;
	float aspec = (float)width / (float)height;
	camera.SetAspect(aspec);
	glutPostRedisplay();
}

void motion(int x, int y){
	float dx = x - mousePos.x;
	float dy = y - mousePos.y;
	camera.Rotate(glm::vec3(dy, dx, 0.0f));
	mousePos.x = x;
	mousePos.y = y;
}

void mouse(int button, int state, int x, int y){
        switch(button){
        case GLUT_LEFT_BUTTON :
                if(state == GLUT_DOWN){
						glutMotionFunc(motion);
                        mousePos = glm::vec2(x, y);
                        glutSetCursor(GLUT_CURSOR_NONE);
                }
                else{
                        glutWarpPointer(mousePos.x, mousePos.y);
                        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
						glutMotionFunc(0);
                }
                break;
        case GLUT_MIDDLE_BUTTON :
                break;
        case GLUT_RIGHT_BUTTON :
                break;

        }
        glutPostRedisplay();
}

void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);

	hud.SetOrtho();

	camera.SetPerspective();
	camera.SetLookAt();
	
	glMatrixMode(GL_MODELVIEW);
}

std::string getSpecialKeyString(int key){
	switch(key){
	case GLUT_KEY_F1:
		return "F1";
	case GLUT_KEY_F2:
		return "F2";
	case GLUT_KEY_F3:
		return "F3";
	case GLUT_KEY_F4:
		return "F4";
	case GLUT_KEY_F5:
		return "F5";
	case GLUT_KEY_F6:
		return "F6";
	case GLUT_KEY_F7:
		return "F7";
	case GLUT_KEY_F8:
		return "F8";
	case GLUT_KEY_F9:
		return "F9";
	case GLUT_KEY_F10:
		return "F10";
	case GLUT_KEY_F11:
		return "F11";
	case GLUT_KEY_F12:
		return "F12";
	case GLUT_KEY_PAGE_UP:
		return "PAGE UP";
	case GLUT_KEY_PAGE_DOWN:
		return "PAGE DOWN";
	case GLUT_KEY_HOME:
		return "HOME";
	case GLUT_KEY_END:
		return "END";
	case GLUT_KEY_LEFT:
		return "LEFT";
	case GLUT_KEY_RIGHT:
		return "RIGHT";
	case GLUT_KEY_UP:
		return "UP";
	case GLUT_KEY_DOWN:
		return "DOWN";
	case GLUT_KEY_INSERT:
		return "INSERT";
	case GLUT_KEY_LSHIFT:
		return "LEFT SHIFT";
	case GLUT_KEY_RSHIFT:
		return "RIGHT SHIFT";
	case GLUT_KEY_LCTRL:
		return "LEFT CTRL";
	case GLUT_KEY_RCTRL:
		return "RIGHT CTRL";
	case GLUT_KEY_LALT:
		return "LEFT ALT";
	case GLUT_KEY_RALT:
		return "RIGHT ALT";
	default:
		return "UNKNOWN";
	}
}


void specialKey(int key, int x, int y){
	/* UWAGA !! 
	   Prawy alt interpretowany jest jako kombinacja PRAWY ALT _i_ LEWY CTRL.
	   Poni¿sza instrukcja ogranicza jego interpretacjê tylko do LEWY CTRL
	*/
	if(key == GLUT_KEY_RALT){
		return;
	}

	switch(key){
	case 0x64:
		camera.Rotate(glm::vec3(0.0f, -10.0f, 0.0f));
		break;
	case 0x65:
		camera.Rotate(glm::vec3(10.0f, 0.0f, 0.0f));
		break;
	case 0x66:
		camera.Rotate(glm::vec3(0.0f, 10.0f, 0.0f));
		break;
	case 0x67:
		camera.Rotate(glm::vec3(-10.0f, 0.0f, 0.0f));
		break;
	}

	std::string _key = getSpecialKeyString(key);
	specialKeys[key] = true;

	std::clog << "Nacisnieo klawisz specjalny " << _key.c_str() <<" kod " << std::hex << key << "\n";
	glutPostRedisplay();
}

void specialKeyUp(int key, int x, int y){
	/* UWAGA !! 
	   Prawy alt interpretowany jest jako kombinacja PRAWY ALT _i_ LEWY CTRL.
	   Poni¿sza instrukcja ogranicza jego interpretacjê tylko do LEWY CTRL
	*/
	if(key == GLUT_KEY_RALT){
		return;
	}

	std::string _key = getSpecialKeyString(key);
	specialKeys[key] = false;

	std::clog << "Zwolniono klawisz specjalny " << _key.c_str() <<" kod " << key << "\n";
	glutPostRedisplay();
}

void keyFunc(unsigned char key, int x, int y){

	if (key == 16 ||key == 17 || key == 18)
		return;

	keys[key] = true;

	switch(key) {
	case 'Q':
		camera.Rotate(glm::vec3(0,0, 10));
		break;
	case 'E':
		camera.Rotate(glm::vec3(0,0, -10));
		break;
	case 'w':
		camera.MoveFront();
		break;
	case 's':
		camera.MoveBack();
		break;
	case 'a':
		camera.MoveLeft();
		break;
	case 'd':
		camera.MoveRight();
		break;
	case 'q':
		camera.MoveUp();
		break;
	case 'e':
		camera.MoveDown();
		break;
	case 0x1B:
		exit(0);
	default:
		std::clog << "Nacisnieo klawisz " << (char)key <<" kod " << (int)key << "\n";
		break;
	}
	glutPostRedisplay();
} 

void keyUpFunc(unsigned char key, int x, int y){

	if (key == 16 ||key == 17 || key == 18)
	return;

	keys[key] = false;

	switch(key) {
	default:
		std::clog << "Zwoniono klawisz " << (char)key <<" kod " << std::hex << (int)key << "\n";
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height); 
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Taki ma³y test");
    
	init();
    
	glutDisplayFunc(display); 
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutMouseFunc(mouse);
	
	glutKeyboardFunc(keyFunc);
	glutKeyboardUpFunc(keyUpFunc);
	glutSpecialFunc(specialKey);
	glutSpecialUpFunc(specialKeyUp);

    glutMainLoop();


    return 0;
}