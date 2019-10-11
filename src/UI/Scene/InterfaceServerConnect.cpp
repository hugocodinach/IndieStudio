/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/InterfaceServerConnect.cpp
*/

#include "InterfaceServerConnect.hpp"

InterfaceServerConnect::InterfaceServerConnect(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId, NetworkClient *servclient,
MusicPlayer &musicPlayer):
AInterfaceScene(device, guiEnv, driver, id, prevSceneId, musicPlayer)
{
    this->create();
    _prevStatu = -1;
    _allStatu = SERVER_CONNECT_STATU::DEFAULT;
    _actualStatu = SERVER_CONNECT_STATU::DEFAULT;
    _servclient = servclient;
    _idLastEditBoxClicked = -1;
    // std::cout << "PAZANI" << std::endl;
    servclient->getMyIp();
}

InterfaceServerConnect::~InterfaceServerConnect()
{
    // std::cout << "~InterfaceGameMode" << std::endl;
}

void InterfaceServerConnect::create()
{
    IInterfaceObj *new_obj;
    UISmartText *smart_text;

//BACK ARROW
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_CONNECT_OBJ_ID::BACK_BUTTON),
    irr::core::rect<irr::f32>(3, 5, 3 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 630, 630),
    "sb_back_arrow",
    "./ressources/UI/global/back_arrow_idle.png",
    "./ressources/UI/global/back_arrow_hover.png",
    "./ressources/UI/global/back_arrow_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_CONNECT_STATU::DEFAULT}, new_obj));
//SETTINGS BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_CONNECT_OBJ_ID::SETTINGS_BUTTON),
    irr::core::rect<irr::f32>(85, 5, 85 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 270, 300),
    "sb_settings",
    "./ressources/UI/global/settings_idle.png",
    "./ressources/UI/global/settings_over.png",
    "./ressources/UI/global/settings_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_CONNECT_STATU::DEFAULT}, new_obj));
//ABOUT BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_CONNECT_OBJ_ID::ABOUT_BUTTON),
    irr::core::rect<irr::f32>(90, 5, 90 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 512, 542),
    "sb_about",
    "./ressources/UI/global/about_idle.png",
    "./ressources/UI/global/about_over.png",
    "./ressources/UI/global/about_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_CONNECT_STATU::DEFAULT}, new_obj));
//GAME MODE OPTION BACKGROUND
    new_obj = new UIImage(_driver, _guiEnv, computeObjId(SERVER_CONNECT_OBJ_ID::BACKGROUND),
    irr::core::rect<irr::f32>(30, 22, 63, 77),
    _driver->getTexture("./ressources/UI/main/fond_menu_binding.png"));
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_CONNECT_STATU::DEFAULT}, new_obj));
//TITLE TEXT
    new_obj = new UISmartText(_driver, _guiEnv, -1,
    "CHOSE SERVER", irr::core::position2df(33, 16), cptFontSize(44));
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_CONNECT_STATU::DEFAULT}, new_obj));
//SUBTITLE TEXT
    new_obj = new UISmartText(_driver, _guiEnv, -1,
    "SERVER IP :", irr::core::position2df(38, 30), cptFontSize(36));
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_CONNECT_STATU::DEFAULT}, new_obj));
//INPUT IP
    new_obj = new UIEditBox(_driver, _guiEnv, computeObjId(SERVER_CONNECT_OBJ_ID::IP_INPUT),
    "./ressources/UI/main/fond_menu.png", "Enter server ip",
    irr::core::rect<irr::f32>(35, 35, 58, 35 + 5), irr::core::position2df(36.5, 36.5), cptFontSize(20), 19);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_CONNECT_STATU::DEFAULT}, new_obj));
//TITLE TEXT
    new_obj = new UISmartText(_driver, _guiEnv, -1,
    "SERVER PORT :", irr::core::position2df(36, 46), cptFontSize(36));
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_CONNECT_STATU::DEFAULT}, new_obj));
//INPUT IP
    new_obj = new UIEditBox(_driver, _guiEnv, computeObjId(SERVER_CONNECT_OBJ_ID::PORT_INPUT),
    "./ressources/UI/main/fond_menu.png", "Enter server port",
    irr::core::rect<irr::f32>(35, 51, 58, 51 + 5), irr::core::position2df(36.5, 52.5), cptFontSize(20), 19);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_CONNECT_STATU::DEFAULT}, new_obj));
//JOIN BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_CONNECT_OBJ_ID::JOIN_BUTTON),
    irr::core::rect<irr::f32>(38, 63, 38 + 16, 63 + 8),
    irr::core::rect<irr::s32>(0, 0, 600, 230),
    "sb_join_arrow",
    "./ressources/UI/gameMode/join_button_idle.png",
    "./ressources/UI/gameMode/join_button_hover.png",
    "./ressources/UI/gameMode/join_button_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_CONNECT_STATU::DEFAULT}, new_obj));
//E_ERROR MESSAGE
    smart_text = new UISmartText(_driver, _guiEnv, -1,
    "Can not connect to server", irr::core::position2df(36, 25), cptFontSize(16));
    smart_text->setHover();
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_CONNECT_STATU::E_ERROR}, smart_text));
    smart_text = new UISmartText(_driver, _guiEnv, -1,
    "please check ip/port", irr::core::position2df(38.2, 27), cptFontSize(16));
    smart_text->setHover();
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_CONNECT_STATU::E_ERROR}, smart_text));

}

bool InterfaceServerConnect::manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene)
{
    int idScene = -1;
    int idObj = -1;
    IInterfaceObj *ptr;
    UIEditBox *cptr;


    if (event.EventType == irr::EET_GUI_EVENT) {
        idScene = this->getSceneFromId(event.GUIEvent.Caller->getID());
        idObj = this->getObjIdFromId(event.GUIEvent.Caller->getID());
        if (idObj == SERVER_CONNECT_OBJ_ID::IP_INPUT && idObj != _idLastEditBoxClicked) {
            ptr = getObjbyId(SERVER_CONNECT_OBJ_ID::IP_INPUT);
            cptr = static_cast<UIEditBox *>(ptr);
            if (cptr->isClicked() == false && event.GUIEvent.EventType == 1) {
                cptr->setClicked();
                _idLastEditBoxClicked = idObj;
                ptr = getObjbyId(SERVER_CONNECT_OBJ_ID::PORT_INPUT);
                cptr = static_cast<UIEditBox *>(ptr);
                cptr->setUnclicked();
                _actualStatu = DEFAULT;
            }
        }
        if (idObj == SERVER_CONNECT_OBJ_ID::PORT_INPUT && idObj != _idLastEditBoxClicked) {
            ptr = getObjbyId(SERVER_CONNECT_OBJ_ID::PORT_INPUT);
            cptr = static_cast<UIEditBox *>(ptr);
            if (cptr->isClicked() == false && event.GUIEvent.EventType == 1) {
                cptr->setClicked();
                _idLastEditBoxClicked = idObj;
                ptr = getObjbyId(SERVER_CONNECT_OBJ_ID::IP_INPUT);
                cptr = static_cast<UIEditBox *>(ptr);
                cptr->setUnclicked();
                _actualStatu = DEFAULT;
            }
        }
    }
    if (event.EventType == irr::EET_KEY_INPUT_EVENT && _idLastEditBoxClicked != -1) {
        ptr = getObjbyId(_idLastEditBoxClicked);
        cptr = static_cast<UIEditBox *>(ptr);
        if (cptr->isClicked() == true && event.KeyInput.Key == irr::EKEY_CODE::KEY_BACK)
            cptr->removeCharacter();
        else if (cptr->isClicked() == true && isInAlphabet(event.KeyInput.Char) == true) {
            cptr->addCharacter(event.KeyInput.Char);
        }
    }
    if (idScene == UI_SCENE_ID::SERVER_CONNECT) {
        switch (idObj) {
            case SERVER_CONNECT_OBJ_ID::JOIN_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::SERVER_ROOM, idObj) == BUTTON_STATU::CLICKED) {
                    if (connectServer() == false) {
                        nextScene.sceneId = UI_SCENE_ID::SERVER_CONNECT;
                        _actualStatu = E_ERROR;
                    }
                }
            break;
            case SERVER_CONNECT_OBJ_ID::BACK_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::MENU, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "BACK BUTTON CLICKED" << std::endl;
                }
            break;
            case SERVER_CONNECT_OBJ_ID::SETTINGS_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::OPTION, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "SETTINGS BUTTON CLICKED" << std::endl;
                }
            break;
            case SERVER_CONNECT_OBJ_ID::ABOUT_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::HELP, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "BACK BUTTON CLICKED" << std::endl;
                }
            break;
        }
    }
	return true;
}

bool InterfaceServerConnect::connectServer(void)
{
    IInterfaceObj *ptrIp = getObjbyId(SERVER_CONNECT_OBJ_ID::IP_INPUT);
    UIEditBox *cptrIp = dynamic_cast<UIEditBox *>(ptrIp);
    IInterfaceObj *ptrPort = getObjbyId(SERVER_CONNECT_OBJ_ID::PORT_INPUT);
    UIEditBox *cptrPort = dynamic_cast<UIEditBox *>(ptrPort);

    if (!cptrIp || !cptrPort)
        return false;
	if (cptrIp->getText() == "" && cptrPort->getText() == "")
	    return (_servclient->run("109.22.211.146", "27018"));
    return (_servclient->run(cptrIp->getText(), cptrPort->getText()));
}


bool InterfaceServerConnect::update()
{
    IInterfaceObj *ptr = getObjbyId(_idLastEditBoxClicked);
    UIEditBox *cptr = dynamic_cast<UIEditBox *>(ptr);

    updateVisibleObj();
    if (cptr)
        cptr->update();
    return true;
}