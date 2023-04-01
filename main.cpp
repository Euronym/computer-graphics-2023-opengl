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
#include "Gun.cpp"

void handleKeyboard(GLubyte, GLint, GLint);
void handleMouse(GLint, GLint, GLint, GLint);

GLfloat xr, xl = 0;

bool shoot = False;

void handleKeyboard(GLubyte key, GLint x, GLint y) {

    GLint m = glutGetModifiers();

    // movimentation logic for the characters.
    switch(key) {
        case 'w':
        // if jump, applies a translation and modifies the state
        break;

        case 'a':
        // if move left, modifies the state, rotates and translates
        break;

        case 's':
        // TODO currently not implemented.
        break;

        case 'd':
        // if move right, modifies the states and translates

        break;

    }
}

void handleMouse(GLint button, GLint action, GLint x, GLint y) {
    if(button == GLUT_LEFT_BUTTON){
        std::cout << "button pressed";
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

    //Character characterOne(characterName, -700, -210);

    Gun gun(10);

    //Scenario scenario(1);

    glClear(GL_COLOR_BUFFER_BIT);
    //scenario.drawSun();
    //scenario.drawPlataforms();
    //characterOne.drawCharacter();

    //lastCoord = scenario.getLastCoord();

    //Character characterTwo(characterName, lastCoord[0], lastCoord[1]);

    //characterTwo.drawCharacter();
    gun.drawGun();
    if(shoot) {
        gun.shoot();
        shoot = False;
    }
    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}

int main(int argc, char **argv) {

    int width = 700;
    int height = 400;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("Jogo");
    initScenario();
    glutDisplayFunc(drawScene);

    glutKeyboardFunc(handleKeyboard);
    glutMouseFunc(handleMouse);
    glutMainLoop();

    return 0;
}