/*
** EPITECH PROJECT, 2018
** IGameObj.hpp
** File description:
** include/IGameObj.hpp
*/

#ifndef IGAME_OBJ
#define IGAME_OBJ

#include <iostream>
#include <vector>
#include <irr/irrlicht.h>

class IGameObj
{
    public:
        virtual ~IGameObj() = default;

        virtual void setVisibility(bool) = 0;
        virtual void toggleVisibility(void) = 0;

        virtual irr::core::vector3df getPosition(void) = 0;
        virtual bool isVisible(void) = 0;
};


#endif