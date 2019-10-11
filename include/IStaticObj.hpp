/*
** EPITECH PROJECT, 2018
** IStaticObj.hpp
** File description:
** include/IStaticObj.hpp
*/

#ifndef ISTATIC_OBJ
#define ISTATIC_OBJ

#include "GameObj.hpp"

class IStaticObj : public GameObj
{
    public:
        virtual ~IStaticObj() = default;
};

#endif