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
void CALLBACK rot_tire_right(void);
void CALLBACK rot_tire_left(void);

static GLfloat x = 0;
static GLfloat y = 0;
static GLfloat alfa = 0;
static GLfloat tire = 0;

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
void CALLBACK rot_tire_right(void)
{
	tire += 10;
}
void CALLBACK rot_tire_left(void)
{
	tire -= 10;
}

void CALLBACK display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	qobj = gluNewQuadric();
	

	glPointSize(5);
	glBegin(GL_POINTS);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
	glEnd();

	glLoadIdentity();
	//glTranslatef(x, y, 0.0);
	glRotatef(alfa, 0, 1, 0);
	

	//corp total masina
	glPushMatrix();
		glColor3d(1.0, 1.0, 0);
	//partea 1/2 a masinii
		glPushMatrix();
			auxSolidBox(25, 15, 20);
		glPopMatrix();

	//partea 2/2 a masinii
		glPushMatrix();
			glTranslatef(32.5, 7.5, 0);
			auxSolidBox(40,30,20);
		glPopMatrix();

	//roata fata dreapta
		glColor3d(0, 0, 0); //culoarea pt roti 
		glPushMatrix();
			glTranslatef(0, -5, -12);
			glRotatef(tire, 0, 1, 0);
			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);
				gluCylinder(qobj, 5, 5, 3, 20, 1);
			glPopMatrix();

			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);			
				gluDisk(qobj, 2.5, 5, 20, 10);
			glPopMatrix();
		glPopMatrix();

	//roata fata stanga
		glPushMatrix();
			glTranslatef(0, -5, 9);
			glRotatef(tire, 0, 1, 0);
			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);
				gluCylinder(qobj, 5, 5, 3, 20, 10);
			glPopMatrix();

			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);	
				gluDisk(qobj, 2.5, 5, 20, 10);
			glPopMatrix();
		glPopMatrix();

	//roata spate stanga
		glPushMatrix();
			glTranslatef(40, -5, -12);
			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);				
				gluCylinder(qobj, 5, 5, 3, 20, 10);
			glPopMatrix();

			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);								
				gluDisk(qobj, 2.5, 5, 20, 10);
			glPopMatrix();
		glPopMatrix();

	//roata spate dreapta 
		glPushMatrix();
			glTranslatef(40, -5, 9);
			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);
				gluCylinder(qobj, 5, 5, 3, 20, 10);
			glPopMatrix();

			glPushMatrix();
				gluQuadricDrawStyle(qobj, GLU_FILL);
				gluDisk(qobj, 2.5, 5, 20, 10);
			glPopMatrix();
		glPopMatrix();

		//parbriz
		glColor3d(0.0, 0.0, 1);
		glPushMatrix();
			gluQuadricDrawStyle(qobj, GLU_FILL);
			glTranslatef(12.3, 15, -10);
			gluCylinder(qobj, 7.5, 7.5, 20, 2, 10);
		glPopMatrix();

		//geam lateral stanga
		/*glPushMatrix();
		glTranslatef(0, 0, -1.5);
		glRotatef(tire, 0, 1, 0);
		glTranslatef(30, 30, 0);
			gluQuadricDrawStyle(qobj, GLU_FILL);
			gluCylinder(qobj, 5, 5, 3, 20, 1);
		glPopMatrix();*/

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

	auxKeyFunc(AUX_a, rot_tire_left);
	auxKeyFunc(AUX_d, rot_tire_right);

	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return(0);
}
