#include<GL/glut.h>
#include<math.h>

#ifdef _WIN32
#include<X11/xlib.h>
Display* disp = XOpenDisplay(NULL);
Screen*  scrn = DefaultScreenOfDisplay(disp);
int height = scrn->height;
int width  = scrn->width;
#endif

#ifdef linux

#endif

#define PI 3.14

void draw_plataform(int, int);
void draw_plataforms();
void draw_sun(void);

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
    draw_plataforms();
    glFlush();
}

void draw_plataforms(void) {
    for(int i = 50;i < 1000; i = i + 50) {
        draw_plataform(i, i);
    }
}

void draw_plataform(int x, int y) {
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + 500, y + 0);
    glVertex2i(x + 500, y + 100);
    glVertex2i(x + 0, y + 100);
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