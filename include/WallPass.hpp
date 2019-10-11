/*
** EPITECH PROJECT, 2018
** WallPass.hpp
** File description:
** include/WallPass.hpp
*/

#ifndef WALLPASS
#define WALLPASS

#include <iostream>
#include <chrono>

class WallPass
{
    public:
        WallPass();
        ~WallPass();

        void update();
        void reset();

        bool isActivated();

    private:
        std::chrono::system_clock::time_point _lastRecord;
        int _duration;
        bool _activated;
};

#endif