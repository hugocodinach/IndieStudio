/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/AInterfaceScene.cpp
*/

#include "AInterfaceScene.hpp"

AInterfaceScene::AInterfaceScene(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId, MusicPlayer &musicPlayer):
_device(device), _guiEnv(guiEnv), _driver(driver), _id(id), _prevSceneId(prevSceneId),
_musicPlayer(musicPlayer)
{
    _fromBack = false;
}

AInterfaceScene::~AInterfaceScene()
{
    // std::cout << "~AInterfaceScene" << std::endl;
    for (int i = 0; i < _objs.size(); i += 1) {
        delete _objs[i].second;
    }
}

int AInterfaceScene::getId(void) const
{
    return (_id);
}


int AInterfaceScene::computeObjId(int ObjId) const
{
    return (_id * 1000 + ObjId);
}

int AInterfaceScene::getSceneFromId(int id)
{
    return (id / 1000);
}

int AInterfaceScene::getObjIdFromId(int id)
{
    int sceneId = getSceneFromId(id);

    return (id - (sceneId * 1000));
}

IInterfaceObj *AInterfaceScene::getObjbyId(int id) const
{
    int id_to_find = computeObjId(id);

    for (int i = 0; i < _objs.size(); i += 1) {
        if (_objs[i].second && _objs[i].second->getId() == id_to_find)
            return (_objs[i].second);
    }
    return (nullptr);
}

bool AInterfaceScene::checkObjType(int objId, int type) const
{
    IInterfaceObj *obj = getObjbyId(objId);

    if (!obj) {
        // std::cout << "Can't find obj " << objId << std::endl;
        return false;
    }
    if (obj->getType() == type)
        return true;
    return false;
}


int AInterfaceScene::buttonUpdate(const irr::SEvent& event,
sceneInfo_t &scene, int nextSceneId, int buttonId) const
{
    IInterfaceObj *ptr = getObjbyId(buttonId);
    UIButton *button;

    if (!ptr) {
        // std::cout << "Can't find button " << buttonId << std::endl;
        return -1;
    }
    // std::cout << "scene.sceneId = " << scene.sceneId << std::endl; 
    // std::cout << "nextSceneId = " << nextSceneId << std::endl;
    button = static_cast<UIButton *>(ptr);
    if (event.GUIEvent.EventType == irr::gui::EGET_ELEMENT_HOVERED) {
        button->setOver();
        return BUTTON_STATU::HOVER;
    } else if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED
    || event.GUIEvent.EventType == 1) {
        scene.sceneId = nextSceneId;
        button->setClicked();
        return BUTTON_STATU::CLICKED;
    } else {
        button->setIdle();
        return BUTTON_STATU::IDLE;
    }
}

int AInterfaceScene::lateralTextUpdate(int id_left_button, int id_right_button,
int id_lateral_text, int id_obj_to_check, const irr::SEvent& event)
{
    IInterfaceObj *ptr = getObjbyId(id_lateral_text);
    UILateralText *cptr = static_cast<UILateralText *>(ptr);

    if (id_obj_to_check == id_right_button &&
    event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
        cptr->nextTextRight();
    }
    if (id_obj_to_check == id_left_button &&
    event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
        cptr->nextTextLeft();
    }
    return cptr->getIdx();
}

MODELS AInterfaceScene::rotatingMeshesUpdate(int id_left_button, int id_right_button,
int id_meshe_to_mode, int id_obj_to_check, RotatingMeshes &meshesManager,
const irr::SEvent& event, int status)
{
    if (id_obj_to_check == id_right_button &&
    event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
        meshesManager.nextPers(id_meshe_to_mode);
    }
    if (id_obj_to_check == id_left_button &&
    event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
        meshesManager.previousPers(id_meshe_to_mode);
    }
    meshesManager.setPersVisibility(id_meshe_to_mode, (status == 2) ? false : true);
    return (meshesManager.getParticularModel(id_meshe_to_mode));
}


bool AInterfaceScene::isObjOnStatu(std::pair<std::vector<int>, IInterfaceObj *> &obj, int statu)
{
    for (int i = 0; i < obj.first.size(); i += 1) {
        if (obj.first[i] == statu || obj.first[i] == _allStatu)
            return true;
    }
    return false;
}

void AInterfaceScene::updateVisibleObj(void)
{
    if (_actualStatu != _prevStatu) {
        for (int i = 0; i < _objs.size(); i += 1) {
            if (isObjOnStatu(_objs[i], _actualStatu))
                _objs[i].second->setVisible(true);
            else
                _objs[i].second->setVisible(false);
        }
        _prevStatu = _actualStatu;
    }
}

bool AInterfaceScene::isInAlphabet(char c)
{
    int j = 0;

    if (c == 0)
        return false;
    for(; alphabet_path[j].c != c && (alphabet_path[j].c + 32) != c
        && alphabet_path[j].c != '@'; j += 1);
    if (alphabet_path[j].c == '@')
        return false;
    return true;
}

bool AInterfaceScene::isFromBack(void) const
{
    return _fromBack;
}

float AInterfaceScene::cptFontSize(float size) const
{
    return (size * 100 / _driver->getScreenSize().Width);
}
