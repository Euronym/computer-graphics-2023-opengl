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

void handleKeyboard(GLubyte, GLint, GLint);
void handleMouse(GLint, GLint, GLint, GLint);

void handleKeyboard(GLubyte key, GLint x, GLint y) {

    GLint m = glutGetModifiers();

    // movimentation logic for the characters.
    if(key == 'w') {
        // if jump, applies a translation and modifies the state
    }
    else if(key == 'a') {
        // if move left, modifies the state, rotates and translates

    }
    else if(key == 's') {
        // TODO currently not implemented.

    }
    else if(key == 'd') {
        // if move right, modifies the states and translates

    }
}

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
    character.drawCharacter();
    glFlush();
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

    glutKeyboardFunc(handleKeyboard);
    //glutMouseFunc(handleMouse);
    glutDisplayFunc(drawScene);
    glutMainLoop();

    return 0;
}