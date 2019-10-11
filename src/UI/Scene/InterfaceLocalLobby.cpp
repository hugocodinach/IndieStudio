/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/InterfaceLocalLobby.cpp
*/

#include "InterfaceLocalLobby.hpp"

InterfaceLocalLobby::InterfaceLocalLobby(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId, MusicPlayer &musicPlayer):
AInterfaceScene(device, guiEnv, driver, id, prevSceneId, musicPlayer),
_characterPreview(irr::core::vector3df(-260, 4, -350), irr::core::vector3df(-310, 4, -313),
4, _device->getSceneManager())
{
    _userInfo.push_back({"Player 1", 1, false, USER_STATU::NOT_PLAYING});
    _userInfo.push_back({"Player 2", 1, false, USER_STATU::NOT_PLAYING});
    _userInfo.push_back({"Player 3", 1, false, USER_STATU::NOT_PLAYING});
    _userInfo.push_back({"Player 4", 1, false, USER_STATU::NOT_PLAYING});
    this->create();
    _prevStatu = -1;
    _actualStatu = LOCAL_LOBBY_STATU::DEFAULT;
    _allStatu = LOCAL_LOBBY_STATU::DEFAULT;
}

InterfaceLocalLobby::~InterfaceLocalLobby()
{
    // std::cout << "~InterfaceLocalLobby" << std::endl;
    _characterPreview.close();
}

void InterfaceLocalLobby::create()
{
    IInterfaceObj *new_obj;
    IInterfaceObj *new_obj_1;
    IInterfaceObj *new_obj_2;

//BACK ARROW
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::BACK_BUTTON),
    irr::core::rect<irr::f32>(3, 5, 3 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 630, 630),
    "sb_back_arrow",
    "./ressources/UI/global/back_arrow_idle.png",
    "./ressources/UI/global/back_arrow_hover.png",
    "./ressources/UI/global/back_arrow_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));
//SETTINGS BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::SETTINGS_BUTTON),
    irr::core::rect<irr::f32>(85, 5, 85 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 270, 300),
    "sb_settings",
    "./ressources/UI/global/settings_idle.png",
    "./ressources/UI/global/settings_over.png",
    "./ressources/UI/global/settings_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));
//ABOUT BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::ABOUT_BUTTON),
    irr::core::rect<irr::f32>(90, 5, 90 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 512, 542),
    "sb_about",
    "./ressources/UI/global/about_idle.png",
    "./ressources/UI/global/about_over.png",
    "./ressources/UI/global/about_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));

//TITLE TEXT
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::TITLE_TEXT),
    "LOBBY", irr::core::position2df(40, 10), cptFontSize(60));
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));

//LEFT ARROW P1
    new_obj_1 = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_P1),
    irr::core::rect<irr::f32>(10, 70, 10 + 3, 70 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj_1));
//RIGHT ARROW P1
    new_obj_2 = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_P1),
    irr::core::rect<irr::f32>(25, 70, 25 + 3, 70 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj_2));
//LEFT ARROW CHAR P1
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P1),
    irr::core::rect<irr::f32>(10, 55, 10 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));
//RIGHT ARROW CHAR P1
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P1),
    irr::core::rect<irr::f32>(25, 55, 25 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));


//LATERAL TEXT P1
    new_obj = new UILateralText(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::LIST_P1),
    new_obj_1, new_obj_2, {"PLAYER", "  AI  ", " NONE "},
    irr::core::position2df(14 , 71), 32);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));
//PSEUDO TEXT P1
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::PSEUDO_P1),
    clearPseudo(_userInfo[0].username), irr::core::position2df(12, 76), cptFontSize(24));
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));

//LEFT ARROW P2
    new_obj_1 = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_P2),
    irr::core::rect<irr::f32>(30, 70, 30 + 3, 70 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj_1));
//RIGHT ARROW P2
    new_obj_2 = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_P2),
    irr::core::rect<irr::f32>(45, 70, 45 + 3, 70 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj_2));
//LEFT ARROW CHAR P2
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P2),
    irr::core::rect<irr::f32>(30, 55, 30 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));
//RIGHT ARROW CHAR P2
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P2),
    irr::core::rect<irr::f32>(45, 55, 45 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));
//LATERAL TEXT P2
    new_obj = new UILateralText(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::LIST_P2),
    new_obj_1, new_obj_2, {"PLAYER", "  AI  ", " NONE "},
    irr::core::position2df(34 , 71), 32);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));
//PSEUDO TEXT P2
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::PSEUDO_P2),
    clearPseudo(_userInfo[1].username), irr::core::position2df(32, 76), cptFontSize(24));
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));

//LEFT ARROW P3
    new_obj_1 = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_P3),
    irr::core::rect<irr::f32>(50, 70, 50 + 3, 70 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj_1));
//RIGHT ARROW P3
    new_obj_2 = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_P3),
    irr::core::rect<irr::f32>(65, 70, 65 + 3, 70 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj_2));

//LEFT ARROW CHAR P3
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P3),
    irr::core::rect<irr::f32>(50, 55, 50 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));
//RIGHT ARROW CHAR P3
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P3),
    irr::core::rect<irr::f32>(65, 55, 65 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));


//LATERAL TEXT P3
    new_obj = new UILateralText(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::LIST_P3),
    new_obj_1, new_obj_2, {"PLAYER", "  AI  ", " NONE "},
    irr::core::position2df(54 , 71), 32);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));
//PSEUDO TEXT P2
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::PSEUDO_P2),
    clearPseudo(_userInfo[2].username), irr::core::position2df(52, 76), cptFontSize(24));
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));


//LEFT ARROW P4
    new_obj_1 = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_P4),
    irr::core::rect<irr::f32>(70, 70, 70 + 3, 70 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj_1));
//RIGHT ARROW P4
    new_obj_2 = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_P4),
    irr::core::rect<irr::f32>(85, 70, 85 + 3, 70 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj_2));

//LEFT ARROW CHAR P4
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P4),
    irr::core::rect<irr::f32>(70, 55, 70 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));
//RIGHT ARROW CHAR P4
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P4),
    irr::core::rect<irr::f32>(85, 55, 85 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));


//LATERAL TEXT P4
    new_obj = new UILateralText(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::LIST_P4),
    new_obj_1, new_obj_2, {"PLAYER", "  AI  ", " NONE "},
    irr::core::position2df(74 , 71), 32);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));
//PSEUDO TEXT P4
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::PSEUDO_P4),
    clearPseudo(_userInfo[3].username), irr::core::position2df(72, 76), cptFontSize(24));
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));

//START BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(LOCAL_LOBBY_OBJ_ID::START_BUTTON),
    irr::core::rect<irr::f32>(80, 85, 90, 85 + 5), irr::core::rect<irr::s32>(0, 0, 570, 530),
    "./ressources/UI/main/fond_menu.png", "START", irr::core::position2df(81.5, 86.5), cptFontSize(28), _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{LOCAL_LOBBY_STATU::DEFAULT}, new_obj));

}

bool InterfaceLocalLobby::isThereEnoughPlayers()
{
    int nbr = 0;

    for (size_t i = 0; i != _userInfo.size(); i += 1) {
        if (_userInfo[i].statu != 2)
            nbr += 1;
    }
    if (nbr > 1)
        return true;
    return false;
}

bool InterfaceLocalLobby::manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene)
{
    int idScene = -1;
    int idObj = -1;

    if (event.EventType == irr::EET_GUI_EVENT) {
        idScene = this->getSceneFromId(event.GUIEvent.Caller->getID());
        idObj = this->getObjIdFromId(event.GUIEvent.Caller->getID());
    }
    if (idScene == UI_SCENE_ID::LOCAL_LOBBY) {
        switch (idObj) {
            case LOCAL_LOBBY_OBJ_ID::BACK_BUTTON:
                buttonUpdate(event, nextScene, UI_SCENE_ID::MENU, idObj) == BUTTON_STATU::CLICKED;
            break;
            case LOCAL_LOBBY_OBJ_ID::START_BUTTON:
                if (isThereEnoughPlayers() && buttonUpdate(event, nextScene, UI_SCENE_ID::PLAY, idObj) == BUTTON_STATU::CLICKED) {
                    serializeUsersInfos(nextScene);
                }
            break;
            case LOCAL_LOBBY_OBJ_ID::SETTINGS_BUTTON:
                 buttonUpdate(event, nextScene, UI_SCENE_ID::OPTION, idObj);
               break;
            case LOCAL_LOBBY_OBJ_ID::ABOUT_BUTTON:
                buttonUpdate(event, nextScene, UI_SCENE_ID::HELP, idObj);
            break;
        }
        _userInfo[0].statu = lateralTextUpdate(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_P1, LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_P1, LOCAL_LOBBY_OBJ_ID::LIST_P1, idObj, event);
        _userInfo[1].statu = lateralTextUpdate(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_P2, LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_P2, LOCAL_LOBBY_OBJ_ID::LIST_P2, idObj, event);
        _userInfo[2].statu = lateralTextUpdate(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_P3, LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_P3, LOCAL_LOBBY_OBJ_ID::LIST_P3, idObj, event);
        _userInfo[3].statu = lateralTextUpdate(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_P4, LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_P4, LOCAL_LOBBY_OBJ_ID::LIST_P4, idObj, event);
        _userInfo[0].characterId = rotatingMeshesUpdate(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P1, LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P1,
        0, idObj, _characterPreview, event, _userInfo[0].statu);
        _userInfo[1].characterId = rotatingMeshesUpdate(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P2, LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P2,
        1, idObj, _characterPreview, event, _userInfo[1].statu);
        _userInfo[2].characterId = rotatingMeshesUpdate(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P3, LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P3,
        2, idObj, _characterPreview, event, _userInfo[2].statu);
        _userInfo[3].characterId = rotatingMeshesUpdate(LOCAL_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P4, LOCAL_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P4,
        3, idObj, _characterPreview, event, _userInfo[3].statu);
    }
    return false;
}

std::string InterfaceLocalLobby::clearPseudo(std::string pseudo)
{
    int max = 12;
    int size = pseudo.size();
    int space_before = (max - size) / 2;
    int space_after = (max - size) / 2;

    for (int i = 0; i < space_before; i += 1)
        pseudo = ' ' + pseudo;
    for (int i = 0; i < space_after; i += 1)
        pseudo = pseudo + ' ';
    return (pseudo);
}

void InterfaceLocalLobby::serializeUsersInfos(sceneInfo_t &nextScene)
{
    nextScene.users.clear();
    for (int i = 0; i < _userInfo.size(); i += 1) {
        nextScene.users.push_back({_userInfo[i].username, _userInfo[i].characterId,
        _userInfo[i].isReady, _userInfo[i].statu});
    }
    nextScene.isOnline = false;
    nextScene.idxLocalUser = -1;
}

bool InterfaceLocalLobby::update()
{
    _characterPreview.update();
    updateVisibleObj();
    return true;
}
