/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/MecheParticule.hpp
*/

#ifndef MECHEPARTICULE_HPP_
#define MECHEPARTICULE_HPP_

#include <string>
#include <iostream>
#include "GameObj.hpp"

class MecheParticule : public GameObj
{
    public:
        MecheParticule(irr::scene::ISceneManager* smgr, irr::core::vector3df pos, irr::scene::ISceneNode *node);
        ~MecheParticule();
        void pure();

    private:
        irr::scene::IParticleSystemSceneNode* _meche;
};

#endif