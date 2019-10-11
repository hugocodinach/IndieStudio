/*
** EPITECH PROJECT, 2018
** PersSelection.cpp
** File description:
** src/PersSelection/PersSelection.cpp
*/

#include "PersSelection.hpp"

RotatingMeshes::RotatingMeshes(irr::core::vector3df firstPlayerPos, irr::core::vector3df lastPlayerPos, int playerNumber, irr::scene::ISceneManager *smgr)
{
    irr::core::vector3df ranges = {lastPlayerPos.X - firstPlayerPos.X, lastPlayerPos.Y - firstPlayerPos.Y, lastPlayerPos.Z - firstPlayerPos.Z};
    _rangesBetween = {ranges.X / static_cast<float>(playerNumber), ranges.Y / static_cast<float>(playerNumber), ranges.Z / static_cast<float>(playerNumber)};
    _playerNumber = playerNumber;
    _smgr = smgr;
    _rotationSpeed = 1.0;
    _rotating = true;
    _rotationDegree = 0;
    _hudPathes = {
        "./ressources/models/HUDModels/penguinHUD.3ds",
        "./ressources/models/HUDModels/pigHUD.3ds",
        "./ressources/models/HUDModels/catHUD.3ds",
        "./ressources/models/HUDModels/chickenHUD.3ds",
        "./ressources/models/HUDModels/hootyHUD.3ds",
        "./ressources/models/HUDModels/lamaHUD.3ds",
        "./ressources/models/HUDModels/sheepHUD.3ds",
        "./ressources/models/HUDModels/snakeHUD.3ds",
        "./ressources/models/HUDModels/squirrelHUD.3ds",
    };
    _particlesSettings = {
        WATER_PERS,
        FIRE_PERS,
        WATER_PERS,
        WIND_PERS,
        WIND_PERS,
        FIRE_PERS,
        FIRE_PERS,
        WATER_PERS,
        WIND_PERS
    };
    MODELS model;

    for (size_t i = 0; i < playerNumber; i += 1) {
        model = static_cast<MODELS>(rand() % MODELS_SIZE);
        _playersModels.push_back(model);
        _playersMeshes.push_back(_smgr->addAnimatedMeshSceneNode(_smgr->getMesh((modelsList[_playersModels[i]].file).c_str())));
        _playerPositions.push_back(irr::core::vector3df(firstPlayerPos.X + _rangesBetween.X * i, firstPlayerPos.Y + _rangesBetween.Y * i, firstPlayerPos.Z + _rangesBetween.Z * i));
        _playersMeshes[i]->setPosition(_playerPositions[i]);
        _playersMeshes[i]->getMaterial(0).NormalizeNormals = true;
        _playersMeshes[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _playersHUD.push_back(_smgr->addAnimatedMeshSceneNode(_smgr->getMesh((_hudPathes[_playersModels[i]]).c_str())));
        _playersHUD[i]->setPosition(irr::core::vector3df(_playerPositions[i].X, _playerPositions[i].Y, _playerPositions[i].Z));
        _playersHUD[i]->getMaterial(0).NormalizeNormals = true;
        _playersHUD[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _particles.push_back(new Particle(smgr, _playersMeshes[i], _particlesSettings[_playersModels[i]]));
        _particles[i]->playParticleFor(-1);
    }
}

RotatingMeshes::~RotatingMeshes(void)
{
}

void RotatingMeshes::setPosition(irr::core::vector3df firstPlayerPos, irr::core::vector3df lastPlayerPos)
{
    irr::core::vector3df ranges = {lastPlayerPos.X - firstPlayerPos.X, lastPlayerPos.Y - firstPlayerPos.Y, lastPlayerPos.Z - firstPlayerPos.Z};
    irr::core::vector3df _rangesBetween = {ranges.X / static_cast<float>(_playerNumber), ranges.Y / static_cast<float>(_playerNumber), ranges.Z / static_cast<float>(_playerNumber)};

    for (size_t i = 0; i < _playersMeshes.size(); i += 1) {
        _playerPositions[i] = irr::core::vector3df(firstPlayerPos.X + _rangesBetween.X * i, firstPlayerPos.Y + _rangesBetween.Y * i, firstPlayerPos.Z + _rangesBetween.Z * i);
        _playersMeshes[i]->setPosition(_playerPositions[i]);
        _playersHUD[i]->setPosition(irr::core::vector3df(_playerPositions[i].X, _playerPositions[i].Y, _playerPositions[i].Z));
    }
}

void RotatingMeshes::setPersPosition(int index, irr::core::vector3df position)
{
    _playerPositions[index] = position;
    _playersMeshes[index]->setPosition(_playerPositions[index]);
    _playersHUD[index]->setPosition(irr::core::vector3df(_playerPositions[index].X, _playerPositions[index].Y, _playerPositions[index].Z));
}

void RotatingMeshes::setRotationSpeed(float speed)
{
    _rotationSpeed = speed;
}

void RotatingMeshes::toggleRotation(void)
{
    _rotating = !_rotating;
}

void RotatingMeshes::changeRotationStatus(bool status)
{
    _rotating = status;
}

void RotatingMeshes::setPersVisibility(int index, bool status)
{
    _playersMeshes[index]->setVisible(status);
    _playersHUD[index]->setVisible(status);
}

void RotatingMeshes::nextPers(int index)
{
    MODELS currentModel = _playersModels[index];
    _playersModels[index] = static_cast<int>(currentModel) + 1 > (MODELS_SIZE - 1) ? static_cast<MODELS>(0) : static_cast<MODELS>(static_cast<int>(currentModel) + 1);
    delete _particles[index];
    _playersMeshes[index]->remove();
    _playersHUD[index]->remove();
    _playersMeshes[index] = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh((modelsList[_playersModels[index]].file).c_str()));
    _playersMeshes[index]->setPosition(_playerPositions[index]);
	_playersMeshes[index]->setRotation(irr::core::vector3df(0, _rotationDegree, 0));
    _playersMeshes[index]->getMaterial(0).NormalizeNormals = true;
    _playersMeshes[index]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _playersHUD[index] = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh((_hudPathes[_playersModels[index]]).c_str()));
    _playersHUD[index]->setPosition(irr::core::vector3df(_playerPositions[index].X, _playerPositions[index].Y, _playerPositions[index].Z));
    _playersHUD[index]->getMaterial(0).NormalizeNormals = true;
    _playersHUD[index]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _particles[index] = new Particle(_smgr, _playersMeshes[index], _particlesSettings[_playersModels[index]]);
    _particles[index]->playParticleFor(-1);
}

void RotatingMeshes::previousPers(int index)
{
    MODELS currentModel = _playersModels[index];
    _playersModels[index] = static_cast<int>(currentModel) - 1 < 0 ? static_cast<MODELS>(MODELS_SIZE - 1) : static_cast<MODELS>(static_cast<int>(currentModel) - 1);
    delete _particles[index];
    _playersMeshes[index]->remove();
    _playersHUD[index]->remove();
    _playersMeshes[index] = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh((modelsList[_playersModels[index]].file).c_str()));
    _playersMeshes[index]->setPosition(_playerPositions[index]);
	_playersMeshes[index]->setRotation(irr::core::vector3df(0, _rotationDegree, 0));
    _playersMeshes[index]->getMaterial(0).NormalizeNormals = true;
    _playersMeshes[index]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _playersHUD[index] = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh((_hudPathes[_playersModels[index]]).c_str()));
    _playersHUD[index]->setPosition(irr::core::vector3df(_playerPositions[index].X, _playerPositions[index].Y, _playerPositions[index].Z));
    _playersHUD[index]->getMaterial(0).NormalizeNormals = true;
    _playersHUD[index]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _particles[index] = new Particle(_smgr, _playersMeshes[index], _particlesSettings[_playersModels[index]]);
    _particles[index]->playParticleFor(-1);
}

void RotatingMeshes::setParticularPers(int index, MODELS model)
{
    _playersModels[index] = model;
    delete _particles[index];
    _playersMeshes[index]->remove();
    _playersHUD[index]->remove();
    _playersMeshes[index] = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh((modelsList[_playersModels[index]].file).c_str()));
    _playersMeshes[index]->setPosition(_playerPositions[index]);
	_playersMeshes[index]->setRotation(irr::core::vector3df(0, _rotationDegree, 0));
    _playersMeshes[index]->getMaterial(0).NormalizeNormals = true;
    _playersMeshes[index]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _playersHUD[index] = _smgr->addAnimatedMeshSceneNode(_smgr->getMesh((_hudPathes[_playersModels[index]]).c_str()));
    _playersHUD[index]->setPosition(irr::core::vector3df(_playerPositions[index].X, _playerPositions[index].Y, _playerPositions[index].Z));
    _playersHUD[index]->getMaterial(0).NormalizeNormals = true;
    _playersHUD[index]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _particles[index] = new Particle(_smgr, _playersMeshes[index], _particlesSettings[_playersModels[index]]);
    _particles[index]->playParticleFor(-1);
}

void RotatingMeshes::addPlayer(void)
{
    if (_playerNumber == 4)
        return;

    irr::core::vector3df firstPlayerPos = {_playerPositions[0].X, _playerPositions[0].Y, _playerPositions[0].Z};
    irr::core::vector3df lastPlayerPos = {_playerPositions[_playerPositions.size() - 1].X, _playerPositions[_playerPositions.size() - 1].Y, _playerPositions[_playerPositions.size() - 1].Z};

    _playerNumber += 1;
    int i = _playerNumber - 1;
    _playersModels.push_back(PENGUIN);
    _playersMeshes.push_back(_smgr->addAnimatedMeshSceneNode(_smgr->getMesh((modelsList[_playersModels[i]].file).c_str())));
    _playerPositions.push_back(irr::core::vector3df(_playerPositions[0].X + _rangesBetween.X * i, _playerPositions[0].Y + _rangesBetween.Y * i, _playerPositions[0].Z + _rangesBetween.Z * i));
    _playersMeshes[i]->setPosition(_playerPositions[i]);
    _playersMeshes[i]->getMaterial(0).NormalizeNormals = true;
    _playersMeshes[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);

    _playersHUD.push_back(_smgr->addAnimatedMeshSceneNode(_smgr->getMesh((_hudPathes[_playersModels[i]]).c_str())));
    _playersHUD[i]->setPosition(irr::core::vector3df(_playerPositions[0].X + _rangesBetween.X * i, _playerPositions[0].Y + _rangesBetween.Y * i, _playerPositions[0].Z + _rangesBetween.Z * i));
    _playersHUD[i]->getMaterial(0).NormalizeNormals = true;
    _playersHUD[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);

    _particles.push_back(new Particle(_smgr, _playersMeshes[i], _particlesSettings[_playersModels[i]]));
    _particles[i]->playParticleFor(-1);

    irr::core::vector3df ranges = {lastPlayerPos.X - firstPlayerPos.X, lastPlayerPos.Y - firstPlayerPos.Y, lastPlayerPos.Z - firstPlayerPos.Z};
    _rangesBetween = {ranges.X / static_cast<float>(_playerNumber), ranges.Y / static_cast<float>(_playerNumber), ranges.Z / static_cast<float>(_playerNumber)};

    for (size_t i = 0; i < _playersMeshes.size(); i += 1) {
        _playerPositions[i] = irr::core::vector3df(firstPlayerPos.X + _rangesBetween.X * i, firstPlayerPos.Y + _rangesBetween.Y * i, firstPlayerPos.Z + _rangesBetween.Z * i);
        _playersMeshes[i]->setPosition(_playerPositions[i]);
        _playersHUD[i]->setPosition(irr::core::vector3df(_playerPositions[i].X, _playerPositions[i].Y, _playerPositions[i].Z));
    }
}

void RotatingMeshes::deleteLastPlayer(void)
{
    if (_playerNumber == 0)
        return;

    irr::core::vector3df firstPlayerPos = {_playerPositions[0].X, _playerPositions[0].Y, _playerPositions[0].Z};
    irr::core::vector3df lastPlayerPos = {_playerPositions[_playerPositions.size() - 1].X, _playerPositions[_playerPositions.size() - 1].Y, _playerPositions[_playerPositions.size() - 1].Z};

    _playerNumber -= 1;
    delete _particles[_playerNumber];
    _playersMeshes[_playerNumber]->remove();
    _playersHUD[_playerNumber]->remove();
    _playersMeshes.erase(_playersMeshes.begin() + _playerNumber);
    _playersHUD.erase(_playersHUD.begin() + _playerNumber);
    _playerPositions.erase(_playerPositions.begin() + _playerNumber);
    _playersModels.erase(_playersModels.begin() + _playerNumber);

    irr::core::vector3df ranges = {lastPlayerPos.X - firstPlayerPos.X, lastPlayerPos.Y - firstPlayerPos.Y, lastPlayerPos.Z - firstPlayerPos.Z};
    _rangesBetween = {ranges.X / static_cast<float>(_playerNumber), ranges.Y / static_cast<float>(_playerNumber), ranges.Z / static_cast<float>(_playerNumber)};

    for (size_t i = 0; i < _playersMeshes.size(); i += 1) {
        _playerPositions[i] = irr::core::vector3df(firstPlayerPos.X + _rangesBetween.X * i, firstPlayerPos.Y + _rangesBetween.Y * i, firstPlayerPos.Z + _rangesBetween.Z * i);
        _playersMeshes[i]->setPosition(_playerPositions[i]);
        _playersHUD[i]->setPosition(irr::core::vector3df(_playerPositions[i].X, _playerPositions[i].Y, _playerPositions[i].Z));
    }
}

void RotatingMeshes::deleteParticularPlayer(int index)
{
    _playerNumber -= 1;
    delete _particles[index];
    _playersMeshes[index]->remove();
    _playersHUD[index]->remove();
    _playersMeshes.erase(_playersMeshes.begin() + index);
    _playersHUD.erase(_playersHUD.begin() + index);
    _playerPositions.erase(_playerPositions.begin() + index);
    _playersModels.erase(_playersModels.begin() + index);

    irr::core::vector3df firstPlayerPos = {_playerPositions[0].X, _playerPositions[0].Y, _playerPositions[0].Z};
    irr::core::vector3df lastPlayerPos = {_playerPositions[_playerPositions.size() - 1].X, _playerPositions[_playerPositions.size() - 1].Y, _playerPositions[_playerPositions.size() - 1].Z};

    irr::core::vector3df ranges = {lastPlayerPos.X - firstPlayerPos.X, lastPlayerPos.Y - firstPlayerPos.Y, lastPlayerPos.Z - firstPlayerPos.Z};
    _rangesBetween = {ranges.X / static_cast<float>(_playerNumber), ranges.Y / static_cast<float>(_playerNumber), ranges.Z / static_cast<float>(_playerNumber)};

    for (size_t i = 0; i < _playersMeshes.size(); i += 1) {
        _playerPositions[i] = irr::core::vector3df(firstPlayerPos.X + _rangesBetween.X * i, firstPlayerPos.Y + _rangesBetween.Y * i, firstPlayerPos.Z + _rangesBetween.Z * i);
        _playersMeshes[i]->setPosition(_playerPositions[i]);
        _playersHUD[i]->setPosition(irr::core::vector3df(_playerPositions[i].X, _playerPositions[i].Y, _playerPositions[i].Z));
    }
}

std::vector<MODELS> RotatingMeshes::getModelList(void)
{
    return _playersModels;
}

MODELS RotatingMeshes::getParticularModel(int index)
{
    return _playersModels[index];
}

int RotatingMeshes::getPlayerNumber(void)
{
    return _playerNumber;
}

irr::core::vector3df RotatingMeshes::getPersPosition(int index)
{
    return _playerPositions[index];
}

void RotatingMeshes::update(void)
{
    if (_rotating) {
        _rotationDegree = (_rotationDegree + _rotationSpeed >= 360) ? _rotationDegree + _rotationSpeed - 360 : _rotationDegree + _rotationSpeed;
        for (size_t i = 0; i < _playersMeshes.size(); i += 1)
            _playersMeshes[i]->setRotation(irr::core::vector3df(0, _rotationDegree, 0));
    }
}

void RotatingMeshes::close(void)
{
    for (size_t i = 0; i < _playersMeshes.size(); i += 1) {
        delete _particles[i];
        _playersMeshes[i]->remove();
        _playersHUD[i]->remove();
    }
}