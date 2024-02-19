#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you type q

    setGameStatText("Game will end when you type q");
    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
}

//Needs to deal with marble that can be pushed
bool StudentWorld::isObstacleAt(int x, int y) {
    for (Actor* object: actors) {
        if (object->getX() == x && object->getY() == y) {
            int ID = object->getIdentification();
            if (ID == IID_WALL || ID == IID_PIT || ID == IID_ROBOT_FACTORY || ID == IID_RAGEBOT || ID == IID_THIEFBOT || ID == IID_MEAN_THIEFBOT)
                return true;
        }
    }
    return false;
}
void StudentWorld::addObject(Actor* object) {
    actors.push_back(object);
}

//can we import whatever we need 
