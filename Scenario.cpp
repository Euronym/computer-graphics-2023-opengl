#include<GL/glut.h>
#include<math.h>

#define PI 3.14

void draw_plataform(void);
void draw_sun(void);

class Scenario{
    private:
        int n_characters = 0;
    public:
        Scenario(int n_characters) {
            this->n_characters = n_characters;
        }
};

void initScenario(void) {
    GLshort redScenario = (GLclampf) 037 / 255;
    GLshort greenScenario = (GLclampf) 197 / 255;
    GLshort blueScenario = (GLclampf) 223 / 255;

    //glClearColor(redScenario, greenScenario, blueScenario, 1);
    glClearColor(0.0f, 0.0f, 1.0f, 1);

    //glColor3f(1, 0, 0);

    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-780, 780, -420, 420);
}

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_sun();
    draw_plataform();
    glFlush();
}

void draw_plataform(void) {
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(500, 0);
    glVertex2i(500, 100);
    glVertex2i(0, 100);
    glColor3f(1, 1, 0);
    glEnd();
}

void draw_sun(void) {
    glBegin(GL_POLYGON);                        // Middle circle
    double radius = 100;
    double ori_x = -600;                         // the origin or center of circle
    double ori_y = 300;
    for (int i = 0; i <= 300; i++) {
        double angle = 2 * PI * i / 300;
        double x = cos(angle) * radius;
        double y = sin(angle) * radius;
        glVertex2d(ori_x + x, ori_y + y);
    }
    glEnd();
}

void draw_lava(void) {
    
}


int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1440, 900);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("Jogo");
    initScenario();

    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}