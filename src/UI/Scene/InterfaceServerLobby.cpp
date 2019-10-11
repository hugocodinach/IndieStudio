/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/InterfaceServerLobby.cpp
*/

#include "InterfaceServerLobby.hpp"

InterfaceServerLobby::InterfaceServerLobby(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId, NetworkClient* servclient,
MusicPlayer &musicPlayer, sceneInfo_t &nextScene):
AInterfaceScene(device, guiEnv, driver, id, prevSceneId, musicPlayer),
_characterPreview(irr::core::vector3df(-260, 4, -350), irr::core::vector3df(-310, 4, -313),
4, _device->getSceneManager()), _nextScene(nextScene)
{
    _userInfo.push_back({"Player 1", nullptr, nullptr, 1, false, false});
    _userInfo.push_back({"Player 2", nullptr, nullptr, 1, false, false});
    _userInfo.push_back({"Player 3", nullptr, nullptr, 1, false, false});
    _userInfo.push_back({"Player 4", nullptr, nullptr, 1, false, false});
    this->create();
    _prevStatu = -1;
    _actualStatu = SERVER_LOBBY_STATU::DEFAULT;
    _allStatu = SERVER_LOBBY_STATU::DEFAULT;
    _serverClient = servclient;
    _isReady = false;
    _idxLocalPlayer = 0;
	_characterPreview.setPersVisibility(0, false);
	_characterPreview.setPersVisibility(1, false);
	_characterPreview.setPersVisibility(2, false);
	_characterPreview.setPersVisibility(3, false);
}

InterfaceServerLobby::~InterfaceServerLobby()
{
    // std::cout << "~InterfaceServerLobby" << std::endl;
    _characterPreview.close();
}


void InterfaceServerLobby::create()
{
    IInterfaceObj *new_obj;
    UISmartText *smart_text;

//BACK ARROW
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::BACK_BUTTON),
    irr::core::rect<irr::f32>(3, 5, 3 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 630, 630),
    "sb_back_arrow",
    "./ressources/UI/global/back_arrow_idle.png",
    "./ressources/UI/global/back_arrow_hover.png",
    "./ressources/UI/global/back_arrow_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, new_obj));
//SETTINGS BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::SETTINGS_BUTTON),
    irr::core::rect<irr::f32>(85, 5, 85 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 270, 300),
    "sb_settings",
    "./ressources/UI/global/settings_idle.png",
    "./ressources/UI/global/settings_over.png",
    "./ressources/UI/global/settings_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, new_obj));
//ABOUT BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::ABOUT_BUTTON),
    irr::core::rect<irr::f32>(90, 5, 90 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 512, 542),
    "sb_about",
    "./ressources/UI/global/about_idle.png",
    "./ressources/UI/global/about_over.png",
    "./ressources/UI/global/about_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, new_obj));

//TITLE TEXT
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::TITLE_TEXT),
    "LOBBY", irr::core::position2df(40, 10), cptFontSize(60));
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, new_obj));

//PSEUDO TEXT P1
    smart_text = new UISmartText(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::PSEUDO_P1),
    clearPseudo(_userInfo[0].username), irr::core::position2df(14, 71), cptFontSize(32));
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, smart_text));
    _userInfo[0].usernameTextObj = smart_text;
//STATU TEXT P1
    smart_text = new UISmartText(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::STATU_P1),
    clearPseudo("Not ready"), irr::core::position2df(14, 76), cptFontSize(20));
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, smart_text));
    _userInfo[0].statuTextObj = smart_text;

//PSEUDO TEXT P2
    smart_text = new UISmartText(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::PSEUDO_P2),
    clearPseudo(_userInfo[1].username), irr::core::position2df(34, 71), cptFontSize(32));
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, smart_text));
    _userInfo[1].usernameTextObj = smart_text;
//STATU TEXT P2
    smart_text = new UISmartText(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::STATU_P2),
    clearPseudo("Not ready"), irr::core::position2df(34, 76), cptFontSize(20));
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, smart_text));
    _userInfo[1].statuTextObj = smart_text;

//PSEUDO TEXT P3
    smart_text = new UISmartText(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::PSEUDO_P3),
    clearPseudo(_userInfo[2].username), irr::core::position2df(54, 71), cptFontSize(32));
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, smart_text));
    _userInfo[2].usernameTextObj = smart_text;
//STATU TEXT P3
    smart_text = new UISmartText(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::STATU_P3),
    clearPseudo("Not ready"), irr::core::position2df(54, 76), cptFontSize(20));
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, smart_text));
    _userInfo[2].statuTextObj = smart_text;

//PSEUDO TEXT P4
    smart_text = new UISmartText(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::PSEUDO_P4),
    clearPseudo(_userInfo[3].username), irr::core::position2df(74, 71), cptFontSize(32));
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, smart_text));
    _userInfo[3].usernameTextObj = smart_text;
//STATU TEXT P4
    smart_text = new UISmartText(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::STATU_P4),
    clearPseudo("Not ready"), irr::core::position2df(74, 76), cptFontSize(20));
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, smart_text));
    _userInfo[3].statuTextObj = smart_text;

//READY BUTTON
    _readyButton = new UIButton(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::READY_BUTTON),
    irr::core::rect<irr::f32>(42, 85, 57, 85 + 5), irr::core::rect<irr::s32>(0, 0, 570, 530),
    "./ressources/UI/main/fond_menu.png", "READY ?", irr::core::position2df(44.5, 86.5),
    cptFontSize(28), _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, _readyButton));

//LEFT ARROW CHAR P1
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P1),
    irr::core::rect<irr::f32>(10, 55, 10 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, new_obj));
//RIGHT ARROW CHAR P1
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P1),
    irr::core::rect<irr::f32>(25, 55, 25 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, new_obj));

//LEFT ARROW CHAR P2
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P2),
    irr::core::rect<irr::f32>(30, 55, 30 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, new_obj));
//RIGHT ARROW CHAR P2
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P2),
    irr::core::rect<irr::f32>(45, 55, 45 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, new_obj));

//LEFT ARROW CHAR P3
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P3),
    irr::core::rect<irr::f32>(50, 55, 50 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, new_obj));
//RIGHT ARROW CHAR P3
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P3),
    irr::core::rect<irr::f32>(65, 55, 65 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, new_obj));

//LEFT ARROW CHAR P4
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P4),
    irr::core::rect<irr::f32>(70, 55, 70 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, new_obj));
//RIGHT ARROW CHAR P4
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P4),
    irr::core::rect<irr::f32>(85, 55, 85 + 3, 55 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_LOBBY_STATU::DEFAULT}, new_obj));


}

bool InterfaceServerLobby::manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene)
{
    int idScene = -1;
    int idObj = -1;
	_nextScene = nextScene;

    if (event.EventType == irr::EET_GUI_EVENT) {
        idScene = this->getSceneFromId(event.GUIEvent.Caller->getID());
        idObj = this->getObjIdFromId(event.GUIEvent.Caller->getID());
    }
    if (idScene == UI_SCENE_ID::SERVER_LOBBY) {
        switch (idObj) {
            case SERVER_LOBBY_OBJ_ID::BACK_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::SERVER_ROOM, idObj) == BUTTON_STATU::CLICKED) {
                    _serverClient->leaveRoom();
                }
            break;
            case SERVER_LOBBY_OBJ_ID::READY_BUTTON:
                if (event.GUIEvent.EventType == irr::gui::EGET_ELEMENT_HOVERED) {
                    if (_isReady == false)
                        _readyButton->setOver();
                }
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED
                || event.GUIEvent.EventType == 1) {
                    if (_isReady == false) {
                        _isReady = true;
                        _serverClient->setStatus(true);
                        _readyButton->setClicked();
                    } else if (_isReady == true) {
                        _isReady = false;
                        _serverClient->setStatus(false);
                        _readyButton->setOver();
                    }
                } else if (_isReady == false) {
                    _readyButton->setIdle();
                }
            break;
        }
    }
	_lastCharacter = _userInfo[_idxLocalPlayer].characterId;
	if (_idxLocalPlayer == 0) {
    	_userInfo[0].characterId = rotatingMeshesUpdate(SERVER_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P1, SERVER_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P1,
    	0, idObj, _characterPreview, event, _userInfo[0].statu);
	} else if (_idxLocalPlayer == 1) {
    	_userInfo[1].characterId = rotatingMeshesUpdate(SERVER_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P2, SERVER_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P2,
    	1, idObj, _characterPreview, event, _userInfo[1].statu);
	} else if (_idxLocalPlayer == 2) {
    	_userInfo[2].characterId = rotatingMeshesUpdate(SERVER_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P3, SERVER_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P3,
    	2, idObj, _characterPreview, event, _userInfo[2].statu);
	} else if (_idxLocalPlayer == 3) {
    	_userInfo[3].characterId = rotatingMeshesUpdate(SERVER_LOBBY_OBJ_ID::LEFT_ARROW_CHAR_P4, SERVER_LOBBY_OBJ_ID::RIGHT_ARROW_CHAR_P4,
    	3, idObj, _characterPreview, event, _userInfo[3].statu);
	}
	verifUpdateCharacter();
    return false;
}

void InterfaceServerLobby::verifUpdateCharacter()
{
	if (_lastCharacter != _userInfo[_idxLocalPlayer].characterId) {
		_serverClient->setCharacter( _userInfo[_idxLocalPlayer].characterId);
	}
}

void InterfaceServerLobby::infoRoom(std::vector<std::string> vect)
{
    int i = 1;
    int idx_user = 0;

    while (i < vect.size()) {
        if (idx_user < _userInfo.size()) {
            if (_userInfo[idx_user].username != vect[i])
                _userInfo[idx_user].username = vect[i];
			if ((i + 3) < vect.size() && vect[i + 3] == "1") {
                _idxLocalPlayer = idx_user;
				// std::cout << "PLAYEEEER " << _idxLocalPlayer << std::endl;
            }
            if ((i + 1) < vect.size() && vect[i + 1] == "unready") {
                _userInfo[idx_user].isReady = false;
                _userInfo[idx_user].statuTextObj->setText(std::string("not ready"));
            } else if ((i + 1) < vect.size() && vect[i + 1] == "ready") {
                _userInfo[idx_user].isReady = true;
                _userInfo[idx_user].statuTextObj->setText(std::string("ready"));
            }
            if ((i + 2) < vect.size()) {
				if ( _idxLocalPlayer != idx_user) {
					// std::cout << "CHANGE : " << _userInfo[idx_user].characterId << " TO " << std::stoi(vect[i + 2]) << std::endl;
					if (_userInfo[idx_user].characterId != std::stoi(vect[i + 2])) {
                		_userInfo[idx_user].characterId = std::stoi(vect[i + 2]);
						_characterPreview.setParticularPers(idx_user, static_cast<MODELS>(_userInfo[idx_user].characterId));
					}
				}
            }
            _userInfo[idx_user].statu = USER_STATU::ONLINE;
            _userInfo[idx_user].usernameTextObj->setText(_userInfo[idx_user].username);
        }
        i += 4;
        idx_user += 1;
    }
    for(; idx_user < _userInfo.size(); idx_user += 1) {
        _userInfo[idx_user].statu = USER_STATU::NOT_PLAYING;
        _userInfo[idx_user].username = "None";
        _userInfo[idx_user].usernameTextObj->setText(_userInfo[idx_user].username);
		_characterPreview.setPersVisibility(idx_user, false);
    }
	_nextScene.autotrigger = true;
};

void InterfaceServerLobby::game(std::vector<std::string> vect)
{
	if (vect[1] == "start") {
		// std::cout << "STARTTTTTTTTTTTTTT" << std::endl;
		serializeUsersInfos(_nextScene);
		_nextScene.sceneId = UI_SCENE_ID::PLAY;
	}
}

void InterfaceServerLobby::pointerFct(std::vector<std::string> action)
{
	command_t const arr_cmd[] = {
	{"QUIT", &InterfaceServerLobby::quit},
    {"CHAT", &InterfaceServerLobby::chat},
	{"LOG", &InterfaceServerLobby::log}, 
	{"ROOM", &InterfaceServerLobby::room},
	{"INFOROOM", &InterfaceServerLobby::infoRoom}, 
	{"CREATEROOM", &InterfaceServerLobby::createRoom},
	{"LEAVEROOM", &InterfaceServerLobby::leaveRoom},
	{"SETUSERNAME", &InterfaceServerLobby::setUserName},
    {"PLAY", &InterfaceServerLobby::play},
    {"GAME", &InterfaceServerLobby::game},
	{"PROMOTE", &InterfaceServerLobby::promote}};

	for (auto e: arr_cmd) {
		if (e.cmd == action[0]) {
			(this->*e.cmd_name)(action);
			return;
		}
	}
    return;
}

void InterfaceServerLobby::unstackActionServe()
{
	std::vector<std::string> strs;

	for (auto e : _serverClient->_action) {
		boost::split(strs, e, boost::is_any_of(" "));
        pointerFct(strs);
		strs.clear();
	}
	_serverClient->_action.clear();
}

std::string InterfaceServerLobby::clearPseudo(std::string pseudo)
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

void InterfaceServerLobby::serializeUsersInfos(sceneInfo_t &nextScene)
{
    nextScene.users.clear();
    for (int i = 0; i < _userInfo.size(); i += 1) {
        nextScene.users.push_back({_userInfo[i].username, _userInfo[i].characterId,
        _userInfo[i].isReady, _userInfo[i].statu});
    }
    nextScene.isOnline = true;
    nextScene.idxLocalUser = _idxLocalPlayer;
}

bool InterfaceServerLobby::update()
{
    updateVisibleObj();
    unstackActionServe();
    _characterPreview.update();
    return true;
}