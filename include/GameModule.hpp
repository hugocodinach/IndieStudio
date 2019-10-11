/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/GameModule.hpp
*/

#ifndef GAMEMODULE_HPP_
#define GAMEMODULE_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "EventManager.hpp"
#include "IGameModule.hpp"
#include "Camera.hpp"
#include "Bomberman.hpp"
#include "Controller.hpp"
#include "ActionHandler.hpp"
#include "MapHandler.hpp"
#include "BlockDestruct.hpp"
#include "TreeParticles.hpp"
#include "musicPlayer.hpp"
#include "NetworkClient.hpp"
#include "AI.hpp"
#include "SaverLoader.hpp"
#include "InterfacePlay.hpp"
#include "PodiumManager.hpp"

class InterfacePlay;

class GameModule : public IGameModule
{
    public:
        enum playerType_e {
            PLAYER_T,
            AI_T,
            ONLINE_T
        };

        typedef struct character_s {
            int characterIDX;
            int x;
            int y;
            playerType_e playerType;
            int playerIDX;
        } character_t;

        typedef struct commandGM_s {
            std::string cmd;
            bool (GameModule::*cmd_name)(std::vector<std::string>);
        } commandGM_t;

        GameModule(irr::IrrlichtDevice *device, MusicPlayer &musicPlayer);
        ~GameModule();

        void initGameModule() final;
        void drawGameModule() final;
        void drawMap(bool);
        void initPlayers();
        void initPlayers(int nbPlayer,
        std::vector<character_t> characterVect,
            std::vector<KeyHandler> P1Key,
            std::vector<KeyHandler> P2Key,
            std::vector<KeyHandler> P3Key,
            std::vector<KeyHandler> P4Key);
        void run() final;
        void playAI();
        void debugMoveCam(void);
        void startGame(void);
        void setSeed(int s);
        void initSolo(std::vector<user_info_t> users, std::vector<KeyHandler> ve1, std::vector<KeyHandler> ve2, std::vector<KeyHandler> ve3, std::vector<KeyHandler> ve4);
        void initOnline(int player, NetworkClient *network);
        void initLoad();
        void unstackActionServe();
        void gameOverScreenInit();
        void reset();
        bool pointerFct(std::vector<std::string> action);
        bool setSeedFromServ(std::vector<std::string>);
        bool doActionOnline(std::vector<std::string> action);
        bool room(std::vector<std::string>){ return true;};
        bool quit(std::vector<std::string>){ return true;};
        bool log(std::vector<std::string>){ return true;};
        bool chat(std::vector<std::string>){ return true;};
        bool infoRoom(std::vector<std::string>){ return true;};
        bool createRoom(std::vector<std::string>){ return true;};
        bool leaveRoom(std::vector<std::string>){ return true;};
        bool setUserName(std::vector<std::string>){ return true;};
        bool play(std::vector<std::string>){ return true;};
        bool promote(std::vector<std::string>){ return true;};
        bool receiveCharacter(std::vector<std::string> strVect);
        bool receiveDeath(std::vector<std::string> strVect);
        bool receiveBonus(std::vector<std::string> strVect);
        bool isOnPodium(void);
        std::vector<IActor*> &getActor(void);
        std::vector<AI*> &getAI(void);
        std::vector<Bomb*> &getBomb(void);
        std::vector<Bonus*> &getBonus(void);
        std::vector<int> &getScore(void);
        MapHandler &getMapHandler(void);
        irr::scene::ISceneManager *getSceneManager(void);
        std::vector<irr::scene::IAnimatedMesh *> getAnimatedMesh(void);
        std::vector<Controller*> &getController(void);
        EventManager *getEventManager(void);
        std::vector<character_t> &getPlayerInfo(void);
        Saver *getSave(void);
	    void setInterfacePLay(InterfacePlay *interf);

        void addScore(int);

    private:
        irr::IrrlichtDevice *_device;
        irr::video::IVideoDriver* _driver;
        irr::scene::ISceneManager* _smgr;
        int _lastFPS;
        irr::scene::ISceneNode* node;
        std::vector<irr::scene::ISceneNode*> _trees;
        Camera* _camera;
        std::vector<Controller*> _controlVect;
        EventManager* _event;
        ActionHandler* _action_handler;
        std::vector<IActor*> _vect_actor;
        MapHandler _mapHandler;
        std::vector<Bomb*> _vectBomb;
        std::vector<Bonus*> _vectBonus;
        std::vector<BlockDestruct*> _vectBlockDestruct;
        std::vector<BlockDestruct*> _vectFlames;
        std::chrono::system_clock::time_point _lastRecord;
        std::vector<AI*> _AIVect;
//        MusicPlayer *_Musicplayer;
        std::vector<irr::scene::IAnimatedMesh *> _vect_mesh;
        std::vector<int> _scores;
        Scores _score;
        bool _gameOver = false;
        bool _launchGame;
        int _seed = 0;
        NetworkClient *_network = nullptr;
        std::vector<character_t> _playersInfos;
        Saver *_saver;
        Loader *_loader;
        bool _startedGame;
	InterfacePlay *_interfacePlay;
        PodiumManager _podiumManager;
        MusicPlayer &_Musicplayer;
	std::vector<innerBonus_t> _innerBonus;
};

#endif