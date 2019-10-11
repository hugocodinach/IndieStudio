/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/InterfaceOption.cpp
*/

#include "InterfaceOption.hpp"

InterfaceOption::InterfaceOption(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId, MusicPlayer &musicPlayer,
option_t &option):
AInterfaceScene(device, guiEnv, driver, id, prevSceneId, musicPlayer), _option(option)
{
    this->create();
    _prevStatu = -1;
    _actualStatu = OPTION_STATU::DEFAULT;
    _allStatu = OPTION_STATU::DEFAULT;
    _musicVolume = _option.musicVolume * 20;
    _soundVolume = _option.soundVolume * 20;
    _maxVolume = 5;
}

InterfaceOption::~InterfaceOption()
{
    // std::cout << "~InterfaceOption" << std::endl;
}

void InterfaceOption::create()
{
    IInterfaceObj *new_obj;
    IInterfaceObj *new_obj_1;
    IInterfaceObj *new_obj_2;

//BACK ARROW
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::BACK_BUTTON),
    irr::core::rect<irr::f32>(3, 5, 3 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 630, 630),
    "sb_back_arrow",
    "./ressources/UI/global/back_arrow_idle.png",
    "./ressources/UI/global/back_arrow_hover.png",
    "./ressources/UI/global/back_arrow_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));
//BACKGROUND
    new_obj = new UIImage(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::NONE),
    irr::core::rect<irr::f32>(30, 22, 63, 77),
    _driver->getTexture("./ressources/UI/main/fond_menu_binding.png"));
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));
//SETTINGS TITLE TEXT
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::NONE),
    "SETTINGS", irr::core::position2df(37, 15), cptFontSize(48));
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));
//KEYBINDING BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::KEY_BINDING_BUTTON),
    irr::core::rect<irr::f32>(35, 30, 58, 30 + 5), irr::core::rect<irr::s32>(0, 0, 570, 530),
    "./ressources/UI/main/fond_menu.png", "Key Binding", irr::core::position2df(38, 31.5),
    cptFontSize(28), _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));


//VOLUME TEXT
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::NONE),
    "VOLUME MUSIC", irr::core::position2df(38, 40), cptFontSize(28));
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));
//LEFT ARROW
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::VOLUME_MUSIC_LEFT_BUTTON),
    irr::core::rect<irr::f32>(33, 42, 33 + 3, 42 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));
//RIGHT ARROW
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::VOLUME_MUSIC_RIGHT_BUTTON),
    irr::core::rect<irr::f32>(57, 42, 57 + 3, 42 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));
//VOLUME IMAGE
    new_obj = new UIImage(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::VOLUME_MUSIC_IMAGE),
    irr::core::rect<irr::f32>(37, 42, 56, 42 + 5),
    _driver->getTexture("./ressources/UI/settings/volume_0_4.png"));
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));
//VOLUME LATERAL MENU
    _musicVolumeObj = new UILateralMenu(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::VOLUME_MUSIC_LIST),
    getObjbyId(OPTION_OBJ_ID::VOLUME_MUSIC_LEFT_BUTTON),
    getObjbyId(OPTION_OBJ_ID::VOLUME_MUSIC_RIGHT_BUTTON),
    getObjbyId(OPTION_OBJ_ID::VOLUME_MUSIC_IMAGE),
    {"./ressources/UI/settings/volume_0_4.png",
    "./ressources/UI/settings/volume_1_4.png",
    "./ressources/UI/settings/volume_2_4.png",
    "./ressources/UI/settings/volume_3_4.png",
    "./ressources/UI/settings/volume_4_4.png"});
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, _musicVolumeObj));
    _musicVolumeObj->setIdx(_option.musicVolume);


//VOLUME TEXT
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::NONE),
    "VOLUME SOUND", irr::core::position2df(38, 50), cptFontSize(28));
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));
//LEFT ARROW
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::VOLUME_SOUND_LEFT_BUTTON),
    irr::core::rect<irr::f32>(33, 52, 33 + 3, 52 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));
//RIGHT ARROW
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::VOLUME_SOUND_RIGHT_BUTTON),
    irr::core::rect<irr::f32>(57, 52, 57 + 3, 52 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));
//VOLUME IMAGE
    new_obj = new UIImage(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::VOLUME_SOUND_IMAGE),
    irr::core::rect<irr::f32>(37, 52, 56, 52 + 5),
    _driver->getTexture("./ressources/UI/settings/volume_0_4.png"));
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));
//VOLUME LATERAL MENU
    _musicSoundObj = new UILateralMenu(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::VOLUME_SOUND_LIST),
    getObjbyId(OPTION_OBJ_ID::VOLUME_SOUND_LEFT_BUTTON),
    getObjbyId(OPTION_OBJ_ID::VOLUME_SOUND_RIGHT_BUTTON),
    getObjbyId(OPTION_OBJ_ID::VOLUME_SOUND_IMAGE),
    {"./ressources/UI/settings/volume_0_4.png",
    "./ressources/UI/settings/volume_1_4.png",
    "./ressources/UI/settings/volume_2_4.png",
    "./ressources/UI/settings/volume_3_4.png",
    "./ressources/UI/settings/volume_4_4.png"});
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, _musicSoundObj));
    _musicSoundObj->setIdx(_option.soundVolume);

//COIN MODE TEXT
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::NONE),
    "COIN MODE", irr::core::position2df(37, 70), cptFontSize(28));
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, new_obj));
//COIN MODE
    coinModeButton = new UIButton(_driver, _guiEnv, computeObjId(OPTION_OBJ_ID::COIN_MODE_BUTTON),
    irr::core::rect<irr::f32>(52, 69, 52 + 3, 69 + 5),
    irr::core::rect<irr::s32>(0, 0, 256, 256),
    "sb_left_arrow",
    "./ressources/UI/gameMode/select_box_idle.png",
    "./ressources/UI/gameMode/select_box_idle.png",
    "./ressources/UI/gameMode/select_box_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{OPTION_STATU::DEFAULT}, coinModeButton));
    if (_option.useCoinMode == true)
        coinModeButton->setClicked();
}

bool InterfaceOption::manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene)
{
    int idScene = -1;
    int idObj = -1;

    if (event.EventType == irr::EET_GUI_EVENT) {
        idScene = this->getSceneFromId(event.GUIEvent.Caller->getID());
        idObj = this->getObjIdFromId(event.GUIEvent.Caller->getID());
        if (idObj == OPTION_OBJ_ID::VOLUME_MUSIC_RIGHT_BUTTON &&
        event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED &&
        _option.musicVolume < (_maxVolume - 1)) {
            _musicVolumeObj->nextTextureRight();
            _option.musicVolume += 1;
            _musicVolume = _option.musicVolume * 20;
            _musicPlayer.setVolumeAllMusic(_musicVolume);
        }
        if (idObj == OPTION_OBJ_ID::VOLUME_MUSIC_LEFT_BUTTON &&
        event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED &&
        _option.musicVolume > 0) {
            _musicVolumeObj->nextTextureLeft();
            _option.musicVolume -= 1;
            _musicVolume = _option.musicVolume * 20;
            _musicPlayer.setVolumeAllMusic(_musicVolume);
        }
        if (idObj == OPTION_OBJ_ID::VOLUME_SOUND_RIGHT_BUTTON &&
        event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED &&
        _option.soundVolume < (_maxVolume - 1)) {
            _musicSoundObj->nextTextureRight();
            _option.soundVolume += 1;
            _musicVolume = _option.soundVolume * 20;
            _musicPlayer.setVolumeAllSound(_musicVolume);
        }
        if (idObj == OPTION_OBJ_ID::VOLUME_SOUND_LEFT_BUTTON &&
        event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED &&
        _option.soundVolume > 0) {
            _musicSoundObj->nextTextureLeft();
            _option.soundVolume -= 1;
            _musicVolume = _option.soundVolume * 20;
            _musicPlayer.setVolumeAllSound(_musicVolume);
        }

    }
    if (idScene == UI_SCENE_ID::OPTION) {
        switch (idObj) {
            case OPTION_OBJ_ID::BACK_BUTTON:
                if (buttonUpdate(event, nextScene,
                _prevSceneId[(_prevSceneId.size() -1) < 0 ? 0 : (_prevSceneId.size() -1) ], idObj) == BUTTON_STATU::CLICKED) {
                    _prevSceneId.pop_back();
                    _fromBack = true;
                }
                break;
            case OPTION_OBJ_ID::SETTINGS_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::OPTION, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "SETTINGS BUTTON CLICKED" << std::endl;
                }
            break;
            case OPTION_OBJ_ID::ABOUT_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::MENU, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "BACK BUTTON CLICKED" << std::endl;
                }
            break;
            case OPTION_OBJ_ID::KEY_BINDING_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::KEY_BINDING, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "KEY_BINDING BUTTON CLICKED" << std::endl;
                }
            break;
            case OPTION_OBJ_ID::COIN_MODE_BUTTON:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                    if (_option.useCoinMode == true) {
                        _option.useCoinMode = false;
                        coinModeButton->setIdle();
                    } else if (_option.useCoinMode == false) {
                        _option.useCoinMode = true;
                        coinModeButton->setClicked();
                    }
                }
            break;
        }
        if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
            if (idObj == OPTION_OBJ_ID::QUIT_BUTTON) {
                nextScene.sceneId = UI_SCENE_ID::QUIT;
                return (true);
            }

        }
    }
    return false;
}

bool InterfaceOption::update()
{
    return true;
}