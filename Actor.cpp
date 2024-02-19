#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream>
#include <string>
class Pea;
using namespace std;

Actor::Actor(StudentWorld* world, int ID, int startX, int startY, int startD, int startHealth): GraphObject(ID, startX, startY, startD) {
    isAlive = true;
    isAttacked = false;
    health = startHealth;
    direction = startD;
    identification = ID;
}
void Actor::setDead() {
    isAlive = false;
}
void Actor::setHealth(int amount) {
    health = amount;
}
void Actor::setAttacked() {
    isAttacked = true;
}
void Actor::setAlive() {
    isAlive = true;
}
void Actor::setDirection(int dir) {
    direction = dir;
}
void Actor::handleDamage(int damage) {
    health -= damage;
}
int Actor::getHealth() const {
    return health;
}
int Actor:: getIdentification() const {
    return identification;
}
int Actor::getDirection() const {
    return direction;
}
bool Actor::isLiving() const {
    return isAlive;
}
StudentWorld* Actor:: getWorld() const {
    return world;
}
void Actor::moveIfPossible(int x, int y) {
    if (!getWorld()->isObstacleAt(x, y))
        moveTo(x, y);
}

class Avatar: public Actor {
    public:
        Avatar(StudentWorld* world, int startX, int startY): Actor(world, IID_PLAYER, startX, startY, right, 20), numPeas(20) {}
        virtual ~Avatar() {}
        int getPeas() const {
            return numPeas;
        }
        void firePea() {
            int peaX = getX();
            int peaY = getY();
            numPeas -= 1;
            switch (getDirection()) {
                case up:
                    peaY++;
                    break;
                case down:
                    peaY--;
                    break;
                case left:
                    peaX--;
                    break;
                default:
                    peaX++;
                    break;
            }
            if (!getWorld()->isObstacleAt(peaX, peaY)) {
                cout << "Work on adding pea here";
                //Pea* newPea = new Pea(getWorld(), peaX, peaY, getDirection());
                //getWorld()->addObject(newPea);
                //would I add peas by creating a pointer to a new pea inside Avatar and then sending that to a function in StudentWorld  that appends objects to the end of the list of obejcts? same for robot factoryy dispensing robots?
            }
            getWorld()->playSound(SOUND_PLAYER_FIRE);
        }
        virtual void doSomething() {
            int key;
            if (!isLiving())
                return;
            if (getWorld()->getKey(key)) {
                switch (key) {
                    case KEY_PRESS_ESCAPE:
                        setDead();
                        break;
                    case KEY_PRESS_SPACE:
                        if (numPeas > 0)
                            firePea();
                        break;
                    case KEY_PRESS_LEFT:
                        setDirection(left);
                        moveIfPossible(getX()-1, getY());
                        break;
                    case KEY_PRESS_RIGHT:
                        setDirection(right);
                        moveIfPossible(getX()+1, getY());
                        break;
                    case KEY_PRESS_UP:
                        setDirection(up);
                        moveIfPossible(getX(), getY()+1);
                        break;
                    case KEY_PRESS_DOWN:
                        setDirection(down);
                        moveIfPossible(getX(), getY()-1);
                        break;
                    /*
                     Then, the
                     Avatar will try to move to the adjacent square in the direction it is facing
                     if that square does not contain an obstruction: a marble that cannot be
                     pushed, a wall, a pit, a robot, or a robot factory. If the player can move, it
                     must update its location with the GraphObject class’s moveTo() method.
                     */
                    default: //Presses tab or enter
                        break;
                }
            }
        }
    virtual void handleAttack() {
        handleDamage(2);
        if (getHealth() > 0)
            getWorld()->playSound(SOUND_PLAYER_IMPACT);
        else {
            setDead();
            getWorld()->playSound(SOUND_PLAYER_DIE);
        }
    }
    private:
        int numPeas;
};

class Wall: public Actor {
    public:
        Wall(StudentWorld* world, int startX, int startY): Actor(world, IID_WALL, startX, startY, none, 0) {}
        virtual ~Wall() {} //Do I need anything in destructor
};

class Pea: public Actor {
    public:
        Pea(StudentWorld* world, int startX, int startY, int direction): Actor(world, IID_PEA, startX, startY, direction, 1) {}
    virtual ~Pea() {}
};

//exit: setVisible(false)
//if I check that a robot can attack a player, how do I set player's isAttacked to true? Dont know how to access player from robot
//actors have multiple actions like moving and shooting so whould I just create separate if statements into each doSomething()
//for interactions like player pushing marble into a pit should I create a function in player, marble, or pit
//do you know how to get around calling the same level everytime
//like if I have     string curLevel = "level01.txt"; its just going to load the first level every time
//I have a virtual handelAttack function in Avatar but where would I call this function?
//error with adding peas
//Why is spec telling to do setVisible(true) even when graph object's constructor has setVisible
