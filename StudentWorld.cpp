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
//Does level just completed is 99 mean getLevel() == 99
//Is hardcoding like this okay?
//Why error
int StudentWorld::init() {
    string curLevel = "level" + to_string(getLevel()) + ".txt";
    Level lev(assetPath());
    Level::LoadResult result = lev.loadLevel(curLevel);
    if (result == Level::load_fail_file_not_found || getLevel() == 99)
        return GWSTATUS_PLAYER_WON;
    else if (result == Level:: load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR;
    else if (result == Level::load_success) {
        for (int x = 0; x < VIEW_WIDTH; x++) {
            for (int y = 0; y < VIEW_HEIGHT; y++) {
                Level::MazeEntry x = lev.getContentsOf(x, y);
                switch (x) {
                    case Level::player:
                        player = new Avatar(x, y, this);
                        break;
                    case Level::empty:
                        break;
                    case Level::exit:
                        break;
                    case Level::horiz_ragebot:
                        break;
                    case Level::vert_ragebot:
                        break;
                    case Level::thiefbot_factory:
                        break;
                    case Level:: mean_thiefbot_factory:
                        break;
                    case Level:: wall:
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

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you type q

    setGameStatText("Game will end when you type q");
    
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
