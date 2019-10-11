/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/actionHandler/MapHandler.cpp
*/

#include "MapHandler.hpp"

MapHandler::MapHandler(std::vector<Bomb*> &bombs, std::vector<Bonus*> &bonus, std::vector<int> &scores): _bombs(bombs), _bonus(bonus), _scores(scores)
{
}

MapHandler::~MapHandler()
{
}

std::string MapHandler::zerofied(std::string entry)
{
    for (auto &e: entry) {
        e = '0';
    }
    return (entry);
}

int MapHandler::getMapSize()
{
    return (_mapSize);
}

void MapHandler::setMng(irr::scene::ISceneManager *smgr)
{
    _smgr = smgr;
}

void MapHandler::createWallPassMap(void)
{
    std::string tmp;

    for (size_t i = 0; i < 20; i += 1) {
        tmp = _map[i];
        for (size_t u = 0; u < tmp.size(); u += 1)
            tmp[u] = (tmp[u] == '1') ? '0' : tmp[u];
        std::cout << tmp << std::endl;
        _wallPassMap.push_back(tmp);
    }
}

void MapHandler::setMap(void)
{
    for (int i = 0; i < 20; i += 1)
        _dangerMap.push_back(zerofied(_map[i]));
    _mapSize = 20;
    createWallPassMap();
}

void MapHandler::setMap(FILE *mapFile)
{
    std::string str;
    boost::iostreams::file_descriptor_source convertFd(fileno(mapFile), boost::iostreams::close_handle);
    boost::iostreams::stream_buffer<boost::iostreams::file_descriptor_source> fdToStream(convertFd);
    std::istream stream(&fdToStream);

    while (std::getline(stream, str) ) {
        std::cout << str << std::endl;
        _map.push_back(str);
        _dangerMap.push_back(zerofied(str));
    }
    _mapSize = 20;
    createWallPassMap();
}

std::vector<std::string> &MapHandler::getMap(void)
{
    return(_map);
}

std::vector<std::string> &MapHandler::getWallPassMap(void)
{
    return (_wallPassMap);
}

std::vector<std::string> &MapHandler::getDangerMap(void)
{
    return (_dangerMap);
}

void MapHandler::updateMap(std::vector<BlockDestruct*> block, std::vector<int> &bombs,
std::vector<irr::scene::IAnimatedMesh *> vect_mesh, int music, NetworkClient *network, bool master,
MusicPlayer &musicPlayer, std::vector<innerBonus_t> &_innerBonus)
{
    for(Bomb *b : _bombs) {
        for (int i = 0; i <= b->getRange(); i++) {
            if ((((b->getPosition().Z + i) < 0) || ((b->getPosition().Z + i) >= 20)) || _map[b->getPosition().Z + i][b->getPosition().X] == '2')
                break;
            if (!b->hasExploded() || ((_map[b->getPosition().Z + i][b->getPosition().X] == '0' || _map[b->getPosition().Z + i][b->getPosition().X] == '4') && _dangerMap[b->getPosition().Z + i][b->getPosition().X] == '1'))
                _dangerMap[b->getPosition().Z + i][b->getPosition().X] = ((b->getRemainingTime() + 49 < _dangerMap[b->getPosition().Z + i][b->getPosition().X]) || (_dangerMap[b->getPosition().Z + i][b->getPosition().X] == '0' || _dangerMap[b->getPosition().Z + i][b->getPosition().X] == '4') ? b->getRemainingTime() + 49 : _dangerMap[b->getPosition().Z + i][b->getPosition().X]);
            if (_map[b->getPosition().Z + i][b->getPosition().X] == '1')
                break;
        }

        for (int i = 0; i <= b->getRange(); i++) {
            if ((((b->getPosition().X + i) < 0) || ((b->getPosition().X + i) >= 20)) || _map[b->getPosition().Z][b->getPosition().X + i] == '2')
                break;
            if (!b->hasExploded() || ((_map[b->getPosition().Z][b->getPosition().X + i] == '0' || _map[b->getPosition().Z][b->getPosition().X + i] == '4') && _dangerMap[b->getPosition().Z][b->getPosition().X + i] == '1'))
                _dangerMap[b->getPosition().Z][b->getPosition().X + i] = ((b->getRemainingTime() + 49 < _dangerMap[b->getPosition().Z][b->getPosition().X + i]) || (_dangerMap[b->getPosition().Z][b->getPosition().X + i] == '0' || _dangerMap[b->getPosition().Z][b->getPosition().X + i] == '4') ? b->getRemainingTime() + 49 : _dangerMap[b->getPosition().Z][b->getPosition().X + i]);
            if (_map[b->getPosition().Z][b->getPosition().X + i] == '1')
                break;
        }

        for (int i = 0; i <= b->getRange(); i++) {
            if ((((b->getPosition().Z - i) < 0) || ((b->getPosition().Z - i) >= 20)) || _map[b->getPosition().Z - i][b->getPosition().X] == '2')
                break;
            if (!b->hasExploded() || ((_map[b->getPosition().Z - i][b->getPosition().X] == '0' || _map[b->getPosition().Z - i][b->getPosition().X] == '4') && _dangerMap[b->getPosition().Z - i][b->getPosition().X] == '1'))
                _dangerMap[b->getPosition().Z - i][b->getPosition().X] = ((b->getRemainingTime() + 49 < _dangerMap[b->getPosition().Z - i][b->getPosition().X]) || (_dangerMap[b->getPosition().Z - i][b->getPosition().X] == '0' || _dangerMap[b->getPosition().Z - i][b->getPosition().X] == '4') ? b->getRemainingTime() + 49 : _dangerMap[b->getPosition().Z - i][b->getPosition().X]);
            if (_map[b->getPosition().Z - i][b->getPosition().X] == '1')
                break;
        }

        for (int i = 0; i <= b->getRange(); i++) {
            if ((((b->getPosition().X - i) < 0) || ((b->getPosition().X - i) >= 20)) || _map[b->getPosition().Z][b->getPosition().X - i] == '2')
                break;
            if (!b->hasExploded() || ((_map[b->getPosition().Z][b->getPosition().X - i] == '0' || _map[b->getPosition().Z][b->getPosition().X - i] == '4') && _dangerMap[b->getPosition().Z][b->getPosition().X - i] == '1'))
                _dangerMap[b->getPosition().Z][b->getPosition().X - i] = ((b->getRemainingTime() + 49 < _dangerMap[b->getPosition().Z][b->getPosition().X - i]) || (_dangerMap[b->getPosition().Z][b->getPosition().X - i] == '0' || _dangerMap[b->getPosition().Z][b->getPosition().X - i] == '4') ? b->getRemainingTime() + 49 : _dangerMap[b->getPosition().Z][b->getPosition().X - i]);
            if (_map[b->getPosition().Z][b->getPosition().X - i] == '1')
                break;
        }

        if (b->getRemainingTime() == 0 && b->hasExploded() == false) {
            bombs[b->getMasterId()] += 1;
            b->setHasExploded(true);
            if (music == 1) {
                musicPlayer.playSoundPlayer("EXPLO" + std::to_string(rand() % 2 + 1));
	    }
            for (int i = 0; i < 20; i++) {
                for (int j = 0; j < 20; j++) {
                    if (_map[i][j] == '1' && _dangerMap[i][j] == '1') {
                        _scores[b->getMasterId()] += 5;
                        std::cout << "PLAYER " << b->getMasterId() << " won 5 pts for a total of " << _scores[b->getMasterId()] << std::endl;
                    }
                }
            }
        }
    }
    int w = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (_map[i][j] == '1' && _dangerMap[i][j] == '1') {
                _map[i][j] = '0';
                addRandomBonus(i, j, vect_mesh, network, master, _innerBonus);
                for (auto e : block) {
                    if (e->BlockIsDestruct(i, j) == true) {
                        block.erase(w + block.begin());
                    }
                    w += 1;
                }
                w = 0;
            }
        }
    }
}

void MapHandler::addRandomBonus(int y, int x, std::vector<irr::scene::IAnimatedMesh *> vect_mesh, NetworkClient *network, bool master, std::vector<innerBonus_t> &_innerBonus)
{
    int addBonus = rand()%100 + 1;
    int chooseBonus = rand()%100 + 1;
    Bonus::bonus_t type;
    irr::scene::ISceneNode *node;
	int j = 0;

	if (network && master == false) {
		for (; j < _innerBonus.size(); j++) {
			if (y == _innerBonus[j].y && x == _innerBonus[j].x) {
				_innerBonus.erase(_innerBonus.begin() + j);
				addSpecificBonus(_innerBonus[j].x, _innerBonus[j].y, static_cast<Bonus::bonus_t>(_innerBonus[j].type), vect_mesh);
				break;
			}
		}
	}
    if (addBonus <= 90)
        return;
    if (chooseBonus <= 30) {
        node = _smgr->addMeshSceneNode(vect_mesh[3] ,0);
        type = Bonus::SPEED_UP;
    } else if (chooseBonus <= 50) {
        node = _smgr->addMeshSceneNode(vect_mesh[4] ,0);
        type = Bonus::FIRE_UP;
    } else if (chooseBonus <= 70) {
        node = _smgr->addMeshSceneNode(vect_mesh[5] ,0);
        type = Bonus::BOMB_UP;
    } else if (chooseBonus <= 85) {
        node = _smgr->addMeshSceneNode(vect_mesh[6] ,0);
        type = Bonus::WALL_PASS;
    } else {
        node = _smgr->addMeshSceneNode(vect_mesh[7] ,0);
        type = Bonus::POWER_UP;
    }
    node->setPosition(irr::core::vector3df(-300 + (y * TILE_SIZE), 0, -300 + (x * TILE_SIZE)));
    node->getMaterial(0).NormalizeNormals = true;
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _bonus.push_back(new Bonus(irr::core::vector3df(x, 0, y), node, type));
    if (network && master) {
	    network->bonus(type, x, y);
    }
    _map[y][x] = '4';
}

void MapHandler::addSpecificBonus(int x, int y, Bonus::bonus_t type, std::vector<irr::scene::IAnimatedMesh *> vect_mesh) {
	std::cout << "inner 1" << std::endl;
	irr::scene::ISceneNode *node;
	int w = 0;
	if (type == Bonus::SPEED_UP) {
	        node = _smgr->addMeshSceneNode(vect_mesh[3] ,0);
	} else if (type == Bonus::FIRE_UP) {
	        node = _smgr->addMeshSceneNode(vect_mesh[4] ,0);
	}else if (type == Bonus::BOMB_UP) {
	        node = _smgr->addMeshSceneNode(vect_mesh[5] ,0);
	}else if (type == Bonus::WALL_PASS) {
	        node = _smgr->addMeshSceneNode(vect_mesh[6] ,0);
	}else if (type == Bonus::POWER_UP) {
	        node = _smgr->addMeshSceneNode(vect_mesh[7] ,0);
	}
	std::cout << "inner 2" << std::endl;
	std::cout << "inner 3" << std::endl;
	node->setPosition(irr::core::vector3df(-300 + (y * TILE_SIZE), 0, -300 + (x * TILE_SIZE)));
	std::cout << "inner 4" << std::endl;
	node->getMaterial(0).NormalizeNormals = true;
	std::cout << "inner 5" << std::endl;

	node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	std::cout << "inner 6" << std::endl;
	_bonus.push_back(new Bonus(irr::core::vector3df(x, 0, y), node, type));
	std::cout << "inner 7" << std::endl;
	_map[y][x] = '4';
	std::cout << "inner 8" << std::endl;

}


void MapHandler::display(int x, int y) {
    char save = _map[y][x];
    _map[y][x] = 'P';
    for (int i = 0; i < 20; i++) {
        std::cout << _dangerMap[i] << "   " << _map[i] << std::endl;
    }
    std::cout << std::endl;
    _map[y][x] = save;
}

std::string MapHandler::getMapForAI() {
    std::string result;
    for (std::string &str: _map) {
        result = result + str + "-";
    }
    result = result + " ";
    for (std::string &str: _dangerMap) {
        result = result + str + "-";
    }
    return (result);
}