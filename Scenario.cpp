#include<GL/freeglut.h>
#include<math.h>
#include<string>
#include<random>

#include "Character.cpp"
#include "stb_image.cpp"

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
        GLuint groundTexture;
        GLuint sunTexture;
        GLuint skyTexture;

        Character c1;
        Character c2;
    public:
        Scenario(float*, float*, bool*, float*, float*, bool*, bool*, bool*, bool*, float*);
        void drawScenario();
        void loadTextures();
    protected:
        void drawCircleFilled(double, double, double, double);
        void drawSun();
        void drawClouds();
        void drawCloud();
        void drawCharacters();
        void drawGround();
        void drawBackground();
        void loadTexture(const char*, GLuint);
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

void Scenario::drawScenario() {
    drawBackground();
    drawSun();
    drawClouds();
    drawGround();
    drawCharacters();
}

void Scenario::drawBackground() {

    int widthScreen = glutGet(GLUT_SCREEN_WIDTH);
    int heightScreen = glutGet(GLUT_SCREEN_HEIGHT);

    glPushMatrix();
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->skyTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(1, 1); glVertex2d(widthScreen, heightScreen);
        glTexCoord2f(0, 1); glVertex2d(-widthScreen, heightScreen);
        glTexCoord2f(0, 0); glVertex2d(-widthScreen, -heightScreen);
        glTexCoord2f(1, 0); glVertex2d(widthScreen, -heightScreen);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Scenario::loadTextures() {
    GLuint groundTexture = 1;
    GLuint sunTexture = 2;
    GLuint skyTexture = 3;

    this->groundTexture = groundTexture;
    this->sunTexture = sunTexture;
    this->skyTexture = skyTexture;

    // ground texture
    loadTexture("Assets/Texture/groundTexture.jpeg", groundTexture);
    // sun texture
    loadTexture("Assets/Texture/sunTexture.jpeg", sunTexture);
    // sky texture
    loadTexture("Assets/Texture/skyTextureNew.jpg", skyTexture);
}


void Scenario::loadTexture(const char *imgPath, GLuint textureId) {

    int height, width, nChannels;

    stbi_set_flip_vertically_on_load(true);  
    unsigned char *dataGroundTexture = stbi_load(imgPath, &width, &height, &nChannels, 0);

    GLuint texture;

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataGroundTexture);

    stbi_image_free(dataGroundTexture);

    //glBindTexture(GL_TEXTURE_2D, 0);
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

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->groundTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 10); glVertex2i(x, y);

        glTexCoord2f(0, 0); glVertex2i(x + width, y);

        glTexCoord2f(10, 0); glVertex2i(x + width, y + height);

        glTexCoord2f(10, 10); glVertex2i(x, y + height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Scenario::drawSun(void) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->sunTexture);
    glBegin(GL_POLYGON);                        
        double radius = 100;
        double ori_x = -600;                  
        double ori_y = 300;
        double xcos, ysin;
        double tx, ty;
        for (int i = 0; i <= 300; i++) {
            double angle = 2 * PI * i / 300;
            xcos = cos(angle);
            ysin = sin(angle);
            double x = xcos * radius;
            double y = ysin * radius;

            tx = xcos * 0.5 + 0.5;
            ty = ysin * 0.5 + 0.5;

            glTexCoord2f(tx, ty); glVertex2d(ori_x + x, ori_y + y);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
