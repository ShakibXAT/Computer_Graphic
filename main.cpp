#include <windows.h>
#include <iostream>
#include <stdlib.h>

#ifdef _APPLE_
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


using namespace std;


//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL); //Enable color
	glClearColor(0.5f, 1.0f, 1.0f,0.0f); //Change the background to sky blue
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 30.0f;
float _cameraAngle = 0.0f;


void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(-_cameraAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -5.0f);

	glPushMatrix();
	glTranslatef(0.0f, 1.0f, 0.0f);
	glRotatef(_angle, 1.0f, 0.0f, 0.0f);
	glScalef(1.f, 1.f, 1.f);

	//hexagoan
	glBegin(GL_POLYGON);
	glColor3f(1.0f, .99f, 0.0f);

	glVertex2f(-0.4f, -0.7f);
	glVertex2f(-0.8f, 0.0f);
	glVertex2f(-0.4f, 0.7f);
	glVertex2f(0.4f, 0.7f);
	glVertex2f(0.8f, 0.0f);
	glVertex2f(0.4f, -0.7f);


	glEnd();

	glPopMatrix();



	glutSwapBuffers();
}

void update(int value) {
	_angle += 5.0f;
	if (_angle > 360) {
		_angle -= 360;
	}

	glutPostRedisplay(); ////Tell GLUT that the scene has changed
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);

	//Create the window
	glutCreateWindow("181-15-10861");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);

	glutReshapeFunc(handleResize);

	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}
