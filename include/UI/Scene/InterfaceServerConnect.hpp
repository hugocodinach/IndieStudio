/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/InterfaceServerConnect.hpp
*/

#ifndef INTERFACE_SERVER_CONNECT
#define INTERFACE_SERVER_CONNECT

    #include <vector>
    #include <iostream>

    #include "irr/irrlicht.h"

    #include "AInterfaceScene.hpp"

    class InterfaceServerConnect: public AInterfaceScene
    {
        public:

            enum SERVER_CONNECT_OBJ_ID {
                BACK_BUTTON,
                SETTINGS_BUTTON,
                ABOUT_BUTTON,
                BACKGROUND,
                JOIN_BUTTON,
                IP_INPUT,
                PORT_INPUT,
            };

            enum SERVER_CONNECT_STATU {
                DEFAULT,
                E_ERROR,
            };

            InterfaceServerConnect(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
            irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId, NetworkClient *servclient,
            MusicPlayer &musicPlayer);
            ~InterfaceServerConnect();

            void create();
            bool manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene);
            bool update(void);
            bool connectServer(void);

        private:
            NetworkClient *_servclient;
            int _idLastEditBoxClicked;
    };

#endif