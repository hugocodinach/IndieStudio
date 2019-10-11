/*
** EPITECH PROJECT, 2018
** SplashScreen.hpp
** File description:
** include/SplashScreen.hpp
*/

#ifndef SPLASH_SCREEN
#define SPLASH_SCREEN

#include <iostream>
#include <vector>
#include <chrono>
#include <irr/irrlicht.h>

#include "UIImage.hpp"

class SplashScreen {
    public:
        SplashScreen(irr::video::IVideoDriver *, irr::IrrlichtDevice *,
        irr::gui::IGUIEnvironment *, irr::core::vector2di);
        ~SplashScreen();

        void run();

    private:
        irr::video::IVideoDriver *_driver;
        irr::IrrlichtDevice *_device;
        irr::gui::IGUIEnvironment* _guiEnv;
        UIImage *_image;
        std::chrono::system_clock::time_point _lastRecord;
};

#endif