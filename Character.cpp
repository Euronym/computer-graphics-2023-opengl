#include<GL/freeglut.h>
#include<string>
#include<vector>
#include<stdio.h>
#include<math.h>

#ifndef PI
#define PI 3.14
#endif

struct Point{
    GLdouble x,y;
};

class Character{
    private:
		bool forwardMov = false;
        float incTheta = 1.5f;
        float fowardIncrmt = 0.0015f;
    	float movTheta = 0.0f;
        float tx_2 = 0.0f;
        float maxTheta = 35.0f;
        int offset = 0;
        std::string name;
        std::vector<Point> characterCoordinates;
    public:
        Character(std::string name);
        void addCoordinates();
        void walkFront();
        void walkBack();
        void drawCharacter(float , float);
        void head(float , float);
        void body(float , float);
        void leftArm(float , float);
        void rightArm(float , float);
        void leftLeg(float , float);
        void rightLeg(float , float);
};

Character::Character(std::string name) {
    addCoordinates();
    this->name = name;
}
void Character::addCoordinates() {
    /*
        Fills the coordinate vector that represents the object. 
    */

    Point origin = {-700, -210};
    Point p1 = {origin.x, origin.y - 100};
    Point p2 = {origin.x + 30, origin.y - 140};
    Point p3 = {origin.x - 30, origin.y - 140};
    Point p4 = {origin.x, origin.y - 50};
    Point p5 = {origin.x - 50, origin.y - 60};
    Point p6 = {origin.x + 50, origin.y - 60};

    characterCoordinates.push_back(origin);
    characterCoordinates.push_back(p1);
    characterCoordinates.push_back(p2);
    characterCoordinates.push_back(p3);
    characterCoordinates.push_back(p4);
    characterCoordinates.push_back(p5);
    characterCoordinates.push_back(p6);
}

void Character::walkFront() {
    glTranslated(1000, 0, 1);
    offset += 10100;
}

void Character::walkBack() {
    glTranslated(0, 0, 0);
    glRotated(180, 0, 0, 1);
    glTranslated(-10, 0, 0);
}   

void Character::head(float xr, float yr) {
    double radius = 10;

    glColor3f(1, 1, 0);

    glBegin(GL_POLYGON);
        for (int i = 0; i <= 300; i++) {
            GLdouble angle = 2 * PI * i / 300;
            GLdouble x = cos(angle) * radius;
            GLdouble y = sin(angle) * radius;
            glVertex2d(xr + this->characterCoordinates[0].x + x, yr + this->characterCoordinates[0].y + y);
        }
    glEnd();
}

void Character::body(float xr, float yr) {
    glColor3f(1, 1, 0);
    glBegin(GL_LINES);
        glVertex2d(xr + this->characterCoordinates[0].x, yr + this->characterCoordinates[0].y);
        glVertex2d(xr + this->characterCoordinates[1].x, yr + this->characterCoordinates[1].y);
    glEnd();
}

void Character::leftLeg(float xr, float yr) {
    glBegin(GL_LINES);
        glVertex2d(xr + this->characterCoordinates[1].x, yr + this->characterCoordinates[1].y);
        glVertex2d(xr + this->characterCoordinates[2].x, yr + this->characterCoordinates[2].y);
    glEnd();
}

void Character::rightLeg(float xr, float yr) {
    glBegin(GL_LINES);
        glVertex2d(xr + this->characterCoordinates[1].x, yr + this->characterCoordinates[1].y);
        glVertex2d(xr + this->characterCoordinates[3].x, yr + this->characterCoordinates[3].y);
    glEnd();
}

void Character::leftArm(float xr, float yr) {
    glBegin(GL_LINES);
            glVertex2d(xr + this->characterCoordinates[4].x, yr + this->characterCoordinates[4].y);
            glVertex2d(xr + this->characterCoordinates[5].x, yr + this->characterCoordinates[5].y);
    glEnd();

}

void Character::rightArm(float xr, float yr) {
    glBegin(GL_LINES);
        glVertex2d(xr + this->characterCoordinates[4].x, yr + this->characterCoordinates[4].y);
        glVertex2d(xr + this->characterCoordinates[6].x, yr + this->characterCoordinates[6].y);
    glEnd();
}

void Character::drawCharacter(float xr, float yr) {
    //draw head
    head(xr, yr);
    //draw body
    body(xr, yr);
    //draw leg
    rightLeg(xr, yr);
    //draw other leg
    leftLeg(xr, yr);
    //draw arm
    rightArm(xr, yr);
    //draw other arm
    leftArm(xr, yr);
    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}