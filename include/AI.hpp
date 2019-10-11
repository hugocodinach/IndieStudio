/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/AI.hpp
*/

#ifndef AI_HPP_
#define AI_HPP_

#include <mutex>
#include <cstdio>
#include <string>
#include <thread>
#include <iostream>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include "Bomberman.hpp"
#include "Controller.hpp"
#include "errno.h"

class AI
{
    public:
        AI(Bomberman *bomber, Controller *controller, std::vector<KeyHandler> &keyVect);
        ~AI();

        std::string getActorsPos(std::vector<IActor*> actorList);

        void executeCommand(std::string command);
        void play(std::vector<IActor*> &actorList, std::string map, char pos);
        bool isBusy();
        Bomberman *getBomberman();

    private:
        Bomberman *_bomberman;
        Controller *_controller;
        std::vector<KeyHandler> &_keyVect;
        std::chrono::system_clock::time_point _lastRecord;
        std::mutex _mut;
        std::vector<std::thread> _activeThread;
        bool _busy = false;
};

#endif