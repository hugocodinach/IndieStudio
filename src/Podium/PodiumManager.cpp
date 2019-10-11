/*
** EPITECH PROJECT, 2018
** PodiumManager.cpp
** File description:
** src/Podium/PodiumManager.cpp
*/

#include "PodiumManager.hpp"

PodiumManager::PodiumManager()
{
}

PodiumManager::~PodiumManager()
{
}

void PodiumManager::initPodium(irr::scene::ISceneManager *smgr, std::vector<MODELS> models, std::vector<int> scores)
{
    std::vector<irr::core::vector3df> pos = {irr::core::vector3df(-333, 4.8, -252), irr::core::vector3df(-333, 3, -258), irr::core::vector3df(-333, 2, -246), irr::core::vector3df(-333, 0, -264)};
    int tmp;

    for (size_t i = 0; i < scores.size() - 1; i += 1) {
        if (scores[i] < scores[i + 1]) {
            tmp = scores[i];
            scores[i] = scores[i + 1];
            scores[i + 1] = tmp;
            tmp = static_cast<int>(models[i]);
            models[i] = models[i + 1];
            models[i + 1] = static_cast<MODELS>(tmp);
            i = -1;
        }
    }

    for (size_t i = 0; i != models.size(); i += 1) {
        _playerAndScores.push_back({
            static_cast<MODELS>(models[i]),
            scores[i]
        });
        _playersMeshes.push_back(smgr->addAnimatedMeshSceneNode(smgr->getMesh((modelsList[_playerAndScores[i].first].file).c_str())));
        _playersMeshes[i]->setPosition(pos[i]);
        _playersMeshes[i]->getMaterial(0).NormalizeNormals = true;
        _playersMeshes[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
}

void PodiumManager::resetPodium()
{
    _playerAndScores.clear();
    for (size_t i = 0; i != _playersMeshes.size(); i += 1)
        _playersMeshes[i]->remove();
    _playersMeshes.clear();
}