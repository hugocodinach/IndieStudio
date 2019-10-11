/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/ExplosionParticule.hpp
*/

#ifndef EXPLOSIONPARTICLES_HPP_
#define EXPLOSIONPARTICLES_HPP_

#include <string>
#include <iostream>
#include "GameObj.hpp"

class ExplosionParticule  : public GameObj
{
    public:
        ExplosionParticule(irr::scene::ISceneManager* smgr, irr::core::vector3df pos, irr::scene::ISceneNode* node);
        ~ExplosionParticule();
        void pure();

    private:
        irr::scene::IParticleSystemSceneNode* _meche;
};

#endif