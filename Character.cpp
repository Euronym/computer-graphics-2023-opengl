#include<GL/freeglut.h>
#include<string>
#include<vector>
#include<stdio.h>
#include<math.h>

#ifndef PI
#define PI 3.14
#endif

#include "Gun.cpp"

struct Point{
    GLdouble x,y;
};

class Character{
    private:
        int isUp = 1;
        float xr, yr = 0;
        bool move = true;
		bool forwardMov = false;
        float incTheta = 1.5f;
        float fowardIncrmt = 0.0015f;
    	float movTheta = 0.0f;
        float tx_2 = 0.0f;
        float maxTheta = 35.0f;
        int offset = 0;
        int hp = 5; // character's total life.
        std::string name;
        std::vector<Point> characterCoordinates;
        Gun characterGun;
    public:
        Character(std::string name, GLdouble xStart, GLdouble yStart);
        void addCoordinates(GLdouble xStart, GLdouble yStart);
        void walkFront();
        void walkBack();
        void drawCharacter(float , float, bool);
        void head(float , float);
        void body(float , float);
        void leftArm(float , float);
        void rightArm(float , float);
        void leftLeg(float , float);
        void rightLeg(float , float);
        void Down();
        void Up();
        void shoot(GLdouble);
        void jump();
        void drawHpBar(GLdouble, GLdouble, GLdouble, GLdouble);
        void reload();
        void discountBullet();
};

int Character::hp = 5;
int Character::currentHp = hp;

void Character::discountBullet() {
    this->characterGun.discountBullet();
}

Character::Character(std::string name, GLdouble xStart, GLdouble yStart): characterGun(10) {
    this->name = name;
    addCoordinates(xStart, yStart);
}

void Character::shoot(GLdouble xbullet) {
    this->characterGun.shoot(this->xr, this->yr, xbullet);
}

void Character::drawHpBar(GLdouble x, GLdouble y, GLdouble xUpdate, GLdouble yUpdate) {
    // frame for hp bar
    /*
    glBegin(GL_QUADS);
        glVertex2d();
        glVertex2d();
        glVertex2d();
        glVertex2d();
    glEnd();
    // hpbar itself.
    glBegin();

    glEnd();
    */
}

void Character::Down() {
    this->isUp = 0;
    this->move = false;
}

void Character::Up() {
    this->isUp = 1;
    this->move = true;
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

    // coordinates for dynamic iteraction

    // #FIXME honestly, there might be better ways 
    // to do this, i'm just too lazy to think about it.
    Point p7 = {origin.x + 30, origin.y - 100};
    Point p8 = {origin.x - 30, origin.y - 100};
    Point p9 = {origin.x + 30, origin.y - 130};
    Point p10 = {origin.x - 30, origin.y - 130};

    characterCoordinates.push_back(origin);
    characterCoordinates.push_back(p1);
    characterCoordinates.push_back(p2);
    characterCoordinates.push_back(p3);
    characterCoordinates.push_back(p4);
    characterCoordinates.push_back(p5);
    characterCoordinates.push_back(p6);
    characterCoordinates.push_back(p7);
    characterCoordinates.push_back(p8);
    characterCoordinates.push_back(p9);
    characterCoordinates.push_back(p10);
}

void Character::walkFront() {
    glTranslated(1000, 0, 1);
    offset += 10100;
}

void Character::jump() {

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
    if(this->isUp) {
        glBegin(GL_LINES);
            glVertex2d(xr + this->characterCoordinates[1].x, yr + this->characterCoordinates[1].y);
            glVertex2d(xr + this->characterCoordinates[2].x, yr + this->characterCoordinates[2].y);
        glEnd();

    }else{
        glBegin(GL_LINE_STRIP);
            glVertex2d(xr + this->characterCoordinates[1].x, yr + this->characterCoordinates[1].y);
            glVertex2d(xr + this->characterCoordinates[10].x, yr + this->characterCoordinates[10].y);
            glVertex2d(xr + this->characterCoordinates[8].x, yr + this->characterCoordinates[8].y);
        glEnd();
    }
}

void Character::rightLeg(float xr, float yr) {
    if(this->isUp) {
        glBegin(GL_LINES);
            glVertex2d(xr + this->characterCoordinates[1].x, yr + this->characterCoordinates[1].y);
            glVertex2d(xr + this->characterCoordinates[3].x, yr + this->characterCoordinates[3].y);
        glEnd();

    }else{
        glBegin(GL_LINE_STRIP);
            glVertex2d(xr + this->characterCoordinates[1].x, yr + this->characterCoordinates[1].y);
            glVertex2d(xr + this->characterCoordinates[7].x, yr + this->characterCoordinates[7].y);
            glVertex2d(xr + this->characterCoordinates[9].x, yr + this->characterCoordinates[9].y);
        glEnd();
    }
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

void Character::drawCharacter(float xr, float yr, bool rot) {
    // if can move, then update the coordinates.
    if(this->move){
        this->xr = xr;
        this->yr = yr;
    }

    float currentX = this->xr;
    float currentY = this->yr;

    // draw gun
    glPushMatrix();
    //glScaled(0.5, 0.5, 0);
    this->characterGun.drawGun(-650, -280, currentX, currentY);
    //draw head
    head(currentX, currentY);
    //draw body
    body(currentX, currentY);
    //draw leg
    rightLeg(currentX, currentY);
    //draw other leg
    leftLeg(currentX, currentY);
    //draw arm
    rightArm(currentX, currentY);
    //draw other arm
    leftArm(currentX, currentY);
    glPopMatrix();

    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}