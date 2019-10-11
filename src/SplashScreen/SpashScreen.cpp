/*
** EPITECH PROJECT, 2018
** SpashScreen.cpp
** File description:
** src/SplashScreen/SpashScreen.cpp
*/

#include "SplashScreen.hpp"

SplashScreen::SplashScreen(irr::video::IVideoDriver *driver, irr::IrrlichtDevice *device,
irr::gui::IGUIEnvironment* guiEnv, irr::core::vector2di window_size)
{
    srand(time(NULL));
    std::vector<irr::io::path> ressources = {"./ressources/img/fireSplash.png",
    "./ressources/img/fireSplash2.png",
    "./ressources/img/fireSplash3.png",
    "./ressources/img/waterSplash.png",
    "./ressources/img/waterSplash2.png",
    "./ressources/img/waterSplash3.png",
    "./ressources/img/windSplash.png",
    "./ressources/img/windSplash2.png",
    "./ressources/img/windSplash3.png"};
    _device = device;
    _driver = driver;
    _guiEnv = guiEnv;

    _image = new UIImage(_driver, _guiEnv, -1,
    irr::core::rect<irr::f32>(0, 0, 100, 100),
    _driver->getTexture(ressources[rand()%ressources.size()]));
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::run()
{
    _lastRecord = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point neo;
    double gap = 0;

    while(_device->run() && gap < 4) {
        if (_device->isWindowActive()) {
            neo = std::chrono::system_clock::now();
            gap = std::chrono::duration<double>(neo - _lastRecord).count();
            _driver->beginScene(true, true, irr::video::SColor(255,87,206,255));
            _guiEnv->drawAll();
            _driver->endScene();
        }
    }
    _guiEnv->clear();
}