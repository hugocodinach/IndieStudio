/*
** EPITECH PROJECT, 2018
** DynamicObj.hpp
** File description:
** include/DynamicObj.hpp
*/

#ifndef DYNAMIC_OBJ
#define DYNAMIC_OBJ

#include "IDynamicObj.hpp"

class DynamicObj : public IDynamicObj
{
    public:
        virtual void pure() = 0;

        void moveTo(irr::core::vector3df newPos);

    protected:
        float _speed;
};

#endif