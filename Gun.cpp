#include<GL/freeglut.h>
#include <unistd.h>


class Gun{
    private:
        int nBullets = 0;
    public:
        Gun(int nBullets);
        void shoot(GLdouble, GLdouble, GLdouble);
        void drawGun(GLdouble, GLdouble, GLdouble, GLdouble);
        void drawBullet(GLdouble x, GLdouble y);
        void shootBullet(GLdouble x, GLdouble y);
        int getnBullets();
        void discountBullet();
};

void Gun::discountBullet() {
    if(this->nBullets > 0){
        this->nBullets -= 1;
    }
}

int Gun::getnBullets() {
    return this->nBullets;
}

Gun::Gun(int nBullets) {
    this->nBullets = nBullets;
}
void Gun::shoot(GLdouble xUpdate, GLdouble yUpdate, GLdouble xbullet) {
    int y = -280;
    int x = -680;
    if(nBullets != 0){
        drawBullet(x + xUpdate + xbullet, y + yUpdate);
        glutPostRedisplay();
        glutSwapBuffers();
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
void Gun::shootBullet(GLdouble x, GLdouble y) {

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
}