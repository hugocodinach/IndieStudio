/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/InterfaceMenu.hpp
*/

#ifndef INTERFACE_MENU
#define INTERFACE_MENU

    #include <vector>
    #include <iostream>

    #include "irr/irrlicht.h"

    #include "AInterfaceScene.hpp"
    #include "IInterfaceObj.hpp"
    #include "InterfaceManager.hpp"


    class InterfaceMenu: public AInterfaceScene
    {
        public:

            enum MENU_OBJ_ID {
                PLAY_BUTTON = 1,
                MULTI_BUTTON = 2,
                SETTINGS_BUTTON = 3,
                ABOUT_BUTTON = 4,
                QUIT_BUTTON = 5,
                BACKGROUND_IMAGE = 6,
                BACKGROUND_BUTTON_IMAGE = 7,
                VERSION_TEXT = 8,
                LOAD_BUTTON = 9,
            };

            enum MENU_STATU {
                DEFAULT = 1,
            };

            InterfaceMenu(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
            irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId,
            MusicPlayer &musicPlayer);
            ~InterfaceMenu();

            void create();
            bool manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene);
            bool update(void);

        private:
    };

#endif