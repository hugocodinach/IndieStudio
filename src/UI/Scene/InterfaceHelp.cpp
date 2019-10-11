/*
** EPITECH PROJECT, 2018
** InterfaceHelp.cpp
** File description:
** src/UI/Scene/InterfaceHelp.cpp
*/

#include "InterfaceHelp.hpp"

InterfaceHelp::InterfaceHelp(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId, MusicPlayer &musicPlayer):
AInterfaceScene(device, guiEnv, driver, id, prevSceneId, musicPlayer)
{
    this->create();
    _prevStatu = -1;
    _actualStatu = OPTION_STATU::DEFAULT;
    _allStatu = OPTION_STATU::DEFAULT;
}

InterfaceHelp::~InterfaceHelp()
{
}

void InterfaceHelp::create()
{
    IInterfaceObj *new_obj;

    new_obj = new UIButton(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::BACK_BUTTON),
    irr::core::rect<irr::f32>(3, 5, 3 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 630, 630),
    "sb_back_arrow",
    "./ressources/UI/global/back_arrow_idle.png",
    "./ressources/UI/global/back_arrow_hover.png",
    "./ressources/UI/global/back_arrow_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));

    new_obj = new UIImage(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::NONE),
    irr::core::rect<irr::f32>(0 + 12, 0 + 10, 35 + 12, 80 + 10),
    _driver->getTexture("./ressources/img/helpArch.png"));
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));

    new_obj = new UIImage(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::NONE),
    irr::core::rect<irr::f32>(0 + 50, 0 + 10, 35 + 50, 80 + 10),
    _driver->getTexture("./ressources/img/helpBonus.png"));
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));
}

bool InterfaceHelp::manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene)
{
    int idScene = -1;
    int idObj = -1;

    if (event.EventType == irr::EET_GUI_EVENT) {
        idScene = this->getSceneFromId(event.GUIEvent.Caller->getID());
        idObj = this->getObjIdFromId(event.GUIEvent.Caller->getID());
    }

    if (idScene == UI_SCENE_ID::HELP) {
        switch (idObj) {
            case OPTION_OBJ_ID::BACK_BUTTON:
                if (buttonUpdate(event, nextScene,
                _prevSceneId[(_prevSceneId.size() -1) < 0 ? 0 : (_prevSceneId.size() -1) ], idObj) == BUTTON_STATU::CLICKED) {
                    _prevSceneId.pop_back();
                    _fromBack = true;
                }
                break;
        }
    }
    return false;
}

bool InterfaceHelp::update(void)
{
    return true;
}