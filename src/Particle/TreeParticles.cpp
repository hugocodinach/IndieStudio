/*
** EPITECH PROJECT, 2018
** ActionHandler.cpp
** File description:
** src/Particle/TreeParticles.cpp
*/

#include "TreeParticles.hpp"

TreeParticule::TreeParticule(irr::scene::ISceneManager* smgr, irr::scene::ISceneNode* node)
{
    _meche = smgr->addParticleSystemSceneNode(false, node);

    irr::scene::IParticleEmitter* em = _meche->createBoxEmitter(
    irr::core::aabbox3d<irr::f32>(-2,0,-2,2,2,2),
    irr::core::vector3df(-0.002f,0.0f,0.0f), 1, 1,
    irr::video::SColor(0,0,170,0),
    irr::video::SColor(0,0,170,0), 100,10000,100,
    irr::core::dimension2df(0.5,0.5),
    irr::core::dimension2df(0.5,0.5));
    _meche->setEmitter(em);
    em->drop();
    irr::scene::IParticleAffector* paf = _meche->createFadeOutParticleAffector(irr::video::SColor(0,0,0,0), 100);
    _meche->addAffector(paf);
    paf->drop();
    _meche->setPosition(irr::core::vector3df(0, 5, 0));
    _meche->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

TreeParticule::~TreeParticule()
{
}