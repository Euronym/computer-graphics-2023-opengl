#include<GL/freeglut.h>
#include<math.h>
#include<vector>
#include<string>
#include<random>

#include "Point.h"

#define PI 3.14
#define COLLISION_THRESHOLD 0.1

struct PlataformPoints{
    std::vector<Point> points;
};

class Scenario{
    private:
        int n;
        std::vector<GLdouble> LastPlatformCoord;
        std::vector<GLdouble> firstPlatformCoord;
        std::vector<PlataformPoints> plataforms;
    public:
        Scenario(int n){
            this->n = n;
        }
        std::vector<GLdouble> getLastCoord();
        std::vector<GLdouble> getFirstCoord();
        void loadBackground();
        void drawPlataform(GLdouble, GLdouble, GLdouble, GLdouble);
        void drawPlataforms();
        void drawSun();
        void drawLava(); 
        void detectCollision(); // detect player/scenario collisions
};

std::vector<GLdouble> Scenario::getLastCoord() {
    return this->LastPlatformCoord;
}
std::vector<GLdouble> Scenario::getFirstCoord() {
    return this->firstPlatformCoord;
}

void Scenario::drawPlataform(GLdouble x, GLdouble y, GLdouble width, GLdouble height) {

    Point p1 = {x, y};
    Point p2 = {x + width, y};
    Point p3 = {x + width, y + height};
    Point p4 = {x, y + height};

    glColor3f(0.1, 0, 0.0);
    glBegin(GL_QUADS);
        glVertex2i(p1.x, p1.y);
        glVertex2i(p2.x, p2.y);
        glVertex2i(p3.x, p3.y);
        glVertex2i(p4.x, p4.y);
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
            Point p = {ori_x + y, ori_y + y};
            glVertex2d(p.x, p.y);
        }
    glEnd();
}
void Scenario::drawPlataforms(void) {

    int characterHeight = 200;
    int characterWidth = 0;
    float screenWidth = glutGet(GLUT_WINDOW_WIDTH);
    float screenHeight = glutGet(GLUT_WINDOW_HEIGHT);

    float sizeGap = 50; // gap between plataforms
    float plataformWidth = 80; // platform width
    float nPlatforms = 10; // total number of plataforms

    int index;

    int i,j;

    // TODO we should separate the logic of creating
    // points from the actual rendering

    this->firstPlatformCoord.push_back(-800);
    this->firstPlatformCoord.push_back(-400);
    // draw rows
    for(i = -screenWidth / 2;i < screenWidth / 2; i = sizeGap + plataformWidth) {
        if(i > screenWidth) {
            break;
        }
        for(j = this->firstPlatformCoord[1]; j <= 0; j = j + characterHeight) {
            if(j > screenHeight) {
                break;
            }

            drawPlataform(i, j, plataformWidth, 50);
        }
    }
    this->LastPlatformCoord.push_back(710);
    this->LastPlatformCoord.push_back(190);
}