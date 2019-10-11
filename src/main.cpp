/*
** EPITECH PROJECT, 2018
** main.cpp
** File description:
** src/main.cpp
*/

#include <irr/irrlicht.h>
#include "EventManager.hpp"
#include "UIButton.hpp"
#include "InterfaceManager.hpp"
#include "NetworkClient.hpp"

int MUSIC = 0;
irr::core::array<irr::SJoystickInfo> myjoystickInfo;

enum
{
    GUI_ID_QUIT_BUTTON = 101,
    GUI_ID_NEW_WINDOW_BUTTON,
    GUI_ID_FILE_OPEN_BUTTON,
    GUI_ID_TRANSPARENCY_SCROLL_BAR
};



int main(void)
{
   srand(1234);
   #ifdef _WIN32
        irr::IrrlichtDevice *device =
        irr::createDevice(irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(1920, 1080), 16,
        false, false, true, 0);
    #elif __linux__
        irr::IrrlichtDevice *device =
        irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080), 16,
        false, false, true, 0);
    #else
    #endif

    if (!device)
        return 1;
    device->setWindowCaption(L"Indie Studio");
    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    SplashScreen splashScreen(driver, device, guienv, irr::core::vector2di(1280, 720));

    InterfaceManager *elManagor = new InterfaceManager(device, guienv, driver, splashScreen);
    EventManager *event_manager = new EventManager(elManagor);
    device->setEventReceiver(event_manager);
    elManagor->launchGame();

/*	IGUISkin* skin = guienv->getSkin();
    IGUIFont* font = guienv->getFont("/home/fugulen/irrlicht-1.8.4/media/fonthaettenschweiler.bmp");
    if (font)
        skin->setFont(font);

    skin->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);*/
    device->activateJoysticks(myjoystickInfo);
	int lastFPS = -1;
    while(device->run())
    if (device->isWindowActive()) {
        driver->beginScene(true, true, irr::video::SColor(255,87,206,255));
        elManagor->update();
        guienv->drawAll();
        driver->endScene();
		int fps = driver->getFPS();

        if (lastFPS != fps)
        {
            irr::core::stringw str = L" [";
            str += driver->getName();
            str += "] FPS:";
            str += fps;

            device->setWindowCaption(str.c_str());
            lastFPS = fps;
        }
    }
    device->drop();
    return 0;
}