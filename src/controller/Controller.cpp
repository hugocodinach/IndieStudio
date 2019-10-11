/*
** EPITECH PROJECT, 2018
** Controller.cpp
** File description:
** src/controller/Controller.cpp
*/

#include "Controller.hpp"

Controller::Controller(IActor *actor, std::vector<KeyHandler> &keymap) : _keymap(keymap)
{
    _actor = actor;
}

Controller::~Controller()
{
}

void Controller::changeActor(IActor *newActor)
{
    _actor = newActor;
}

void Controller::changeKeymap(std::vector<KeyHandler> &keymap)
{
    _keymap = keymap;
}

void Controller::callActorAction(std::vector< std::pair<KeyHandler, IActorMethodPtr> > binds, KeyHandler key, NetworkClient *network)
{
	std::vector<std::string> stt = {"FIRST", "SECOND", "THIRD", "FORTH", "FIFTH", "SIXTH"};
    for (size_t i = 0; i < binds.size(); i += 1) {
        if (binds[i].first == key) {
	//     if (network != nullptr) {
	// 	    network->action(stt[i]);
	//     }
	if (_actor->getWait() == false) {
            (_actor->*binds[i].second)();
	}
	}
    }
}

void Controller::handleControll(NetworkClient *network)
{
	//// std::cout << "CP3.710" << std::endl;
    
    if (!_actor)
        return;
	//// std::cout << "CP3.711" << std::endl;
    std::vector< std::pair<KeyHandler, IActorMethodPtr> > binds = _actor->getBinds();
	//// std::cout << "CP3.712" << std::endl;
    for (size_t i = 0; i <  _keymap.size(); i += 1)
        callActorAction(binds, _keymap[i], network);
	//// std::cout << "CP3.713" << std::endl;

}