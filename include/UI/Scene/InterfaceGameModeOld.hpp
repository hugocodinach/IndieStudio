/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/InterfaceGameMode.hpp
*/

#ifndef INTERFACE_GAME_MODE
#define INTERFACE_GAME_MODE

    #include <vector>
    #include <iostream>

    #include "irr/irrlicht.h"

    #include "AInterfaceScene.hpp"
    #include "GameModule.hpp"
//    #include "IInterfaceObj.hpp"
//    #include "InterfaceManager.hpp"


    class InterfaceGameMode: public AInterfaceScene
    {
        public:

            enum GAME_MODE_OBJ_ID {
                BACKGROUND = 1,
                LEFT_ARROW = 2,
                RIGHT_ARROW = 3,
                LIST_LEFT_ARROW = 4,
                LIST_RIGHT_ARROW = 5,
                TEXT_MODE = 6,
                MODE_MENU = 7,
                SERVER_SMART_LIST = 500,
                BACKGROUND_OPTION = 8,
                JOIN_BUTTON = 9,
                CREATE_BUTTON = 10,
                PLAYER_SELECT_TEXT,
                TWO_PLAYER_SELECT_BOX,
                THREE_PLAYER_SELECT_BOX,
                FOUR_PLAYER_SELECT_BOX,
                PLAY_BUTTON,
                BACK_BUTTON,
                SETTINGS_BUTTON,
                ABOUT_BUTTON,
            };

            enum GAME_MODE_STATU {
                PLAY_ON_THIS_COMPUTER = 0,
                LOCAL_NETWORK = 1,
                ONLINE = 2,
                ALL = 3,
            };

            InterfaceGameMode(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
            irr::video::IVideoDriver *driver, int id, int prevSceneId, NetworkClient *servclient);
            ~InterfaceGameMode();

			void unstackActionServe();

            void create();
            bool manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene);
            bool update(void);


			void pointerFct(std::vector<std::string> cmd);
			void room(std::vector<std::string>);
			void quit(std::vector<std::string>){};
			void log(std::vector<std::string>){};
			void chat(std::vector<std::string>){};
			void infoRoom(std::vector<std::string>){};
			void createRoom(std::vector<std::string>){};
			void leaveRoom(std::vector<std::string>){};
			void setUserName(std::vector<std::string>){};
			void play(std::vector<std::string>){};
			void promote(std::vector<std::string>){};

			NetworkClient *_servclient;

        private:
			typedef struct command_s {
        	    std::string cmd;
        	    void (InterfaceGameMode::*cmd_name)(std::vector<std::string>);
        	} command_t;
            GameModule *_game;
    };

#endif