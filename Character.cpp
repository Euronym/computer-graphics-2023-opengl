#include <GL/freeglut.h>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include<irrKlang.h>

#include "point.h"
#ifndef PI
#define PI 3.14
#endif

#include "Gun.cpp"

class Character
{
private:
    int isUp = 1;
    float xr, yr = 0;
    bool move = true;
    int hp = 5;         // character's total life.
    int currentHp = hp; // current life
    std::string name;
    std::vector<Point> characterCoordinates;
	irrklang::ISoundEngine* audioEngine = irrklang::createIrrKlangDevice();
    Gun characterGun;
    Point characterLocation;

public:
    Character(std::string name, GLdouble xStart, GLdouble yStart);
    void addCoordinates(GLdouble xStart, GLdouble yStart);
    void drawCharacter(float, float, bool, int);
    void head(float, float);
    void body(float, float);
    void leftArm(float, float);
    void rightArm(float, float);
    void leftLeg(float, float);
    void rightLeg(float, float);
    void nameBar(GLdouble, GLdouble, GLdouble, GLdouble);
    void Down();
    void Up();
    void shoot(int, GLdouble);
    void drawAmmo(GLdouble, GLdouble, GLdouble, GLdouble);
    void drawHpBar(GLdouble, GLdouble, GLdouble, GLdouble);
    void reload();
    void discountBullet();
    void discountHp();
    void setCharacterLocation(Point);
    bool checkBulletCollision(Point);
    Point getBulletPosition();
    int getCharacterHp();
};

void Character::discountBullet()
{
    this->audioEngine->play2D("Assets/Audio/4magnusn.wav", false);
    this->characterGun.discountBullet();
}

void Character::setCharacterLocation(Point characterLocation)
{
    this->characterLocation = characterLocation;
}

int Character::getCharacterHp() 
{
    return this->currentHp;
}

void Character::nameBar(GLdouble x, GLdouble y, GLdouble xUpdate, GLdouble yUpdate) 
{
    glColor3f(0, 0, 0);
    glRasterPos2i(x + xUpdate, y + yUpdate);
    const unsigned char *name = reinterpret_cast<const unsigned char *>(this->name.c_str());
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, name);
}

void Character::discountHp()
{
    if(this->currentHp > 0)
    {
        this->currentHp -= 1;
    }
}

Point Character::getBulletPosition()
{
    return this->characterGun.getBulletPosition();
}

bool Character::checkBulletCollision(Point bulletPosition)
{

    double distX = pow((this->characterLocation.x - bulletPosition.x), 2);
    double distY = pow((this->characterLocation.y - bulletPosition.y), 2);

    if (sqrt(distX + distY) <= 300)
    {
        return true;
    }

    return false;
}

Character::Character(std::string name, GLdouble xStart, GLdouble yStart) : characterGun(10)
{
    this->name = name;
    addCoordinates(xStart, yStart);
}

void Character::shoot(int rotate_angle, GLdouble xbullet)
{
    glPushMatrix();
    if (!this->isUp)
    {
        glTranslated(0, -20, 0);
    }
    this->characterGun.shoot(this->xr, this->yr, rotate_angle, xbullet);

    glPopMatrix();
}

void Character::reload()
{
    this->audioEngine->play2D("Assets/Audio/reload_for_gun.wav", false);
    this->characterGun.reloadGun();
}

void Character::drawAmmo(GLdouble x, GLdouble y, GLdouble xUpdate, GLdouble yUpdate)
{
    glRasterPos2i(x + xUpdate, y + yUpdate);
    glColor3f(0, 0, 0);
    std::string currentBullets = std::to_string(this->characterGun.getnBullets());
    std::string capacity = std::to_string(this->characterGun.getnCapacity());
    std::string str = currentBullets + "/" + capacity;
    const unsigned char *ammo = reinterpret_cast<const unsigned char *>(str.c_str());

    glutBitmapString(GLUT_BITMAP_HELVETICA_18, ammo);
}

void Character::drawHpBar(GLdouble x, GLdouble y, GLdouble xUpdate, GLdouble yUpdate)
{

    GLdouble boxWidth = 100;
    GLdouble boxHeight = 50;

    GLdouble barStartxp1 = x + xUpdate;
    GLdouble barStartyp1 = y + yUpdate;
    GLdouble barStartxp2 = x + xUpdate;
    GLdouble barStartyp2 = y + yUpdate + boxHeight;

    GLdouble barEndxp1 = x + xUpdate + 20;
    GLdouble barEndyp1 = y + yUpdate;
    GLdouble barEndxp2 = x + xUpdate + 20;
    GLdouble barEndyp2 = y + yUpdate + boxHeight;

    int factor = 1;

    // frame for hp bar
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex2d(x + xUpdate, y + yUpdate);
    glVertex2d(x + xUpdate + boxWidth, y + yUpdate);
    glVertex2d(x + xUpdate + boxWidth, y + yUpdate + boxHeight);
    glVertex2d(x + xUpdate, y + yUpdate + boxHeight);
    glEnd();
    // hpbar itself.
    glColor3f(0, 1, 0);
    // generate multiple health bars
    for (int i = 0; i < this->hp; i++)
    {
        // if current hp is lower than total
        // does not show bars as green.
        if (i > this->currentHp - 1)
        {
            factor = 0;
        }
        glBegin(GL_QUADS);
        // hpbar itself.
        glVertex2d(factor * barStartxp1, factor * barStartyp1);
        glVertex2d(factor * barEndxp1, factor * barEndyp1);
        glVertex2d(factor * barEndxp2, factor * barEndyp2);
        glVertex2d(factor * barStartxp2, factor * barStartyp2);
        glEnd();

        barStartxp1 = barEndxp1;
        barStartxp2 = barEndxp2;

        barEndxp1 += 20;
        barEndxp2 += 20;
    }
}

void Character::Down()
{
    this->isUp = 0;
    this->move = false;
}

void Character::Up()
{
    this->isUp = 1;
    this->move = true;
}

void Character::addCoordinates(GLdouble xStart, GLdouble yStart)
{
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

void Character::head(float xr, float yr)
{
    double radius = 10;

    glColor3f(1, 1, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 300; i++)
    {
        GLdouble angle = 2 * PI * i / 300;
        GLdouble x = cos(angle) * radius;
        GLdouble y = sin(angle) * radius;
        glVertex2d(xr + this->characterCoordinates[0].x + x, yr + this->characterCoordinates[0].y + y);
    }
    glEnd();
}

void Character::body(float xr, float yr)
{
    glColor3f(1, 1, 0);
    glBegin(GL_LINES);
    glVertex2d(xr + this->characterCoordinates[0].x, yr + this->characterCoordinates[0].y);
    glVertex2d(xr + this->characterCoordinates[1].x, yr + this->characterCoordinates[1].y);
    glEnd();
}

void Character::leftLeg(float xr, float yr)
{
    if (this->isUp)
    {
        glBegin(GL_LINES);
        glVertex2d(xr + this->characterCoordinates[1].x, yr + this->characterCoordinates[1].y);
        glVertex2d(xr + this->characterCoordinates[2].x, yr + this->characterCoordinates[2].y);
        glEnd();
    }
    else
    {
        glBegin(GL_LINE_STRIP);
        glVertex2d(xr + this->characterCoordinates[1].x, yr + this->characterCoordinates[1].y);
        glVertex2d(xr + this->characterCoordinates[10].x, yr + this->characterCoordinates[10].y);
        glVertex2d(xr + this->characterCoordinates[8].x, yr + this->characterCoordinates[8].y);
        glEnd();
    }
}

void Character::rightLeg(float xr, float yr)
{
    if (this->isUp)
    {
        glBegin(GL_LINES);
        glVertex2d(xr + this->characterCoordinates[1].x, yr + this->characterCoordinates[1].y);
        glVertex2d(xr + this->characterCoordinates[3].x, yr + this->characterCoordinates[3].y);
        glEnd();
    }
    else
    {
        glBegin(GL_LINE_STRIP);
        glVertex2d(xr + this->characterCoordinates[1].x, yr + this->characterCoordinates[1].y);
        glVertex2d(xr + this->characterCoordinates[7].x, yr + this->characterCoordinates[7].y);
        glVertex2d(xr + this->characterCoordinates[9].x, yr + this->characterCoordinates[9].y);
        glEnd();
    }
}

void Character::leftArm(float xr, float yr)
{
    glBegin(GL_LINES);
    glVertex2d(xr + this->characterCoordinates[4].x, yr + this->characterCoordinates[4].y);
    glVertex2d(xr + this->characterCoordinates[5].x, yr + this->characterCoordinates[5].y);
    glEnd();
}

void Character::rightArm(float xr, float yr)
{
    glBegin(GL_LINES);
    glVertex2d(xr + this->characterCoordinates[4].x, yr + this->characterCoordinates[4].y);
    glVertex2d(xr + this->characterCoordinates[6].x, yr + this->characterCoordinates[6].y);
    glEnd();
}

void Character::drawCharacter(float xr, float yr, bool rot, int rotateAngle)
{
    if (this->currentHp > 0)
    {
        // draw gun
        glPushMatrix();

        if (rotateAngle > 0)
        {
            glTranslatef((xr + characterCoordinates[0].x), (yr + characterCoordinates[0].y), 0);
            glRotatef(rotateAngle, 0, 1, 0);
            glTranslatef(-(xr + characterCoordinates[0].x), -(yr + characterCoordinates[0].y), 0);
        }

        // if can move, then update the coordinates.
        if (this->move)
        {
            this->xr = xr;
            this->yr = yr;
        }

        float currentX = this->xr;
        float currentY = this->yr;

        // check if character is up
        if (!this->isUp)
        {
            glTranslated(0, -10, 0);
        }

        // draw gun
        this->characterGun.drawGun(40, -65, currentX, currentY);
        // draw hp bar
        drawHpBar(-120, -20, currentX, currentY);
        // draw ammo info
        drawAmmo(-140, -85, currentX, currentY);
        // draw head
        head(currentX, currentY);
        // draw body
        body(currentX, currentY);
        // draw leg
        rightLeg(currentX, currentY);
        // draw other leg
        leftLeg(currentX, currentY);
        // draw arm
        rightArm(currentX, currentY);
        // draw other arm
        leftArm(currentX, currentY);
        glPopMatrix();
        // draw name bar
        nameBar(-60, 30, currentX, currentY);
    }
}