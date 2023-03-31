#include<GL/freeglut.h>
#include<math.h>
#include<vector>
#include<string>

#define PI 3.14

class Scenario{
    private:
        int n;
    public:
        Scenario(int n){
            this->n = n;
        }
        void loadBackground();
        void drawPlataform(int x, int y);
        void drawPlataforms();
        void drawSun();
};

void Scenario::loadBackground() {

}
void Scenario::drawPlataform(int x, int y) {
    glColor3f(1, 1, 0);
    glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x + 500, y + 0);
        glVertex2i(x + 500, y + 50);
        glVertex2i(x + 0, y + 50);
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
void Scenario::drawPlataforms(void) {
    //for(int i = 50;i < 1000; i = i + 50) {
    //    drawPlataform(i, i);
    //}
    drawPlataform(-750, -400);
}