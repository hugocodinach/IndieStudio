/*
** EPITECH PROJECT, 2018
** Particle.cpp
** File description:
** src/Particle/ExplosionParticle.cpp
*/

#include "ExplosionParticles.hpp"

ExplosionParticule::ExplosionParticule(irr::scene::ISceneManager* smgr, irr::core::vector3df pos, irr::scene::ISceneNode* node) {
    _meche = smgr->addParticleSystemSceneNode(false, node);
    irr::scene::IParticleEmitter* em = _meche->createBoxEmitter(
    irr::core::aabbox3d<irr::f32>(-0.1,0,-0.1,0.1,0.1,0.1),
    irr::core::vector3df(0.0f,0.06f,0.0f), 80,100,
    irr::video::SColor(0,255,165,0),
    irr::video::SColor(0,255,165,0), 150,200,0,
    irr::core::dimension2df(1.f,1.f),
    irr::core::dimension2df(4.f,4.f));
    _meche->setEmitter(em);
    em->drop(); 
    irr::scene::IParticleAffector* paf = _meche->createFadeOutParticleAffector(irr::video::SColor(0,0,0,0), 100);
    _meche->addAffector(paf);
    paf->drop();
    _meche->setPosition(irr::core::vector3df(0, -5, 0));
    _meche->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _meche->setVisible(true);
}

ExplosionParticule::~ExplosionParticule()
{
}

void ExplosionParticule::pure()
{
}