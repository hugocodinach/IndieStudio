/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/InterfaceGameMode.cpp
*/

#include "InterfaceGameMode.hpp"

InterfaceGameMode::InterfaceGameMode(irr::IrrlichtDevice *device, irr::gui::IGUIEnvironment *guiEnv,
irr::video::IVideoDriver *driver, int id, int prevSceneId, NetworkClient *servclient):
AInterfaceScene(device, guiEnv, driver, id, prevSceneId)
{
    this->create();
    _prevStatu = -1;
    _allStatu = GAME_MODE_STATU::ALL;
	_servclient = servclient;
	_servclient->run("127.0.0.1", "5909");
}

InterfaceGameMode::~InterfaceGameMode()
{
    // std::cout << "~InterfaceGameMode" << std::endl;
}

void InterfaceGameMode::create()
{
    UIButton *new_button;
    UIImage *new_image;
    UIText *new_text;
    UILateralMenu *new_menu;
    IInterfaceObj *new_obj;

//BACK ARROW
    new_button = new UIButton(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::BACK_BUTTON),
    irr::core::rect<irr::f32>(3, 5, 3 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 630, 630),
    "sb_back_arrow",
    "./ressources/UI/global/back_arrow_idle.png",
    "./ressources/UI/global/back_arrow_hover.png",
    "./ressources/UI/global/back_arrow_clicked.png");
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::ALL}, new_button));
//LEFT ARROW
    new_button = new UIButton(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::LEFT_ARROW),
    irr::core::rect<irr::f32>(33, 15, 33 + 3, 15 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png");
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::ALL}, new_button));
//RIGHT ARROW
    new_button = new UIButton(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::RIGHT_ARROW),
    irr::core::rect<irr::f32>(57, 15, 57 + 3, 15 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png");
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::ALL}, new_button));
//MODE TEXT (as image)
    new_image = new UIImage(_guiEnv, computeObjId(GAME_MODE_OBJ_ID::TEXT_MODE),
    irr::core::rect<irr::f32>(37, 15, 56, 15 + 5),
    _driver->getTexture("./ressources/UI/gameMode/Jeu_sur_cet_ordi.png"));
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::ALL}, new_image));
//LATERAL MENU
    new_menu = new UILateralMenu(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::MODE_MENU),
    getObjbyId(GAME_MODE_OBJ_ID::LEFT_ARROW),
    getObjbyId(GAME_MODE_OBJ_ID::RIGHT_ARROW),
    getObjbyId(GAME_MODE_OBJ_ID::TEXT_MODE),
    {"./ressources/UI/gameMode/Jeu_sur_cet_ordi.png",
    "./ressources/UI/gameMode/Jeu_en_reseau_local.png",
    "./ressources/UI/gameMode/Jeu_en_ligne.png"});
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::ALL}, new_menu));
    _actualStatu = new_menu->getActualTextureNb();
//GAME MODE OPTION BACKGROUND
    new_image = new UIImage(_guiEnv, computeObjId(GAME_MODE_OBJ_ID::BACKGROUND_OPTION),
    irr::core::rect<irr::f32>(30, 22, 63, 77),
    _driver->getTexture("./ressources/UI/main/fond_menu_binding.png"));
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::ALL}, new_image));
//LIST BOX
    new_obj = new UISmartListBox(_driver,
            _guiEnv, irr::core::rect<irr::f32>(31.25, 27.77, 100, 100),
            computeObjId(GAME_MODE_OBJ_ID::SERVER_SMART_LIST),
            {"serveur_01  le meilleur serv  1 sur 4",
            "serveur_01  le meilleur serv  2 sur 4",
            "serveur_01  le meilleur serv  3 sur 4",
            "serveur_01  le meilleur serv  4 sur 4",
            "serveur_01  le meilleur serv  5 sur 4",
            "serveur_01  le meilleur serv  6 sur 4",
            "serveur_01  le meilleur serv  7 sur 4",
            "serveur_01  le meilleur serv  8 sur 4"}, 16, 4);
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::LOCAL_NETWORK,
    GAME_MODE_STATU::ONLINE}, new_obj));
//LIST LEFT ARROW
    new_button = new UIButton(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::LIST_LEFT_ARROW),
    irr::core::rect<irr::f32>(35, 70, 35 + 3, 70 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_list_left_arrow",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png",
    "./ressources/UI/gameMode/left_arrow.png");
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::LOCAL_NETWORK,
    GAME_MODE_STATU::ONLINE}, new_button));
//LIST RIGHT ARROW
    new_button = new UIButton(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::LIST_RIGHT_ARROW),
    irr::core::rect<irr::f32>(55, 70, 55 + 3, 70 + 5),
    irr::core::rect<irr::s32>(0, 0, 233, 295),
    "sb_list_left_arrow",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png",
    "./ressources/UI/gameMode/right_arrow.png");
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::LOCAL_NETWORK,
    GAME_MODE_STATU::ONLINE}, new_button));
//JOIN BUTTON LOCAL NETWORK
    new_button = new UIButton(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::JOIN_BUTTON),
    irr::core::rect<irr::f32>(46, 70, 46 + 8, 70 + 5),
    irr::core::rect<irr::s32>(0, 0, 600, 230),
    "sb_join_arrow",
    "./ressources/UI/gameMode/join_button_idle.png",
    "./ressources/UI/gameMode/join_button_hover.png",
    "./ressources/UI/gameMode/join_button_clicked.png");
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::LOCAL_NETWORK,
    GAME_MODE_STATU::ONLINE}, new_button));
//CREATE BUTTON LOCAL NETWORK
    new_button = new UIButton(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::CREATE_BUTTON),
    irr::core::rect<irr::f32>(39, 70, 39 + 5, 70 + 5),
    irr::core::rect<irr::s32>(0, 0, 850, 250),
    "sb_create_arrow",
    "./ressources/UI/gameMode/create_button_idle.png",
    "./ressources/UI/gameMode/create_button_hover.png",
    "./ressources/UI/gameMode/create_button_clicked.png");
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::LOCAL_NETWORK,
    GAME_MODE_STATU::ONLINE}, new_button));
//NUMBER OF PLAYER TEXT
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::PLAYER_SELECT_TEXT),
    "NUMBER OF PLAYER", irr::core::position2df(33.85, 32.40), 32);
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::PLAY_ON_THIS_COMPUTER}, new_obj));
//TWO PLAYER TEXT
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::PLAYER_SELECT_TEXT),
    "2", irr::core::position2df(35.7, 41.66), 32);
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::PLAY_ON_THIS_COMPUTER}, new_obj));
//TWO PLAYER BOX
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::TWO_PLAYER_SELECT_BOX),
    irr::core::rect<irr::f32>(35, 45, 35 + 3, 45 + 5),
    irr::core::rect<irr::s32>(0, 0, 256, 256),
    "sb_box_arrow",
    "./ressources/UI/gameMode/select_box_idle.png",
    "./ressources/UI/gameMode/select_box_hover.png",
    "./ressources/UI/gameMode/select_box_clicked.png");
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::PLAY_ON_THIS_COMPUTER}, new_obj));
//THREE PLAYER TEXT
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::PLAYER_SELECT_TEXT),
    "3", irr::core::position2df(46.7, 41.66), 32);
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::PLAY_ON_THIS_COMPUTER}, new_obj));
//THREE PLAYER BOX
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::THREE_PLAYER_SELECT_BOX),
    irr::core::rect<irr::f32>(46, 45, 46 + 3, 45 + 5),
    irr::core::rect<irr::s32>(0, 0, 256, 256),
    "sb_box_arrow",
    "./ressources/UI/gameMode/select_box_idle.png",
    "./ressources/UI/gameMode/select_box_hover.png",
    "./ressources/UI/gameMode/select_box_clicked.png");
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::PLAY_ON_THIS_COMPUTER}, new_obj));
//FOUR PLAYER TEXT
    new_obj = new UISmartText(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::PLAYER_SELECT_TEXT),
    "4", irr::core::position2df(56.7, 41.66), 32);
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::PLAY_ON_THIS_COMPUTER}, new_obj));
//FOUR PLAYER BOX
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::FOUR_PLAYER_SELECT_BOX),
    irr::core::rect<irr::f32>(56, 45, 56 + 3, 45 + 5),
    irr::core::rect<irr::s32>(0, 0, 256, 256),
    "sb_box_arrow",
    "./ressources/UI/gameMode/select_box_idle.png",
    "./ressources/UI/gameMode/select_box_hover.png",
    "./ressources/UI/gameMode/select_box_clicked.png");
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::PLAY_ON_THIS_COMPUTER}, new_obj));
//PLAY BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::PLAY_BUTTON),
    irr::core::rect<irr::f32>(37, 55, 37 + 20, 55 + 15),
    irr::core::rect<irr::s32>(0, 0, 530, 122),
    "sb_play",
    "./ressources/UI/main/play_idle.png",
    "./ressources/UI/main/play_over.png",
    "./ressources/UI/main/play_clicked.png");
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::PLAY_ON_THIS_COMPUTER}, new_obj));
//SETTINGS BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::SETTINGS_BUTTON),
    irr::core::rect<irr::f32>(85, 5, 85 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 270, 300),
    "sb_settings",
    "./ressources/UI/global/settings_idle.png",
    "./ressources/UI/global/settings_over.png",
    "./ressources/UI/global/settings_clicked.png");
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::ALL}, new_obj));
//ABOUT BUTTON
    new_obj = new UIButton(_driver, _guiEnv, computeObjId(GAME_MODE_OBJ_ID::ABOUT_BUTTON),
    irr::core::rect<irr::f32>(90, 5, 90 + 3, 5 + 5),
    irr::core::rect<irr::s32>(0, 0, 512, 542),
    "sb_about",
    "./ressources/UI/global/about_idle.png",
    "./ressources/UI/global/about_over.png",
    "./ressources/UI/global/about_clicked.png");
    _objs.push_back(std::make_pair(std::vector<int>{GAME_MODE_STATU::ALL}, new_obj));
}

bool InterfaceGameMode::manageEvent(const irr::SEvent& event, sceneInfo_t &nextScene)
{
    int idScene = -1;
    int idObj = -1;

    if (event.EventType == irr::EET_GUI_EVENT) {
        idScene = this->getSceneFromId(event.GUIEvent.Caller->getID());
        idObj = this->getObjIdFromId(event.GUIEvent.Caller->getID());
    }
    if (idScene == UI_SCENE_ID::GAME_MODE) {
        if (idObj == GAME_MODE_OBJ_ID::RIGHT_ARROW &&
        event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
            IInterfaceObj *ptr = getObjbyId(GAME_MODE_OBJ_ID::MODE_MENU);
            UILateralMenu *cptr = static_cast<UILateralMenu *>(ptr);
            cptr->nextTextureRight();
            _actualStatu = cptr->getActualTextureNb();
        }
        if (idObj == GAME_MODE_OBJ_ID::LEFT_ARROW &&
        event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
            IInterfaceObj *ptr = getObjbyId(GAME_MODE_OBJ_ID::MODE_MENU);
            UILateralMenu *cptr = static_cast<UILateralMenu *>(ptr);
            cptr->nextTextureLeft();
            _actualStatu = cptr->getActualTextureNb();
        }
        if (idObj == GAME_MODE_OBJ_ID::LIST_LEFT_ARROW &&
        event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
            IInterfaceObj *ptr = getObjbyId(GAME_MODE_OBJ_ID::SERVER_SMART_LIST);
            UISmartListBox *cptr = static_cast<UISmartListBox *>(ptr);
            cptr->showPrevPage();
        }
        if (idObj == GAME_MODE_OBJ_ID::LIST_RIGHT_ARROW &&
        event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
            IInterfaceObj *ptr = getObjbyId(GAME_MODE_OBJ_ID::SERVER_SMART_LIST);
            UISmartListBox *cptr = static_cast<UISmartListBox *>(ptr);
            cptr->showNextPage();
        }
        if (idObj >= 500) {
            // std::cout << "event.GUIEvent.EventType = " << event.GUIEvent.EventType << std::endl;
            IInterfaceObj *ptr = getObjbyId(GAME_MODE_OBJ_ID::SERVER_SMART_LIST);
            UISmartListBox *cptr = static_cast<UISmartListBox *>(ptr);
            if (event.GUIEvent.EventType == 1)
                cptr->setRowClicked(idObj - 500);
            else
                cptr->setRowHover(idObj - 500);
        } else {
            IInterfaceObj *ptr = getObjbyId(GAME_MODE_OBJ_ID::SERVER_SMART_LIST);
            UISmartListBox *cptr = static_cast<UISmartListBox *>(ptr);
            cptr->unhover();
        }
        switch (idObj) {
            case GAME_MODE_OBJ_ID::JOIN_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::LOBBY, idObj) == BUTTON_STATU::CLICKED)
                    // std::cout << "JOIN BUTTON CLICKED" << std::endl;
            break;
            case GAME_MODE_OBJ_ID::CREATE_BUTTON:
                if (buttonUpdate(event, nextScene, nextScene.sceneId, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "CREATE BUTTON CLICKED" << std::endl;
                    nextScene.sceneId = UI_SCENE_ID::LOBBY;
                    _servclient->createRoom();
                    }
            break;
            case GAME_MODE_OBJ_ID::TWO_PLAYER_SELECT_BOX:
                if (buttonUpdate(event, nextScene, nextScene.sceneId, idObj) == BUTTON_STATU::CLICKED)
                    // std::cout << "TWO BUTTON CLICKED" << std::endl;
            break;
            case GAME_MODE_OBJ_ID::THREE_PLAYER_SELECT_BOX:
                if (buttonUpdate(event, nextScene, nextScene.sceneId, idObj) == BUTTON_STATU::CLICKED)
                    // std::cout << "THREE BUTTON CLICKED" << std::endl;
            break;
            case GAME_MODE_OBJ_ID::FOUR_PLAYER_SELECT_BOX:
                if (buttonUpdate(event, nextScene, nextScene.sceneId, idObj) == BUTTON_STATU::CLICKED)
                    // std::cout << "FOUR BUTTON CLICKED" << std::endl;
            break;
            case GAME_MODE_OBJ_ID::PLAY_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::LOBBY, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "PLAY BUTTON CLICKED" << std::endl;
                }
            break;
            case GAME_MODE_OBJ_ID::BACK_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::MENU, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "BACK BUTTON CLICKED" << std::endl;
                }
            break;
            case GAME_MODE_OBJ_ID::SETTINGS_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::OPTION, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "SETTINGS BUTTON CLICKED" << std::endl;
                }
            break;
            case GAME_MODE_OBJ_ID::ABOUT_BUTTON:
                if (buttonUpdate(event, nextScene, UI_SCENE_ID::MENU, idObj) == BUTTON_STATU::CLICKED) {
                    // std::cout << "BACK BUTTON CLICKED" << std::endl;
                }
            break;
        }
    }
	return true;
}

void InterfaceGameMode::room(std::vector<std::string> vect)
{
	int i = 1;
	std::vector<std::string> array;
	std::string tmp;

	while (i < vect.size() - 1) {
		tmp = "id: " + vect[i] + " nb people: " + vect[i + 1];
		// std::cout << tmp << std::endl;
		array.push_back(tmp);
		i += 2;
	}
	IInterfaceObj *ptr = getObjbyId(GAME_MODE_OBJ_ID::SERVER_SMART_LIST);
    UISmartListBox *cptr = static_cast<UISmartListBox *>(ptr);
    cptr->setArray(array);
}

void InterfaceGameMode::pointerFct(std::vector<std::string> action)
{
    command_t const arr_cmd[12] = {
	{"QUIT", &InterfaceGameMode::quit},
    {"CHAT", &InterfaceGameMode::chat},
	{"LOG", &InterfaceGameMode::log}, 
	{"ROOM", &InterfaceGameMode::room},
	{"INFOROOM", &InterfaceGameMode::infoRoom}, 
    {"CREATEROOM", &InterfaceGameMode::createRoom},
	{"LEAVEROOM", &InterfaceGameMode::leaveRoom},
	{"SETUSERNAME", &InterfaceGameMode::setUserName},
    {"PLAY", &InterfaceGameMode::play},
	{"PROMOTE", &InterfaceGameMode::promote}};

	for (auto e: arr_cmd) {
		if (e.cmd == action[0]) {
			(this->*e.cmd_name)(action);
			return;
		}
	}
    return;
}

void InterfaceGameMode::unstackActionServe()
{
	std::vector<std::string> strs;
	for (auto e : _servclient->_action) {
		boost::split(strs,e, boost::is_any_of(" "));
		pointerFct(strs);
		strs.clear();
	}
	_servclient->_action.clear();
}

bool InterfaceGameMode::update()
{
    updateVisibleObj();
	unstackActionServe();
    return true;
}