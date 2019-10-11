/*
** EPITECH PROJECT, 2018
** ActionHandler.cpp
** File description:
** src/Particle/TreeParticles.cpp
*/

#include "PersoParticles.hpp"

PersoParticule::PersoParticule(irr::scene::ISceneManager* smgr, irr::core::vector3df pos, irr::scene::ISceneNode* node) {
    _meche = smgr->addParticleSystemSceneNode(false, node);
    irr::scene::IParticleEmitter* em = _meche->createBoxEmitter(
    irr::core::aabbox3d<irr::f32>(-1,0,-1,1,1,1),
    irr::core::vector3df(0.0f,0.0f,0.0f),  80,100,
    irr::video::SColor(0,255,255,255),
    irr::video::SColor(0,255,255,255),
    100,300,0,
    irr::core::dimension2df(0.5,0.5),
    irr::core::dimension2df(0.5,0.5));
    _meche->setEmitter(em);
    em->drop();
    irr::scene::IParticleAffector* paf = _meche->createFadeOutParticleAffector(irr::video::SColor(0,0,0,0), 100);
    _meche->addAffector(paf);
    paf->drop();
    _meche->setPosition(irr::core::vector3df(0, 0, 0));
    _meche->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

PersoParticule::~PersoParticule() 
{
}

void PersoParticule::SetVisible(bool status)
{
	// _meche->setVisible(status);
}

void PersoParticule::pure()
{
}