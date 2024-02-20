#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <list>
#include "Level.h"
class Wall;
class Avatar;
#include "Actor.h"
using namespace std;

class StudentWorld : public GameWorld {
    public:
        StudentWorld(std::string assetPath);
        virtual ~StudentWorld();
        virtual int init();
        virtual int move();
        virtual void cleanUp();
        void getWallX() const;
        void getWallY() const;
        bool isObstacleAt(int x, int y);
        void addObject(Actor* object);
    private:
        std::list<Actor*> actors;
        Actor* player;
};

#endif // STUDENTWORLD_H_
