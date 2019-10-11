/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/Bomb.hpp
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include <string>
#include <iostream>
#include <chrono>
#include "DynamicObj.hpp"
#include "MecheParticles.hpp"

class Bomb: public DynamicObj
{
    public:
        Bomb(irr::core::vector3df pos, irr::scene::ISceneNode *node, int range, int id);
        ~Bomb();

        int getRemainingTime();
        int getRange();
        int update();

        template<typename T>
        void setPosition(irr::core::vector3df pos, T node) {
            node->setPosition(irr::core::vector3df(- 300 + (pos.Z * 5), pos.Y, - 300 + (pos.X * 5)));
            _pos = pos;
        }

        irr::scene::ISceneNode *getNode();
        bool hasExploded(void);
        void setHasExploded(bool neo);
        int getMasterId();
        void pure();

        void setRemainingTime(int);


    private:
        std::chrono::system_clock::time_point _lastRecord;
        int _remainingTime = 3;
        int _range = 1;
        irr::scene::ISceneNode *_node;
        bool _hasExploded = false; 
        MecheParticule* _meche;
        int _id;
};

#endif