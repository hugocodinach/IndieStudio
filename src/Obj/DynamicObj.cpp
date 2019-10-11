/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/Obj/DynamicObj.cpp
*/

#include "DynamicObj.hpp"

void DynamicObj::moveTo(irr::core::vector3df newPos)
{
    _pos.X = newPos.X;
    _pos.Y = newPos.Y;
    _pos.Z = newPos.Z;
}