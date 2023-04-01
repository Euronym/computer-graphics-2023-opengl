#include<GL/freeglut.h>

class Gun{
    private:
        int nBullets = 0;
    public:
        Gun(int nBullets);
        void shoot();
        void drawGun();
        void drawBullet();
        void shootBullet(GLdouble x, GLdouble y);
};

Gun::Gun(int nBullets) {
    this->nBullets = nBullets;
}
void Gun::shoot() {
    /*
    int x = 40;
    if(nBullets != 0){
        for(int y = 40; y < 1000; y = y + 10){
            shootBullet(x, y);
        }
    }
    */
    this->nBullets -= 1;
    drawBullet();
}
void Gun::drawGun() {
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
        glVertex2d(0, 0);
        glVertex2d(10, 0);
        glVertex2d(10, 20);
        glVertex2d(0, 20);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2d(0, 20);
        glVertex2d(10, 20);
        glVertex2d(10, 30);
        glVertex2d(0, 30);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2d(10, 20);
        glVertex2d(30, 20);
        glVertex2d(30, 30);
        glVertex2d(10, 30);
    glEnd();
}
void Gun::shootBullet(GLdouble x, GLdouble y) {
    glPushMatrix();
    glTranslated(x, y, 0);
    drawBullet();
    glPopMatrix();
}
void Gun::drawBullet() {
    int f1 = 40;
    int f2 = 20;
    glColor3f(1, 0.5, 0);
    glBegin(GL_TRIANGLES);
        glVertex2d(0 + f1, 0 + f2);
        glVertex2d(0 + f1, 10 + f2);
        glVertex2d(20 + f1, 5 + f2);
    glEnd();
}