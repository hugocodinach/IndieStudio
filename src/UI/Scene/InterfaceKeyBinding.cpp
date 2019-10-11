/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/InterfaceKeyBinding.cpp
*/

#include "InterfaceKeyBinding.hpp"

InterfaceKeyBinding::InterfaceKeyBinding(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId,
std::map<int, std::pair<std::string, KeyHandler>> &keys, MusicPlayer &musicPlayer):
AInterfaceScene(device, guiEnv, driver, id, prevSceneId, musicPlayer), _keys(keys)
{
    _prevStatu = -1;
    _actualStatu = KEY_BINDING_STATU::DEFAULT;
    _allStatu = KEY_BINDING_STATU::DEFAULT;
    _keyPerPlayer = 6;
    _idWaitingBind = -1;
    this->create();
}

InterfaceKeyBinding::~InterfaceKeyBinding()
{
    // std::cout << "~InterfaceKeyBinding" << std::endl;
}


void InterfaceKeyBinding::create()
{
    IInterfaceObj *new_obj;
    std::map<int, std::pair<std::string, KeyHandler>>::iterator it;
    irr::EKEY_CODE key_code;
    float col = 0;
    float row = 0;
    std::pair<float, float> offset[4] = {std::make_pair(5, 20),
    std::make_pair(5, 60), std::make_pair(50, 20), std::make_pair(50, 60)};
    int idx_offset = 0;
    int i = 0;
    float offset_key_button = 10.0;
    KeyType type;
    int ctrlKey;

//INIT ALL INPUT BUTTON
    for (it = _keys.begin(); it != _keys.end(); it++, row += 1, i += 1) {
        if (row >= 4) {
            col += 1;
            row = 0;
        }
        if (col >= 2) {
            col = 0;
            idx_offset += 1;
        }
        if (i > 0 && (i % _keyPerPlayer) == 0) {
            idx_offset += 1;
            row = 0;
            col = 0;
        }
        key_code = it->second.second.getIrrKey();
        type = it->second.second.getType();
        ctrlKey = it->second.second.getKey();
        controller_map[(static_cast<ControllerKey>(ctrlKey))];
        new_obj = new UISmartText(_driver, _guiEnv, computeObjId(it->first + 100),
        it->second.first, irr::core::position2df(col * 21 + offset[idx_offset].first,
        row * 6 + offset[idx_offset].second), cptFontSize(22));
        _objs.push_back(std::make_pair(std::vector<int>{KEY_BINDING_STATU::DEFAULT}, new_obj));
        new_obj = new UIButton(_driver, _guiEnv, computeObjId(it->first),
        irr::core::rect<irr::f32>(col * 22 + offset[idx_offset].first + offset_key_button,
            row * 6 + offset[idx_offset].second,
            col * 22 + offset[idx_offset].first + 10 + offset_key_button,
            row * 6 + offset[idx_offset].second + 4),
        irr::core::rect<irr::s32>(0, 0, 570, 530),
        "./ressources/UI/main/fond_menu_binding.png",
        ((type == KEYBOARD) ? key_map[key_code] : controller_map[(static_cast<ControllerKey>(ctrlKey))]),
        irr::core::position2df(col * 22 + offset[idx_offset].first + 1 + offset_key_button,
        row * 6 + offset[idx_offset].second + 1), cptFontSize(18), _musicPlayer);
        _objs.push_back(std::make_pair(std::vector<int>{KEY_BINDING_STATU::DEFAULT}, new_obj));
    }
//WAIT KEY POPUP BACKGROUND
    new_obj = new UIImage(_driver, _guiEnv, computeObjId(KEY_BINDING_OBJ_ID::POPUP_BACKGROUND),
    irr::core::rect<irr::f32>(30, 40, 70, 50),
    _driver->getTexture("./ressources/UI/main/fond_menu_binding.png"));
    _objs.push_back(std::make_pair(std::vector<int>{KEY_BINDING_STATU::WAIT_INPUT}, new_obj));
//WAIT KEY POPUP BACKGROUND
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(KEY_BINDING_OBJ_ID::POPUP_TEXT),
    "PRESS ANY KEY", irr::core::position2df(36, 43), cptFontSize(42));
    _objs.push_back(std::make_pair(std::vector<int>{KEY_BINDING_STATU::WAIT_INPUT}, new_obj));
//PLAYER ONE TEXT
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(KEY_BINDING_OBJ_ID::POPUP_TEXT),
    "PLAYER 1", irr::core::position2df(18, 11), cptFontSize(42));
    _objs.push_back(std::make_pair(std::vector<int>{KEY_BINDING_STATU::DEFAULT}, new_obj));
//PLAYER TWO TEXT
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(KEY_BINDING_OBJ_ID::POPUP_TEXT),
    "PLAYER 3", irr::core::position2df(63, 11), cptFontSize(42));
    _objs.push_back(std::make_pair(std::vector<int>{KEY_BINDING_STATU::DEFAULT}, new_obj));
//PLAYER THREE TEXT
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(KEY_BINDING_OBJ_ID::POPUP_TEXT),
    "PLAYER 2", irr::core::position2df(18, 51), cptFontSize(42));
    _objs.push_back(std::make_pair(std::vector<int>{KEY_BINDING_STATU::DEFAULT}, new_obj));
//PLAYER FOUR TEXT
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(KEY_BINDING_OBJ_ID::POPUP_TEXT),
    "PLAYER 4", irr::core::position2df(63, 51), cptFontSize(42));
    _objs.push_back(std::make_pair(std::vector<int>{KEY_BINDING_STATU::DEFAULT}, new_obj));
//BACK ARROW
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(KEY_BINDING_OBJ_ID::BACK_BUTTON),
    irr::core::rect<irr::f32>(3, 5, 3 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 630, 630),
    "sb_back_arrow",
    "./ressources/UI/global/back_arrow_idle.png",
    "./ressources/UI/global/back_arrow_hover.png",
    "./ressources/UI/global/back_arrow_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{KEY_BINDING_STATU::DEFAULT}, new_obj));

}

bool InterfaceKeyBinding::manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene)
{
    int idScene = -1;
    int idObj = -1;
    std::map<int, std::pair<std::string, KeyHandler>>::iterator it;

    // std::cout << "InterfaceKeyBinding::manageEvent" << std::endl;
    if (event.EventType == irr::EET_GUI_EVENT) {
        // std::cout << "InterfaceKeyBinding::manageEvent 1" << std::endl;
        idScene = this->getSceneFromId(event.GUIEvent.Caller->getID());
        idObj = this->getObjIdFromId(event.GUIEvent.Caller->getID());
        if (idScene == UI_SCENE_ID::KEY_BINDING && _actualStatu != KEY_BINDING_STATU::WAIT_INPUT
        && event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
            // std::cout << "FIND CLICK" << std::endl;
            it = _keys.find(idObj);
            if (it != _keys.end()) {
                _idWaitingBind = idObj;
                _actualStatu = KEY_BINDING_STATU::WAIT_INPUT;
            }
        }
        switch (idObj) {
            case KEY_BINDING_OBJ_ID::BACK_BUTTON:
                // std::cout << "_prevSceneId.size() = " << _prevSceneId.size() << std::endl;
                if (buttonUpdate(event, nextScene, _prevSceneId[_prevSceneId.size() - 1], idObj) == BUTTON_STATU::CLICKED) {
                    _prevSceneId.pop_back();
                    _fromBack = true;
                }
            break;
        }
    }
    if (event.EventType == irr::EET_KEY_INPUT_EVENT && _actualStatu == KEY_BINDING_STATU::WAIT_INPUT
    && _idWaitingBind >= 0) {
		// std::cout << "rzez" << std::endl;

        it = _keys.find(_idWaitingBind);
        if (it != _keys.end()) {
            it->second.second.setKey(event.KeyInput.Key);
            IInterfaceObj *ptr = getObjbyId(_idWaitingBind);
            UIButton *cptr = static_cast<UIButton *>(ptr);
            cptr->setLabelText(key_map[event.KeyInput.Key]);
            _actualStatu = KEY_BINDING_STATU::DEFAULT;
            _idWaitingBind = -1;
        }
    } else if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT && _actualStatu == KEY_BINDING_STATU::WAIT_INPUT
    && _idWaitingBind >= 0 && static_cast<ControllerKey>(joystick(event)) != -1) {
		// std::cout << "préJAJ" << std::endl;
        it = _keys.find(_idWaitingBind);
        if (it != _keys.end()) {
		// std::cout << "JAJ" << std::endl;
            it->second.second.setKey(static_cast<ControllerKey>(joystick(event)));
            IInterfaceObj *ptr = getObjbyId(_idWaitingBind);
            UIButton *cptr = static_cast<UIButton *>(ptr);
            cptr->setLabelText(controller_map[static_cast<ControllerKey>(joystick(event))]);
            _actualStatu = KEY_BINDING_STATU::DEFAULT;
            _idWaitingBind = -1;
        }
    }
    return false;
}

int InterfaceKeyBinding::joystick(const irr::SEvent& event) {
		int joy = 0;
	if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT)
	{
		for (irr::u32 joystick = 0; joystick < myjoystickInfo.size(); ++joystick)
		{
			joy = joystick;
			const irr::SEvent::SJoystickEvent & joystickData = event.JoystickEvent;
			if (myjoystickInfo.size() <= (int)joystickData.Joystick || myjoystickInfo[joystickData.Joystick].Name != myjoystickInfo[joystick].Name)
				continue;
			if (joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_V] > 0) {
				return (RT1 + (joy * 17));
			}
			if (joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Z] > 0) {
				return (LT1 + (joy * 17));
			} else {
			}
			if (floatAbs(joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X]) > floatAbs(joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y])) {
				if (joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X] > 25000) {
					return (RD1 + (joy * 17));
				}
				else if (joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X] < - 25000) {
					return (LD1 + (joy * 17));
				}					
			} else if (floatAbs(joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X]) < floatAbs(joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y])) {
				if (joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] > 25000) {
					return (DD1 + (joy * 17));
				}
				else if (joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] < - 25000) {
					return (UD1 + (joy * 17));
				}
			}
			for (int i = 0; i < 9; i++) {
				if (joystickData.IsButtonPressed((irr::u32)i) == true) {
					return (i + (joy * 17));
				}
			}
		}
	}
	return (- 1);
}

void InterfaceKeyBinding::print(irr::EKEY_CODE key) const
{
}
bool InterfaceKeyBinding::update()
{
    updateVisibleObj();
    return true;
}
