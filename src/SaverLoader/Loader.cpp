/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/SaverLoader/Loader.cpp
*/

#include <boost/algorithm/string.hpp>
#include "GameModule.hpp"

Loader::Loader()
{
}

Loader::~Loader()
{
}

void Loader::loadMap(MapHandler &mapHandler, std::ifstream &file)
{
    std::string tmp;
    std::vector<std::string> tmpTab;

    mapHandler.getMap().clear();
    while (std::getline(file, tmp)) {
        tmpTab.clear();
        boost::split(tmpTab, tmp, boost::is_any_of(" "));
        if (tmpTab[0].compare("BomberList") == 0)
            return;
        mapHandler.getMap().push_back(tmp);
    }
}

void Loader::loadScore(GameModule *gameModule, std::ifstream &file)
{
    std::string tmp;
    std::vector<std::string> tmpTab;

    gameModule->getScore().clear();
    while (std::getline(file, tmp)) {
        tmpTab.clear();
        boost::split(tmpTab, tmp, boost::is_any_of(" "));
        if (tmpTab[0].compare("Infos") == 0)
            return;
        gameModule->getScore().push_back(atoi(tmp.c_str()));
    }
}

void Loader::loadPlayerInfo(GameModule *gameModule, std::ifstream &file)
{
    std::string tmp;
    std::vector<std::string> tmpTab;

    gameModule->getPlayerInfo().clear();
    while (std::getline(file, tmp)) {
        tmpTab.clear();
        boost::split(tmpTab, tmp, boost::is_any_of(" "));
        gameModule->getPlayerInfo().push_back({std::atoi(tmpTab[1].c_str()), 0, 0, GameModule::playerType_e::PLAYER_T, std::atoi(tmpTab[0].c_str())});
    }
}

void Loader::loadBonus(GameModule *gameModule, std::ifstream &file)
{
    std::string tmp;
    std::vector<std::string> tmpTab;
    irr::scene::ISceneNode *node;

    gameModule->getBonus().clear();
    while (std::getline(file, tmp)) {
        tmpTab.clear();
        boost::split(tmpTab, tmp, boost::is_any_of(" "));
        if (tmpTab[0].compare("Scores") == 0)
            return;
        if (tmpTab[3].compare("2") == 0)
            node = gameModule->getSceneManager()->addMeshSceneNode(gameModule->getAnimatedMesh()[3] ,0);
        else if (tmpTab[3].compare("1") == 0)
            node = gameModule->getSceneManager()->addMeshSceneNode(gameModule->getAnimatedMesh()[4] ,0);
        else if (tmpTab[3].compare("0") == 0)
            node = gameModule->getSceneManager()->addMeshSceneNode(gameModule->getAnimatedMesh()[5] ,0);
        else if (tmpTab[3].compare("3") == 0)
            node = gameModule->getSceneManager()->addMeshSceneNode(gameModule->getAnimatedMesh()[6] ,0);
        else
            node = gameModule->getSceneManager()->addMeshSceneNode(gameModule->getAnimatedMesh()[7] ,0);
        node->setPosition(irr::core::vector3df(-300 + (std::atoi(tmpTab[2].c_str()) * TILE_SIZE), 0, -300 + (std::atoi(tmpTab[1].c_str()) * TILE_SIZE)));
        node->getMaterial(0).NormalizeNormals = true;
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        gameModule->getBonus().push_back(new Bonus(irr::core::vector3df(std::atoi(tmpTab[1].c_str()), 0, std::atoi(tmpTab[2].c_str())), node, static_cast<Bonus::bonus_t>(std::atoi(tmpTab[3].c_str()))));
    }
}

void Loader::loadBomb(GameModule *gameModule, std::ifstream &file)
{
    std::string tmp;
    std::vector<std::string> tmpTab;
    irr::scene::ISceneNode *node;

    gameModule->getBomb().clear();
    while (std::getline(file, tmp)) {
        tmpTab.clear();
        if (boost::split(tmpTab, tmp, boost::is_any_of(" "))[0].compare("BonusList") == 0)
            return;
        node = gameModule->getSceneManager()->addMeshSceneNode(gameModule->getAnimatedMesh()[2], 0);
        node->setPosition(irr::core::vector3df(-300 + (std::atoi(tmpTab[3].c_str()) * TILE_SIZE), 0, -300 + (std::atoi(tmpTab[2].c_str()) * TILE_SIZE)));
        node->getMaterial(0).NormalizeNormals = true;
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        gameModule->getBomb().push_back(new Bomb(irr::core::vector3df(std::atoi(tmpTab[2].c_str()), 0, std::atoi(tmpTab[3].c_str())), node, std::atoi(tmpTab[4].c_str()), std::atoi(tmpTab[1].c_str())));
        gameModule->getBomb()[gameModule->getBomb().size() - 1]->setRemainingTime(std::atoi(tmpTab[5].c_str()));
    }
}

void Loader::loadAI(GameModule *gameModule, std::ifstream &file)
{
    std::string tmp;
    std::vector<std::string> tmpTab;

    gameModule->getAI().clear();
    while (std::getline(file, tmp)) {
        tmpTab.clear();
        if (boost::split(tmpTab, tmp, boost::is_any_of(" "))[0].compare("BombList") == 0)
            return;
        for (int i = 0; i < gameModule->getActor().size(); i += 1) {
            if (gameModule->getActor()[i]->getId() == std::atoi(tmpTab[1].c_str())) {
                gameModule->getAI().push_back(new AI(dynamic_cast<Bomberman*>(gameModule->getActor()[i]), gameModule->getController()[i], gameModule->getEventManager()->getKeyVect()));
                break;
            }
        }
    }
}

void Loader::loadBomber(GameModule *gameModule, std::ifstream &file)
{
    std::string tmp;
    std::vector<std::string> tmpTab;

    gameModule->getActor().clear();
    gameModule->getController().clear();
    while (std::getline(file, tmp)) {
        tmpTab.clear();
        boost::split(tmpTab, tmp, boost::is_any_of(" "));
        if (tmpTab[0].compare("AIList") == 0)
            return;
        gameModule->getActor().push_back(new Bomberman(gameModule->getSceneManager(), irr::core::vector3df(-300 + (std::atoi(tmpTab[2].c_str()) * TILE_SIZE), 0, -300 + (std::atoi(tmpTab[1].c_str()) * TILE_SIZE)), std::atoi(tmpTab[1].c_str()), std::atoi(tmpTab[2].c_str()), std::atoi(tmpTab[0].c_str()), gameModule->getAnimatedMesh(), std::atoi(tmpTab[7].c_str())));
        gameModule->getActor()[gameModule->getActor().size() - 1]->setActualBombs(std::atoi(tmpTab[5].c_str()));
        gameModule->getActor()[gameModule->getActor().size() - 1]->setMaxBombs(std::atoi(tmpTab[4].c_str()));
        gameModule->getActor()[gameModule->getActor().size() - 1]->setRange(std::atoi(tmpTab[3].c_str()));
        gameModule->getActor()[gameModule->getActor().size() - 1]->setStatus(std::atoi(tmpTab[6].c_str()));
        for (int i = 0; i < 6; i += 1) {
            if (!std::getline(file, tmp))
                return;
            tmpTab.clear();
            boost::split(tmpTab, tmp, boost::is_any_of(" "));
            gameModule->getActor()[gameModule->getActor().size() - 1]->setInput(i, KeyHandler(std::atoi(tmpTab[0].c_str()), std::atoi(tmpTab[1].c_str())));
        }
        gameModule->getController().push_back(new Controller(dynamic_cast<Bomberman*>(gameModule->getActor()[gameModule->getActor().size() - 1]), gameModule->getEventManager()->getKeyVect()));
    }
}

void Loader::loadGameModule(GameModule *gameModule)
{
    std::ifstream file("./save/save.txt");

    if (file.fail())
        return;
    loadMap(gameModule->getMapHandler(), file);
    loadBomber(gameModule, file);
    loadAI(gameModule, file);
    loadBomb(gameModule, file);
    loadBonus(gameModule, file);
    loadScore(gameModule, file);
    loadPlayerInfo(gameModule, file);
    file.close();
}