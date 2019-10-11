/*
** EPITECH PROJECT, 2018
** Status.cpp
** File description:
** src/Status/Status.cpp
*/

#include "Status.hpp"

Status::Status()
{
    _currentStatus = NONE;
}

Status::~Status()
{
}

void Status::updateStatus()
{
    void (Status::*ptr[])(void) = {nullptr, &Status::updateStun};

    if (_currentStatus == NONE)
        return;
    (this->*ptr[_currentStatus])();
}

void Status::setStatus(status_e status)
{
    _currentStatus = status;
    _lastRecord = std::chrono::system_clock::now();
}

status_e Status::getStatus()
{
    return _currentStatus;
}

void Status::updateStun(void)
{
    std::chrono::system_clock::time_point neo = std::chrono::system_clock::now();
    double tmp = std::chrono::duration<double>(neo - _lastRecord).count();

    if (tmp > STUN_DURATION)
        _currentStatus = NONE;
}