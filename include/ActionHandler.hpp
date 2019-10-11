/*
** EPITECH PROJECT, 2018
** ActionHandler.hpp
** File description:
** include/ActionHandler.hpp
*/

#ifndef ACTION_HANDLER_HPP
#define ACTION_HANDLER_HPP

#include <queue>
#include "MapHandler.hpp"
#include "musicPlayer.hpp"

class IActor;

class ActionHandler
{
    public:
        ActionHandler(std::vector<IActor*> &, MapHandler &_mapHandler,
        std::vector<Bomb*> &, irr::scene::ISceneManager* &_smgr,
        std::vector<irr::scene::IAnimatedMesh *> &vect_mesh, MusicPlayer &music);
        ~ActionHandler();

        void handleAction();
        void moveActor(IActor&);
        void callResolve(IActor&);
        void PutBomb(IActor &actor);
        void windSpell(IActor &actor);
        void fireSpell(IActor &actor);
        void waterSpell(IActor &actor);

    private:
        std::vector<IActor*> &_actors;
        MapHandler &_mapHandler;
        MusicPlayer &_music;
        std::vector<Bomb*> &_bombVect;
        irr::scene::ISceneManager* &_smgr;
        std::vector<irr::scene::IAnimatedMesh *> &_vect_mesh;
};

#endif