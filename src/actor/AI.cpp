/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/actor/IA.cpp
*/

#include "AI.hpp"

AI::AI(Bomberman *bomber, Controller *controller, std::vector<KeyHandler> &keyVect): _bomberman(bomber), _controller(controller), _keyVect(keyVect)
{
};

AI::~AI() {};

std::string AI::getActorsPos(std::vector<IActor*> actorList)
{
    std::string str;
    for (IActor * act: actorList) {
        if (act != _bomberman)
            str += " " + std::to_string(act->getCoord().x) + " " + std::to_string(act->getCoord().y) + " " ;
    }
    return (str);
}

void AI::executeCommand(std::string command)
{
    std::string tmp;

    #ifdef _WIN32
        FILE *file = _popen(command.c_str(), "r");
        std::string endline("\r");
    #elif __linux__
        FILE *file = popen(command.c_str(), "r");
        std::string endline("");
    #else
    #endif

    if (file == nullptr) {
        perror("Popen le S:");
        _busy = false;
        return;
    }
    boost::iostreams::file_descriptor_source convertFd(fileno(file), boost::iostreams::close_handle);
    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_source> fdToStream(convertFd);
    std::istream stream(&fdToStream);
    std::getline(stream, tmp);
    if (tmp.compare("Left" + endline) == 0) {
        if (_bomberman != nullptr)
            _keyVect.push_back(_bomberman->getBinds()[0].first);
    } else if (tmp.compare("Right" + endline) == 0) {
        if (_bomberman != nullptr)
            _keyVect.push_back(_bomberman->getBinds()[2].first);
    } else if (tmp.compare("Up" + endline) == 0) {
        if (_bomberman != nullptr)
            _keyVect.push_back(_bomberman->getBinds()[3].first);
    } else if (tmp.compare("Down" + endline) == 0) {
        if (_bomberman != nullptr)
            _keyVect.push_back(_bomberman->getBinds()[1].first);
    } else if (tmp.compare("Bomb" + endline) == 0) {
        if (_bomberman != nullptr)
            _keyVect.push_back(_bomberman->getBinds()[4].first);
    } else if (tmp.compare("Special" + endline) == 0) {
        if (_bomberman != nullptr)
            _keyVect.push_back(_bomberman->getBinds()[5].first);
    } else if (tmp.compare("Stay" + endline) == 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds((800)));
    }
    #ifdef _WIN32
        _pclose(file);
    #elif __linux__
        pclose(file);
    #else
    #endif
    _busy = false;
}

void AI::play(std::vector<IActor*> &actorList, std::string map, char pos)
{
    _busy = true;
    std::string command;
    std::string wallPass = "0";
    std::string power = "-1";
    std::string direction = std::to_string(_bomberman->getDirection());

    if (getBomberman()->getWallPass() == true || pos == '1')
        wallPass = "1";
    if (_bomberman->hasPower() == true)
        power = std::to_string(static_cast<int>(_bomberman->getType()));

    #ifdef _WIN32
        command = "rub.exe ./script/AIEasy.rb " + map + " " + std::to_string(_bomberman->getRange()) + " " + wallPass + " " + power + " " + direction + " " + std::to_string(_bomberman->getCoord().x) + " " + std::to_string(_bomberman->getCoord().y) + " " + getActorsPos(actorList);
    #elif __linux__
        command = "./rub ./script/AIEasy.rb " + map + " " + std::to_string(_bomberman->getRange()) + " " + wallPass + " " + power + " " + direction + " " + std::to_string(_bomberman->getCoord().x) + " " + std::to_string(_bomberman->getCoord().y) + " " + getActorsPos(actorList);
    #else
    #endif
    if (_activeThread.size() != 0) {
        _activeThread.begin()->join();
        _activeThread.clear();
    }
    _activeThread.push_back(std::thread([this, command](){this->executeCommand(command);}));
}

bool AI::isBusy()
{
    std::unique_lock<std::mutex> lock(_mut);

    if (_bomberman->getActionsToDo().size() == 0 && _busy == false)
        return (false);
    return (true);
}

Bomberman *AI::getBomberman() {
    std::unique_lock<std::mutex> lock(_mut);

    return (_bomberman);
}