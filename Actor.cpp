#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream>
#include <string>
using namespace std;

Actor::Actor(StudentWorld* world, int ID, int startX, int startY, int startD, int startHealth): GraphObject(ID, startX, startY, startD) {
    isAlive = true;
    isAttacked = false;
    health = startHealth;
    direction = startD;
    isObstacle = false;
    setWorld(world);
}
Actor::~Actor() {}
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
void Actor::setAsObstacle() {
    isObstacle = true;
}
bool Actor::returnIfObstacle() const {
    return isObstacle;
}
void Actor::decreaseHealth(int damage) {
    health -= damage;
}
int Actor::getHealth() const {
    return health;
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
void Actor::setWorld(StudentWorld* world) {
    this->world = world;
}
void Actor::moveIfPossible(int x, int y) {
    if (!getWorld()->isObstacleAt(x, y))
        moveTo(x, y);
}
void Actor::doSomething() {}

void Actor:: handleAttack() {}

Avatar::Avatar(StudentWorld* world, int startX, int startY): Actor(world, IID_PLAYER, startX, startY, right, 20), numPeas(20) {}

Avatar::~Avatar() {}

int Avatar::getPeas() const {
    return numPeas;
}

void Avatar:: doSomething() {
    int key;
    if (!isLiving())
        return;
    if (getWorld()->getKey(key)) {
        switch (key) {
            case KEY_PRESS_ESCAPE:
                setDead();
                //how do we indicate to game to restart the level with all the objects in the original position. Would I need to keep track of the original x,y of each object in StudentWorld.cpp?
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

void Avatar::handleAttack() { //avatar collides with smth
    decreaseHealth(2);
    if (getHealth() > 0)
        getWorld()->playSound(SOUND_PLAYER_IMPACT);
    else {
        setDead();
        getWorld()->playSound(SOUND_PLAYER_DIE);
    }
}

Wall::Wall(StudentWorld* world, int startX, int startY): Actor(world, IID_WALL, startX, startY, none, 0) {
    setAsObstacle();
}

Wall::~Wall() {}

class Pea: public Actor {
    public:
        Pea(StudentWorld* world, int startX, int startY, int direction): Actor(world, IID_PEA, startX, startY, direction, 1) {}
        virtual ~Pea() {}
};

void Avatar::firePea() {
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
        Pea* newPea = new Pea(getWorld(), peaX, peaY, getDirection());
        getWorld()->addObject(newPea);
    }
    getWorld()->playSound(SOUND_PLAYER_FIRE);
}
//is it colliding - look at #7
//collision method inside pea
//studentworld - if colliding / pass peas current position and traverse current array - return ptr to other obj not pea
//inside actor.cpp collide method -> decrease health

//pea hits object - custom things / in actor have method in actor and inherited class overrides method 




//setasobstacle for pit, robot factory and robot base class
//exit: setVisible(false)
//if I check that a robot can attack a player, how do I set player's isAttacked to true? Dont know how to access player from robot
//actors have multiple actions like moving and shooting so whould I just create separate if statements into each doSomething()
//for interactions like player pushing marble into a pit should I create a function in player, marble, or pit
//do you know how to get around calling the same level everytime
//like if I have     string curLevel = "level01.txt"; its just going to load the first level every time

//I have a virtual handelAttack function in Avatar but where would I call this function?
//error with adding peas
//Never make any class’s data members public or protected. You may make class constants public, protected or private. ??
//If only some objects have hit points like Avatar and robots, should I put health points in the base Actor class or repeat having health points in both avatar and robot classe s

