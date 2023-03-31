#include "Character.h"

class Scenario{
    private:
        Character character;
        int n;
    public:
        Scenario(int n);
        void addCharacter(Character character);
        void loadBackground();
        void drawPlataform(int x, int y);
        void drawPlataforms();
        void drawSun();
};