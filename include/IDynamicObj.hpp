/*
** EPITECH PROJECT, 2018
** IDynamicObj.hpp
** File description:
** include/IDynamicObj.hpp
*/

#ifndef IDYNAMIC_OBJ
#define IDYNAMIC_OBJ

#include "GameObj.hpp"

class IDynamicObj : public GameObj
{
    public:
        virtual ~IDynamicObj() = default;

        virtual void moveTo(irr::core::vector3df) = 0;
};

#endif