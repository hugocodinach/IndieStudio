/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/InterfaceServerLobby.hpp
*/

#ifndef INTERFACE_SERVER_LOBBY
#define INTERFACE_SERVER_LOBBY

    #include <vector>
    #include <iostream>

    #include "irr/irrlicht.h"

    #include "AInterfaceScene.hpp"
    #include "IInterfaceObj.hpp"
    #include "InterfaceManager.hpp"
    #include "GameModule.hpp"

    class InterfaceServerLobby: public AInterfaceScene
    {
        public:

            typedef struct user_info_extended_s {
                std::string username;
                UISmartText *usernameTextObj;
                UISmartText *statuTextObj;
                int characterId;
                bool isReady;
                int statu;
            } user_info_extended_t;

            enum SERVER_LOBBY_OBJ_ID { 
                BACK_BUTTON,
                SETTINGS_BUTTON,
                ABOUT_BUTTON,

                TITLE_TEXT,

                SERVER_SMART_LIST,
                LEFT_ARROW,

                STATU_P1,
                PSEUDO_P1,
                LEFT_ARROW_CHAR_P1,
                RIGHT_ARROW_CHAR_P1,

                STATU_P2,
                PSEUDO_P2,
                LEFT_ARROW_CHAR_P2,
                RIGHT_ARROW_CHAR_P2,

                STATU_P3,
                PSEUDO_P3,
                LEFT_ARROW_CHAR_P3,
                RIGHT_ARROW_CHAR_P3,

                STATU_P4,
                PSEUDO_P4,
                LEFT_ARROW_CHAR_P4,
                RIGHT_ARROW_CHAR_P4,

                READY_BUTTON,
                START_BUTTON,
            };

            enum SERVER_LOBBY_STATU {
                DEFAULT = 1,
            };

            InterfaceServerLobby(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
            irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId, NetworkClient *_servclient,
            MusicPlayer &musicPlayer, sceneInfo_t &nextScene);
            ~InterfaceServerLobby();

            void create();
            bool manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene);
            bool update(void);


            void pointerFct(std::vector<std::string> cmd);
            void room(std::vector<std::string>){};
            void quit(std::vector<std::string>){};
            void log(std::vector<std::string>){};
            void chat(std::vector<std::string>){};
            void infoRoom(std::vector<std::string>);
            void createRoom(std::vector<std::string>){};
            void leaveRoom(std::vector<std::string>){};
            void setUserName(std::vector<std::string>){};
            void play(std::vector<std::string>){};
            void game(std::vector<std::string>);
            void promote(std::vector<std::string>){};

			void verifUpdateCharacter();
            void serializeUsersInfos(sceneInfo_t &nextScene);
            void unstackActionServe();

        private:
            std::string clearPseudo(std::string pseudo);

            NetworkClient *_serverClient;

            typedef struct command_s {
                std::string cmd;
                void (InterfaceServerLobby::*cmd_name)(std::vector<std::string>);
            } command_t;
            std::vector<user_info_extended_t> _userInfo;
            UIButton *_readyButton;
            bool _isReady;
            GameModule *_gameModule;
            int _idxLocalPlayer;
			int _lastCharacter;
            RotatingMeshes _characterPreview;
			sceneInfo_t &_nextScene;
    };

#endif