/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/InterfaceServerRoom.cpp
*/

#include "InterfaceServerRoom.hpp"

InterfaceServerRoom::InterfaceServerRoom(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
irr::video::IVideoDriver *driver, int id, std::vector<int> &prevSceneId, NetworkClient *servclient,
MusicPlayer &musicPlayer, sceneInfo_t &nextScene):
AInterfaceScene(device, guiEnv, driver, id, prevSceneId, musicPlayer), _nextScene(nextScene)
{
    this->create();
    _prevStatu = -1;
    _allStatu = SERVER_ROOM_STATU::DEFAULT;
    _servclient = servclient;
	_enterInRoom = -1;
}

InterfaceServerRoom::~InterfaceServerRoom()
{
    // std::cout << "~InterfaceServerRoom" << std::endl;
}

void InterfaceServerRoom::create()
{
    UIButton *new_button;
    UIImage *new_image;
    UIText *new_text;
    UILateralMenu *new_menu;
    IInterfaceObj *new_obj;

//BACK ARROW
    new_button = new UIButton(_driver, _guiEnv, computeObjId(SERVER_ROOM_OBJ_ID::BACK_BUTTON),
    irr::core::rect<irr::f32>(3, 5, 3 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 630, 630),
    "sb_back_arrow",
    "./ressources/UI/global/back_arrow_idle.png",
    "./ressources/UI/global/back_arrow_hover.png",
    "./ressources/UI/global/back_arrow_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_ROOM_STATU::DEFAULT}, new_button));
//SETTINGS BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_ROOM_OBJ_ID::SETTINGS_BUTTON),
    irr::core::rect<irr::f32>(85, 5, 85 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 270, 300),
    "sb_settings",
    "./ressources/UI/global/settings_idle.png",
    "./ressources/UI/global/settings_over.png",
    "./ressources/UI/global/settings_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_ROOM_STATU::DEFAULT}, new_obj));
//ABOUT BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(SERVER_ROOM_OBJ_ID::ABOUT_BUTTON),
    irr::core::rect<irr::f32>(90, 5, 90 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 512, 542),
    "sb_about",
    "./ressources/UI/global/about_idle.png",
    "./ressources/UI/global/about_over.png",
    "./ressources/UI/global/about_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_ROOM_STATU::DEFAULT}, new_obj));
//TITLE TEXT
    new_obj = new UISmartText(_driver, _guiEnv, -1,
    "CHOOSE ROOM", irr::core::position2df(33, 16), cptFontSize(TITLE_TEXT_SIZE));
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_ROOM_STATU::DEFAULT}, new_obj));
//BACKGROUND
    new_image = new UIImage(_driver, _guiEnv, computeObjId(SERVER_ROOM_OBJ_ID::BACKGROUND_OPTION),
    irr::core::rect<irr::f32>(30, 22, 68, 77),
    _driver->getTexture("./ressources/UI/main/fond_menu_binding.png"));
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_ROOM_STATU::DEFAULT}, new_image));

//LIST LEFT ARROW
    new_button = new UIButton(_driver, _guiEnv, computeObjId(SERVER_ROOM_OBJ_ID::LIST_LEFT_ARROW),
    irr::core::rect<irr::f32>(36, 70, 39, 70 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_list_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_ROOM_STATU::DEFAULT}, new_button));
//LIST RIGHT ARROW
    new_button = new UIButton(_driver, _guiEnv, computeObjId(SERVER_ROOM_OBJ_ID::LIST_RIGHT_ARROW),
    irr::core::rect<irr::f32>(58, 70, 61, 70 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_list_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_ROOM_STATU::DEFAULT}, new_button));
//JOIN BUTTON LOCAL NETWORK
    new_button = new UIButton(_driver, _guiEnv, computeObjId(SERVER_ROOM_OBJ_ID::JOIN_BUTTON),
    irr::core::rect<irr::f32>(49, 70, 57, 70 + 5),
    irr::core::rect<irr::s32>(0, 0, 600, 230),
    "sb_join_arrow",
    "./ressources/UI/gameMode/join_button_idle.png",
    "./ressources/UI/gameMode/join_button_hover.png",
    "./ressources/UI/gameMode/join_button_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_ROOM_STATU::DEFAULT}, new_button));
//CREATE BUTTON LOCAL NETWORK
    new_button = new UIButton(_driver, _guiEnv, computeObjId(SERVER_ROOM_OBJ_ID::CREATE_BUTTON),
    irr::core::rect<irr::f32>(40, 69, 47, 76),
    irr::core::rect<irr::s32>(0, 0, 850, 250),
    "sb_create_arrow",
    "./ressources/UI/gameMode/create_button_idle.png",
    "./ressources/UI/gameMode/create_button_hover.png",
    "./ressources/UI/gameMode/create_button_clicked.png", _musicPlayer);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_ROOM_STATU::DEFAULT}, new_button));

	new_obj = new UIEditBox(_driver, _guiEnv, computeObjId(SERVER_ROOM_OBJ_ID::CHAT_INPUT),
    "./ressources/UI/main/fond_menu.png", "Type message here.",
    irr::core::rect<irr::f32>(3, 80, 58, 35 + 5), irr::core::position2df(3, 81.5), cptFontSize(20), 26);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_ROOM_STATU::DEFAULT}, new_obj));

	new_obj = new UISmartListBox(_driver,
            _guiEnv, irr::core::rect<irr::f32>(3., 40., 100, 100),
            computeObjId(SERVER_ROOM_OBJ_ID::CHAT_LIST),
            {"",
			"",
            "",
			"",
            "",
			"",
            "",
			"",
            "",
			"",
            "",
			"",
            "",
			"",
            "", 
			""}, cptFontSize(16), 16);
    _serverRoom = static_cast<UISmartListBox *>(new_obj);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_ROOM_STATU::DEFAULT}, new_obj));


new_obj = new UISmartListBox(_driver,
            _guiEnv, irr::core::rect<irr::f32>(3., 20., 100, 100),
            computeObjId(SERVER_ROOM_OBJ_ID::NB_PLAYER),
            {"Number of players : 0"}, cptFontSize(16), 1);
    _serverRoom = static_cast<UISmartListBox *>(new_obj);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_ROOM_STATU::DEFAULT}, new_obj));

	//LIST BOX
    new_obj = new UISmartListBox(_driver,
            _guiEnv, irr::core::rect<irr::f32>(31.25, 27.77, 100, 100),
            computeObjId(SERVER_ROOM_OBJ_ID::SERVER_SMART_LIST),
            {"serveur_01  le meilleur serv  1 sur 4",
            "serveur_01  le meilleur serv  2 sur 4",
            "serveur_01  le meilleur serv  3 sur 4",
            "serveur_01  le meilleur serv  4 sur 4",
            "serveur_01  le meilleur serv  5 sur 4",
            "serveur_01  le meilleur serv  6 sur 4",
            "serveur_01  le meilleur serv  7 sur 4",
            "serveur_01  le meilleur serv  8 sur 4"}, cptFontSize(16), 8);
    _serverRoom = static_cast<UISmartListBox *>(new_obj);
    _objs.push_back(std::make_pair(std::vector<int>{SERVER_ROOM_STATU::DEFAULT}, new_obj));

}

bool InterfaceServerRoom::manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene)
{
    int idScene = -1;
    int idObj = -1;
	_nextScene = nextScene;
	IInterfaceObj *ptr;
    UIEditBox *cptr;

    if (event.EventType == irr::EET_GUI_EVENT) {
        idScene = this->getSceneFromId(event.GUIEvent.Caller->getID());
        idObj = this->getObjIdFromId(event.GUIEvent.Caller->getID());
		// if (idObj == SERVER_ROOM_OBJ_ID::CHAT_INPUT) {
        //     ptr = getObjbyId(SERVER_ROOM_OBJ_ID::CHAT_INPUT);
        //     cptr = static_cast<UIEditBox *>(ptr);
        //     if (cptr->isClicked() == false && event.GUIEvent.EventType == 1) {
        //         cptr->setClicked();
        //         _idLastEditBoxClicked = idObj;
        //         ptr = getObjbyId(SERVER_CONNECT_OBJ_ID::PORT_INPUT);
        //         cptr = static_cast<UIEditBox *>(ptr);
        //         cptr->setUnclicked();
        //         _actualStatu = DEFAULT;
        //     }
        // }
    }
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
        ptr = getObjbyId(SERVER_ROOM_OBJ_ID::CHAT_INPUT);
        cptr = static_cast<UIEditBox *>(ptr);
        if (event.KeyInput.Key == irr::EKEY_CODE::KEY_BACK)
            cptr->removeCharacter();
		if (event.KeyInput.Key == irr::EKEY_CODE::KEY_RETURN) {
            _servclient->chat(cptr->getText());
			std::string t = "";
			cptr->setText(t);
		}
        if (isInAlphabet(event.KeyInput.Char) == true) {
            cptr->addCharacter(event.KeyInput.Char);
        }
    }
    if (idScene == UI_SCENE_ID::SERVER_ROOM) {
        if (idObj == SERVER_ROOM_OBJ_ID::LIST_LEFT_ARROW &&
        event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
            _serverRoom->showPrevPage();
        }
        if (idObj == SERVER_ROOM_OBJ_ID::LIST_RIGHT_ARROW &&
        event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
            _serverRoom->showNextPage();
        }
        if (idObj >= 500) {
            if (event.GUIEvent.EventType == 1)
                _serverRoom->setRowClicked(idObj - 500);
            else
                _serverRoom->setRowHover(idObj - 500);
        } else {
            _serverRoom->unhover();
        }
        switch (idObj) {
            case SERVER_ROOM_OBJ_ID::JOIN_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::SERVER_ROOM, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "JOIN BUTTON CLICKED" << std::endl;
					_servclient->joinRoom(_serverRoom->getRowSelected());
				}
            break;
            case SERVER_ROOM_OBJ_ID::CREATE_BUTTON:
                if (buttonUpdate(event, nextScene, nextScene.sceneId, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "CREATE BUTTON CLICKED" << std::endl;
                    nextScene.sceneId = UI_SCENE_ID::SERVER_LOBBY;
                    _servclient->createRoom();
                    }
            break;
            case SERVER_ROOM_OBJ_ID::BACK_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::MENU, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "BACK BUTTON CLICKED" << std::endl;
					_servclient->quit();
                }
            break;
            case SERVER_ROOM_OBJ_ID::SETTINGS_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::OPTION, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "SETTINGS BUTTON CLICKED" << std::endl;
                }
            break;
            case SERVER_ROOM_OBJ_ID::ABOUT_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::HELP, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "BACK BUTTON CLICKED" << std::endl;
                }
            break;
        }
    }
	return true;
}

void InterfaceServerRoom::room(std::vector<std::string> vect)
{
    int i = 3;
    std::vector<std::string> array;
    std::string tmp;

	IInterfaceObj *ptr = getObjbyId(SERVER_ROOM_OBJ_ID::NB_PLAYER);
    UISmartListBox *cptr = static_cast<UISmartListBox *>(ptr);
	tmp = "Number of players : " + vect[2];
	array.push_back(tmp);
	cptr->setArray(array);
	tmp.clear();
	array.clear();

    while (i < vect.size() - 1) {

        if (vect[i + 1] == "1")
            tmp = "Server[" + vect[i] + "]  -  " + vect[i + 1] + " player is waiting for fun";
        else
            tmp = "Server[" + vect[i] + "]  -  " + vect[i + 1] + " player are waiting for fun";
        // std::cout << tmp << std::endl;
        array.push_back(tmp);
        i += 2;
    }
    ptr = getObjbyId(SERVER_ROOM_OBJ_ID::SERVER_SMART_LIST);
    cptr = static_cast<UISmartListBox *>(ptr);
    cptr->setArray(array);
}

void InterfaceServerRoom::chat(std::vector<std::string> msg)
{
	IInterfaceObj *ptr = getObjbyId(SERVER_ROOM_OBJ_ID::CHAT_LIST);
    UISmartListBox *cptr = static_cast<UISmartListBox *>(ptr);
	std::vector<std::string> array = cptr->getArray();
    std::string tmp;
	msg.erase(msg.begin());
	for (auto e : msg) {
		tmp += e;
		tmp += " ";
	}

    array.push_back(tmp);
	if (array.size() > 16)
		array.erase(array.begin());

    cptr->setArray(array);
}

void InterfaceServerRoom::pointerFct(std::vector<std::string> action)
{
    command_t const arr_cmd[] = {
	{"QUIT", &InterfaceServerRoom::quit},
    {"CHAT", &InterfaceServerRoom::chat},
	{"LOG", &InterfaceServerRoom::log}, 
	{"ROOM", &InterfaceServerRoom::room},
	{"INFOROOM", &InterfaceServerRoom::infoRoom}, 
    {"CREATEROOM", &InterfaceServerRoom::createRoom},
    {"JOINROOM", &InterfaceServerRoom::joinRoom},
	{"LEAVEROOM", &InterfaceServerRoom::leaveRoom},
	{"SETUSERNAME", &InterfaceServerRoom::setUserName},
    {"PLAY", &InterfaceServerRoom::play},
	{"PROMOTE", &InterfaceServerRoom::promote}};

	for (auto e: arr_cmd) {
		if (e.cmd == action[0]) {
			(this->*e.cmd_name)(action);
			return;
		}
	}
    return;
}

void InterfaceServerRoom::joinRoom(std::vector<std::string> arr)
{
	if (arr[1] == "OK")
		_nextScene.sceneId = UI_SCENE_ID::SERVER_LOBBY;
}

void InterfaceServerRoom::unstackActionServe()
{
	std::vector<std::string> strs;
	for (auto &e : _servclient->_action) {
		boost::split(strs,e, boost::is_any_of(" "));
		pointerFct(strs);
		if (strs[0] == "JOINROOM") {
			e = "a";
			strs.clear();
			return;
		}
		strs.clear();
	}
	_servclient->_action.clear();
}

bool InterfaceServerRoom::update()
{
    // std::cout << "_serverRoom->getRowSelected() = " << _serverRoom->getRowSelected() << std::endl;
    // std::cout << "_serverRoom->getRowSelectedText() = " << _serverRoom->getRowSelectedText() << std::endl;
	IInterfaceObj *ptr = getObjbyId(SERVER_ROOM_OBJ_ID::CHAT_INPUT);
    UIEditBox *cptr = dynamic_cast<UIEditBox *>(ptr);
    updateVisibleObj();
	if (cptr)
        cptr->update();
	unstackActionServe();
    return true;
}