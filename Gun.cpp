#include<GL/freeglut.h>
#include <unistd.h>

class Gun{
    private:
        int nBullets;
        int capacity = 10;
        int bulletPosition[2];
    public:
        Gun(int nBullets);
        void shoot(GLdouble, GLdouble, int, GLdouble);
        void drawGun(GLdouble, GLdouble, GLdouble, GLdouble);
        void drawBullet(GLdouble x, GLdouble y);
        void reloadGun();
        int getnCapacity();
        int getnBullets();
        void discountBullet();
        int *getBulletPosition();
};

void Gun::discountBullet() {
    if(this->nBullets > 0){
        this->nBullets -= 1;
    }
}

int Gun::getnBullets() {
    return this->nBullets;
}

int Gun::getnCapacity() {
    return this->capacity;
}

void Gun::reloadGun() {
    this->nBullets = 10;
}

Gun::Gun(int nBullets) {
    this->nBullets = nBullets;
}
void Gun::shoot(GLdouble xUpdate, GLdouble yUpdate, int rotate_angle, GLdouble xbullet) {
    int y = -65;
    int x = 40;

    if(nBullets != 0){
        if(rotate_angle > 0){
            glPushMatrix();
                glTranslatef(x + xUpdate, y + yUpdate, 0);
                glRotatef(rotate_angle, 0, 1, 0);
                glTranslatef(-(x + xUpdate), -(y + yUpdate), 0);
                drawBullet(x + xUpdate + xbullet, y + yUpdate);
            glPopMatrix();
        }else{
            glPushMatrix();
                drawBullet(x + xUpdate + xbullet, y + yUpdate);
            glPopMatrix();
        }
        glutPostRedisplay();
    }
}
void Gun::drawGun(GLdouble x, GLdouble y, GLdouble xUpdate, GLdouble yUpdate) {
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
        glVertex2d(x + xUpdate, y + yUpdate);
        glVertex2d(x + 10 + xUpdate, y + 0 + yUpdate);
        glVertex2d(x + 10 + xUpdate, y + 20 + yUpdate);
        glVertex2d(x + 0 + xUpdate, y + 20 + yUpdate);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2d(x + 0 + xUpdate, y + 20 + yUpdate);
        glVertex2d(x + 10 + xUpdate, y + 20 + yUpdate);
        glVertex2d(x + 10 + xUpdate, y + 30 + yUpdate);
        glVertex2d(x + 0 + xUpdate, y + 30 + yUpdate);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2d(x + 10 + xUpdate, y + 20 + yUpdate);
        glVertex2d(x + 30 + xUpdate, y + 20 + yUpdate);
        glVertex2d(x + 30 + xUpdate, y + 30 + yUpdate);
        glVertex2d(x + 10 + xUpdate, y + 30 + yUpdate);
    glEnd();
}
void Gun::drawBullet(GLdouble x, GLdouble y) {
    int f1 = 40;
    int f2 = 20;
    glColor3f(1, 0.5, 0);
    glBegin(GL_TRIANGLES);
        glVertex2d(0 + f1 + x, 0 + f2 + y);
        glVertex2d(0 + f1 + x, 10 + f2 + y);
        glVertex2d(20 + f1 + x, 5 + f2 + y);
    glEnd();
    this->bulletPosition[0] = 20 + f1 + x;
    this->bulletPosition[1] = 5 + f2 + y;
}

int *Gun::getBulletPosition() {
    return this->bulletPosition;
}