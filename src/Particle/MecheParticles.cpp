/*
** EPITECH PROJECT, 2018
** Particle.cpp
** File description:
** src/Particle/MecheParticle.cpp
*/

#include "MecheParticles.hpp"

MecheParticule::MecheParticule(irr::scene::ISceneManager* smgr, irr::core::vector3df pos, irr::scene::ISceneNode *node)
{
    _meche = smgr->addParticleSystemSceneNode(false, node);
    irr::scene::IParticleEmitter* em = _meche->createPointEmitter(
    irr::core::vector3df((0.0F), (0.02F), (0.0F)), 10, 20, 
    irr::video::SColor(0,255,165,0),
    irr::video::SColor(0,255,165,0), 300, 500, 0,
    irr::core::dimension2df((0.5F), (0.5F)),
    irr::core::dimension2df((0.5F), (0.5F)));
    _meche->setEmitter(em);
    em->drop();
    irr::scene::IParticleAffector* paf = _meche->createFadeOutParticleAffector(irr::video::SColor(0,0,0,0), 100);
    _meche->addAffector(paf);
    paf->drop();
    _meche->setPosition(irr::core::vector3df(_meche->getPosition().X - 0.03, 0, _meche->getPosition().Z + 0.5));
    _meche->setScale(irr::core::vector3df(0.1));
    _meche->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

MecheParticule::~MecheParticule()
{
}

void MecheParticule::pure()
{
}