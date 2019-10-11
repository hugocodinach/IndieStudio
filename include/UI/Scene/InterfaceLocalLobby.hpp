/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/InterfaceLocalLobby.hpp
*/

#ifndef INTERFACE_LOBBY
#define INTERFACE_LOBBY

    #include <vector>
    #include <iostream>

    #include "irr/irrlicht.h"

    #include "AInterfaceScene.hpp"
    #include "IInterfaceObj.hpp"
    #include "InterfaceManager.hpp"
    #include "PersSelection.hpp"

    class InterfaceLocalLobby: public AInterfaceScene
    {
        public:

            enum LOCAL_LOBBY_OBJ_ID { 
                BACK_BUTTON,
                SETTINGS_BUTTON,
                ABOUT_BUTTON,

                TITLE_TEXT,

                SERVER_SMART_LIST,
                LEFT_ARROW,

                LEFT_ARROW_P1,
                RIGHT_ARROW_P1,
                LEFT_ARROW_CHAR_P1,
                RIGHT_ARROW_CHAR_P1,
                LIST_P1,
                PSEUDO_P1,

                LEFT_ARROW_P2,
                RIGHT_ARROW_P2,
                LEFT_ARROW_CHAR_P2,
                RIGHT_ARROW_CHAR_P2,
                LIST_P2,
                PSEUDO_P2,

                LEFT_ARROW_P3,
                RIGHT_ARROW_P3,
                LEFT_ARROW_CHAR_P3,
                RIGHT_ARROW_CHAR_P3,
                LIST_P3,
                PSEUDO_P3,

                LEFT_ARROW_P4,
                RIGHT_ARROW_P4,
                LEFT_ARROW_CHAR_P4,
                RIGHT_ARROW_CHAR_P4,
                LIST_P4,
                PSEUDO_P4,

                START_BUTTON,
            };

            enum LOCAL_LOBBY_STATU {
                DEFAULT = 1,
            };

            InterfaceLocalLobby(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
            irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId,
            MusicPlayer &musicPlayer);
            ~InterfaceLocalLobby();

            void create();
            bool manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene);
            bool update(void);
            bool isThereEnoughPlayers(void);

            void serializeUsersInfos(sceneInfo_t &nextScene);

        private:
            std::string clearPseudo(std::string pseudo);

            typedef struct command_s {
                std::string cmd;
                void (InterfaceLocalLobby::*cmd_name)(std::vector<std::string>);
            } command_t;

            std::vector<user_info_t> _userInfo;
            RotatingMeshes _characterPreview;
    };

#endif