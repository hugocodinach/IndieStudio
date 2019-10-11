/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/Camera.hpp
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <string>
#include <iostream>
#include "GameObj.hpp"

class Camera : public GameObj
{
    public:
        Camera(irr::scene::ISceneManager* smgr, irr::core::vector3df pos,
        irr::core::vector3df target, irr::IrrlichtDevice *device);
        ~Camera();

        void pure();
        void setTarget(irr::core::vector3df target);
        irr::core::vector3df getTarget(void) const;
        void setPos(irr::core::vector3df pos);
        irr::core::vector3df getPos(void) const;
        void playIntro(void);
        void setTargetNext(irr::core::vector3df targetNext);
        void setPosNext(irr::core::vector3df posNext);
        bool isOnPos(float goal, float pos, float min_diff);
        float absf(float value);
        void update(void);
	    bool isMoving(void);
        bool isOnPodium(void);

        irr::scene::ICameraSceneNode* _camera;

    private:
        irr::core::vector3df _target;
        irr::core::vector3df _targetNext;
        bool _targetMove;
        irr::core::vector3df _pos;
        irr::core::vector3df _posNext;
        bool _posMove;
        bool _playable;
        bool _onPodium;
        irr::core::array<irr::core::vector3df> _aminationPoints;
        irr::IrrlichtDevice *_device;
        irr::scene::ISceneManager *_sceneManager;
        irr::scene::ISceneNodeAnimator *_nodeAnimator;
};

#endif