#include<GL/freeglut.h>
#include<math.h>
#include<vector>
#include<string>
#include<random>

#define PI 3.14
#define COLLISION_THRESHOLD 0.1

struct Point{
    GLdouble x,y;
};

struct PlataformPoints{
    std::vector<Point> points;
};

class Scenario{
    private:
        int n;
        std::vector<GLdouble> LastPlatformCoord;
        std::vector<GLdouble> firstPlatformCoord;
        std::vector<PlataformPoints> plataformPoints;
    public:
        Scenario(int n){
            this->n = n;
        }
        std::vector<GLdouble> getLastCoord();
        std::vector<GLdouble> getFirstCoord();
        void loadBackground();
        void drawPlataform(int x, int y, int width, int height);
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

void Scenario::loadBackground() {

}
void Scenario::drawPlataform(int x, int y, int width, int height) {

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
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    int blockWidths[] = {80, 120};
    int blockWidth;
    int index;

    int i,j;

    this->firstPlatformCoord.push_back(-800);
    this->firstPlatformCoord.push_back(-400);
    // draw rows
    for(i = this->firstPlatformCoord[0];i < 1000; i = i + 150) {
        // draw columns
        if(i > screenWidth) {
            break;
        }
        for(j = this->firstPlatformCoord[1]; j <= 0; j = j + characterHeight) {
            if(j > screenHeight) {
                break;
            }
            blockWidth = blockWidths[0];
            // draws an individual block
            drawPlataform(i, j, blockWidth, 50);
        }
    }
    this->LastPlatformCoord.push_back(710);
    this->LastPlatformCoord.push_back(190);
}