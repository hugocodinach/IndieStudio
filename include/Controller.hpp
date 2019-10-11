/*
** EPITECH PROJECT, 2018
** Controller.hpp
** File description:
** include/Controller.hpp
*/

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <irr/irrlicht.h>
#include "IActor.hpp"

class Controller
{
    public:
        Controller(IActor *, std::vector<KeyHandler>&);

        ~Controller();
        void changeActor(IActor *);
        void changeKeymap(std::vector<KeyHandler> &);
        void callActorAction(std::vector< std::pair<KeyHandler, IActorMethodPtr> >, KeyHandler, NetworkClient *network);
        void handleControll(NetworkClient *network);

    private:
        IActor *_actor;
        std::vector<KeyHandler> &_keymap;
};
#endif