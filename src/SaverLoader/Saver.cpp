/*
** EPITECH PROJECT, 2018
** ActionHandler.cpp
** File description:
** src/SaverLoader/SaverLoader.cpp
*/

#include "GameModule.hpp"

Saver::Saver()
{
}

Saver::~Saver()
{
}

void Saver::saveMap(MapHandler &mapHandler, std::ofstream &file)
{
    for (int i = 0; i < mapHandler.getMap().size(); i += 1) {
        file << mapHandler.getMap()[i] << std::endl;
    }
}

void Saver::saveScore(std::vector<int> &score, std::ofstream &file)
{
    file << "Scores" << std::endl;
    for (int i = 0; i < score.size(); i += 1) {
        file << score[i] << std::endl;
    }
}

void Saver::savePlayerInfo(GameModule *gameModule, std::ofstream &file)
{
    std::vector<GameModule::character_t> &character = gameModule->getPlayerInfo();

    file << "Infos" << std::endl;
    for (int i = 0; i < character.size(); i += 1) {
        file << character[i].playerIDX << " " << character[i].characterIDX << std::endl;
    }
}

void Saver::saveBonus(std::vector<Bonus*> &vectBonus, std::ofstream &file)
{
    file << "BonusList" << std::endl;
    for (int i = 0; i < vectBonus.size(); i += 1) {
        file << "Bonus " << vectBonus[i]->getPosition().X << " " << vectBonus[i]->getPosition().Z << " " << vectBonus[i]->getType() << std::endl;
    }
}

void Saver::saveBomb(std::vector<Bomb*> &vectBomb, std::ofstream &file)
{
    file << "BombList" << std::endl;
    for (int i = 0; i < vectBomb.size(); i += 1) {
        file << "Bomb " << vectBomb[i]->getMasterId() << " " << vectBomb[i]->getPosition().X << " " << vectBomb[i]->getPosition().Z << " " << vectBomb[i]->getRange() << " " << vectBomb[i]->getRemainingTime() << std::endl;
    }
}

void Saver::saveAI(std::vector<AI*> &vectAI, std::ofstream &file)
{
    file << "AIList" << std::endl;
    for (int i = 0; i < vectAI.size(); i += 1) {
        file << "AI " << vectAI[i]->getBomberman()->getId() << std::endl;
    }
}

void Saver::saveBomber(std::vector<IActor*> &vectActor, std::ofstream &file)
{
    file << "BomberList" << std::endl;
    for (int i = 0; i < vectActor.size(); i += 1) {
        file << vectActor[i]->getId() << " " << vectActor[i]->getCoord().x << " " << vectActor[i]->getCoord().y << " " << vectActor[i]->getRange() << " " << vectActor[i]->getMaxBomb() << " " << vectActor[i]->getBombs() << " " << static_cast<int>(vectActor[i]->getStatus()) << " " << vectActor[i]->getCharacterIDX() << std::endl;
        file << vectActor[i]->getBinds()[0].first.getKey() << " " << static_cast<int>(vectActor[i]->getBinds()[0].first.getType()) << std::endl;
        file << vectActor[i]->getBinds()[1].first.getKey() << " " << static_cast<int>(vectActor[i]->getBinds()[1].first.getType()) << std::endl;
        file << vectActor[i]->getBinds()[2].first.getKey() << " " << static_cast<int>(vectActor[i]->getBinds()[2].first.getType()) << std::endl;
        file << vectActor[i]->getBinds()[3].first.getKey() << " " << static_cast<int>(vectActor[i]->getBinds()[3].first.getType()) << std::endl;
        file << vectActor[i]->getBinds()[4].first.getKey() << " " << static_cast<int>(vectActor[i]->getBinds()[4].first.getType()) << std::endl;
        file << vectActor[i]->getBinds()[5].first.getKey() << " " << static_cast<int>(vectActor[i]->getBinds()[5].first.getType()) << std::endl;
    }
}

void Saver::saveGameModule(GameModule *gameModule) 
{
    std::ofstream file("./save/save.txt", std::ios::trunc);

    if (file.fail())
        return;
    saveMap(gameModule->getMapHandler(), file);
    saveBomber(gameModule->getActor(), file);
    saveAI(gameModule->getAI(), file);
    saveBomb(gameModule->getBomb(), file);
    saveBonus(gameModule->getBonus(), file);
    saveScore(gameModule->getScore(), file);
    savePlayerInfo(gameModule, file);
    file.close();
}