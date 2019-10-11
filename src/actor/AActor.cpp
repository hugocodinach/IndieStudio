/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/actor/AActor.cpp
*/

#include "AActor.hpp"

AActor::AActor()
{
    _actions.push_back({KeyHandler (irr::KEY_KEY_Q), static_cast<IActorMethodPtr>(&AActor::firstAction)});
    _actions.push_back({KeyHandler (irr::KEY_KEY_S), static_cast<IActorMethodPtr>(&AActor::secondAction)});
    _actions.push_back({KeyHandler (irr::KEY_KEY_D), static_cast<IActorMethodPtr>(&AActor::thirdAction)});
    _actions.push_back({KeyHandler (irr::KEY_KEY_Z), static_cast<IActorMethodPtr>(&AActor::forthAction)});
    _actions.push_back({KeyHandler (irr::KEY_KEY_E), static_cast<IActorMethodPtr>(&AActor::fifthAction)});
    _actions.push_back({KeyHandler (irr::KEY_KEY_A), static_cast<IActorMethodPtr>(&AActor::sixthAction)});
    _coord.x = 0;
    _coord.y = 0;
}

AActor::~AActor() {}

void AActor::firstAction(void)
{
    if (_actionsToDo.size() == 0) {
        _moveVector.Z -= TILE_SIZE;
        pushAction(&ActionHandler::moveActor, static_cast<IActorMethodPtr>(&AActor::firstActionResolve));
    }
}

void AActor::secondAction(void)
{
    if (_actionsToDo.size() == 0) {
        _moveVector.X += TILE_SIZE;
        pushAction(&ActionHandler::moveActor, static_cast<IActorMethodPtr>(&AActor::secondActionResolve));
    }
}

void AActor::thirdAction(void)
{
    if (_actionsToDo.size() == 0) {
        _moveVector.Z += TILE_SIZE;
        pushAction(&ActionHandler::moveActor, static_cast<IActorMethodPtr>(&AActor::thirdActionResolve));
    }
}

void AActor::forthAction(void)
{
    if (_actionsToDo.size() == 0) {
        _moveVector.X -= TILE_SIZE;
        pushAction(&ActionHandler::moveActor, static_cast<IActorMethodPtr>(&AActor::forthActionResolve));
    }
}

void AActor::fifthAction(void) {}

void AActor::sixthAction(void) {}

void AActor::firstActionResolve(void)
{
    unstackAction();
}

void AActor::secondActionResolve(void)
{
    unstackAction();
}

void AActor::thirdActionResolve(void)
{
    unstackAction();
}

void AActor::forthActionResolve(void)
{
    unstackAction();
}

void AActor::fifthActionResolve(void)
{
    unstackAction();
}

void AActor::sixthActionResolve(void)
{
    unstackAction();
}

void AActor::applyBonus(Bonus *bonus)
{
}

void AActor::pushAction(handleMethodPtr PTR, IActorMethodPtr ptr)
{
    _actionsToDo.push({PTR, ptr});
}

void AActor::unstackAction()
{
    _actionsToDo.pop();
}

std::queue< std::pair<handleMethodPtr, IActorMethodPtr> >& AActor::getActionsToDo()
{
    return _actionsToDo;
}

std::vector< std::pair<KeyHandler, IActorMethodPtr> > AActor::getBinds()
{
    std::unique_lock<std::mutex> lock(_mut);
    return _actions;
}

coord_t AActor::getCoord()
{
    return (_coord);
}

void AActor::setCoord(coord_t coord)
{
    _coord = coord;
}

direction AActor::getDirection(void)
{
    return RIGHT;
}

irr::core::vector3df AActor::getMoveVector(void)
{
    return (_moveVector);
}

void AActor::setMoveVector(irr::core::vector3df vect)
{
    _moveVector = vect;
}

bool AActor::getWallPass(void)
{
    return false;
}

void AActor::updateWallPass(void)
{
}

void AActor::updateParticles(void)
{
    for (size_t i = 0; i < _particles.size(); i += 1)
        _particles[i]->updateParticle();
}

int AActor::getRange()
{
    return (0);
}

void AActor::setInput(int idx, KeyHandler key)
{
    _actions[idx].first = key;
}

void AActor::stun(void)
{
}

status_e AActor::getStatus(void)
{
    return NONE;
}

void AActor::updateStatus(void)
{
}

void AActor::deleteGameObj()
{
}

void AActor::resetLastRecord()
{
}

int AActor::getMaxBomb()
{
    return (0);
}

int AActor::getBombs()
{
    return (0);
}

int AActor::getCharacterIDX()
{
    return (0);
}

void AActor::setBombs(int bombs)
{
}

int AActor::getId(void)
{
    return (_id);
}

bool AActor::hasPower()
{
    return (_hasPower);
}

void AActor::setPower(bool power)
{
    _hasPower = power;
}

bool AActor::isOnline()
{
    return (_isOnline);
}

void AActor::setIsOnline(bool neo)
{
    _isOnline = neo;
}

void AActor::setNetwork(NetworkClient *network)
{
	_network = network;
}

NetworkClient *AActor::getNetwork(void)
{
	return (_network);
}

void AActor::setActualBombs(int bombs)
{
}

void AActor::setMaxBombs(int maxBombs)
{
}

void AActor::setRange(int range)
{
}

void AActor::setStatus(int status)
{
}

void AActor::setDeath(bool neo)
{
	_dead = neo;
}

bool AActor::getDeath()
{
	return (_dead);
}