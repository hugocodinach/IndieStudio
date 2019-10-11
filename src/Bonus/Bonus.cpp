/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/Bonus/Bonus.cpp
*/

#include "Bonus.hpp"

Bonus::Bonus(irr::core::vector3df pos, irr::scene::ISceneNode *node, bonus_t type): _node(node)
{
    _pos = pos;
    _type = type;
}

Bonus::~Bonus()
{
    _node->remove();
    _node = nullptr;
};

Bonus::bonus_t Bonus::getType()
{
    return _type;
}

void Bonus::pure()
{
}