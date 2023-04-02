#include<GL/freeglut.h>
#include<math.h>
#include<vector>
#include<string>
#include<random>

#define PI 3.14

#include "stb_image.cpp"

struct TextureContent{
    unsigned char* dataPointer;
    int widthImg;
    int heightImg;
    int nrChannels;    
};

class Scenario{
    private:
        int n;
        TextureContent blockTexture;
        std::vector<GLdouble> LastPlatformCoord;
        std::vector<GLdouble> firstPlatformCoord;
    public:
        Scenario();
        ~Scenario();
        std::vector<GLdouble> getLastCoord();
        std::vector<GLdouble> getFirstCoord();
        void drawPlataform(int x, int y, int width, int height);
        void drawPlataforms();
        void drawSun();
        void loadBackground();
};

Scenario::Scenario() {
}

Scenario::~Scenario() {
}

void Scenario::loadBackground() {
    unsigned int texture;

    int widthImg, heightImg, nrChannels;

    unsigned char* data = stbi_load("skyTexture.jpeg", &widthImg, &heightImg, &nrChannels, 0);

    glGenTextures(1, &texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
       glTexCoord2f(0, 0); glVertex2f(0, 0); 
       glTexCoord2f(0, 1); glVertex2f(0, 100);
       glTexCoord2f(1, 1); glVertex2f(100, 100);
       glTexCoord2f(1, 0); glVertex2f(100, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    stbi_image_free(data);

}

std::vector<GLdouble> Scenario::getLastCoord() {
    return this->LastPlatformCoord;
}
std::vector<GLdouble> Scenario::getFirstCoord() {
    return this->firstPlatformCoord;
}

void Scenario::drawPlataform(int x, int y, int width, int height) {

    glBegin(GL_QUADS);
        //glTexCoord2f(0, 0);
        glVertex2i(x, y);

        //glTexCoord2f(1, 0);
        glVertex2i(x + width, y);

        //glTexCoord2f(1, 1);
        glVertex2i(x + width, y + height);

        //glTexCoord2f(0, 1);
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