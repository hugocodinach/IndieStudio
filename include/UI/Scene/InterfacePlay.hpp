/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/InterfacePlay.hpp
*/

#ifndef INTERFACE_PLAY
#define INTERFACE_PLAY

    #include <vector>
    #include <iostream>

    #include "irr/irrlicht.h"

    #include "AInterfaceScene.hpp"
    #include "IInterfaceObj.hpp"
    #include "InterfaceManager.hpp"
    #include "GameModule.hpp"
    #include "Bonus.hpp"

    const std::vector<float> scoresPodiumPos = {
        23,
        30,
        26,
        28,
        30,
        7,
        25,
        20,
        30,
    };

    class InterfacePlay: public AInterfaceScene
    {
        public:

            enum PLAY_OBJ_ID {
                START_BUTTON = 1,
                QUIT_BUTTON = 2,
                SAVE_BUTTON = 3,
                HOME_BUTTON,
            };

            enum PLAY_STATU {
                DEFAULT = 1,
            };

            std::vector<std::pair<int, irr::io::path>> bonusesPath =
            {
                {Bonus::bonus_t::BOMB_UP, "./ressources/UI/play/bombUp.png"},
                {Bonus::bonus_t::FIRE_UP, "./ressources/UI/play/fireUp.png"},
                {Bonus::bonus_t::SPEED_UP, "./ressources/UI/play/speedUp.png"},
                {Bonus::bonus_t::WALL_PASS, "./ressources/UI/play/wallPass.png"},
                {Bonus::bonus_t::POWER_UP, "./ressources/UI/play/star.png"},
                {-1, ""},
            };

            #define BONUS_IMG_HEIGHT    (float)3.5
            #define BONUS_IMG_WIDTH    (float)2
            #define BONUS_IMG_HEIGT_OFFSET (float)0.2

            typedef struct player_ui_s {
                irr::core::position2df startPos;
                std::vector<std::pair<int, UIImage *>> bonuses;
            } player_ui_t;

            InterfacePlay(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
            irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId,
            std::vector<user_info_t> &users, GameModule *game, MusicPlayer &musicPlayer, NetworkClient* serveclient);
            ~InterfacePlay();

            void create();
            bool manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene);
            bool update(void);

            bool addBonus(int player, int bonus);
            int getNbOfBonus(int player, int bonus);
            void updateTime(int time);
            void frezzClock(void);
            void unfrezzClock(void);

        private:
            GameModule *_game;
            std::vector<user_info_t> _users;
            std::vector<player_ui_t> _usersUi;
            irr::ITimer *_timer;
            irr::u32 _timerStart;
            UISmartText _timerText;
            bool _frezzTime;
            bool _scoresCreated;
			NetworkClient* _serveclient;
    };

#endif