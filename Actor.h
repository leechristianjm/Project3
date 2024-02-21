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
        virtual bool isObstacle() const;
        virtual bool canbeAttacked() const;
        void decreaseHealth(int damage);
        int getHealth() const;
        int getIdentification() const;
        bool isLiving() const;
        void moveIfPossible(int x, int y);
        virtual void handleAttack();
        StudentWorld* getWorld() const;
    private:
        StudentWorld* world;
        bool isAlive;
        bool isAttacked;
        //bool canMove; put in thiefbot and ragebot base class
        //bool playSound; //put in goodie base class
        int health;
        int direction;
};
class Wall: public Actor {
    public:
        Wall(StudentWorld* world, int startX, int startY);
        virtual bool isObstacle() const;
        virtual ~Wall();
};
class Avatar: public Actor {
    public:
        Avatar(StudentWorld* world, int startX, int startY);
        virtual ~Avatar();
        virtual bool canbeAttacked() const;
        int getPeas();
        void firePea();
        virtual void doSomething();
        virtual void handleAttack();
    private:
        int numPeas;
};
//have robot have virtual bool canbeAttacked();
class Marble: public Actor {
    public:
        Marble(StudentWorld* world, int startX, int startY);
        virtual ~Marble();
        virtual bool canbeAttacked() const;
        virtual void doSomething();
    private:
        int numPeas;
};
class Pea: public Actor {
    public:
        Pea(StudentWorld* world, int startX, int startY, int direction);
        virtual ~Pea();
        virtual void doSomething();
};
#endif // ACTOR_H_

