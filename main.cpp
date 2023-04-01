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

#include "Scenario.cpp"
#include "Character.cpp"

int xr, yr = 0;


void handleMouse(GLint button, GLint action, GLint x, GLint y) {

}

void initScenario(void) {
    glClearColor(0, 0, 1, 1.0);

    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-780, 780, -420, 420);
    //gluOrtho2D(0, 0, 0, 0);

}

void drawScene(void) {
    std::string characterName = "cladius";
    Character character(characterName);

    Scenario scenario(1);

    glClear(GL_COLOR_BUFFER_BIT);
    scenario.drawSun();
    scenario.drawPlataforms();
    character.drawCharacter(xr, yr);
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
        xr -= 10;
        glutPostRedisplay();
        break;

        case 'd':
        xr += 10;
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

    glutKeyboardFunc(handleKeyboard);
    //glutMouseFunc(handleMouse);
    glutDisplayFunc(drawScene);
    glutMainLoop();

    return 0;
}