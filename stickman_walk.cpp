#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <bits/stdc++.h>

#define drawOneLine(x1,y1,x2,y2)  glBegin(GL_LINES);  \
   glVertex3f ((x1),(y1),(-5.0)); glVertex3f ((x2),(y2),(-5.0)); glEnd();   //draw...dotted line

float tx=0.0f;    //X-axis translation varaible
float ty = 0.0f;	//Y-axis translation varaible
float cloudTanslat = 0.0;  //Translation varaible for cloud
float tx_2=0.0f;
float cloudMove = 0.00275;   //Translation increament value (speed)
float Maxtx = 6.0f;
float forwardIncrmt = 0.0015f;
bool forwardTrans = false;
float backwardIncrmt = 0.0015f;        //backward movement speed
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
void init(void) //initial
{
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
void head()  //stickman head
{
	circle(0.08, -1.0f, 0.97f);

}

void sky()
{
    glColor3f(0.22, 0.5, 0.67);
    glBegin(GL_POLYGON);
    glVertex3f(-4.0f, -1.80f, -5.0f);
    glVertex3f(4.0f, -1.80f, -5.0f);
    glVertex3f(4.0f, 4.5f, -5.0f);
    glVertex3f(-4.0f, 4.5f,-5.0f);
    glEnd();
}



void road()
{
	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(5.0);
	glBegin(GL_POLYGON);
	glVertex3f(-1.5f, -1.8f, -5.0f);
	glVertex3f(-1.6f, -3.1f, -5.0f);
	glVertex3f(0.5f, -3.1f, -5.0f);
	glVertex3f(0.6f, -1.80f, -5.0f);
	glEnd();
}
//road mark
void roadMark()
{

	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(5.0);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(5, 0x1C47);
	drawOneLine(-5.95, -1.70, 5.50, -1.70);
	glDisable(GL_LINE_STIPPLE);
}
void neck() //stickman neck
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.9f, -5.0f);
	glVertex3f(-1.0f, 0.8f, -5.0f);
	glEnd();
}
void body()  //stickman body
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f,0.8f,-5.0f);
	glVertex3f(-1.0f, 0.5f,-5.0f);
	glEnd();
}
void leftHand()  //stickman1 left hand
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.8f, -5.0f);
	glVertex3f(-0.9f, 0.7f, -5.0f);
	glEnd();
}
void rightHand()  //stick man 1 right hand
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.8f, -5.0f);
	glVertex3f(-0.89f, 0.75f, -5.0f);
	glEnd();
}
void leftArm()
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.89f, 0.75f, -5.0f);
	glVertex3f(-0.79f, 0.80f, -5.0f);
	glEnd();
}

void rightArm()
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.9f, 0.7f, -5.0f);
	glVertex3f(-0.79f, 0.80f, -5.0f);
	glEnd();
}

void umbrellaStick()
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.79f, 0.80f, -5.0f);
	glVertex3f(-0.79f, 1.2f, -5.0f);
	glEnd();
}


void leftLeg()
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.5f, -5.0f);
	glVertex3f(-1.01f, 0.4f, -5.0f);
	glEnd();
}
void rightLeg()
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.5f, -5.0f);
	glVertex3f(-0.99f, 0.4f, -5.0f);
	glEnd();
}
void leftShin()
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.4f, -5.0f);
	glVertex3f(-1.01f, 0.3f, -5.0f);
	glEnd();
}
void rightShin()
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.4f, -5.0f);
	glVertex3f(-0.99f, 0.3f, -5.0f);
	glEnd();
}

void leftHand_2()  //stick man 2 left hand
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.8f, -5.0f);
	glVertex3f(-1.01f, 0.6f, -5.0f);
	glEnd();
}

void rightHand_2() //stick man 2 right hand
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f, 0.8f, -5.0f);
	glVertex3f(-0.99f, 0.6f, -5.0f);
	glEnd();
}


void halfCircle(float rad, float xx, float yy) {

	float thetha = 2 * 3.1415 / 20;
	float x, y;
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(1.0);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < 10; i++) {
		x = rad * cos(i*thetha) + xx;
		y = rad*sin(i*thetha) + yy;
		float z = -5.0f;
		glVertex3f(x,y,z);
	}
	glEnd();
}


void umbrella()
{
	halfCircle(0.60, -0.8f, 0.97f);
}


void filledCircle(float rad, float xx, float yy) {

	float thetha = 2 * 3.1415 / 20;
	float x, y;
	glColor3f(1.1, 1.1, 1.10);
	glLineWidth(1.0);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < 20; i++) {
		x = rad * cos(i*thetha) + xx;
		y = rad*sin(i*thetha) + yy;
		float z = -5.0f;
		glVertex3f(x, y, z);
	}
	glEnd();
}

void treeCircle(float rad, float xx, float yy) {

	float thetha = 2 * 3.1415 / 20;
	float x, y;
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(1.0);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < 20; i++) {
		x = rad * cos(i*thetha) + xx;
		y = rad*sin(i*thetha) + yy;
		float z = -5.0f;
		glVertex3f(x, y, z);
	}
	glEnd();
}

void cloud()
{
	glColor3f(1.1, 1.1, 1.1);
	filledCircle(0.4, -0.9f, 1.7f);
	filledCircle(0.4, -1.4f, 1.7f);
	filledCircle(0.4, -2.0f, 1.7f);
	filledCircle(0.4, -1.5f, 1.4f);
	filledCircle(0.4, 0.3f, 1.9f);
	filledCircle(0.4, 0.8f, 1.9f);
	filledCircle(0.4, 1.4f, 1.9f);
	filledCircle(0.4, 0.9f, 1.5f);
    filledCircle(0.4, 1.8f, 1.9f);
	filledCircle(0.4, 2.5f, 1.9f);
	filledCircle(0.4, 1.5f, 1.5f);

}


void rain()  //raindrops
{

    for(int i=1;i<=250000;i++)
    {

        int x=rand(),y=rand();
        x%=1500; y%=800;
        if(x>=500&&x<=1500&&y<=400)continue;
        glBegin(GL_LINES);
        glColor3f(1.0,1.0,1.0);
        float z=-5.0;
        glVertex3f(x,y,z);
        glVertex3f(x+0.08,y+0.09,z);
        glEnd();
    }



}


void tree()
{
	glColor3ub(165, 42, 42);
	glLineWidth(50.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.0f,0.8f,-5.0f);
	glVertex3f(-1.0f, 1.7f,-5.0f);
	glEnd();
}

void treebody_1()
{
    glColor3f(0.0, 0.8, 0.0);
    treeCircle(0.09, -2.5f, -0.7f);
    treeCircle(0.09, -2.4f, -0.7f);
    treeCircle(0.09, -2.3f, -0.6f);
    treeCircle(0.09, -2.6f, -0.7f);
    treeCircle(0.09, -2.7f, -0.6f);
    treeCircle(0.09, -2.6f, -0.5f);
    treeCircle(0.09, -2.5f, -0.5f);
    treeCircle(0.09, -2.4f, -0.5f);
    treeCircle(0.09, -2.4f, -0.6f);
    treeCircle(0.14, -2.5f, -0.6f);


}


void treebody_2()
{
    glColor3f(0.0, 0.8, 0.0);
    treeCircle(0.09, 0.66f, -0.7f);
    treeCircle(0.09, 0.56f, -0.7f);
    treeCircle(0.09, 0.46f, -0.6f);
    treeCircle(0.09, 0.76f, -0.7f);
    treeCircle(0.09, 0.86f, -0.6f);
    treeCircle(0.09, 0.76f, -0.5f);
    treeCircle(0.09, 0.66f, -0.5f);
    treeCircle(0.09, 0.56f, -0.5f);
    treeCircle(0.09, 0.46f, -0.6f);
    treeCircle(0.14, 0.66f, -0.6f);


}


void treebody_3()
{
    glColor3f(0.0, 0.8, 0.0);
    treeCircle(0.09, 2.0f, -0.7f);
    treeCircle(0.09, 1.90f, -0.7f);
    treeCircle(0.09, 1.80f, -0.6f);
    treeCircle(0.09, 2.10f, -0.7f);
    treeCircle(0.09, 2.20f, -0.6f);
    treeCircle(0.09, 2.10f, -0.5f);
    treeCircle(0.09, 2.00f, -0.5f);
    treeCircle(0.09, 1.90f, -0.5f);
    treeCircle(0.09, 1.80f, -0.6f);
    treeCircle(0.14, 2.00f, -0.6f);


}


void sunCircle(float rad, float xx, float yy) {

	float thetha = 2 * 3.1415 / 20;
	float x, y;
	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(1.0);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < 20; i++) {
		x = rad * cos(i*thetha) + xx;
		y = rad*sin(i*thetha) + yy;
		float z = -5.0f;
		glVertex3f(x, y, z);
	}
	glEnd();
}


void sun()
{
    glColor3f(1.0, 1.0, 0.0);
    sunCircle(0.4, 1.5f, 1.5f);
}


void cloud_Move()  //cloud movement control
{
	if (counter < 19500)
	{
		glTranslatef(cloudTanslat, 0.0, 0.0);
		counter++;
	}
	else
	{
		glTranslatef(cloudTanslat, 0.0, 0.0);
		cloudTanslat = cloudTanslat-cloudMove;
	}
}


void bodyMovement()   //stick man 1 body movement control
{
	if (counter <= 17500)
	{
		glTranslatef(tx, 0.0, 0.0);
		tx = tx + forwardIncrmt;
		counter++;
	}

}


void bodyMovement_2() //stickman 2 body movement control
{

		if (counter < 19400)
	{
		glTranslatef(tx_2, 0.0, 0.0);
		counter++;
	}
	else
	{
		glTranslatef(tx_2, 0.0, 0.0);
		tx_2 = tx_2-backwardIncrmt;
	}

}


void leftHandMovement() //stick man 2 left hand movement
{
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



void angleTheta() //max movement angle
{
	if (forwardMov)
	{
		movTheta += incTheta;
		if (movTheta > maxTheta)
			forwardMov = false;
	}
	else if (!forwardMov)
	{
		movTheta -= incTheta;
		if (movTheta < -maxTheta)

			forwardMov = true;

	}
}


void drawStickman()
{

	//body
	glPushMatrix();
	bodyMovement();
	body();
	head();
	neck();
	glPopMatrix();
	//leftHand
	glPushMatrix();
	bodyMovement();
	leftHand();
	glPopMatrix();

	//leftArm
	glPushMatrix();
	bodyMovement();
	leftArm();
	glPopMatrix();


	//rightHand
	glPushMatrix();
	bodyMovement();
	rightHand();
	glPopMatrix();

	//rightarm
	glPushMatrix();
	bodyMovement();
	rightArm();
	glPopMatrix();

    //umbrellaStick
	glPushMatrix();
	bodyMovement();
	umbrellaStick();
	glPopMatrix();

	//halfCircle
	glPushMatrix();
	bodyMovement();
	umbrellaStick();
	umbrella();
	glPopMatrix();


    //raindrops
	glPushMatrix();
	if(counter>0 && counter<18000)
    rain();
	glPopMatrix();


	//leftLeg
	glPushMatrix();
	bodyMovement();
	leftLegMovement();
	leftLeg();
	leftShin();
	glPopMatrix();

	//rightLeg
	glPushMatrix();
	bodyMovement();
	rightLegMovement();
	rightLeg();
	rightShin();
	glPopMatrix();

	angleTheta();

}

void drawStickman_2()
{
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

void print(float x, float y, float z, char *string) {
	glRasterPos3f(x, y, z);
	int len = (int)strlen(string);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
//text
void text()
{
    glColor3f(1.0f, 1.0f, 1.0f);
	print(-0.2, 0.0, -5.0, "THE END");
               print(2.0, -1.0, -5.0, "Presented by,");
	print(2.0, -1.2, -5.0, "Divyashree Dutta");
	print(2.0, -1.4, -5.0, "Roll No.: 133005");
	print(2.0, -1.6, -5.0, "Section: A");
	print(2.0, -1.8, -5.0, "Session: 2013-14");
}


void blackBG()
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0f, -3.80f, -5.0f);
    glVertex3f(5.0f, -3.80f, -5.0f);
    glVertex3f(5.0f, 4.5f, -5.0f);
    glVertex3f(-5.0f, 4.5f,-5.0f);
    glEnd();
}



void display()
{

	glClear(GL_COLOR_BUFFER_BIT);


	//sky
    //glLoadIdentity();
	//glLoadIdentity();

	glPushMatrix();
	sky();
    glPopMatrix();



    //road
	glPushMatrix();
	glTranslatef(1.0, 0.25, 0.0);
	glScalef(5.5, 1.0, 1.0);
	road();
	glPopMatrix();



	//sun
	glPushMatrix();
	//glTranslatef(0.12f, 0.02f, 0.5f);
	sun();
	glPopMatrix();


	//cloud
	glPushMatrix();
	cloud_Move();
	cloud();
	glPopMatrix();



    //tree_1
	glPushMatrix();
	glTranslatef(-4.5f, -7.0f,0.0f);
	glScalef(3.0f, 3.0f, 3.0f);
	tree();
	glPopMatrix();


	//treebody_1
	glPushMatrix();
	treebody_1();
	glPopMatrix();

	//tree_2
	glPushMatrix();
	glTranslatef(5.0f, -7.0f,0.0f);
	glScalef(3.0f, 3.0f, 3.0f);
	tree();
	glPopMatrix();


    //treebody_2
	glPushMatrix();
	treebody_2();
	glPopMatrix();


	//tree_3
	glPushMatrix();
	glTranslatef(9.0f, -7.0f,0.0f);
	glScalef(3.0f, 3.0f, 3.0f);
	tree();
	glPopMatrix();


	//treebody_3
	glPushMatrix();
	treebody_3();
	glPopMatrix();

    //stickman_1
	glPushMatrix();
	glTranslatef(-6.8f, -1.77f, 0.0f);
	glScalef(0.7, 0.7, 1.0);
	drawStickman();
	glPopMatrix();


	//stickman_2
	glPushMatrix();
	glTranslatef(5.0f, -1.77f, 0.0f);
	glScalef(0.7, 0.7, 1.0);
	drawStickman_2();
	glPopMatrix();


	roadMark();

    //scene2
	if(counter>22000){
        blackBG();
        text();
	}

    counter++;


	glutSwapBuffers();


}


void Timer(int value)
{

	glutPostRedisplay();
	glutTimerFunc(timer, Timer, value);
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 1500);
	glutInitWindowPosition(0, 0);
	initRendering();
	glutCreateWindow("Rain");
	glutDisplayFunc(display);
	glutReshapeFunc(handleResize);
	glutTimerFunc(timer, Timer, 1);
	init();
	glutMainLoop();
	return 0;
}

