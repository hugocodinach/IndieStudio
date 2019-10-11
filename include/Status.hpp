/*
** EPITECH PROJECT, 2018
** Status.hpp
** File description:
** include/Status.hpp
*/

#ifndef STATUS
#define STATUS

#include <iostream>
#include <chrono>
#include <map>

#define STUN_DURATION 1

enum status_e {
    NONE,
    STUN
};

class Status
{
    public:
        Status();
        ~Status();

        void updateStatus();
        void setStatus(status_e status);

        status_e getStatus();

    private:
        std::chrono::system_clock::time_point _lastRecord;
        status_e _currentStatus;

        void updateStun();
};

#endif