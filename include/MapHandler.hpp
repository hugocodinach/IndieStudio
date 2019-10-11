/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/MapHandler.hpp
*/

#ifndef MAPHANDLER_HPP_
#define MAPHANDLER_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include "Bomb.hpp"
#include "Bonus.hpp"
#include "Map.hpp"
#include "scores.hpp"
#include "BlockDestruct.hpp"
#include "musicPlayer.hpp"
#include "NetworkClient.hpp"

class MapHandler
{
    public:
        MapHandler(std::vector<Bomb*> &bombs, std::vector<Bonus*> &bonus, std::vector<int> &scores);
        ~MapHandler();

        std::string zerofied(std::string entry);
        int getMapSize();
        void setMng(irr::scene::ISceneManager *smgr);
        void createWallPassMap(void);
        void setMap(FILE *mapFile);
        void setMap(void);
        std::vector<std::string> &getWallPassMap(void);
        std::vector<std::string> &getDangerMap(void);
        std::vector<std::string> &getMap(void);
        void updateMap(std::vector<BlockDestruct*> block, std::vector<int> &bombs,
            std::vector<irr::scene::IAnimatedMesh *> vect_mesh, int music,
            NetworkClient *network, bool master, MusicPlayer &, std::vector<innerBonus_t> &_innerBonus);
        void addRandomBonus(int y, int x, std::vector<irr::scene::IAnimatedMesh *> vect_mesh, NetworkClient *network, bool master, std::vector<innerBonus_t> &_innerBonus);
	void addSpecificBonus(int x, int y, Bonus::bonus_t type, std::vector<irr::scene::IAnimatedMesh *> vect_mesh);
        void display(int x, int y);
        std::string getMapForAI();

        std::vector<std::string> _map;

    private:
        std::vector<std::string> _dangerMap;
        std::vector<std::string> _wallPassMap;
        std::vector<Bomb*> &_bombs;
        std::vector<Bonus*> &_bonus;
        irr::scene::ISceneManager* _smgr;
        int _mapSize;
        std::vector<int> &_scores;
};

#endif
