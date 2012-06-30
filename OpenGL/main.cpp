#include <GL\freeglut.h>

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

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(250, 250); 
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Taki ma³y test");
    init();
    glutDisplayFunc(display); 
    glutMainLoop();
    return 0;
}