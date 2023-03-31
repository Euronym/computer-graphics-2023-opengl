#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<math.h>
#include<stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include<bits/stdc++.h>

#define drawOneLine(x1,y1,x2,y2)  glBegin(GL_LINES);  \
   glVertex3f ((x1),(y1),(-5.0)); glVertex3f ((x2),(y2),(-5.0)); glEnd();   //draw...dotted line

float tx=0.0f;    //X-axis translation varaible
float ty = 0.0f;	//Y-axis translation varaible
float cloudTanslat = 0.0;  //Translation varaible for cloud
float tx_2=0.0f;
float cloudMove = 0.00275;   //Translation increament value (speed)
float Maxtx = 6.0f;
float forwardIncrmt = 0.15f;
bool forwardTrans = false;
float backwardIncrmt = 0.15f;        //backward movement speed
float maxTheta = 35.0f;					//maximum rotation angle
float movTheta = 0.0f;
float incTheta = 1.5f;
bool forwardMov = false;
int timer =30;
int counter;
float Cx = 0.0f;
float Cincrmt = 0.03f;

//Initializes 3D
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 800, 0.0, 800, -1000.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

//reshape handler
void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(double)w / (double)h, 1.0, 200.0);
}

void init(void) {//initial 
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
}

void circle(float rad, float xx, float yy) {

	float thetha = 2 * 3.1415 / 20;
	float x, y;
	glColor3f(1.1, 1.1, 1.10);
	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 20; i++) {
		x = rad * cos(i*thetha) + xx;
		y = rad*sin(i*thetha) + yy;
		float z = -5.0f;
		glVertex3f(x,y,z);
	}
	glEnd();
}

void head() {//stickman head
	circle(0.08, -1.0f, 0.97f);

}

void neck() {//stickman neck
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.9f, -5.0f);
	glVertex3f(-1.0f, 0.8f, -5.0f);
	glEnd();
}

void body() { //stickman body
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f,0.8f,-5.0f);
	glVertex3f(-1.0f, 0.5f,-5.0f);
	glEnd();
}

void leftHand() {//stickman1 left hand
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.8f, -5.0f);
	glVertex3f(-0.9f, 0.7f, -5.0f);
	glEnd();
}

void rightHand() { //stick man 1 right hand

	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.8f, -5.0f);
	glVertex3f(-0.89f, 0.75f, -5.0f);
	glEnd();
}
void leftArm() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.89f, 0.75f, -5.0f);
	glVertex3f(-0.79f, 0.80f, -5.0f);
	glEnd();
}

void rightArm() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.9f, 0.7f, -5.0f);
	glVertex3f(-0.79f, 0.80f, -5.0f);
	glEnd();
}

void leftLeg() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.5f, -5.0f);
	glVertex3f(-1.01f, 0.4f, -5.0f);
	glEnd();
}

void rightLeg() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.5f, -5.0f);
	glVertex3f(-0.99f, 0.4f, -5.0f);
	glEnd();
}

void leftShin() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.4f, -5.0f);
	glVertex3f(-1.01f, 0.3f, -5.0f);
	glEnd();
}

void rightShin() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.4f, -5.0f);
	glVertex3f(-0.99f, 0.3f, -5.0f);
	glEnd();
}

void leftHand_2() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.8f, -5.0f);
	glVertex3f(-1.01f, 0.6f, -5.0f);
	glEnd();
}

void rightHand_2() {
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.8f, -5.0f);
	glVertex3f(-0.99f, 0.6f, -5.0f);
	glEnd();
}

void bodyMovement_2() {
	if (counter < 19400) {
		glTranslatef(tx_2, 0.0, 0.0);
		counter++;
	} else {
		glTranslatef(tx_2, 0.0, 0.0);
		tx_2 = tx_2-backwardIncrmt;
	}

}

void leftHandMovement() {
	glTranslatef(-1.0, 0.8, -5.0);
	glRotatef(movTheta, 0.0, 0.0, 1.0);
	glTranslatef(1.0, -0.8, 5.0);
}


void rightHandMovement() //stick man 2 right hand movement
{
	glTranslatef(-1.0f, 0.8f, -5.0f);
	glRotatef(-movTheta, 0.0f, 0.0f, 1.0f);
	glTranslatef(1.0f, -0.8f, 5.0f);
}

//leg movement
void leftLegMovement()
{
	glTranslatef(-1.0, 0.5, -5.0);
	glRotatef(-movTheta, 0.0, 0.0, 1.0);
	glTranslatef(1.0, -0.5, 5.0);
}

void rightLegMovement()
{
	glTranslatef(-1.0f, 0.5f, -5.0f);
	glRotatef(movTheta, 0.0, 0.0, 1.0);
	glTranslatef(1.0f, -0.5f, 5.0f);

}

void angleTheta() {
	if (forwardMov) {
		movTheta += incTheta;
		if (movTheta > maxTheta)
			forwardMov = false;
	} else if (!forwardMov) {
		movTheta -= incTheta;
		if (movTheta < -maxTheta)

			forwardMov = true;
	}
}

void drawStickman_2() {
	//body
	glPushMatrix();
	bodyMovement_2();
	body();
	head();
	neck();
	glPopMatrix();
	
	//leftHand
	glPushMatrix();
	bodyMovement_2();
	leftHandMovement();
	leftHand_2();
	glPopMatrix();

	//rightHand
	glPushMatrix();
	bodyMovement_2();
	rightHandMovement();
	rightHand_2();
	glPopMatrix();

	//leftLeg
	glPushMatrix();
	bodyMovement_2();
	leftLegMovement();
	leftLeg();
	leftShin();
	glPopMatrix();

	//rightLeg
	glPushMatrix();
	bodyMovement_2();
	rightLegMovement();
	rightLeg();
	rightShin();
	glPopMatrix();

	angleTheta();
}

void blackBG() {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0f, -3.80f, -5.0f);
    glVertex3f(5.0f, -3.80f, -5.0f);
    glVertex3f(5.0f, 4.5f, -5.0f);
    glVertex3f(-5.0f, 4.5f,-5.0f);
    glEnd();
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT);

	//stickman_2
	glPushMatrix();
	glTranslatef(0, -1.77f, 0.0f);
	glScalef(0.7, 0.7, 1.0);
	drawStickman_2();
	glPopMatrix();

	counter++;

	glutSwapBuffers();
}


void pressKey(unsigned char key, int x, int y) {
	if(key == 'd') {
		display();
	} 
}

void Timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(timer, Timer, value);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 1500);
	glutInitWindowPosition(0, 0);
	initRendering();
	glutCreateWindow("CG_stickman");
	glutKeyboardFunc(pressKey);
	//glutDisplayFunc(display);
	glutReshapeFunc(handleResize);
	glutTimerFunc(timer, Timer, 1);
	init();
	glutMainLoop();

	return 0;
}

