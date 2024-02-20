#ifndef ACTOR_H_
#define ACTOR_H_
#include "GraphObject.h"
class StudentWorld;

class Actor: public GraphObject {
    public:
        Actor(StudentWorld* world, int ID, int startX, int startY, int startD, int startHealth);
        virtual ~Actor();
        virtual void doSomething();
        void setDead();
        void setHealth(int amount);
        void setAttacked();
        void setAlive();
        void setWorld(StudentWorld* world);
        void setDirection(int dir);
        void setAsObstacle();
        void decreaseHealth(int damage);
        bool returnIfObstacle() const;
        int getHealth() const;
        int getDirection() const;
        int getIdentification() const;
        bool isLiving() const;
        void moveIfPossible(int x, int y);
        virtual void handleAttack();
        StudentWorld* getWorld() const;
    private:
        StudentWorld* world;
        bool isAlive;
        bool isObstacle;
        bool isAttacked;
        //bool canMove; put in thiefbot and ragebot base class
        //bool playSound; //put in goodie base class
        int health;
        int direction;
};

#endif // ACTOR_H_
