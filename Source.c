/*
Programul afiseaza un patrat pe care il translateaza
pe axa x la apasarea sagetilor stanga, dreapta
*/
#include "header.h"
#include <glaux.h>
#include <gl.h>
#include <glu.h>
#include <math.h>


void myinit(void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK MutaStanga(void);
void CALLBACK MutaDreapta(void);
void CALLBACK MutaSus(void);
void CALLBACK MutaJos(void);
void CALLBACK rot_y_up(void);
void CALLBACK rot_y_down(void);

static GLfloat x = 0;
static GLfloat y = 0;
static GLfloat alfa = 0;
GLUquadricObj* qobj;
void myinit(void) {
	glClearColor(0.0, 0.0, 0.4, 1.0);
}


void CALLBACK MutaStanga(void)
{
	x = x - 10;
}

void CALLBACK MutaDreapta(void)
{
	x = x + 10;
}
void CALLBACK MutaSus(void)
{
	y = y + 10;
}
void CALLBACK MutaJos(void)
{
	y = y - 10;
}
void CALLBACK rot_y_up(void)
{
	alfa = alfa + 10;
}
void CALLBACK rot_y_down(void)
{
	alfa = alfa - 10;
}
void CALLBACK display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	//glTranslatef(x, y, 0.0);
	glRotatef(alfa, 0, 1, 0);

	glColor3d(1.0, 1.0, 0);
	qobj = gluNewQuadric();

	//un hexagon, pct pe circumsferinta unui cerc
	/*glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
	gluCylinder(qobj, 50, 50, 1, 6, 1);
	glPopMatrix();

	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
	gluCylinder(qobj, 50, 50, 1, 30, 1);
	glPopMatrix();*/

	//corp total masina
	glPushMatrix();
	
	//partea 1/2 a masinii
		glPushMatrix();
			auxWireBox(25, 15, 20);
		glPopMatrix();

	//partea 2/2 a masinii
		glPushMatrix();
			glTranslatef(32.5, 7.5, 0);
			auxWireBox(40,30,20);
		glPopMatrix();

	//roata fata dreapta
		glPushMatrix();
			glColor3d(0, 0, 0);
			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);
				glTranslatef(0, -5, -12);
				gluCylinder(qobj, 5, 5, 3, 20, 10);
			glPopMatrix();

			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);
				glTranslatef(0, -5, -12);			
				gluDisk(qobj, 2.5, 5, 20, 10);
			glPopMatrix();
		glPopMatrix();

	//roata fata stanga
		glPushMatrix();
			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);
				glTranslatef(0, -5, 9);
				gluCylinder(qobj, 5, 5, 3, 20, 10);
			glPopMatrix();

			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);
				glTranslatef(0, -5, 9);			
				gluDisk(qobj, 2.5, 5, 20, 10);
			glPopMatrix();
		glPopMatrix();

	//roata spate stanga
		glPushMatrix();
			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);
				glTranslatef(40, -5, -12);
				gluCylinder(qobj, 5, 5, 3, 20, 10);
			glPopMatrix();

			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);
				glTranslatef(40, -5, -12);				
				gluDisk(qobj, 2.5, 5, 20, 10);
			glPopMatrix();
		glPopMatrix();

	//roata spate dreapta 
		glPushMatrix();
			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);
				glTranslatef(40, -5, 9);
				gluCylinder(qobj, 5, 5, 3, 20, 10);
			glPopMatrix();

			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);
				glTranslatef(40, -5, 9);
				gluDisk(qobj, 2.5, 5, 20, 10);
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();

	auxSwapBuffers();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-95.0, 95.0, 95.0 * (GLfloat)h / (GLfloat)w,
			-95.0 * (GLfloat)h / (GLfloat)w, -100.0, 100.0);
	else
		glOrtho(-95.0 * (GLfloat)w / (GLfloat)h,
			95.0 * (GLfloat)w / (GLfloat)h, -95.0, 95.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_DOUBLE | AUX_RGB);
	auxInitPosition(0, 0, 1920, 1080);
	auxInitWindow("Project C.A.R");
	myinit();
	auxKeyFunc(AUX_LEFT, MutaStanga);
	auxKeyFunc(AUX_RIGHT, MutaDreapta);
	auxKeyFunc(AUX_UP, MutaSus);
	auxKeyFunc(AUX_DOWN, MutaJos);
	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, rot_y_up);
	auxMouseFunc(AUX_RIGHTBUTTON, AUX_MOUSEDOWN, rot_y_down);
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return(0);
}
