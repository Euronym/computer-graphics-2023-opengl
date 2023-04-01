#include<GL/freeglut.h>
#include<string>
#include<vector>
#include<math.h>

#ifndef PI
#define PI 3.14
#endif


struct Point{
    GLdouble x,y;
};

class Character{
    private:
        std::string name;
        std::vector<Point> characterCoordinates;
    public:
        Character(std::string name, GLdouble xStart, GLdouble yStart);
        void addCoordinates(GLdouble xStart, GLdouble yStart);
        void walkFront();
        void walkBack();
        void drawCharacter();
};

Character::Character(std::string name, GLdouble xStart, GLdouble yStart) {
    this->name = name;
    addCoordinates(xStart, yStart);
}
void Character::addCoordinates(GLdouble xStart, GLdouble yStart) {
    /*
        Fills the coordinate vector that represents the object. 
    */

    Point origin = {xStart, yStart};
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
    glMatrixMode(GL_MODELVIEW);
    glTranslated(10, 0, 0);
}

void Character::walkBack() {
    glMatrixMode(GL_MODELVIEW);
    glTranslated(0, 0, 0);
    glRotated(180, 0, 0, 1);
    glTranslated(-10, 0, 0);
}

void Character::drawCharacter() {
    double radius = 10;

    glColor3f(1, 1, 0);

    glBegin(GL_POLYGON);
        for (int i = 0; i <= 300; i++) {
            GLdouble angle = 2 * PI * i / 300;
            GLdouble x = cos(angle) * radius;
            GLdouble y = sin(angle) * radius;
            glVertex2d(this->characterCoordinates[0].x + x, this->characterCoordinates[0].y + y);
        }
    glEnd();
    // body
    glColor3f(1, 1, 0);
    glBegin(GL_LINES);
        glVertex2d(this->characterCoordinates[0].x, this->characterCoordinates[0].y);
        glVertex2d(this->characterCoordinates[1].x, this->characterCoordinates[1].y);
    glEnd();
    // leg
    glBegin(GL_LINES);
        glVertex2d(this->characterCoordinates[1].x, this->characterCoordinates[1].y);
        glVertex2d(this->characterCoordinates[2].x, this->characterCoordinates[2].y);
    glEnd();
    // other leg
    glBegin(GL_LINES);
        glVertex2d(this->characterCoordinates[1].x, this->characterCoordinates[1].y);
        glVertex2d(this->characterCoordinates[3].x, this->characterCoordinates[3].y);
    glEnd();
    // arm
    glBegin(GL_LINES);
        glVertex2d(this->characterCoordinates[4].x, this->characterCoordinates[4].y);
        glVertex2d(this->characterCoordinates[5].x, this->characterCoordinates[5].y);

    glEnd();
    // other arm
    glBegin(GL_LINES);
        glVertex2d(this->characterCoordinates[4].x, this->characterCoordinates[4].y);
        glVertex2d(this->characterCoordinates[6].x, this->characterCoordinates[6].y);
    glEnd();
}