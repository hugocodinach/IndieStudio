/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/SaverLoader.hpp
*/

#include "GameModule.hpp"

class Saver
{
    public:
        Saver();
        ~Saver();

        void saveMap(MapHandler &mapHandler, std::ofstream &file);
        void saveBomber(std::vector<IActor*> &vectActor, std::ofstream &file);
        void saveAI(std::vector<AI*> &vectAI, std::ofstream &file);
        void saveBomb(std::vector<Bomb*> &vectBomb, std::ofstream &file);
        void saveBonus(std::vector<Bonus*> &vectBonus, std::ofstream &file);
        void saveScore(std::vector<int> &score, std::ofstream &file);
        void savePlayerInfo(GameModule *gameModule, std::ofstream &file);
        void saveGameModule(GameModule *gameModule);
};

class Loader
{
    public:
        Loader();
        ~Loader();

        void loadMap(MapHandler &mapHandler, std::ifstream &file);
        void loadBomber(GameModule *gameModule, std::ifstream &file);
        void loadAI(GameModule *gameModule, std::ifstream &file);
        void loadBomb(GameModule *gameModule, std::ifstream &file);
        void loadBonus(GameModule *gameModule, std::ifstream &file);
        void loadScore(GameModule *gameModule, std::ifstream &file);
        void loadPlayerInfo(GameModule *gameModule, std::ifstream &file);
        void loadGameModule(GameModule *gameModule);
};