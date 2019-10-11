/*
** EPITECH PROJECT, 2018
** PersSelection.hpp
** File description:
** include/PersSelection.hpp
*/

#ifndef PERS_SELECTION
#define PERS_SELECTION

#include <iostream>
#include "irr/irrlicht.h"
#include "Bomberman.hpp"

#define WIND_PERS {\
    irr::core::aabbox3d<irr::f32>(-2,0,-2,2,1,2),\
    irr::core::vector3df(0.0f,0.005f,0.0f),\
    {20, 40},\
    irr::video::SColor(0,100,221,23),\
    irr::video::SColor(0,100,221,23),\
    100,\
    1000,\
    0,\
    irr::core::dimension2df(0.3,0.3),\
    irr::core::dimension2df(0.4,0.4),\
    irr::core::vector3df(0, 0, 0),\
	true\
}\

#define FIRE_PERS {\
    irr::core::aabbox3d<irr::f32>(-2,0,-2,2,1,2),\
    irr::core::vector3df(0.0f,0.005f,0.0f),\
    {20, 40},\
    irr::video::SColor(0,255,0,0),\
    irr::video::SColor(0,255,0,0),\
    100,\
    1000,\
    0,\
    irr::core::dimension2df(0.3,0.3),\
    irr::core::dimension2df(0.4,0.4),\
    irr::core::vector3df(0, 0, 0),\
	true\
}\

#define WATER_PERS {\
    irr::core::aabbox3d<irr::f32>(-2,0,-2,2,1,2),\
    irr::core::vector3df(0.0f,0.005f,0.0f),\
    {20, 40},\
    irr::video::SColor(0,33,150,243),\
    irr::video::SColor(0,33,150,243),\
    100,\
    1000,\
    0,\
    irr::core::dimension2df(0.3,0.3),\
    irr::core::dimension2df(0.4,0.4),\
    irr::core::vector3df(0, 0, 0),\
	true\
}\

class RotatingMeshes {

    public:
        RotatingMeshes(irr::core::vector3df, irr::core::vector3df, int, irr::scene::ISceneManager *);
        ~RotatingMeshes(void);

        void update(void);

        void setPosition(irr::core::vector3df, irr::core::vector3df);
        void setPersPosition(int, irr::core::vector3df);

        void setRotationSpeed(float);

        void toggleRotation(void);
        void changeRotationStatus(bool);

        void setPersVisibility(int, bool);

        void nextPers(int);
        void previousPers(int);
        void setParticularPers(int, MODELS);

        void addPlayer(void);
        void deleteLastPlayer(void);
        void deleteParticularPlayer(int);

        void close(void);

        std::vector<MODELS> getModelList(void);
        MODELS getParticularModel(int);
        int getPlayerNumber(void);
        std::pair<irr::core::vector3df, irr::core::vector3df> getPosition(void);
        irr::core::vector3df getPersPosition(int);

    private:
        irr::scene::ISceneManager *_smgr;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> _playersMeshes;
        std::vector<Particle *> _particles;
        std::vector<particleSettings> _particlesSettings;
        std::vector<irr::scene::IAnimatedMeshSceneNode *> _playersHUD;
        std::vector<std::string> _hudPathes;
        std::vector<MODELS> _playersModels;
        std::vector<irr::core::vector3df> _playerPositions;
        irr::core::vector3df _rangesBetween;
        int _playerNumber;
        float _rotationSpeed;
        bool _rotating;
        int _rotationDegree;
};

#endif