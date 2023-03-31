#include<GL/freeglut.h>
#include<string>
#include<vector>
#include<math.h>

#ifndef PI
#define PI 3.14
#endif

struct Point{
    GLdouble x,y;
};

class Character{
    private:
        std::string name;
        std::vector<Point> characterCoordinates;
    public:
        Character(std::string name);
        void addCoordinates();
        void walkFront();
        void walkBack();
        void drawCharacter();
};