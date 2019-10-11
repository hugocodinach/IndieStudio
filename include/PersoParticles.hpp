/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/PersoParticule.hpp
*/

#ifndef PERSOPARTICLES_HPP_
#define PERSOPARTICLES_HPP_

#include <string>
#include <iostream>
#include "GameObj.hpp"

class PersoParticule : public GameObj
{
    public:
        PersoParticule(irr::scene::ISceneManager* smgr, irr::core::vector3df pos, irr::scene::ISceneNode* node);
        ~PersoParticule();
        void SetVisible(bool status);
        void pure();

    private:
        irr::scene::IParticleSystemSceneNode* _meche;
};

#endif