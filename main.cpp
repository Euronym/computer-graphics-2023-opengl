/**
 * @file Scenario.cpp
 * @author Bruno Martins (bruno.martins@itec.ufpa.br)
 * @brief 
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include<GL/glut.h>
#include<X11/Xlib.h>
#include<iostream>

#include "Scenario.cpp"

#define SPACEBAR 32

float xr, yr = 0;
float xbullet = 0;
float xCloud = 0;
float rotate_angle = 0;
float cloudLimit = 500;

char button_stack = ' ';
bool shoot = false;
bool rot = false;
bool reload = false;
bool down = false;
bool jump = false;
bool discountBullet = false;

int timer = 100;
int shootTimer = 10;
int cloudTimer = 500; // move clouds every 0.5s

float *xrP = &xr;
float *yrP = &yr;
float *xCloudP = &xCloud;
bool *rotP = &rot; 
float *rotateAngleP = &rotate_angle;
float *xbulletP = &xbullet;
bool *shootP = &shoot;
bool *reloadP = &reload;
bool *downP = &down;
bool *discountBulletP = &discountBullet;

Scenario scenario(xrP, yrP, rotP, rotateAngleP, xbulletP, shootP, reloadP, downP, discountBulletP, xCloudP);

void handleMouse(GLint button, GLint action, GLint x, GLint y) {
    if(action == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
        xbullet = 10;
        shoot = true;
        discountBullet = true;
        glutPostRedisplay();
    }
}

void initScenario(void) {
    glClearColor(0, 0, 1, 1.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-780, 780, -420, 420);

}

void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    scenario.drawScenario();
    glFlush();
}

void handleKeyboard(unsigned char key, int x, int y) {
    switch(key) {
        case SPACEBAR:
        if(yr == 0){
            yr = 40;
            jump = true;
        }
        glutPostRedisplay();
        break;

        case 'w':
        down = false;
        glutPostRedisplay();
        break;

        case 's':
        down = true;
        glutPostRedisplay();
        break;

        case 'a':
            if(!down) {
                if (button_stack == 'd') {
                    rotate_angle = 180;
                    xr -= 10;
                } else if (button_stack == ' ' || button_stack == 'a') {
                    xr -= 10;
                }
                button_stack = 'a';            
                glutPostRedisplay();
            }
            break;

        case 'd':
            if(!down) {
                if (button_stack == 'a') {
                    rotate_angle = 180;
                    xr += 10;
                } else if (button_stack == ' ' || button_stack == 'd') {
                    xr += 10;
                    rotate_angle = 0;
                }
                button_stack = 'd';
                glutPostRedisplay();
            }
            break;
        
        case 'r':
            reload = true;
            glutPostRedisplay();
            break;
    }

}

void shootTimerFunc(int value){
    if(shoot){
        if(xbullet != 0 && xbullet < 1000){
            xbullet += 10;
        }else{
            shoot = false;
        }        
    }
	glutPostRedisplay();
	glutTimerFunc(shootTimer, shootTimerFunc, value);
}


void Timer(int value) {
    if(jump){
        if(yr != 0){
            yr -= 5;
        }else{
            jump = false;
        }
    }

	glutPostRedisplay();
	glutTimerFunc(timer, Timer, value);
}

void cloudsTimer(int value) {
    if(xCloud < cloudLimit){
        xCloud += 30;
    }else{
        xCloud -= 30;
    }

    glutPostRedisplay();
	glutTimerFunc(cloudTimer, cloudsTimer, value);
}

int main(int argc, char **argv) {

    int width = 700;
    int height = 400;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("Jogo");
    initScenario();
    scenario.loadTextures();
    glutDisplayFunc(drawScene);

    glutKeyboardFunc(handleKeyboard);
    glutMouseFunc(handleMouse);
    glutTimerFunc(timer, Timer, 1);
    glutTimerFunc(shootTimer, shootTimerFunc, 1);
    glutTimerFunc(cloudTimer, cloudsTimer, 1);
    glutMainLoop();

    return 0;
}