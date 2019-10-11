/*
** EPITECH PROJECT, 2018
** IntrfaceHelp.hpp
** File description:
** include/UI/Scene/IntrfaceHelp.hpp
*/

#ifndef INTERFACE_HELP
#define INTERFACE_HELP

#include <vector>
#include <iostream>

#include "irr/irrlicht.h"
#include "AInterfaceScene.hpp"

class InterfaceHelp: public AInterfaceScene {
    public:
        InterfaceHelp(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
            irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId,
            MusicPlayer &musicPlayer);
        ~InterfaceHelp();

        enum OPTION_OBJ_ID {
            BACK_BUTTON,
            NONE = -1,
        };

        enum OPTION_STATU {
            DEFAULT = 1,
        };

        void create();
        bool manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene);
        bool update(void);

    private:
};

#endif