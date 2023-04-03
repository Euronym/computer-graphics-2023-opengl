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
#include "Character.cpp"

#define SPACEBAR 32

int xr, yr = 0;
int xbullet = 0;

bool shoot = false;
bool rot = false;
bool jump = false;

int timer = 100;
int shootTimer = 10;

Character character("claudius", -700, -210);

Scenario scenario(1);

void handleMouse(GLint button, GLint action, GLint x, GLint y) {
    if(action == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
        xbullet = 10;
        character.discountBullet();
        shoot = true;
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
    scenario.drawSun();
    scenario.drawPlataforms();
    character.drawCharacter(xr, yr, rot);
    if(shoot) {
        character.shoot(xbullet);
    }
    glFlush();
}

void handleKeyboard(unsigned char key, int x, int y) {
    switch(key) {
        case SPACEBAR:
        yr += 40;
        jump = true;
        glutPostRedisplay();
        break;

        case 'w':
        character.Up();
        glutPostRedisplay();
        break;

        case 's':
        character.Down();
        glutPostRedisplay();
        break;

        case 'a':
        xr -= 10;
        glutPostRedisplay();
        break;

        case 'd':
        xr += 10;
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

int main(int argc, char **argv) {

    int width = 700;
    int height = 400;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("Jogo");
    glutDisplayFunc(drawScene);

    glutKeyboardFunc(handleKeyboard);
    glutMouseFunc(handleMouse);
    glutTimerFunc(timer, Timer, 1);
    glutTimerFunc(shootTimer, shootTimerFunc, 1);
    initScenario();
    glutMainLoop();

    return 0;
}