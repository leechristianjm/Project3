#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath): GameWorld(assetPath), player(nullptr) {}

StudentWorld::~StudentWorld() {
    cleanUp();
}

int StudentWorld::init() {
    string curLevel = "level0" + to_string(getLevel()) + ".txt";
    Level lev(assetPath());
    Level::LoadResult result = lev.loadLevel(curLevel);
    if (result == Level::load_fail_file_not_found || getLevel() == 100)
        return GWSTATUS_PLAYER_WON;
    else if (result == Level:: load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR;
    else if (result == Level::load_success) {
        for (int x = 0; x < VIEW_WIDTH; x++) {
            for (int y = 0; y < VIEW_HEIGHT; y++) {
                Level::MazeEntry me = lev.getContentsOf(x, y);
                switch (me) {
                    case Level::player:
                        player = new Avatar(this, x, y);
                        break;
                    case Level:: empty:
                        break;
                    case Level:: exit:
                        break;
                    case Level:: horiz_ragebot:
                        break;
                    case Level:: vert_ragebot:
                        break;
                    case Level:: thiefbot_factory:
                        break;
                    case Level:: mean_thiefbot_factory:
                        break;
                    case Level:: wall:
                        addObject(new Wall(this, x, y));
                        break;
                    case Level:: marble:
                        break;
                    case Level:: pit:
                        break;
                    case Level:: crystal:
                        break;
                    case Level:: restore_health:
                        break;
                    case Level:: extra_life:
                        break;
                    case Level:: ammo:
                        break;
                }
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() {
    setGameStatText("Score: ");
    //"Score: " + getScore() + " Level: " + getLevel() + " Lives: " + getLives() + " Health: " + get
    //for health, ammo, bonus, would i use Avatar pointer to access them 
    if (player->isLiving())
        player->doSomething();
    for (Actor* obj: actors) {
        if (obj->isLiving()) {
            obj->doSomething();
            if (!player->isLiving())
                return GWSTATUS_PLAYER_DIED;
            //How to check if player completes a level
            //how to know when to restart a level 
        }
    }
    //Remove dead actors
    //Reduce current bonus
    //Check if player collects all crystals
    if (!player->isLiving())
        return GWSTATUS_PLAYER_DIED;
    //Check if player completes level
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp() {
    delete player;
    player = nullptr;
    for (Actor* obj: actors)
        delete obj;
}

//Needs to deal with marble that can be pushed
bool StudentWorld::isObstacleAt(int x, int y) {
    for (Actor* object: actors) {
        if (object->getX() == x && object->getY() == y && object->returnIfObstacle())
            return true;
    }
    return false;
}
void StudentWorld::addObject(Actor* object) {
    actors.push_back(object);
}
