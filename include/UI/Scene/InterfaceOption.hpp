/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/InterfaceOption.hpp
*/

#ifndef INTERFACE_OPTION
#define INTERFACE_OPTION

    #include <vector>
    #include <iostream>

    #include "irr/irrlicht.h"

    #include "AInterfaceScene.hpp"
    #include "IInterfaceObj.hpp"
    #include "InterfaceManager.hpp"


    class InterfaceOption: public AInterfaceScene
    {
        public:

            enum OPTION_OBJ_ID {
                BACK_BUTTON,
                QUIT_BUTTON,
                KEY_BINDING_BUTTON,
                SETTINGS_BUTTON,
                ABOUT_BUTTON,
                VOLUME_MUSIC_LEFT_BUTTON,
                VOLUME_MUSIC_RIGHT_BUTTON,
                VOLUME_MUSIC_IMAGE,
                VOLUME_MUSIC_LIST,
                VOLUME_SOUND_LEFT_BUTTON,
                VOLUME_SOUND_RIGHT_BUTTON,
                VOLUME_SOUND_IMAGE,
                VOLUME_SOUND_LIST,
                RESOLUTION_LEFT_BUTTON,
                RESOLUTION_RIGHT_BUTTON,
                RESOLUTION_TEXT,
                COIN_MODE_BUTTON,
                
                NONE = -1,
            };

            enum OPTION_STATU {
                DEFAULT = 1,
            };

            InterfaceOption(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
            irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId,
            MusicPlayer &musicPlayer, option_t &option);
            ~InterfaceOption();

            void create();
            bool manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene);
            bool update(void);

        private:
            option_t &_option;
            UIButton *coinModeButton;
            UILateralMenu *_musicVolumeObj;
            UILateralMenu *_musicSoundObj;
            UILateralText *_resolutionObj;
            int _musicVolume;
            int _soundVolume;
            int _maxVolume;
    };

#endif