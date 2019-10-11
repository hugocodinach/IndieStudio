#include <room.hpp>

Room::Room(int id)
{
    _roomId = id;
	_testthread = 0;
	_seed = std::to_string(rand() % 10000);
	// std::cout << _seed << std::endl;
}

Room::~Room()
{
}

int Room::getRoomId(void)
{
    return _roomId;
}

void Room::setRoomId(int id)
{
    _roomId = id;
}

void Room::clientJoin(Client *client)
{
    _clients.push_back(client);
  //  sendMessageUser("NEWUSER " + client->getUsername() + " connected in room", client);
//	sendMessageAll(getRoomInfo());
	sendRoomInfo();
//    dprintf(client->getFd(), "%s\n", getRoomInfo().c_str());
}

void Room::generateChief(void)
{
    if (_clients.size() != 0) {
        for (unsigned int ct = 0; ct != _clients.size(); ct ++)
            if (_clients[ct]->getChief() == true) {
                // std::cout << "THERE IS ONE CHIEF ALREADY !" << std::endl;
                return;
            }
        _clients[0]->setChief(true);
    }
}

void Room::clientLeave(Client *client)
{
	if (_testthread == 1) {
		_thread.join();
		_testthread = 0;
	}
	// std::cout << "SIZE BEF" <<_clients.size() << std::endl;
    for (unsigned int ct = 0; ct != _clients.size(); ct ++)
        if (client->getFd() == _clients[ct]->getFd()) {
            _clients.erase(_clients.begin() + ct);
			// std::cout << "SIZE AFTER" <<_clients.size() << std::endl;
			// sendMessageAll(getRoomInfo());
			sendRoomInfo();
            return;
        }
	// std::cout << "TRES BIZZARE" <<_clients.size() << std::endl;	
}

void Room::sendRoomInfo()
{
	std::string msg;
	int i = 0;
	std::string tmp;

	for (auto a : _clients) {
		msg = "INFOROOM";
		for (auto e : _clients) {
			msg += " ";
			// if (e->getCharacter() == -1)
			// 		return;


			// for (unsigned int ct = 0; ct != _clients.size(); ct ++) {
				if ( e->getStatus() == true)
					tmp = "ready";
				else
					tmp = "unready";
        		msg = msg + e->getUsername() + " " + tmp + " "; 
			// }

			if (a->getFd() == e->getFd())
				msg += std::to_string(e->getCharacter()) + " " + "1";
			else
				msg += std::to_string(e->getCharacter()) + " " + "0";
		}
		dprintf(a->getFd(), "%s\n", msg.c_str());
		a->_idingame = i;
		i += 1;
	}
}

std::string Room::getRoomInfo(void)
{
    std::string msg = "INFOROOM ";
	std::string tmp;

    if (_clients.size() == 0)
        msg = msg + "-1";
    for (unsigned int ct = 0; ct != _clients.size(); ct ++) {
		if ( _clients[ct]->getStatus() == true)
			tmp = "ready";
		else
			tmp = "unready";
        msg = msg + _clients[ct]->getUsername() + " " + tmp + " "; 
    }
    return msg;
}

std::string Room::getSeed(void)
{
    std::string msg = "SEED " + _seed;
    return msg;
}

void Room::sendMessageUser(std::string msg, Client *client)
{
	for (auto e : _clients) {
		if (client->getFd() != e->getFd())
			dprintf(e->getFd(), "%s\n", msg.c_str());
	}
    // std::cout <<  "SENT THE MSG" << std::endl;
}

void Room::sendMessageAll(std::string msg)
{
	for (auto e : _clients) {
		dprintf(e->getFd(), "%s\n", msg.c_str());
	}
}

unsigned int Room::getRoomClientNbr(void)
{
    return _clients.size();
}

bool Room::getStatusClients(void)
{
    int clientsStatus = 0;

    if (_clients.size() <= 1)
        return false;
    for (unsigned int ct = 0; ct != _clients.size(); ct ++) {
        if (_clients[ct]->getStatus() == true)
            clientsStatus ++;
    }
    if (clientsStatus == _clients.size())
        return true;
    // std::cout << clientsStatus << std::endl;
    return false;
}

int Room::getRoomGameStatus(void)
{
    return _roomGameStatus;
}

void Room::setRoomGameStatus(int status)
{
    _roomGameStatus = status;
}

void Room::setClientsRoomStatus(bool status)
{
	for (auto e : _clients) {
		e->setStatus(false);
	}
}

void Room::setPosition()
{
	if (_clients.size() >= 1) {
		int x1 = 0;
		int y1 = 0;
		_clients[0]->setPosition(x1, y1);
	}

	if (_clients.size() >= 2) {
		int x2 = 19;
		int y2 = 0;
		_clients[1]->setPosition(x2, y2);
	}

	if (_clients.size() >= 3) {
		int x3 = 0;
		int y3 = 19;
		_clients[2]->setPosition(x3, y3);
	}

	if (_clients.size() >= 4) {
		int x4 = 19;
		int y4 = 19;
		_clients[3]->setPosition(x4, y4);
	}
}

void Room::sendCharacterIfAllOk(Client * client)
{
	setPosition();
	std::string msg;
	// int i = 0;

	
	msg = "SETCHARACTER";
	for (auto e : _clients) {
		msg += " ";
		if (e->getCharacter() == -1)
				return;
			if (client->getFd() == e->getFd())
				msg += std::to_string(e->getCharacter()) + " " + e->getPosition() + " 1";
			else
				msg += std::to_string(e->getCharacter()) + " " + e->getPosition() + " 0";
	}
	dprintf(client->getFd(), "%s\n", msg.c_str());
	// client->_idingame = i;
	// i += 1;
}

void Room::CompteurStart()
{
	int i = -1;
	int nb = _clients.size();

	while (i != -1) {
		sendMessageAll(std::to_string(i));
		std::this_thread::sleep_for(std::chrono::seconds((1)));
		if (getStatusClients() == false || nb != _clients.size()) {
			setClientsRoomStatus(false);
			sendMessageAll("ANNULATION");
			 _roomGameStatus = -1;
			return;
		}
		i -= 1;
	}
    GameStart();
    GameEnd();
}

void Room::GameLunch(void)
{
    //EN ATTENTE DES 3 SECONDES
	if (_testthread == 1) {
		_thread.join();
		_testthread = 0;
	}
    _roomGameStatus = 0;

	_testthread = 1;
	_thread = std::thread([this]() {CompteurStart();});
    //envoie msg game start
}

void Room::GameStart(void)
{

    //EN ATTENTE DES 3 SECONDES
	setClientsRoomStatus(false);
    _roomGameStatus = 1;
    sendMessageAll("GAME start");
//	sendCharacterIfAllOk();
    //envoie msg game start
}

void Room::GameEnd(void)
{
    //EN ATTENTE DES 3 SECONDES
    _roomGameStatus = -1;
    sendMessageAll("GAME end");
    //envoie msg game start
}