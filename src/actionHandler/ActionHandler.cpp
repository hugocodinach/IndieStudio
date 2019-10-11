/*
** EPITECH PROJECT, 2018
** ActionHandler.cpp
** File description:
** src/actionHandler/ActionHandler.cpp
*/

#include "ActionHandler.hpp"
#include "IActor.hpp"
#include "MapHandler.hpp"
#include "Bomb.hpp"

ActionHandler::ActionHandler(std::vector<IActor *> &actors, MapHandler &mapHandler,
std::vector<Bomb *> &vectB, irr::scene::ISceneManager *&smgr,
std::vector<irr::scene::IAnimatedMesh *> &vect_mesh, MusicPlayer &music) :
_actors(actors), _mapHandler(mapHandler), _bombVect(vectB), _smgr(smgr),
_vect_mesh(vect_mesh), _music(music)
{
}

ActionHandler::~ActionHandler()
{
}

void ActionHandler::handleAction()
{

    for (size_t i = 0; i < _actors.size(); i += 1) {
        if (_actors[i] != nullptr && _actors[i]->getActionsToDo().size() != 0) {
            (this->*(_actors[i]->getActionsToDo()).front().first)(*_actors[i]);
            _actors[i]->resetLastRecord();
        }
    }
}

void ActionHandler::moveActor(IActor &actor)
{
    std::vector<std::string> map = (actor.getWallPass() || (_mapHandler.getMap())[actor.getCoord().y][actor.getCoord().x] == '1') ? _mapHandler.getWallPassMap() : _mapHandler.getMap();
    int mapSize = _mapHandler.getMapSize();

    if ((actor.getMoveVector().Z < TILE_SIZE && actor.getMoveVector().Z > -TILE_SIZE && actor.getMoveVector().Z) ||
        (actor.getMoveVector().X < TILE_SIZE && actor.getMoveVector().X > -TILE_SIZE && actor.getMoveVector().X) ||
        (actor.getMoveVector().Z > 0 && (actor.getCoord().x + 1 < mapSize) && ((map)[actor.getCoord().y][actor.getCoord().x + 1] == '0' || (map)[actor.getCoord().y][actor.getCoord().x + 1] == '4') ||
         (actor.getMoveVector().Z < 0 && (actor.getCoord().x - 1 >= 0) && ((map)[actor.getCoord().y][actor.getCoord().x - 1] == '0' || (map)[actor.getCoord().y][actor.getCoord().x - 1] == '4')) ||
         (actor.getMoveVector().X > 0 && (actor.getCoord().y + 1 < mapSize) && ((map)[actor.getCoord().y + 1][actor.getCoord().x] == '0' || (map)[actor.getCoord().y + 1][actor.getCoord().x] == '4')) ||
         (actor.getMoveVector().X < 0 && (actor.getCoord().y - 1 >= 0) && ((map)[actor.getCoord().y - 1][actor.getCoord().x] == '0' || (map)[actor.getCoord().y - 1][actor.getCoord().x] == '4'))))
    {
        (actor.*(actor.getActionsToDo().front().second))();
    }
    else
    {
        actor.unstackAction();
        actor.setMoveVector({0, 0, 0});
    }
}

void ActionHandler::windSpell(IActor &actor)
{
    std::vector<std::string> map = (actor.getWallPass() || (_mapHandler.getMap())[actor.getCoord().y][actor.getCoord().x] == '1') ? _mapHandler.getWallPassMap() : _mapHandler.getMap();
    int mapSize = _mapHandler.getMapSize();
    direction dir = actor.getDirection();

    if ((dir == RIGHT && (actor.getCoord().x + 2 < mapSize) && ((map)[actor.getCoord().y][actor.getCoord().x + 2] == '0' || (map)[actor.getCoord().y][actor.getCoord().x + 2] == '4') ||
         (dir == LEFT && (actor.getCoord().x - 2 >= 0) && ((map)[actor.getCoord().y][actor.getCoord().x - 2] == '0' || (map)[actor.getCoord().y][actor.getCoord().x - 2] == '4')) ||
         (dir == DOWN && (actor.getCoord().y + 2 < mapSize) && ((map)[actor.getCoord().y + 2][actor.getCoord().x] == '0' || (map)[actor.getCoord().y + 2][actor.getCoord().x] == '4')) ||
         (dir == UP && (actor.getCoord().y - 2 >= 0) && ((map)[actor.getCoord().y - 2][actor.getCoord().x] == '0' || (map)[actor.getCoord().y - 2][actor.getCoord().x] == '4'))))
    {
        if (MUSIC == 1)
        {
            _music.playSoundPlayer("TP");
        }
        (actor.*(actor.getActionsToDo().front().second))();
    }
    actor.unstackAction();
}

void ActionHandler::fireSpell(IActor &actor)
{
    std::vector<std::string> map = _mapHandler.getWallPassMap();
    int mapSize = _mapHandler.getMapSize();
    std::vector<coord_t> area = {
        {actor.getCoord().x, actor.getCoord().y - 1},
        {actor.getCoord().x + 1, actor.getCoord().y},
        {actor.getCoord().x, actor.getCoord().y + 1},
        {actor.getCoord().x - 1, actor.getCoord().y}};
    coord_t currentCoord;

    for (size_t i = 0; i < _actors.size(); i += 1)
    {
        for (size_t u = 0; u < area.size(); u += 1)
        {
            currentCoord = _actors[i]->getCoord();
            if (currentCoord.x == area[u].x && currentCoord.y == area[u].y)
            {
                _actors[i]->stun();
                break;
            }
        }
    }
    if (MUSIC == 1)
    {
        _music.playSoundPlayer("STUN");
    }
    (actor.*(actor.getActionsToDo().front().second))();
    actor.unstackAction();
}

void ActionHandler::PutBomb(IActor &actor)
{
    irr::scene::ISceneNode *node;

    actor.unstackAction();
    if (_mapHandler.getMap()[actor.getCoord().y][actor.getCoord().x] == '0' && actor.getBombs() > 0)
    {
        node = _smgr->addMeshSceneNode(_vect_mesh[2], 0);
        node->setPosition(irr::core::vector3df(-300 + (actor.getCoord().y * TILE_SIZE), 0, -300 + (actor.getCoord().x * TILE_SIZE)));
        node->getMaterial(0).NormalizeNormals = true;
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _bombVect.push_back(new Bomb(irr::core::vector3df(actor.getCoord().x, 0, actor.getCoord().y), node, actor.getRange(), actor.getId()));
        _mapHandler.getMap()[actor.getCoord().y][actor.getCoord().x] = '3';
        actor.setBombs(-1);
    }
}

void ActionHandler::waterSpell(IActor &actor)
{
    float x = 0;
    float y = 0;
    for (Bomb *b : _bombVect)
    {
        if (b->hasExploded())
        {
            continue;
        }
        if (actor.getCoord().x + 1 < 20 && b->getPosition().X == actor.getCoord().x + 1 && b->getPosition().Z == actor.getCoord().y)
        {
            for (; b->getPosition().X + x + 1 < 20 && _mapHandler.getMap()[b->getPosition().Z + y][b->getPosition().X + x + 1] == '0'; x++)
                ;
        }
        else if (actor.getCoord().x - 1 >= 0 && b->getPosition().X == actor.getCoord().x - 1 && b->getPosition().Z == actor.getCoord().y)
        {
            for (; b->getPosition().X + x - 1 >= 0 && _mapHandler.getMap()[b->getPosition().Z + y][b->getPosition().X + x - 1] == '0'; x--)
                ;
        }
        else if (actor.getCoord().y + 1 < 20 && b->getPosition().Z == actor.getCoord().y + 1 && b->getPosition().X == actor.getCoord().x)
        {
            for (; b->getPosition().Z + y + 1 < 20 && _mapHandler.getMap()[b->getPosition().Z + y + 1][b->getPosition().X + x] == '0'; y++)
                ;
        }
        else if (actor.getCoord().y - 1 >= 0 && b->getPosition().Z == actor.getCoord().y - 1 && b->getPosition().X == actor.getCoord().x)
        {
            for (; (b->getPosition().Z + y - 1 >= 0) && (_mapHandler.getMap()[b->getPosition().Z + y - 1][b->getPosition().X + x] == '0'); y--)
                ;
        }
        for (int i = -b->getRange(); i < b->getRange(); i++)
        {
            if (b->getPosition().Z + i >= 0 && b->getPosition().Z + i < 20)
            {
                _mapHandler.getDangerMap()[b->getPosition().Z + i][b->getPosition().X] = '0';
            }
            if (b->getPosition().X + i >= 0 && b->getPosition().X + i < 20)
            {
                _mapHandler.getDangerMap()[b->getPosition().Z][b->getPosition().X + i] = '0';
            }
        }
        _mapHandler.getMap()[b->getPosition().Z][b->getPosition().X] = '0';
        b->setPosition(irr::core::vector3df(b->getPosition().X + x, b->getPosition().Y, b->getPosition().Z + y), b->getNode());
        _mapHandler.getMap()[b->getPosition().Z][b->getPosition().X] = '3';
        x = 0;
        y = 0;
    }
    if (MUSIC == 1)
    {
        _music.playSoundPlayer("KICK");
    }
    (actor.*(actor.getActionsToDo().front().second))();
    actor.unstackAction();
}

void ActionHandler::callResolve(IActor &actor)
{
    void (IActor::*tmp)(void) = (actor.getActionsToDo()).front().second;
    actor.unstackAction();
    (actor.*tmp)();
}