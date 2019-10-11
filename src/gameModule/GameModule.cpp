/*
** EPITECH PROJECT, 2018
** GameModule.cpp
** File description:
** src/gameModule/GameModule.cpp
*/

#include "GameModule.hpp"
#include "AI.hpp"
extern irr::core::array<irr::SJoystickInfo> myjoystickInfo;

GameModule::GameModule(irr::IrrlichtDevice *device, MusicPlayer &musicPlayer) :
_mapHandler(MapHandler(_vectBomb, _vectBonus, _scores)), _Musicplayer(musicPlayer)
{
    _device = device;
    _driver = _device->getVideoDriver();
    _smgr = _device->getSceneManager();
    _scores.push_back(0);
    _scores.push_back(0);
    _scores.push_back(0);
    _scores.push_back(0);
    _startedGame = false;

    if (MUSIC == 1)
    {
//        _Musicplayer = new MusicPlayer;
        _Musicplayer.setLoopMusicPlayer("MENU", true);
        _Musicplayer.playMusicPlayer("MENU");
    }
    _launchGame = false;
    _saver = new Saver();
    _loader = new Loader();
};

GameModule::~GameModule()
{
    _smgr->clear();
};

void GameModule::drawMap(bool init)
{
    if (_seed == 0)
    {
        srand(time(NULL));
        _seed = rand() % 10000;
    }
    srand(_seed);
    _mapHandler.setMng(_smgr);
    if (init == true) {
        #ifdef __linux__
            _mapHandler.setMap(popen(("./rub ./script/MapPattern.rb " + std::to_string(_seed)).c_str(), "r"));
        #elif _WIN32
            _mapHandler.setMap(_popen(("rub.exe ./script/MapPattern.rb " + std::to_string(_seed)).c_str(), "r"));
        #else
        #endif
    } else {
        _mapHandler.setMap();
    }

    int x = -300;
    int y = -300;
    int wy = 0;
    int wx = 0;
    for (auto e : _mapHandler.getMap())
    {
        for (auto a : e)
        {
            if (a == '2')
            {
                node = _smgr->addMeshSceneNode(_smgr->getMesh("./ressources/models/Walls/tree.3ds"), 0);
                node->setPosition(irr::core::vector3df(y, 0, x));
                node->getMaterial(0).NormalizeNormals = true;
                node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		_trees.push_back(node);
                if (rand() % 6 == 0)
                    TreeParticule *part = new TreeParticule(_smgr, node);
            }
            else if (a == '1')
            {
                _vectBlockDestruct.push_back(new BlockDestruct(_smgr, irr::core::vector3df(y, 0, x), wx, wy, "./ressources/foin.jpg"));
            }

            x += TILE_SIZE;
            wx += 1;
        }
        wx = 0;
        wy += 1;
        x = -300;
        y += TILE_SIZE;
    }
}

void GameModule::setInterfacePLay(InterfacePlay *interf)
{
	_interfacePlay = interf;
}

void GameModule::initPlayers(int nbPlayer,
                 std::vector<character_t> characterVect,
                 std::vector<KeyHandler> P1Key,
                 std::vector<KeyHandler> P2Key,
                 std::vector<KeyHandler> P3Key,
                 std::vector<KeyHandler> P4Key)
{
    Bomberman *_bomber = new Bomberman(_smgr, irr::core::vector3df(-300 + (characterVect[0].y * TILE_SIZE), 0, -300 + (characterVect[0].x * TILE_SIZE)), characterVect[0].x, characterVect[0].y, characterVect[0].playerIDX, _vect_mesh, characterVect[0].characterIDX);
    _bomber->setInput(0, KeyHandler(P1Key[0]));
    _bomber->setInput(1, KeyHandler(P1Key[1]));
    _bomber->setInput(2, KeyHandler(P1Key[2]));
    _bomber->setInput(3, KeyHandler(P1Key[3]));
    _bomber->setInput(4, KeyHandler(P1Key[4]));
    _bomber->setInput(5, KeyHandler(P1Key[5]));
    if (_network != nullptr)
    {
        _bomber->setNetwork(_network);
    }
    _vect_actor.push_back(_bomber);
    _controlVect.push_back(new Controller(_bomber, _event->getKeyVect()));
    if (characterVect[0].playerType == ONLINE_T)
    {
        _bomber->setIsOnline(true);
    }
    if (characterVect[0].playerType == AI_T)
    {
        _AIVect.push_back(new AI(_bomber, *_controlVect.end(), _event->getKeyVect()));
    }
    if (nbPlayer == 1)
    {
        return;
    }

    Bomberman *_bomber2 = new Bomberman(_smgr, irr::core::vector3df(-300 + (characterVect[1].y * TILE_SIZE), 0, -300 + (characterVect[1].x * TILE_SIZE)), characterVect[1].x, characterVect[1].y, characterVect[1].playerIDX, _vect_mesh, characterVect[1].characterIDX);
    _bomber2->setInput(0, KeyHandler(P2Key[0]));
    _bomber2->setInput(1, KeyHandler(P2Key[1]));
    _bomber2->setInput(2, KeyHandler(P2Key[2]));
    _bomber2->setInput(3, KeyHandler(P2Key[3]));
    _bomber2->setInput(4, KeyHandler(P2Key[4]));
    _bomber2->setInput(5, KeyHandler(P2Key[5]));
    if (_network != nullptr)
    {
        _bomber2->setNetwork(_network);
    }
    _vect_actor.push_back(_bomber2);
    _controlVect.push_back(new Controller(_bomber2, _event->getKeyVect()));
    if (characterVect[1].playerType == ONLINE_T)
    {
        _bomber2->setIsOnline(true);
    }
    if (characterVect[1].playerType == AI_T)
    {
        _AIVect.push_back(new AI(_bomber2, *_controlVect.end(), _event->getKeyVect()));
    }
    if (nbPlayer == 2)
    {
        return;
    }
    Bomberman *_bomber3 = new Bomberman(_smgr, irr::core::vector3df(-300 + (characterVect[2].y * TILE_SIZE), 0, -300 + (characterVect[2].x * TILE_SIZE)), characterVect[2].x, characterVect[2].y, characterVect[2].playerIDX, _vect_mesh, characterVect[2].characterIDX);
    _bomber3->setInput(0, KeyHandler(P3Key[0]));
    _bomber3->setInput(1, KeyHandler(P3Key[1]));
    _bomber3->setInput(2, KeyHandler(P3Key[2]));
    _bomber3->setInput(3, KeyHandler(P3Key[3]));
    _bomber3->setInput(4, KeyHandler(P3Key[4]));
    _bomber3->setInput(5, KeyHandler(P3Key[5]));
    if (_network != nullptr)
    {
        _bomber3->setNetwork(_network);
    }
    _vect_actor.push_back(_bomber3);
    _controlVect.push_back(new Controller(_bomber3, _event->getKeyVect()));
    if (characterVect[2].playerType == ONLINE_T)
    {
        _bomber3->setIsOnline(true);
    }
    if (characterVect[2].playerType == AI_T)
    {
        _AIVect.push_back(new AI(_bomber3, *_controlVect.end(), _event->getKeyVect()));
    }
    if (nbPlayer == 3)
    {
        return;
    }
    Bomberman *_bomber4 = new Bomberman(_smgr, irr::core::vector3df(-300 + (characterVect[3].y * TILE_SIZE), 0, -300 + (characterVect[3].x * TILE_SIZE)), characterVect[3].x, characterVect[3].y, characterVect[3].playerIDX, _vect_mesh, characterVect[3].characterIDX);
    _bomber4->setInput(0, KeyHandler(P4Key[0]));
    _bomber4->setInput(1, KeyHandler(P4Key[1]));
    _bomber4->setInput(2, KeyHandler(P4Key[2]));
    _bomber4->setInput(3, KeyHandler(P4Key[3]));
    _bomber4->setInput(4, KeyHandler(P4Key[4]));
    _bomber4->setInput(5, KeyHandler(P4Key[5]));
    if (_network != nullptr)
    {
        _bomber4->setNetwork(_network);
    }
    _vect_actor.push_back(_bomber4);
    _controlVect.push_back(new Controller(_bomber4, _event->getKeyVect()));
    if (characterVect[3].playerType == ONLINE_T)
    {
        _bomber4->setIsOnline(true);
    }
    if (characterVect[3].playerType == AI_T)
    {
        _AIVect.push_back(new AI(_bomber4, *_controlVect.end(), _event->getKeyVect()));
    }
}

bool GameModule::setSeedFromServ(std::vector<std::string> strVect)
{
    setSeed(std::atoi(strVect[1].c_str()));
    return true;
}

void GameModule::setSeed(int s)
{
    _seed = s;
}

void GameModule::initPlayers()
{
    srand(1234);
    Bomberman *_bomber = new Bomberman(_smgr, irr::core::vector3df(-300, 0, -300), 0, 0, 0, _vect_mesh, 0);

    _vect_actor.push_back(_bomber);
    _controlVect.push_back(new Controller(_bomber, _event->getKeyVect()));
    //     _AIVect.push_back(new AI(_bomber, *_controlVect.end(), _event->getKeyVect()));

    Bomberman *_bomber2 = new Bomberman(_smgr, irr::core::vector3df(-300, 0, -205), 19, 0, 1, _vect_mesh, 0);
    _bomber2->setInput(0, KeyHandler(ControllerKey::LD1));
    _bomber2->setInput(1, KeyHandler(ControllerKey::DD1));
    _bomber2->setInput(2, KeyHandler(ControllerKey::RD1));
    _bomber2->setInput(3, KeyHandler(ControllerKey::UD1));
    _bomber2->setInput(4, KeyHandler(ControllerKey::A1));
    _bomber2->setInput(5, KeyHandler(ControllerKey::B1));
    _vect_actor.push_back(_bomber2);
    _controlVect.push_back(new Controller(_bomber2, _event->getKeyVect()));
    //     _AIVect.push_back(new AI(_bomber2, *_controlVect.end(), _event->getKeyVect()));

    Bomberman *_bomber3 = new Bomberman(_smgr, irr::core::vector3df(-205, 0, -300), 0, 19, 2, _vect_mesh, 0);
    _bomber3->setInput(0, KeyHandler(ControllerKey::LD2));
    _bomber3->setInput(1, KeyHandler(ControllerKey::DD2));
    _bomber3->setInput(2, KeyHandler(ControllerKey::RD2));
    _bomber3->setInput(3, KeyHandler(ControllerKey::UD2));
    _bomber3->setInput(4, KeyHandler(ControllerKey::A2));
    _bomber3->setInput(5, KeyHandler(ControllerKey::B2));
    _vect_actor.push_back(_bomber3);
    _controlVect.push_back(new Controller(_bomber3, _event->getKeyVect()));
    //     _AIVect.push_back(new AI(_bomber3, *_controlVect.end(), _event->getKeyVect()));

    Bomberman *_bomber4 = new Bomberman(_smgr, irr::core::vector3df(-205, 0, -205), 19, 19, 3, _vect_mesh, 0);
    _bomber4->setInput(0, KeyHandler(irr::KEY_KEY_K));
    _bomber4->setInput(1, KeyHandler(irr::KEY_KEY_L));
    _bomber4->setInput(2, KeyHandler(irr::KEY_KEY_M));
    _bomber4->setInput(3, KeyHandler(irr::KEY_KEY_O));
    _bomber4->setInput(4, KeyHandler(irr::KEY_KEY_P));
    _bomber4->setInput(5, KeyHandler(irr::KEY_KEY_I));
    _vect_actor.push_back(_bomber4);
    _controlVect.push_back(new Controller(_bomber4, _event->getKeyVect()));
    //     _AIVect.push_back(new AI(_bomber4, *_controlVect.end(), _event->getKeyVect()));
}

void GameModule::initLoad()
{
    _loader->loadGameModule(this);
    drawMap(false);
    std::vector<int> vectt = {{0}, {0}, {0}, {0}};
    _mapHandler.updateMap(_vectBlockDestruct, vectt, _vect_mesh, MUSIC, _network, false, _Musicplayer, _innerBonus);
    _action_handler = new ActionHandler(_vect_actor, _mapHandler, _vectBomb, _smgr, _vect_mesh, _Musicplayer);
}

void GameModule::initSolo(std::vector<user_info_t> users, std::vector<KeyHandler> ve1, std::vector<KeyHandler> ve2, std::vector<KeyHandler> ve3, std::vector<KeyHandler> ve4)
{
	// std::vector<KeyHandler> ve1 = {irr::KEY_KEY_Q, irr::KEY_KEY_S, irr::KEY_KEY_D, irr::KEY_KEY_Z, irr::KEY_KEY_E, irr::KEY_KEY_A};
	// std::vector<KeyHandler> ve2 = {irr::KEY_KEY_X, irr::KEY_KEY_W, irr::KEY_KEY_C, irr::KEY_KEY_V, irr::KEY_KEY_B, irr::KEY_KEY_N};
	// std::vector<KeyHandler> ve3 = {irr::KEY_KEY_T, irr::KEY_KEY_Y, irr::KEY_KEY_U, irr::KEY_KEY_I, irr::KEY_KEY_O, irr::KEY_KEY_P};
	// std::vector<KeyHandler> ve4 = {irr::KEY_KEY_G, irr::KEY_KEY_H, irr::KEY_KEY_J, irr::KEY_KEY_K, irr::KEY_KEY_L, irr::KEY_KEY_M};
	_seed = 1234;
	drawMap(true);
	std::vector<int> xtab = {0, 19, 0, 19};
	std::vector<int> ytab = {0, 0, 19, 19};
	for (int i = 0; i < users.size(); i++) {
		if (users[i].statu != NOT_PLAYING) {
			// std::cout << "BAPTIDSTE = "  << users[i].characterId << std::endl;
			_playersInfos.push_back(character_t {users[i].characterId, xtab[i], ytab[i], (users[i].statu == AI_PLAYER ? AI_T : PLAYER_T), i});
		}
	}
	// _playersInfos.push_back({0, 19, 0, AI_T, 1});
	// _playersInfos.push_back({0, 0, 19, PLAYER_T, 2});
	// _playersInfos.push_back({0, 19, 19, PLAYER_T, 3});
	initPlayers(_playersInfos.size(), _playersInfos, ve1, ve2, ve3, ve4);
	std::vector<int> vectt = {{0}, {0}, {0}, {0}};
	_mapHandler.updateMap(_vectBlockDestruct, vectt, _vect_mesh, MUSIC, _network, false, _Musicplayer, _innerBonus);
	_action_handler = new ActionHandler(_vect_actor, _mapHandler, _vectBomb, _smgr, _vect_mesh, _Musicplayer);
	// std::cout << "CP1" << std::endl;
}

void GameModule::reset(void)
{
    _startedGame = false;
    _gameOver = false;
    _launchGame = false;
    if (MUSIC == 1)
    {
        _Musicplayer.stopMusicPlayer("GAME");
        _Musicplayer.setLoopMusicPlayer("MENU", true);
        _Musicplayer.playMusicPlayer("MENU");
    }
    _camera->setPosNext(irr::core::vector3df(-260.811, 15.0742, -314.429));
    _camera->setTargetNext(irr::core::vector3df(-357.911, -10.1637, -434.027));
    _playersInfos.clear();
    // for (size_t i = 0; i != _AIVect.size(); i += 1) {
    //     if (_AIVect[i]->isBusy())
    //         i = -1;
    // }
    // for (size_t i = 0; i != _AIVect.size(); i += 1)
    //     delete _AIVect[i];
    _AIVect.clear();
    for (size_t i = 0; i != _controlVect.size(); i += 1)
        delete _controlVect[i];
    _controlVect.clear();
    for (size_t i = 0; i != _vect_actor.size(); i += 1) {
        _vect_actor[i]->deleteGameObj();
    }
    for (size_t i = 0; i != _vect_actor.size(); i += 1)
        delete _vect_actor[i];
    _vect_actor.clear();
    for (size_t i = 0; i != _vectBomb.size(); i += 1)
        delete _vectBomb[i];
    _vectBomb.clear();
    delete _action_handler;
    for (size_t i = 0; i != _vectBonus.size(); i += 1)
        delete _vectBonus[i];
    _vectBonus.clear();
    _scores.clear();
    _scores.push_back(0);
    _scores.push_back(0);
    _scores.push_back(0);
    _scores.push_back(0);
    for (size_t i = 0; i != _vectBlockDestruct.size(); i += 1)
        delete _vectBlockDestruct[i];
    _vectBlockDestruct.clear();
    for (size_t i = 0; i != _trees.size(); i += 1)
        _trees[i]->remove();
    for (size_t i = 0; i != _vectFlames.size(); i += 1)
        delete _vectFlames[i];
    _vectFlames.clear();
    _trees.clear();
    _score.reset();
    _seed = 0;
    _podiumManager.resetPodium();
    _mapHandler.getMap().clear();
    _mapHandler.getDangerMap().clear();
    _mapHandler.getWallPassMap().clear();
}

bool GameModule::receiveBonus(std::vector<std::string> strVect)
{
	Bonus::bonus_t type = static_cast<Bonus::bonus_t> (std::atoi(strVect[0].c_str()));
	int y = std::atoi(strVect[1].c_str());
	int x = std::atoi(strVect[2].c_str());
	std::cout << x << " "<< y << type << std::endl;

	_innerBonus.push_back({x, y, type});
	// _mapHandler.addSpecificBonus(x, y, type, _vect_mesh, _vectBlockDestruct);
	return (true);
}

bool GameModule::isOnPodium(void)
{
    return _camera->isOnPodium();
}


bool GameModule::pointerFct(std::vector<std::string> action)
{
	commandGM_t const arr_cmd[] = {
	    {"ACTION", &GameModule::doActionOnline},
	    {"DEAD", &GameModule::receiveDeath},
	    {"BONUS", &GameModule::receiveBonus},
	    {"QUIT", &GameModule::quit},
	    {"CHAT", &GameModule::chat},
	    {"LOG", &GameModule::log},
	    {"ROOM", &GameModule::room},
	    {"INFOROOM", &GameModule::infoRoom},
	    {"CREATEROOM", &GameModule::createRoom},
	    {"LEAVEROOM", &GameModule::leaveRoom},
	    {"SETUSERNAME", &GameModule::setUserName},
	    {"PLAY", &GameModule::play},
	    {"SEED", &GameModule::setSeedFromServ},
	    {"PROMOTE", &GameModule::promote},
	    {"SETCHARACTER", &GameModule::receiveCharacter}};

	for (auto e : arr_cmd)
	{
		if (e.cmd == action[0])
		{
			return (this->*e.cmd_name)(action);
		}
	}
	return true;
}

void GameModule::unstackActionServe()
{
    // // // std::cout << "UNSTAK" << std::endl;
    // std::vector<std::string> strs;
    // for (auto e : _network->_action) {
    // 	// std::cout << "IN UNSTRAK : " << e << std::endl;
    // 	boost::split(strs,e, boost::is_any_of(" "));
    // 	pointerFct(strs);
    // 	strs.clear();
    // }
    // _network->_action.clear();

    std::vector<std::string> strs;
    if (_network->_action.size() > 0)
    {
        boost::split(strs, _network->_action[0], boost::is_any_of(" "));
        if (pointerFct(strs) == true)
            _network->_action.erase(_network->_action.begin());
    }
}

bool GameModule::receiveDeath(std::vector<std::string> strVect)
{
    int i = 0;
	while (std::atoi(strVect[1].c_str()) != _vect_actor[i]->getId()) {
		i++;
	}
	// std::cout << _vect_actor[i]->getCharacterIDX() << std::endl;
	// i = _vect_actor[i]->getId();
        // if (_vect_actor[i]->isOnline() == true)
        // {
        //     _score.addNewScore(std::to_string(_vect_actor[i]->getId()), _scores[_vect_actor[i]->getId()]);
            _vect_actor[i]->deleteGameObj();
            _vect_actor[i] = nullptr;
            _vect_actor.erase(_vect_actor.begin() + i);
            _controlVect.erase(_controlVect.begin() + i);
            i -= 1;
        // }
    return (true);
}

bool GameModule::receiveCharacter(std::vector<std::string> strVect)
{
    for (int i = 1; i < strVect.size(); i += 4)
    {
        // std::cout << "ENFéT C" << strVect[i + 3] << " " << (strVect[i + 3] == "0" ? ONLINE_T : PLAYER_T) << std::endl;
        if (strVect[i + 3] == "1")
        {
            _playersInfos.push_back({std::atoi(strVect[i].c_str()),
                         std::atoi(strVect[i + 1].c_str()),
                         std::atoi(strVect[i + 2].c_str()),
                         (strVect[i + 3] == "0" ? ONLINE_T : PLAYER_T),
                         i / 4});
        }
    }
    for (int i = 1; i < strVect.size(); i += 4)
    {
        // std::cout << "ENFéT C" << strVect[i + 3] << " " << (strVect[i + 3] == "0" ? ONLINE_T : PLAYER_T) << std::endl;
        if (strVect[i + 3] == "0")
        {
            _playersInfos.push_back({std::atoi(strVect[i].c_str()),
                         std::atoi(strVect[i + 1].c_str()),
                         std::atoi(strVect[i + 2].c_str()),
                         (strVect[i + 3] == "0" ? ONLINE_T : PLAYER_T),
                         i / 4});
        }
    }
    return true;
}

void GameModule::initOnline(int player, NetworkClient *network)
{
	std::vector<KeyHandler> ve1 = {irr::KEY_KEY_Q, irr::KEY_KEY_S, irr::KEY_KEY_D, irr::KEY_KEY_Z, irr::KEY_KEY_E, irr::KEY_KEY_A};
	std::vector<KeyHandler> ve2 = {irr::KEY_KEY_X, irr::KEY_KEY_W, irr::KEY_KEY_C, irr::KEY_KEY_V, irr::KEY_KEY_B, irr::KEY_KEY_N};
	std::vector<KeyHandler> ve3 = {irr::KEY_KEY_T, irr::KEY_KEY_Y, irr::KEY_KEY_U, irr::KEY_KEY_I, irr::KEY_KEY_O, irr::KEY_KEY_P};
	std::vector<KeyHandler> ve4 = {irr::KEY_KEY_G, irr::KEY_KEY_H, irr::KEY_KEY_J, irr::KEY_KEY_K, irr::KEY_KEY_L, irr::KEY_KEY_M};

    _network = network;
	_network->getSeed();
	while (_seed == 0)
	{
		#ifdef _WIN32
    	    _sleep(1);
    	#elif __linux__
    	    sleep(1);
    	#else
    	#endif
		unstackActionServe();
	}
	_network->getCharacter();
	drawMap(true);
	while (_playersInfos.size() == 0)
	{
		#ifdef _WIN32
    	    _sleep(1);
    	#elif __linux__
    	    sleep(1);
    	#else
    	#endif
		unstackActionServe();
	};
	initPlayers(_playersInfos.size(), _playersInfos, ve1, ve2, ve3, ve4);
	std::vector<int> vectt = {{0}, {0}, {0}, {0}};
	_mapHandler.updateMap(_vectBlockDestruct, vectt, _vect_mesh, MUSIC, _network, false, _Musicplayer, _innerBonus);
	_action_handler = new ActionHandler(_vect_actor, _mapHandler, _vectBomb, _smgr, _vect_mesh, _Musicplayer);
}

void GameModule::initGameModule()
{
    irr::core::stringw windowName = "Bomberman";
    _device->setWindowCaption(windowName.c_str());
    _event = static_cast<EventManager *>(_device->getEventReceiver());

    //    _camera = new Camera(_smgr, irr::core::vector3df(-231.211, 71.8743, -248.03),
    //    irr::core::vector3df(-245.113, 3.03636, -248.03), _device);
    _camera = new Camera(_smgr, irr::core::vector3df(-260.811, 15.0742, -314.429),
                 irr::core::vector3df(-357.911, -10.1637, -434.027), _device);
    //    _camera = new Camera(_smgr, irr::core::vector3df(-232.411, 71.8743, -248.03));
    _vect_mesh.push_back(_smgr->getMesh("./ressources/models/Ground/ground.3ds"));
    _vect_mesh.push_back(_smgr->getMesh("./ressources/models/Walls/tree.3ds"));
    _vect_mesh.push_back(_smgr->getMesh("./ressources/models/Bomb/bomb.3ds"));
    _vect_mesh.push_back(_smgr->getMesh("./ressources/models/Bonus/speedUp.3ds"));
    _vect_mesh.push_back(_smgr->getMesh("./ressources/models/Bonus/fireUp.3ds"));
    _vect_mesh.push_back(_smgr->getMesh("./ressources/models/Bonus/bombUp.3ds"));
    _vect_mesh.push_back(_smgr->getMesh("./ressources/models/Bonus/wallPass.3ds"));
    _vect_mesh.push_back(_smgr->getMesh("./ressources/models/Bonus/star.3ds"));
    node = _smgr->addMeshSceneNode(_smgr->getMesh("./ressources/models/Ground/ground.3ds"), 0);
    node->getMaterial(0).NormalizeNormals = true;
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    node->setPosition(irr::core::vector3df(-300 + 46, -145, -300 + 48));
    //     drawMap();
    // //     initPlayers();
    //     std::vector<int> vectt = {{0}, {0}, {0}, {0}};

    //     _mapHandler.updateMap(_vectBlockDestruct, vectt, _vect_mesh);
    //     _action_handler = new ActionHandler(_vect_actor, _mapHandler, _vectBomb, _smgr, _vect_mesh, _Musicplayer);
}

bool GameModule::doActionOnline(std::vector<std::string> action)
{
    IActor *actor = nullptr;
    for (IActor *act : _vect_actor)
    {
        // std::cout << act->getId() << " and " << std::atoi(action[1].c_str()) << std::endl;
        if (act->getId() == std::atoi(action[1].c_str()))
        {
            actor = act;
        }
    }
    if (actor == nullptr)
    {
        return true;
    }
	// if (actor->isOnline() == false)
	// 	actor->getWait() = true;
    int size = actor->getActionsToDo().size();
    // std::cout << "LOLOLOLO" << action[0] << action[1] << action[2] << std::endl;
    std::string tmp = action[2];
    if (tmp.compare("FIRST") == 0)
    {
        // std::cout << "FIRSTTTTTT" << std::endl;
        (actor->*actor->getBinds()[0].second)();
    }
    else if (tmp.compare("SECOND") == 0)
    {
        // std::cout << "SECONNNNNNNDD" << std::endl;
        (actor->*actor->getBinds()[1].second)();
    }
    else if (tmp.compare("THIRD") == 0)
    {
        // std::cout << "THIRDDDDDD" << std::endl;
        (actor->*actor->getBinds()[2].second)();
    }
    else if (tmp.compare("FORTH") == 0)
    {
        (actor->*actor->getBinds()[3].second)();
    }
    else if (tmp.compare("FIFTH") == 0)
    {
        (actor->*actor->getBinds()[4].second)();
    }
    else if (tmp.compare("SIXTH") == 0)
    {
        (actor->*actor->getBinds()[5].second)();
    }
    if (size < actor->getActionsToDo().size())
    {
        return (true);
    }
	// if (actor->isOnline() == false)
	// 	return true;
    return false;
}

void GameModule::gameOverScreenInit()
{
    std::vector<MODELS> models;

	std::sort(_playersInfos.begin(), _playersInfos.end(), [](const GameModule::character_t &a, const GameModule::character_t &b) {return a.playerIDX < b.playerIDX;});
    for (size_t i = 0; i != _playersInfos.size(); i += 1)
        models.push_back(static_cast<MODELS>(_playersInfos[i].characterIDX));

    _podiumManager.initPodium(_smgr, models, _scores);
}

void GameModule::drawGameModule()
{
    /*    irr::core::vector3df cameraTarget = _camera->_camera->getTarget();
    irr::core::vector3df cameraPos = _camera->_camera->getPosition();

    // std::cout << "cameraTarget = {" << cameraTarget.X << ", " << cameraTarget.Y << ", " << cameraTarget.Z << "}" << std::endl;
    // std::cout << "cameraPos = {" << cameraPos.X << ", " << cameraPos.Y << ", " << cameraPos.Z << "}" << std::endl;
*/
    // irr::core::vector3df pos = _camera->_camera->getPosition();
    // // std::cout << pos.X << " " << pos.Y << " " << pos.Z << std::endl;
    // pos = _camera->_camera->getTarget();
    // // std::cout << pos.X << " " << pos.Y << " " << pos.Z << std::endl;
    //        _camera->playIntro();
    /*    if (_event->IsKeyDown(irr::EKEY_CODE::KEY_KEY_H)) {
        _camera->setTargetNext(irr::core::vector3df(-245.113, 3.03636, -248.03));
        _camera->setPosNext(irr::core::vector3df(-232.411, 71.8743, -248.03));
    }
    if (_event->IsKeyDown(irr::EKEY_CODE::KEY_KEY_J)) {
        _camera->setTargetNext(irr::core::vector3df(-357.911, -10.1637, -434.027));
        _camera->setPosNext(irr::core::vector3df(-260.811, 15.0742, -314.429));
    }*/

    _camera->update();
    //    debugMoveCam();
    _event->getKeyVect(_AIVect, _vect_actor);
    // if (_network) {
    //     unstackActionServe();
    // }
    if (_startedGame)
        _launchGame = _camera->isMoving();
    if (_launchGame == false || _gameOver) {
        _smgr->drawAll();
        return;
    }

    for (int i = 0; i < _vectBomb.size(); i += 1)
    {
        if (_vectBomb[i]->getRemainingTime() < 0 && _vectBomb[i]->hasExploded())
        {
            delete _vectBomb[i];
            _vectBomb.erase(_vectBomb.begin() + i);
            i -= 1;
        }
    }

    for (int i = 0; i < _vectBomb.size(); i += 1)
    {
        if (_vectBomb[i]->update() == 1)
        {
            _mapHandler.getMap()[_vectBomb[i]->getPosition().Z][_vectBomb[i]->getPosition().X] = '0';
        }
    }
    for (IActor *player : _vect_actor)
    {
        for (int i = 0; i < _vectBonus.size(); i += 1)
        {
            if (_vectBonus[i]->getPosition().X == player->getCoord().x &&
                _vectBonus[i]->getPosition().Z == player->getCoord().y)
            {
                _mapHandler.getMap()[_vectBonus[i]->getPosition().Z][_vectBonus[i]->getPosition().X] = '0';
		if ((_vectBonus[i]->getType() != Bonus::POWER_UP && _vectBonus[i]->getType() != Bonus::WALL_PASS) ||
		(player->hasPower() == false && _vectBonus[i]->getType() == Bonus::POWER_UP) ||
		(player->getWallPass() && _vectBonus[i]->getType() == Bonus::WALL_PASS)) {
			_interfacePlay->addBonus(player->getId(), _vectBonus[i]->getType());
		}
                player->applyBonus(_vectBonus[i]);
                if (MUSIC == 1)
                {
                    _Musicplayer.playSoundPlayer("BONUS");
                }
                delete _vectBonus[i];
                _vectBonus.erase(_vectBonus.begin() + i);
                i -= 1;
            }
        }
        if (player->getWallPass())
            player->updateWallPass();
        player->updateStatus();
        player->updateParticles();
    }

	for (int i = 0; i < _vect_actor.size(); i++)
	{
		if (_mapHandler.getDangerMap()[_vect_actor[i]->getCoord().y][_vect_actor[i]->getCoord().x] == '1')
		{
			for (int y = 0; y < _AIVect.size(); y++)
			{
				if (_AIVect[y]->getBomberman() == _vect_actor[i])
				{
					_AIVect.erase(_AIVect.begin() + y);
					break;
				}
			}
			for (Bomb *bt : _vectBomb)
			{
				if (bt->getMasterId() != _vect_actor[i]->getId())
				{
					for (int y = -bt->getRange(); y < bt->getRange(); y++)
					{
						if ((_vect_actor[i]->getCoord().y == bt->getPosition().Z + y && _vect_actor[i]->getCoord().x == bt->getPosition().X) ||
						    (_vect_actor[i]->getCoord().y == bt->getPosition().Z && _vect_actor[i]->getCoord().x == bt->getPosition().X + y))
						{
							_scores[bt->getMasterId()] += 100;
						}
					}
				}
			}
			if (_vect_actor[i]->isOnline() == false && _vect_actor[i]->getDeath() == false)
			{
				if (_network != nullptr)
				{
					// std::cout << "DDDDDDDDDDEEEEEEEEEEEEEEEEEEEEEEAAAAAAAAAAAAAD" << std::endl;
					_network->action("DEAD");
					_vect_actor[i]->setDeath(true);
					// _network->dead();
					// _network->action("BITEE");
				} else {
					_score.addNewScore(std::to_string(_vect_actor[i]->getId()), _scores[_vect_actor[i]->getId()]);
					_vect_actor[i]->deleteGameObj();
					_vect_actor[i] = nullptr;
					_vect_actor.erase(_vect_actor.begin() + i);
					_controlVect.erase(_controlVect.begin() + i);
					i -= 1;
				}
			}
			if (MUSIC == 1) {
				_Musicplayer.playSoundPlayer("DEATH");
			}
		}
	}
	//// std::cout << "CP3" << std::endl;

    if (_vect_actor.size() == 1 && _gameOver == false)
    {
	_interfacePlay->frezzClock();
        _gameOver = true;
        if (_vect_actor.size())
            _scores[_vect_actor[0]->getId()] += 500;
	_score.addNewScore(std::to_string(_vect_actor[0]->getId()), _scores[_vect_actor[0]->getId()]);
        _score.saveScores();
        _camera->setTargetNext(irr::core::vector3df(-381.267, -2.33152, -237.228));
        _camera->setPosNext(irr::core::vector3df(-315.656, 8.04248, -259.307));
        gameOverScreenInit();
        
    }
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            if (_mapHandler.getDangerMap()[y][x] == '1')
            {
                for (BlockDestruct *blck : _vectFlames)
                {
                    if (blck->_x == x && blck->_y == y)
                        continue;
                }
                _vectFlames.push_back(new BlockDestruct(_smgr, irr::core::vector3df(-300 + (y * TILE_SIZE), 0, -300 + (x * TILE_SIZE)), x, y, "./ressources/feu.jpg"));
            }
            for (int j = 0; j < _vectFlames.size(); j++)
            {
                if (_vectFlames[j]->_x == x && _vectFlames[j]->_y == y && _mapHandler.getDangerMap()[y][x] != '1')
                {
                    _vectFlames[j]->BlockIsDestruct(y, x);
                    _vectFlames.erase(_vectFlames.begin() + j);
                    j -= 1;
                }
            }
        }
    }

    std::vector<int> vectt = {{0}, {0}, {0}, {0}};

	_mapHandler.updateMap(_vectBlockDestruct, vectt, _vect_mesh, MUSIC, _network,
    (_vect_actor.size() && _vect_actor[0]->getId() == 0 ? true : false), _Musicplayer, _innerBonus);
	if (vectt[0] || vectt[1] || vectt[2] || vectt[3])
	{
		for (IActor *act : _vect_actor)
		{
			act->setBombs(vectt[act->getId()]);
			// std::cout << act->getId() << "bombs:" << act->getBombs() << std::endl;
		}
	}
	//// std::cout << "CP3.5" << std::endl;


    for (AI *ai : _AIVect)
    {
        if (ai->isBusy() == false && ai->getBomberman()->getStatus() != STUN)
        {
            ai->play(_vect_actor, _mapHandler.getMapForAI(), _mapHandler.getMap()[ai->getBomberman()->getCoord().y][ai->getBomberman()->getCoord().x]);
        }
    }
	//// std::cout << "CP3.6" << std::endl;

    _smgr->drawAll();
    if (_network)
    {
        unstackActionServe();
    }
	//// std::cout << "CP3.7" << std::endl;

    for (Controller *ctrl : _controlVect)
    {
        ctrl->handleControll(_network);
    }

	//     // std::cout << "NB AI " << _AIVect.size() << std::endl;
	//     _mapHandler.display(19, 19);
	_action_handler->handleAction();

}

/*Call this function in the game loop allow you to dynamically move
the camera with :
G/T: target.X +/-
H/Y: target.Y +/-
J/U: target.Z +/-
K/I: pos.X +/-
L/O: pos.Y +/-
M/P: pos.Z +/-
*/
void GameModule::debugMoveCam(void)
{
    irr::core::vector3df cameraTarget = _camera->getTarget();
    irr::core::vector3df cameraPos = _camera->getPos();
    float move_offset = 0.4;

    // std::cout << "cameraTarget = {" << cameraTarget.X << ", " << cameraTarget.Y << ", " << cameraTarget.Z << "}" << std::endl;
    // std::cout << "cameraPos = {" << cameraPos.X << ", " << cameraPos.Y << ", " << cameraPos.Z << "}" << std::endl;
    if (_event->IsKeyDown(irr::EKEY_CODE::KEY_KEY_G))
        cameraTarget.X += move_offset;
    if (_event->IsKeyDown(irr::EKEY_CODE::KEY_KEY_H))
        cameraTarget.Y += move_offset;
    if (_event->IsKeyDown(irr::EKEY_CODE::KEY_KEY_J))
        cameraTarget.Z += move_offset;
    if (_event->IsKeyDown(irr::EKEY_CODE::KEY_KEY_T))
        cameraTarget.X -= move_offset;
    if (_event->IsKeyDown(irr::EKEY_CODE::KEY_KEY_Y))
        cameraTarget.Y -= move_offset;
    if (_event->IsKeyDown(irr::EKEY_CODE::KEY_KEY_U))
        cameraTarget.Z -= move_offset;
    if (_event->IsKeyDown(irr::EKEY_CODE::KEY_KEY_K))
        cameraPos.X += move_offset;
    if (_event->IsKeyDown(irr::EKEY_CODE::KEY_KEY_I))
        cameraPos.X -= move_offset;
    if (_event->IsKeyDown(irr::EKEY_CODE::KEY_KEY_L))
        cameraPos.Z += move_offset;
    if (_event->IsKeyDown(irr::EKEY_CODE::KEY_KEY_O))
        cameraPos.Z -= move_offset;
    if (_event->IsKeyDown(irr::EKEY_CODE::KEY_KEY_M))
        cameraPos.Y -= move_offset;
    if (_event->IsKeyDown(irr::EKEY_CODE::KEY_KEY_P))
        cameraPos.Y += move_offset;
    _camera->setTarget(cameraTarget);
    _camera->setPos(cameraPos);
}

void GameModule::startGame(void)
{
        // NetworkClient* net = new NetworkClient();
    // net->run("10.101.54.25", "3031");
    // initOnline(net);
    _camera->setTargetNext(irr::core::vector3df(-245.113, 3.03636, -248.03));
    _camera->setPosNext(irr::core::vector3df(-231.211, 71.8743, -248.03));
    _launchGame = true;
    _startedGame = true;
    if (MUSIC == 1) {
	_Musicplayer.stopMusicPlayer("MENU");
	_Musicplayer.setLoopMusicPlayer("GAME", true);
	_Musicplayer.playMusicPlayer("GAME");
    }
}

void GameModule::run()
{
    drawGameModule();
}

std::vector<IActor*> &GameModule::getActor(void)
{
    return _vect_actor;
}

std::vector<AI*> &GameModule::getAI(void)
{
    return _AIVect;
}

std::vector<Bomb*> &GameModule::getBomb(void)
{
    return _vectBomb;
}

std::vector<Bonus *> &GameModule::getBonus(void)
{
    return _vectBonus;
}

std::vector<int> &GameModule::getScore(void)
{
    return _scores;
}

MapHandler &GameModule::getMapHandler(void)
{
    return _mapHandler;
}

void GameModule::addScore(int scores)
{
    _scores.push_back(scores);
}

irr::scene::ISceneManager *GameModule::getSceneManager(void)
{
    return _smgr;
}

std::vector<irr::scene::IAnimatedMesh *> GameModule::getAnimatedMesh(void)
{
    return _vect_mesh;
}

EventManager *GameModule::getEventManager(void)
{
    return _event;
}

std::vector<Controller*> &GameModule::getController(void)
{
    return _controlVect;
}

std::vector<GameModule::character_t> &GameModule::getPlayerInfo(void)
{
    return _playersInfos;
}

Saver *GameModule::getSave(void)
{
    return _saver;
}
