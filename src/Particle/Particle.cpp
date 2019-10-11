/*
** EPITECH PROJECT, 2018
** Particle.cpp
** File description:
** src/Particle/Particle.cpp
*/

#include "Particle.hpp"

Particle::Particle(irr::scene::ISceneManager* smgr, irr::scene::ISceneNode* node, particleSettings settings)
{
    _meche = smgr->addParticleSystemSceneNode(false, node);

    irr::scene::IParticleEmitter* em = _meche->createBoxEmitter(
    settings.transmitterSize,
    settings.initialPosition,
    settings.emissionRate.first, settings.emissionRate.second,
    settings.darkestColor,
    settings.lightestColor,
    settings.maxAge, settings.maxAge,
    settings.angle,
    settings.minSize,
    settings.maxSize);

    _meche->setEmitter(em); // Ceci prend l'émetteur
    em->drop(); // Donc on peut le jeter sans qu'il soit supprimé.

	if (settings.fade) {
    	irr::scene::IParticleAffector* paf = _meche->createFadeOutParticleAffector(irr::video::SColor(0,0,0,0), 100);
    	_meche->addAffector(paf); // de même pour l'affecteur
    	paf->drop();
	}

    _meche->setPosition(settings.pos);
    _meche->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _meche->setVisible(false);
    _playing = false;
}

Particle::~Particle()
{
    _meche->remove();
}

void Particle::playParticleFor(float delay)
{
    _delay = delay;
    _lastRecord = std::chrono::system_clock::now();
    _playing = true;
    _meche->setVisible(true);
}

void Particle::updateParticle(void)
{
    std::chrono::system_clock::time_point neo = std::chrono::system_clock::now();
    double tmp = std::chrono::duration<double>(neo - _lastRecord).count();

    if (!_playing)
        return;

    if (_delay != -1 && tmp > _delay) {
        _playing = false;
        _meche->setVisible(false);
    }
}

void Particle::setPosition(irr::core::vector3df pos)
{
    _meche->setPosition(pos);
}