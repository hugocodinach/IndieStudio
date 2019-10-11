/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/Obj/Camera.cpp
*/

#include "Camera.hpp"

Camera::Camera(irr::scene::ISceneManager* smgr, irr::core::vector3df pos,
irr::core::vector3df target, irr::IrrlichtDevice *device): _pos(pos), _target(target), _sceneManager(smgr), _device(device)
{
    _camera = smgr->addCameraSceneNode(0);
    _targetNext = _target;
    _targetMove = false;
    _posMove = false;
    _playable = false;
    _onPodium = false;
    setPosition(pos, _camera);
    setTarget(_target);
}

Camera::~Camera()
{
}

void Camera::pure()
{
}

void Camera::setTarget(irr::core::vector3df target)
{
    _camera->setTarget(target);
    _target = target;
}

irr::core::vector3df Camera::getTarget(void) const
{
    return _target;
}

void Camera::setPos(irr::core::vector3df pos)
{
    _camera->setPosition(pos);
    _pos = pos;
}

irr::core::vector3df Camera::getPos(void) const
{
    return _pos;
}

void Camera::playIntro(void)
{
//  _aminationPoints.push_back(irr::core::vector3df(-317.267, -28.0927, -381.781));
    _aminationPoints.push_back(irr::core::vector3df(-232.411, 71.9743, -238.03));
    _aminationPoints.push_back(irr::core::vector3df(-232.411, 74.0743, -228.03));
    _aminationPoints.push_back(irr::core::vector3df(-232.411, 72.1743, -218.03));
    _aminationPoints.push_back(irr::core::vector3df(-232.411, 72.2743, -208.03));
    _aminationPoints.push_back(irr::core::vector3df(-232.411, 72.3743, -198.03));
    _aminationPoints.push_back(irr::core::vector3df(-232.411, 72.4743, -208.03));
    _aminationPoints.push_back(irr::core::vector3df(-232.411, 74.5743, -218.03));
    _aminationPoints.push_back(irr::core::vector3df(-232.411, 72.6743, -228.03));
    _aminationPoints.push_back(irr::core::vector3df(-232.411, 72.7743, -238.03));
    _aminationPoints.push_back(irr::core::vector3df(-232.411, 72.8743, -248.03));
    //_camera = _sceneManager->addCameraSceneNode(0, _aminationPoints[0], irr::core::vector3df(0 ,400,0));


    //_nodeAnimator =_sceneManager->createFlyStraightAnimator(irr::core::vector3df(-317.267, -28.0927, -381.781),
    //irr::core::vector3df(-232.411, 72.8743, -248.03), 1000);
    _nodeAnimator = _sceneManager->createFollowSplineAnimator(_device->getTimer()->getTime(), _aminationPoints);
    _camera->addAnimator(_nodeAnimator);
}

void Camera::setTargetNext(irr::core::vector3df targetNext)
{
    _targetNext = targetNext;
    _targetMove = true;
}

void Camera::setPosNext(irr::core::vector3df posNext)
{
    _posNext = posNext;
    _posMove = true;
}


bool Camera::isOnPos(float goal, float pos, float min_diff)
{
    float diff = 0;

    goal *= (goal < 0) ? -1 : 1;
    pos *= (pos < 0) ? -1 : 1;
    diff = goal - pos;
    diff *= (diff < 0) ? -1 : 1;
    if (diff <= min_diff)
        return true;
    return false;
}

float Camera::absf(float value)
{
    return ((value < 0) ? value * -1 : value);
}

void Camera::update(void)
{
    short modified_target_value = 0;
    short modified_pos_value = 0;
    float move = 0;

    _playable = (_target.X >= -245.422 && _target.Z >= -248.54) ? true : false;
    _onPodium = (_target.X <= -380.268) ? true : false;


    if (_targetMove) {
        move = (absf(_targetNext.X - _target.X)) / 100;
        if (isOnPos(_target.X, _targetNext.X, move) == false) {
            modified_target_value += 1;
            _target.X += (_target.X > _targetNext.X) ? -move : move;
        }
        move = (absf(_targetNext.Y - _target.Y)) / 100;
        if (isOnPos(_target.Y, _targetNext.Y, move) == false) {
            modified_target_value += 1;
            _target.Y += (_target.Y > _targetNext.Y) ? -move : move;
        }
        move = (absf(_targetNext.Z - _target.Z)) / 100;
        if (isOnPos(_target.Z, _targetNext.Z, move) == false) {
            modified_target_value += 1;
            _target.Z += (_target.Z > _targetNext.Z) ? -move : move;
        }
        _camera->setTarget(_target);
    }
    if (modified_target_value == 0)
        _targetMove = false;
    if (_posMove) {
        move = (absf(_posNext.X - _pos.X)) / 100;
        if (isOnPos(_pos.X, _posNext.X, move) == false) {
            modified_pos_value += 1;
            _pos.X += (_pos.X > _posNext.X) ? -move : move;
        }
        move = (absf(_posNext.Y - _pos.Y)) / 100;
        if (isOnPos(_pos.Y, _posNext.Y, move) == false) {
            modified_pos_value += 1;
            _pos.Y += (_pos.Y > _posNext.Y) ? -move : move;
        }
        move = (absf(_posNext.Z - _pos.Z)) / 100;
        if (isOnPos(_pos.Z, _posNext.Z, move) == false) {
            modified_pos_value += 1;
            _pos.Z += (_pos.Z > _posNext.Z) ? -move : move;
        }
        _camera->setPosition(_pos);
    }
    if (modified_pos_value == 0)
        _posMove = false;
}

bool Camera::isMoving(void)
{
    return _playable;
}

bool Camera::isOnPodium(void)
{
    return _onPodium;
}