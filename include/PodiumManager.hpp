/*
** EPITECH PROJECT, 2018
** PodiumManager.hpp
** File description:
** include/PodiumManager.hpp
*/

#ifndef PODIUM_MANAGER
#define PODIUM_MANAGER

#include "Bomberman.hpp"

class PodiumManager {
    public:
        PodiumManager();
        ~PodiumManager();

        void initPodium(irr::scene::ISceneManager *, std::vector<MODELS>, std::vector<int>);
        void resetPodium();

    private:
        std::vector<irr::scene::IAnimatedMeshSceneNode *> _playersMeshes;
        std::vector<std::pair<MODELS, int>> _playerAndScores;
};

#endif