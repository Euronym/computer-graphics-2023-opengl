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

int xr, yr = 0;

bool shoot = False;
bool rot = False;
char button_stack = ' ';
int rotate_angle = 0;


void handleMouse(GLint button, GLint action, GLint x, GLint y) {
    if(button == GLUT_LEFT_BUTTON){
        shoot = True;
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
    std::string characterName = "cladius";

    std::vector<GLdouble> lastCoord;

    Character character(characterName, -700, -210);

    Scenario scenario(1);

    glClear(GL_COLOR_BUFFER_BIT);
    scenario.drawSun();
    scenario.drawPlataforms();
    character.drawCharacter(xr, yr, rot, rotate_angle);
    if(shoot){
        character.shoot(xr, yr, rotate_angle);
        shoot = False;
    }
    glFlush();
}

void handleKeyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'w':
            yr += 10;
            glutPostRedisplay();
            break;

        case 's':
            yr -= 10;
            glutPostRedisplay();
            break;

        case 'a':
            if (button_stack == 'd') {
                rotate_angle = 180;
                xr -= 10;
            } else if (button_stack == ' ' || button_stack == 'a') {
                xr -= 10;
            }
            button_stack = 'a';            
            glutPostRedisplay();
            break;

        case 'd':
            if (button_stack == 'a') {
                rotate_angle = 180;
                xr += 10;
            } else if (button_stack == ' ' || button_stack == 'd') {
                xr += 10;
                rotate_angle = 0;
            }
            button_stack = 'd';
            glutPostRedisplay();
            break;
    }

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
    glutDisplayFunc(drawScene);

    glutKeyboardFunc(handleKeyboard);
/*
    if (rotate) {
        rotate_angle = 180;
    } {
        rotate_angle = 0;
    }
*/
    glutMouseFunc(handleMouse);
    glutMainLoop();

    return 0;
}