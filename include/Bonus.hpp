/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/Bonus.hpp
*/

#ifndef BONUS_HPP_
#define BONUS_HPP_

#include <string>
#include <iostream>
#include <chrono>
#include "StaticObj.hpp"

class Bonus: public StaticObj
{
    public:
        typedef enum bonus_e {
            BOMB_UP,
            FIRE_UP,
            SPEED_UP,
            WALL_PASS,
            POWER_UP
        } bonus_t;

        Bonus(irr::core::vector3df pos, irr::scene::ISceneNode *node, bonus_t type);
        ~Bonus();

        bonus_t getType();
        void pure();

    private:
        irr::scene::ISceneNode *_node;
        bonus_t _type;
};

#endif