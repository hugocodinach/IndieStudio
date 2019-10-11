/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/Obj/Bomb.cpp
*/

#include "Bomb.hpp"

Bomb::Bomb(irr::core::vector3df pos, irr::scene::ISceneNode *node, int range, int id): _node(node)
{
    _pos = pos;
    _lastRecord = std::chrono::system_clock::now();
    _range = range;
    _meche = new MecheParticule(node->getSceneManager(), node->getPosition(), node);
    _id = id;
}

Bomb::~Bomb()
{
    if (_node != nullptr)
        _node->remove();
}

int Bomb::getRemainingTime()
{
    return (_remainingTime);
}

int Bomb::getRange()
{
    return (_range);
}

int Bomb::update()
{
    std::chrono::system_clock::time_point neo = std::chrono::system_clock::now();
    double tmp = std::chrono::duration<double>(neo - _lastRecord).count();

    if (tmp > 1 && _remainingTime >= 0) {
        _remainingTime -= 1;
        _lastRecord = neo; 
    } else if (_remainingTime == 0 && tmp > 0.6) {
        _remainingTime -= 1;
        _lastRecord = neo; 
    }
    if (_remainingTime == 0 && _node != nullptr) {
        _node->remove();
        _node = nullptr;
        return (1);
    }
    return (0);
}

irr::scene::ISceneNode *Bomb::getNode()
{
    return (_node);
}

bool Bomb::hasExploded(void)
{
    return (_hasExploded);
}

void Bomb::setHasExploded(bool neo)
{
    _hasExploded = neo;
}

int Bomb::getMasterId()
{
    return (_id);
}

void Bomb::pure()
{
}

void Bomb::setRemainingTime(int time)
{
    _remainingTime = time;
}