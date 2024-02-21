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
bool Actor::isObstacle() const {
    return false;
}
bool Actor::canbeAttacked() const {
    return false;
}
void Actor::decreaseHealth(int damage) {
    health -= damage;
}
int Actor::getHealth() const {
    return health;
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

bool Avatar::canbeAttacked() const {
    return true;
}

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
}

Wall::~Wall() {}

bool Wall::isObstacle() const {
    cout << "BRO" << endl;
    return true;
}

Pea::Pea(StudentWorld* world, int startX, int startY, int direction): Actor(world, IID_PEA, startX, startY, direction, 1) {}

Pea::~Pea() {}

void Pea::doSomething() {
    if (!isLiving())
        return;
    Actor* target = getWorld()->isCollidableWith(getX(), getY());
    if (target != nullptr) {
        target->handleAttack(); //marble, robot, player
        setDead();
        return;
        //Right now I have a canBeAttacked function that I override only for marble robot player and I have a StudentWorld function that returns if an object thats on the same square as Pea is marble robot or player but then I would have to create separate variables for wall and robot factory / is it good code implementation or would i need to create another class that wall and robot factory can derive from 
    }
}

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
        Pea* newPea = new Pea(getWorld(), peaX, peaY, getDirection());
        getWorld()->addObject(newPea);
    }
    getWorld()->playSound(SOUND_PLAYER_FIRE);
}

bool Marble::canbeAttacked() const {
    return true;
}

//figure out how to run demo
//is it colliding - look at #7
//collision method inside pea
//studentworld - if colliding / pass peas current position and traverse current array - return ptr to other obj not pea
//inside actor.cpp collide method -> decrease health

//pea hits object - custom things / in actor have method in actor and inherited class overrides method 
//add isPushable in Actor
//collision detection
//overlap - goodies with players or
//class that means collidable -
//Actor -> Collidable actors -> Actor(Player, goodies, marbles, pits, certain robots)


//setasobstacle for pit, robot factory and robot base class
//exit: setVisible(false)
//exit: define canoverlap with #3
//if u can overlap, then use handle overlap
//see whats in common/have parent class for common stuff
//player will interact with smth then make interactable lcass with shareing like overlapped actions
//class hierarchy 

//if I check that a robot can attack a player, how do I set player's isAttacked to true? Dont know how to access player from robot
//actors have multiple actions like moving and shooting so whould I just create separate if statements into each doSomething()
//for interactions like player pushing marble into a pit should I create a function in player, marble, or pit


//If only some objects have hit points like Avatar and robots, should I put health points in the base Actor class or repeat having health points in both avatar and robot classe s

