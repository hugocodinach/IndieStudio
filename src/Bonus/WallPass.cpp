/*
** EPITECH PROJECT, 2018
** WallPass.cpp
** File description:
** src/Bonus/WallPass.cpp
*/

#include "WallPass.hpp"

WallPass::WallPass()
{
    _duration = 3;
    _activated = false;
}

WallPass::~WallPass()
{
}

void WallPass::update()
{
    std::chrono::system_clock::time_point neo = std::chrono::system_clock::now();
    double tmp = std::chrono::duration<double>(neo - _lastRecord).count();

    if (tmp > _duration)
        _activated = false;
}

void WallPass::reset()
{
    _lastRecord = std::chrono::system_clock::now();
    _activated = true;
}

bool WallPass::isActivated()
{
    return _activated;
}