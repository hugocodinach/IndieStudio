/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/InterfaceMenu.cpp
*/

#include "InterfaceMenu.hpp"

InterfaceMenu::InterfaceMenu(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId, MusicPlayer &musicPlayer):
AInterfaceScene(device, guiEnv, driver, id, prevSceneId, musicPlayer)
{
    this->create();
    _prevStatu = -1;
    _actualStatu = MENU_STATU::DEFAULT;
    _allStatu = MENU_STATU::DEFAULT;

}

InterfaceMenu::~InterfaceMenu()
{
    // std::cout << "~InterfaceMenu" << std::endl;
}

void InterfaceMenu::create()
{
    IInterfaceObj *new_obj;

//BACKGROUND IMAGE
/*    new_obj = new UIImage(_guiEnv, computeObjId(MENU_OBJ_ID::BACKGROUND_IMAGE),
    irr::core::rect<irr::f32>(0, 0, 100, 100),
    _driver->getTexture("./ressources/UI/main/fond_test.png"));
    _objs.push_back(std::make_pair(std::vector<int>{MENU_STATU::DEFAULT}, new_obj));*/
//BACKGROUND BUTTON
    new_obj = new UIImage(_driver, _guiEnv, computeObjId(MENU_OBJ_ID::BACKGROUND_BUTTON_IMAGE),
    irr::core::rect<irr::f32>(4, 5, 35, 21),
    _driver->getTexture("./ressources/UI/main/fond_menu.png"));
    _objs.push_back(std::make_pair(std::vector<int>{MENU_STATU::DEFAULT}, new_obj));
//PLAY BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(MENU_OBJ_ID::PLAY_BUTTON),
    irr::core::rect<irr::f32>(6, 7, 33, 25),
    irr::core::rect<irr::s32>(0, 0, 540, 243),
    "sb_play",
    "./ressources/UI/main/play_idle.png",
    "./ressources/UI/main/play_over.png",
    "./ressources/UI/main/play_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{MENU_STATU::DEFAULT}, new_obj));
//BACKGROUND BUTTON
    new_obj = new UIImage(_driver, _guiEnv, computeObjId(MENU_OBJ_ID::BACKGROUND_BUTTON_IMAGE),
    irr::core::rect<irr::f32>(4, 23, 35, 39),
    _driver->getTexture("./ressources/UI/main/fond_menu.png"));
    _objs.push_back(std::make_pair(std::vector<int>{MENU_STATU::DEFAULT}, new_obj));
//MULTI BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(MENU_OBJ_ID::MULTI_BUTTON),
    irr::core::rect<irr::f32>(6, 25, 33, 47),
    irr::core::rect<irr::s32>(0, 0, 540, 222),
    "sb_multi",
    "./ressources/UI/main/multi_idle.png",
    "./ressources/UI/main/multi_over.png",
    "./ressources/UI/main/multi_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{MENU_STATU::DEFAULT}, new_obj));
//LOAD BUTTON
    std::ifstream file("./save/save.txt");

    if (file.fail() == false) {
        new_obj = new UIButton(_driver, _guiEnv, computeObjId(MENU_OBJ_ID::LOAD_BUTTON),
        irr::core::rect<irr::f32>(6, 44, 33, 67),
        irr::core::rect<irr::s32>(0, 0, 540, 300),
        "sb_multi",
        "./ressources/UI/main/load_idle.png",
        "./ressources/UI/main/load_over.png",
        "./ressources/UI/main/load_clicked.png", _musicPlayer);
        _objs.push_back(std::make_pair(std::vector<int>{MENU_STATU::DEFAULT}, new_obj));
        file.close();
    }
//SETTINGS BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(MENU_OBJ_ID::SETTINGS_BUTTON),
    irr::core::rect<irr::f32>(5, 80, 5 + 5, 80 + 9),
    irr::core::rect<irr::s32>(0, 0, 270, 300),
    "sb_settings",
    "./ressources/UI/global/settings_idle.png",
    "./ressources/UI/global/settings_over.png",
    "./ressources/UI/global/settings_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{MENU_STATU::DEFAULT}, new_obj));
//ABOUT BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(MENU_OBJ_ID::ABOUT_BUTTON),
    irr::core::rect<irr::f32>(12, 80, 12 + 5, 80 + 9),
    irr::core::rect<irr::s32>(0, 0, 512, 542),
    "sb_about",
    "./ressources/UI/global/about_idle.png",
    "./ressources/UI/global/about_over.png",
    "./ressources/UI/global/about_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{MENU_STATU::DEFAULT}, new_obj));
//QUIT BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(MENU_OBJ_ID::QUIT_BUTTON),
    irr::core::rect<irr::f32>(19, 80, 19 + 5, 80 + 9),
    irr::core::rect<irr::s32>(0, 0, 300, 300),
    "sb_play",
    "./ressources/UI/main/cross_idle.png",
    "./ressources/UI/main/cross_over.png",
    "./ressources/UI/main/cross_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{MENU_STATU::DEFAULT}, new_obj));
}

bool InterfaceMenu::manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene)
{
    int idScene = -1;
    int idObj = -1;

    if (event.EventType == irr::EET_GUI_EVENT) {
        idScene = this->getSceneFromId(event.GUIEvent.Caller->getID());
        idObj = this->getObjIdFromId(event.GUIEvent.Caller->getID());
    }
    if (idScene == UI_SCENE_ID::MENU) {
        switch (idObj) {
            case MENU_OBJ_ID::PLAY_BUTTON:
                // std::cout << "PLAY_BUTTON" << std::endl;
                buttonUpdate(event, nextScene, UI_SCENE_ID::LOCAL_LOBBY, idObj);
                break;
            case MENU_OBJ_ID::MULTI_BUTTON:
                // std::cout << "MULTI_BUTTON" << std::endl;
                buttonUpdate(event, nextScene, UI_SCENE_ID::SERVER_CONNECT, idObj);
                break;
            case MENU_OBJ_ID::SETTINGS_BUTTON:
                // std::cout << "SETTINGS_BUTTON" << std::endl;
                buttonUpdate(event, nextScene, UI_SCENE_ID::OPTION, idObj);
               break;
            case MENU_OBJ_ID::ABOUT_BUTTON:
                buttonUpdate(event, nextScene, UI_SCENE_ID::HELP, idObj);
                break;
            case MENU_OBJ_ID::LOAD_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::PLAY, idObj) == BUTTON_STATU::CLICKED) {
                    nextScene.loadGame = true;
                }
                break;
            case MENU_OBJ_ID::QUIT_BUTTON:
                buttonUpdate(event, nextScene, UI_SCENE_ID::MENU, idObj);
                break;
        }
        if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
            if (idObj == MENU_OBJ_ID::QUIT_BUTTON) {
                nextScene.sceneId = UI_SCENE_ID::QUIT;
                return (true);
            }
        }
        // std::cout << "Event in menu" << std::endl;
    }
    return false;
}

bool InterfaceMenu::update()
{
    irr::core::vector3df pos = _device->getSceneManager()->getActiveCamera()->getPosition();
    irr::core::vector3df target = _device->getSceneManager()->getActiveCamera()->getTarget();

//    // std::cout << "\nPOS: " << pos.X << " " << pos.Y << " " << pos.Z << std::endl;
//    // std::cout << "TARGET: " << target.X << " " << target.Y << " " << target.Z << std::endl;
    return true;
}