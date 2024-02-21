#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath): GameWorld(assetPath), player(nullptr), levelBonus(0) {}

StudentWorld::~StudentWorld() {
    cleanUp();
}

int StudentWorld::init() {
    levelBonus = 1000;
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
int StudentWorld::getBonus() const {
    return levelBonus;
}
void StudentWorld::decreaseBonus() {
    levelBonus--;
}

string StudentWorld::formatScore(int score, int level, int lives, int health, int ammo, int bonus) const {
    ostringstream ss;
    ss << "Score: " << setw(7) << setfill('0') << score << "  ";
    ss << "Level: " << setw(2) << setfill('0') << level << "  ";
    ss << "Lives: " << setw(2) << setfill(' ') << lives << "  ";
    ss << "Health: " << setw(3) << setfill(' ') << health << "%  ";
    ss << "Ammo: " << setw(3) << setfill(' ') << ammo << "  ";
    ss << "Bonus: " << setw(4) << setfill(' ') << bonus;
    return ss.str();
}

void StudentWorld::setDisplayText() {
    int score = getScore();
    int level = getLevel();
    int bonus = getBonus();
    int lives = getLives();
    int health = player->getHealth()/20 * 100;
    int ammo = player->getPeas();
    string s = formatScore(score, level, lives, health, ammo, bonus);
    setGameStatText(s);
    
}
int StudentWorld::move() {
    setDisplayText();
    for (Actor* obj: actors) {
        if (obj->isLiving()) {
            obj->doSomething();
            if (!player->isLiving())
                return GWSTATUS_PLAYER_DIED;
            //Check if player completes level
        }
    }
    if (player->isLiving())
        player->doSomething();
    //Remove dead actors - traverse through list and check if health = 0
    if (getBonus() > 0)
        decreaseBonus();
    //Check if player collects all crystals and then expose exit
    if (!player->isLiving())
        return GWSTATUS_PLAYER_DIED;
    //Check if player completes level
        //if (crystalpickedup = max, exit coordinate matches player coordiante)
        //increaseScore(getBonus());
    return GWSTATUS_CONTINUE_GAME;
}
void StudentWorld::cleanUp() {
    list<Actor*>::iterator itr = actors.begin();
    delete player;
    player = nullptr;
    while (itr != actors.end()) {
        delete *itr;
        itr = actors.erase(itr);
    }
}
//Needs to deal with marble that can be pushed
bool StudentWorld::isObstacleAt(int x, int y) const {
    for (Actor* object: actors) {
        if (object->getX() == x && object->getY() == y && object->isObstacle())
            return true;
    }
    return false;
}

Actor* StudentWorld::isCollidableWith(int x, int y) const {
    for (Actor* object: actors) {
        if (object->getX() == x && object->getY() == y && object->canbeAttacked())
            return object;
    }
    return nullptr;
}

void StudentWorld::addObject(Actor* object) {
    actors.push_back(object);
}
