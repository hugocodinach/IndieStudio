/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/TreeParticule.hpp
*/

#ifndef TREEPARTICLES_HPP_
#define TREEPARTICLES_HPP_

#include <string>
#include <iostream>
#include "GameObj.hpp"

class TreeParticule
{
    public:
        TreeParticule(irr::scene::ISceneManager* smgr, irr::scene::ISceneNode* node);
        ~TreeParticule();

    private:
        irr::scene::IParticleSystemSceneNode* _meche;
};

#endif