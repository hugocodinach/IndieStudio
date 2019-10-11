/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/Obj/GameObj.cpp
*/

#include "GameObj.hpp"

void GameObj::pure()
{
}

void GameObj::setVisibility(bool visibility)
{
    _visible = visibility;
}

void GameObj::toggleVisibility(void)
{
    _visible = !_visible;
}

irr::core::vector3df GameObj::getPosition(void)
{
    return _pos;
}

bool GameObj::isVisible(void)
{
    return _visible;
}
