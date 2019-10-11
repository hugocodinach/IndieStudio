/*
** EPITECH PROJECT, 2018
** Paticle.hpp
** File description:
** include/Paticle.hpp
*/

#ifndef PARTICLE
#define PARTICLE

#include <chrono>
#include "GameObj.hpp"

struct particleSettings {
    irr::core::aabbox3d<irr::f32> transmitterSize;
    irr::core::vector3df initialPosition;
    std::pair<int, int> emissionRate;
    irr::video::SColor darkestColor;
    irr::video::SColor lightestColor;
    int minAge;
    int maxAge;
    int angle;
    irr::core::dimension2df minSize;
    irr::core::dimension2df maxSize;
    irr::core::vector3df pos;
	bool fade;
};

class Particle
{
    public:
        Particle(irr::scene::ISceneManager* smgr, irr::scene::ISceneNode* node, particleSettings settings);
        ~Particle();

        void playParticleFor(float);
        void updateParticle(void);
        void setPosition(irr::core::vector3df);

    private:
        std::chrono::system_clock::time_point _lastRecord;
        irr::scene::IParticleSystemSceneNode* _meche;
        float _delay;
        bool _playing;
};

#endif