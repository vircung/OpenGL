#include <GL\freeglut.h>
#include <iostream>

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
	    glColor3f(1.0, 0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
	    glColor3f(0.0, 1.0, 0.0); glVertex3f(1.0, 0.0, 0.0);
	    glColor3f(0.0, 0.0, 1.0); glVertex3f(0.5, 1.0, 0.0);
    glEnd();

	glFlush();
}

void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
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
	case 0x70:
		return "LEFT SHIFT";
	case 0x71:
		return "RIGHT SHIFT";
	case 0x72:
		return "LEFT CTRL";
	case 0x73:
		return "RIGHT CTRL";
	case 0x74:
		return "LEFT ALT";
	case 0x75:
		return "RIGHT ALT";
	default:
		return "UNKNOWN";
	}
}


void specialKey(int key, int x, int y){
	std::string _key = getSpecialKeyString(key);

	std::clog << "Nacisnieo klawisz " << _key.c_str() <<" kod "<< key << "\n";

}

void specialKeyUp(int key, int x, int y){
	std::string _key = getSpecialKeyString(key);

	std::clog << "Zwolniono klawisz " << _key.c_str() <<" kod "<< key << "\n";
}

void keyFunc(unsigned char key, int x, int y){

	if (key == 16 ||key == 17 || key == 18)
		return;

	switch(key) {

	default:
		std::clog << "Nacisnieo klawisz " << (char)key <<" kod "<< (int)key << "\n";
		break;
	}
} 

void keyUpFunc(unsigned char key, int x, int y){

		if (key == 16 ||key == 17 || key == 18)
		return;

	switch(key) {

	default:
		std::clog << "Zwoniono klawisz " << (char)key <<" kod "<< (int)key << "\n";
		break;
	}
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(250, 250); 
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Taki ma³y test");
    init();
    glutDisplayFunc(display); 
	glutKeyboardFunc(keyFunc);
	glutKeyboardUpFunc(keyUpFunc);
	glutSpecialFunc(specialKey);
	glutSpecialUpFunc(specialKeyUp);
    glutMainLoop();
    return 0;
}