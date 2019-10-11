/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/InterfaceServerRoom.hpp
*/

#ifndef INTERFACE_SERVER_ROOM
#define INTERFACE_SERVER_ROOM

    #include <vector>
    #include <iostream>

    #include "irr/irrlicht.h"

    #include "AInterfaceScene.hpp"
    #include "GameModule.hpp"



    class InterfaceServerRoom: public AInterfaceScene
    {
        public:

            enum SERVER_ROOM_OBJ_ID {
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
				CHAT_INPUT,
				CHAT_LIST,
				NB_PLAYER
            };

            enum SERVER_ROOM_STATU {
                PLAY_ON_THIS_COMPUTER = 0,
                LOCAL_NETWORK = 1,
                ONLINE = 2,
                DEFAULT = 3,
            };

            InterfaceServerRoom(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
            irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId, NetworkClient *servclient,
            MusicPlayer &musicPlayer, sceneInfo_t &_nextScene);
            ~InterfaceServerRoom();

			void unstackActionServe();

            void create();
            bool manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene);
            bool update(void);


			void pointerFct(std::vector<std::string> cmd);
			void room(std::vector<std::string>);
			void quit(std::vector<std::string>){};
			void log(std::vector<std::string>){};
			void chat(std::vector<std::string>);
			void infoRoom(std::vector<std::string>){};
			void createRoom(std::vector<std::string>){};
			void joinRoom(std::vector<std::string>);
			void leaveRoom(std::vector<std::string>){};
			void setUserName(std::vector<std::string>){};
			void play(std::vector<std::string>){};
			void promote(std::vector<std::string>){};

			NetworkClient *_servclient;

        private:
			typedef struct command_s {
        	    std::string cmd;
        	    void (InterfaceServerRoom::*cmd_name)(std::vector<std::string>);
        	} command_t;
            GameModule *_game;
            UISmartListBox *_serverRoom;
			int _enterInRoom;
			sceneInfo_t &_nextScene;
    };

#endif