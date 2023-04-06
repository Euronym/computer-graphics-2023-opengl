#include<GL/freeglut.h>
#include<math.h>
#include<string>
#include<random>

#include "Character.cpp"

#ifndef PI
#define PI 3.14
#endif

class Scenario{
    private:
        float *xr;
        float *yr;
        bool *rot;
        float *rotateAngle;
        float *xBullet;
        bool *shoot;
        bool *reload;
        bool *down;
        bool *DiscountBullet;
        float *xCloud;
        Character c1;
        Character c2;
    public:
        Scenario(float*, float*, bool*, float*, float*, bool*, bool*, bool*, bool*, float*);
        void drawGround();
        void drawCharacters();
        void drawSun();
        void drawClouds();
        void drawCloud();
    protected:
        void drawCircleFilled(double, double, double, double);
};

Scenario::Scenario(float *xr, 
                   float *yr, 
                   bool *rot, 
                   float *rotateAngle, 
                   float *xBullet, 
                   bool *shoot, 
                   bool *reload, 
                   bool *down,
                   bool *discountBullet,
                   float *xCloud): c1("claudius", 0, 0), c2("Bruno", 0, 0) {
    this->xr = xr;
    this->yr = yr;
    this->rot = rot;
    this->rotateAngle = rotateAngle;
    this->xBullet = xBullet;
    this->shoot = shoot;
    this->reload = reload;
    this->down = down;
    this->DiscountBullet = discountBullet;
    this->xCloud = xCloud;
}

void Scenario::drawCircleFilled (double centerX, double centerY, double radiusX, double radiusY) {
    // Creditos:
    // https://community.khronos.org/t/i-have-this-code-that-draws-a-cloud-house-female-and-male/75173

    const float DEG2RAD = PI / 180;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2d (centerX, centerY);
        for (int i = -1; i < 360; i++) {
            float degInRad = i * DEG2RAD;
            glVertex2d (centerX + cos (degInRad) * radiusX, 
                            centerY + sin (degInRad) * radiusY);
            
        }
        
    glEnd();
}

void Scenario::drawClouds() {
    int firstY = 0;

    glPushMatrix();
    glTranslated(-*this->xCloud, firstY, 0);
    drawCloud();
    glPopMatrix();

    glPushMatrix();
    glTranslated(*this->xCloud - 200, firstY + 50, 0);
    drawCloud();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-*this->xCloud + 200, firstY + 300, 0);
    drawCloud();
    glPopMatrix();

    glPushMatrix();
    glTranslated(*this->xCloud + 400, firstY + 200, 0);
    drawCloud();
    glPopMatrix();

    glPushMatrix();
    glTranslated(*this->xCloud, firstY + 600, 0);
    drawCloud();
    glPopMatrix();

}

void Scenario::drawCloud() {
    // Creditos:
    // https://community.khronos.org/t/i-have-this-code-that-draws-a-cloud-house-female-and-male/75173

    int x = 0;
    int y = 0;

    glColor3f(255.0, 255.0, 255.0);
    drawCircleFilled(x, y, 80, 45);
    drawCircleFilled(x + 25, y + 15, 35, 35);
    drawCircleFilled(x + 25, y - 15, 35, 35);
    drawCircleFilled(x - 25, y - 15, 35, 35);
    drawCircleFilled(x - 25, y + 15, 35, 35);
}

void Scenario::drawCharacters() {
    glPushMatrix();
    glTranslated(20, -210, 0);
    this->c1.drawCharacter(*this->xr, *this->yr, *this->rot, *this->rotateAngle);
    if(*this->DiscountBullet){
        this->c1.discountBullet();
        *this->DiscountBullet = false;
    }
    // keeps drawing the bullet's trajectory. 
    if(*this->shoot) {
        this->c1.shoot(*this->rotateAngle, *this->xBullet);
    }

    if(*this->reload) {
        this->c1.reload();
        *this->reload = false;
    }

    if(*this->down) {
        this->c1.Down();
    }else{
        this->c1.Up();
    }

    glPopMatrix();

    // second player logic
    glPushMatrix();
    glTranslated(200, -210, 0);
    glScaled(-1, 1, 1);
    this->c2.drawCharacter(0, 0, 0, 0);
    glPopMatrix();

    glutPostRedisplay();
}

void Scenario::drawGround() {

    GLint x = -800;
    GLint y = -430;
    GLint height = 100;
    GLint width = 1800;

    glColor3f(0.1, 0, 0.0);
    glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x + width, y);
        glVertex2i(x + width, y + height);
        glVertex2i(x, y + height);
    glEnd();
}

void Scenario::drawSun(void) {
    glColor3f(1, 1, 0);
    glBegin(GL_POLYGON);                        
        double radius = 100;
        double ori_x = -600;                  
        double ori_y = 300;
        for (int i = 0; i <= 300; i++) {
            double angle = 2 * PI * i / 300;
            double x = cos(angle) * radius;
            double y = sin(angle) * radius;
            glVertex2d(ori_x + x, ori_y + y);
        }
    glEnd();
}