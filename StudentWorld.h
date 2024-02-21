#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
#include "GameWorld.h"
#include <string>
#include <list>
#include "Level.h"
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
        void setDisplayText();
        string formatScore(int score, int level, int lives, int health, int ammo, int bonus) const;
        void getWallY() const;
        bool isObstacleAt(int x, int y) const;
        void addObject(Actor* object);
        int getBonus() const;
        void decreaseBonus();
    void removeObject(Actor* target);
    Actor* isCollidableWith(int x, int y) const;
    private:
        int levelBonus;
        std::list<Actor*> actors;
        Avatar* player;
};

#endif // STUDENTWORLD_H_
