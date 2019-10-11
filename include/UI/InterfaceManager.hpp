/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/InterfaceManager.hpp
*/

#ifndef INTERFACE_MANAGER_HPP
#define INTERFACE_MANAGER_HPP

    #include "irr/irrlicht.h"

    #include <map>

    #include "IInterfaceScene.hpp"
    #include "NetworkClient.hpp"
    #include "UISmartText.hpp"
    #include "UIButton.hpp"
    #include "Key.hpp"
    #include "musicPlayer.hpp"
    #include "SplashScreen.hpp"


    class GameModule;

    class InterfaceManager
    {
        public:
        #define KB InterfaceKeyBinding::KEY_BINDING_OBJ_ID
            InterfaceManager(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
            irr::video::IVideoDriver *driver, SplashScreen splash);
            ~InterfaceManager();

            void onUIEvent(const irr::SEvent& event);
            bool changeScene(int nextSceneId);
            bool update(void);
            void launchGame(void);
            void endGame(void);

//            bool getLoadedScene(void) const;

        private:
            irr::IrrlichtDevice *_device;
            irr::gui::IGUIEnvironment *_guiEnv;
            std::map<int, IInterfaceScene *> _scene;
            IInterfaceScene *_actualScene;
            std::vector<int> _sceneStack;
            int _prevScene;
            sceneInfo_t _nextScene;
            option_t _option;
            irr::video::IVideoDriver *_driver;
            NetworkClient *_servclient;
            GameModule *_game;
            std::map<int, std::pair<std::string, KeyHandler>> _keys;
            MusicPlayer _musicPlayer;
    };

#endif