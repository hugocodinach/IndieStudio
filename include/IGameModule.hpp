/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/IGameModule.hpp
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include <string>
#include <iostream>
#include <vector>
#include "irr/irrlicht.h"
#include "IGameObj.hpp"

class IGameModule
{
    public:
        virtual ~IGameModule() = default;

        virtual void initGameModule() = 0;
        virtual void drawGameModule() = 0;
        virtual void run() = 0;
};

#endif