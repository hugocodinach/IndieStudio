/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/InterfaceManager.cpp
*/

#include "InterfaceManager.hpp"
#include "InterfaceMenu.hpp"
#include "InterfacePlay.hpp"
#include "InterfaceServerRoom.hpp"
#include "InterfaceKeyBinding.hpp"
#include "InterfaceLocalLobby.hpp"
#include "InterfaceServerLobby.hpp"
#include "InterfaceOption.hpp"
#include "InterfaceServerConnect.hpp"
#include "InterfaceKeyBinding.hpp"
#include "InterfaceHelp.hpp"

class InterfaceKeyBinding;

InterfaceManager::InterfaceManager(irr::IrrlichtDevice *device,
irr::gui::IGUIEnvironment *guiEnv, irr::video::IVideoDriver *driver, SplashScreen splash):
_device(device), _guiEnv(guiEnv), _driver(driver), _musicPlayer()
{
    if (MUSIC == 1)
    {
        _musicPlayer.playMusicPlayer("SPLASH");
    }
    splash.run();
    IInterfaceScene *scene_menu = new InterfaceMenu(_device, _guiEnv, _driver, UI_SCENE_ID::MENU, _sceneStack, _musicPlayer);
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::FORWARD_INPUT_J1, std::make_pair("FORWARD", KeyHandler(irr::EKEY_CODE::KEY_KEY_Z))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::BACKWARD_INPUT_J1, std::make_pair("BACKWARD", KeyHandler(irr::EKEY_CODE::KEY_KEY_S))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::LEFT_INPUT_J1, std::make_pair("LEFT", KeyHandler(irr::EKEY_CODE::KEY_KEY_Q))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::RIGHT_INPUT_J1, std::make_pair("RIGHT", KeyHandler(irr::EKEY_CODE::KEY_KEY_D))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::DROP_BOMB_INPUT_J1, std::make_pair("DROP BOMB", KeyHandler(irr::EKEY_CODE::KEY_KEY_E))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::INTERACTION_INPUT_J1, std::make_pair("INTERACTE", KeyHandler(irr::EKEY_CODE::KEY_KEY_A))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::FORWARD_INPUT_J2, std::make_pair("FORWARD", KeyHandler(irr::EKEY_CODE::KEY_KEY_G))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::BACKWARD_INPUT_J2, std::make_pair("BACKWARD", KeyHandler(irr::EKEY_CODE::KEY_KEY_B))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::LEFT_INPUT_J2, std::make_pair("LEFT", KeyHandler(irr::EKEY_CODE::KEY_KEY_V))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::RIGHT_INPUT_J2, std::make_pair("RIGHT", KeyHandler(irr::EKEY_CODE::KEY_KEY_N))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::DROP_BOMB_INPUT_J2, std::make_pair("DROP BOMB", KeyHandler(irr::EKEY_CODE::KEY_KEY_H))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::INTERACTION_INPUT_J2, std::make_pair("INTERACTE", KeyHandler(irr::EKEY_CODE::KEY_KEY_F))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::FORWARD_INPUT_J3, std::make_pair("FORWARD", KeyHandler(irr::EKEY_CODE::KEY_KEY_I))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::BACKWARD_INPUT_J3, std::make_pair("BACKWARD", KeyHandler(irr::EKEY_CODE::KEY_KEY_K))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::LEFT_INPUT_J3, std::make_pair("LEFT", KeyHandler(irr::EKEY_CODE::KEY_KEY_J))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::RIGHT_INPUT_J3, std::make_pair("RIGHT", KeyHandler(irr::EKEY_CODE::KEY_KEY_L))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::DROP_BOMB_INPUT_J3, std::make_pair("DROP BOMB", KeyHandler(irr::EKEY_CODE::KEY_KEY_O))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::INTERACTION_INPUT_J3, std::make_pair("INTERACTE", KeyHandler(irr::EKEY_CODE::KEY_KEY_U))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::FORWARD_INPUT_J4, std::make_pair("FORWARD", KeyHandler(irr::EKEY_CODE::KEY_UP))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::BACKWARD_INPUT_J4, std::make_pair("BACKWARD", KeyHandler(irr::EKEY_CODE::KEY_DOWN))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::LEFT_INPUT_J4, std::make_pair("LEFT", KeyHandler(irr::EKEY_CODE::KEY_LEFT))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::RIGHT_INPUT_J4, std::make_pair("RIGHT", KeyHandler(irr::EKEY_CODE::KEY_RIGHT))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::DROP_BOMB_INPUT_J4, std::make_pair("DROP BOMB", KeyHandler(irr::EKEY_CODE::KEY_NEXT))});
    _keys.insert({InterfaceKeyBinding::KEY_BINDING_OBJ_ID::INTERACTION_INPUT_J4, std::make_pair("INTERACTE", KeyHandler(irr::EKEY_CODE::KEY_PRIOR))});
    _actualScene = scene_menu;
    _nextScene.sceneId = _actualScene->getId();
    _game = nullptr;
    _servclient = new NetworkClient();
    _nextScene.isOnline = false;
    _option.useCoinMode = false;
    _option.soundVolume = 3;
    _option.musicVolume = 3;
}

InterfaceManager::~InterfaceManager()
{
}

void InterfaceManager::onUIEvent(const irr::SEvent &event)
{
    if (_option.useCoinMode)
        _musicPlayer.playSoundPlayer("BUTTON_CLICKED");
    _actualScene->manageEvent(event, _nextScene);
    if (_nextScene.sceneId != _actualScene->getId())
        this->changeScene(_nextScene.sceneId);
}

bool InterfaceManager::changeScene(int nextSceneId)
{
    int tmpSceneId = _actualScene->getId();

    if (!_actualScene->isFromBack()) {
        _sceneStack.push_back(tmpSceneId);
    }
    delete _actualScene;
    _guiEnv->clear();
    switch (nextSceneId)
    {
        case UI_SCENE_ID::MENU:
            _actualScene = new InterfaceMenu(_device, _guiEnv, _driver, UI_SCENE_ID::MENU,
            _sceneStack, _musicPlayer);
            _nextScene.sceneId = UI_SCENE_ID::MENU;
            break;
        case UI_SCENE_ID::PLAY:
            _actualScene = new InterfacePlay(_device, _guiEnv, _driver, UI_SCENE_ID::PLAY,
            _sceneStack, _nextScene.users, _game, _musicPlayer, _servclient);
            _game->setInterfacePLay(static_cast<InterfacePlay*>(_actualScene));
            if (_nextScene.isOnline == true) {
                 _game->initOnline(_nextScene.users[_nextScene.idxLocalUser].characterId,
                 _servclient);
            } else if (_nextScene.loadGame == true) {
                _game->initLoad();
            } else {
                _game->initSolo(_nextScene.users,
                {(_keys.at(KB::LEFT_INPUT_J1).second), (_keys.at(KB::BACKWARD_INPUT_J1).second), (_keys.at(KB::RIGHT_INPUT_J1).second), (_keys.at(KB::FORWARD_INPUT_J1).second), (_keys.at(KB::DROP_BOMB_INPUT_J1).second), (_keys.at(KB::INTERACTION_INPUT_J1).second)},
                {(_keys.at(KB::LEFT_INPUT_J2).second), (_keys.at(KB::BACKWARD_INPUT_J2).second), (_keys.at(KB::RIGHT_INPUT_J2).second), (_keys.at(KB::FORWARD_INPUT_J2).second), (_keys.at(KB::DROP_BOMB_INPUT_J2).second), (_keys.at(KB::INTERACTION_INPUT_J2).second)},
                {(_keys.at(KB::LEFT_INPUT_J3).second), (_keys.at(KB::BACKWARD_INPUT_J3).second), (_keys.at(KB::RIGHT_INPUT_J3).second), (_keys.at(KB::FORWARD_INPUT_J3).second), (_keys.at(KB::DROP_BOMB_INPUT_J3).second), (_keys.at(KB::INTERACTION_INPUT_J3).second)},
                {(_keys.at(KB::LEFT_INPUT_J4).second), (_keys.at(KB::BACKWARD_INPUT_J4).second), (_keys.at(KB::RIGHT_INPUT_J4).second), (_keys.at(KB::FORWARD_INPUT_J4).second), (_keys.at(KB::DROP_BOMB_INPUT_J4).second), (_keys.at(KB::INTERACTION_INPUT_J4).second)});
            }
            _game->startGame();
            _nextScene.sceneId = UI_SCENE_ID::PLAY;
            break;
        case UI_SCENE_ID::SERVER_ROOM:
            _actualScene = new InterfaceServerRoom(_device, _guiEnv, _driver, UI_SCENE_ID::SERVER_ROOM,
            _sceneStack, _servclient, _musicPlayer, _nextScene);
            _nextScene.sceneId = UI_SCENE_ID::SERVER_ROOM;
            break;
        case UI_SCENE_ID::KEY_BINDING:
            _actualScene = new InterfaceKeyBinding(_device, _guiEnv, _driver, UI_SCENE_ID::KEY_BINDING,
            _sceneStack, _keys, _musicPlayer);
            _nextScene.sceneId = UI_SCENE_ID::KEY_BINDING;
            break;
        case UI_SCENE_ID::LOCAL_LOBBY:
            _actualScene = new InterfaceLocalLobby(_device, _guiEnv, _driver, UI_SCENE_ID::LOCAL_LOBBY,
            _sceneStack, _musicPlayer);
            _nextScene.sceneId = UI_SCENE_ID::LOCAL_LOBBY;
            break;
        case UI_SCENE_ID::OPTION:
            _actualScene = new InterfaceOption(_device, _guiEnv, _driver, UI_SCENE_ID::OPTION,
            _sceneStack, _musicPlayer, _option);
            _nextScene.sceneId = UI_SCENE_ID::OPTION;
            break;
        case UI_SCENE_ID::SERVER_CONNECT:
            _actualScene = new InterfaceServerConnect(_device, _guiEnv, _driver, UI_SCENE_ID::SERVER_CONNECT,
            _sceneStack, _servclient, _musicPlayer);
            _nextScene.sceneId = UI_SCENE_ID::SERVER_CONNECT;
            break;
        case UI_SCENE_ID::SERVER_LOBBY:
            _actualScene = new InterfaceServerLobby(_device, _guiEnv, _driver, UI_SCENE_ID::SERVER_LOBBY,
            _sceneStack, _servclient, _musicPlayer, _nextScene);
            _nextScene.sceneId = UI_SCENE_ID::SERVER_LOBBY;
            break;
        case UI_SCENE_ID::HELP:
            _actualScene = new InterfaceHelp(_device, _guiEnv, _driver, UI_SCENE_ID::HELP,
            _sceneStack, _musicPlayer);
            _nextScene.sceneId = UI_SCENE_ID::HELP;
            break;
        case UI_SCENE_ID::QUIT:
            _nextScene.sceneId = UI_SCENE_ID::QUIT;
            endGame();
            _device->closeDevice();
            break;
        default:
            // std::cout << "UNKNOW SCENE" << std::endl;
            break;
    }
    return true;
}
/*
bool getLoadedScene(void) const
{
    if (_actualScene)
    return (_actualScene);
}
*/

void InterfaceManager::endGame(void)
{
    delete _game;
    delete _servclient;
    _musicPlayer.~MusicPlayer();
}

void InterfaceManager::launchGame(void)
{
    _game = new GameModule(_device, _musicPlayer);
    _game->initGameModule();
}

bool InterfaceManager::update(void)
{
    if (_game)
        _game->run();
	if (_nextScene.sceneId != _actualScene->getId()) 
        this->changeScene(_nextScene.sceneId);
	if ( _nextScene.autotrigger == true) {
		irr::SEvent event;
		_actualScene->manageEvent(event, _nextScene);
		_nextScene.autotrigger = false;
	}
    return _actualScene->update();
}