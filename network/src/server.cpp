#include "server.hpp"

Server::Server(int port)
{
    _port = port;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_family = AF_INET;
	_inthread = false;
}

Server::~Server()
{
}

Client *Server::getClient(int fd)
{
    for (unsigned int ct = 0; ct != _clients.size(); ct++) {
        if (fd == _clients[ct]->getFd()) {
            return _clients[ct];
		}
    }
	std::cout << "ALLLERRRRT !!!!" << std::endl;
	return nullptr;
}

int Server::accept_client(int fd_sock, int mode)
{
    int fd_new = 0;
    size_t size = 0;

    if (mode == 0) {
        size = sizeof(_addr);
        fd_new = accept(fd_sock, (struct sockaddr *)&_addr, (socklen_t *)&size);
    }
    if (fd_new < 0) {
        fprintf(stderr, "Accept failed.\n");
        return (-1);
    }
    return (fd_new);
}

void Server::addClient(int fd, std::string clientName)
{
	Client * new_client = new Client(fd, clientName, _mainRoom);
    _clients.push_back(new_client);
	_mainRoom->clientJoin(new_client);
    std::cout <<  "ADDED A CLIENT \n";
	_mainRoom->sendMessageAll(getServerInfoRoom());
}

Room *Server::addRoom(void)
{
    int id = 0;
    std::cout <<  "ADDED A ROOM \n";
	Room *new_room;

	if (_rooms.size() == 0) {
		new_room = new Room(-1);
		_rooms.push_back(new_room);
		return (new_room);
	}
	std::cout << "SIZE " << _rooms.size() << std::endl;
    for (unsigned int ct = 0; ct != _rooms.size(); ct ++) {
        if (_rooms[ct]->getRoomId() > ct)
            id = _rooms[ct]->getRoomId();
		id += 1;
	}
    new_room = new Room(id);
    _rooms.push_back(new_room);
    return new_room;
}

void Server::addClientInRoom(Client *client, Room *room)
{
	Room *old_room = client->getRoom();
	client->setWhichRoom(room);
	room->clientJoin(client);
	deleteClientInRoom(client, old_room);
}

void Server::deleteClientInRoom(Client *client, Room *room)
{
    client->setStatus(false);
    client->setChief(false);
    room->clientLeave(client);
    room->clientLeave(client);
	checkDeleteRoom();
}

void Server::read_from_client(int fdClient)
{
	FILE *fp = fdopen(fdClient, "r");
    char *str = NULL;
    size_t llen;
    int ct = 0;

    if ((ct = getline(&str, &llen, fp)) == -1) {
        std::cout << "close" << fdClient << std::endl;
        deleteClient(getClient(fdClient));
        checkDeleteRoom();
    } else {
        std::cout << std::to_string(ct) + "\n\n";
        if (ct > 1)
            pointerFct(getClient(fdClient), str);
        printf("Message received :     %s\n", str);
    }
}

void Server::deleteClient(Client *client)
{
    std::cout << "CLIENT DELETE\n";
    deleteClientInRoom(client, client->getRoom());
	FD_CLR(client->getFd(), &_active_fd_set);
    close(client->getFd());
	for (unsigned int ct = 0; ct != _clients.size(); ct++) {
		if (_clients[ct] == client) {
    		delete(_clients[ct]);
    		_clients.erase(_clients.begin() + ct);
    		break;
		}
	}
	_mainRoom->sendMessageAll(getServerInfoRoom());
}

void Server::checkDeleteRoom(void)
{
    std::cout << "CHECK DELETEROOM\n";
    for (unsigned int ct = 0; ct != _rooms.size(); ct ++)
        if (_rooms[ct]->getRoomClientNbr() == 0 && _rooms[ct] != _mainRoom) {
            delete(_rooms[ct]);
            _rooms.erase(_rooms.begin() + ct);
            break;
        }
}

void Server::getServerInfo(void)
{
    getServerInfoUser();
    getServerInfoRoom();
}

void Server::getServerInfoUser(void)
{
    if (_clients.size() == 0)
        std::cout << "No user in the server\n";
    else
        std::cout << "List of clients : \n\n";
    for (unsigned int ct = 0; ct != _clients.size(); ct ++) {
        std::cout << "USERNAME : " + _clients[ct]->getUsername() + " FD : " + std::to_string(_clients[ct]->getFd()) << std::endl; 
    }
}

std::string Server::getServerInfoRoom(void)
{
    std::string msg = "ROOM ";
    if (_rooms.size() == 0)
        msg = msg + "-1";
    for (unsigned int ct = 0; ct != _rooms.size(); ct ++) {
		if (ct == 0) {
			msg = msg + std::to_string(_rooms[ct]->getRoomId()) + " " + std::to_string(_clients.size()) + " ";
		} else {
	        msg = msg + std::to_string(_rooms[ct]->getRoomId()) + " " + std::to_string(_rooms[ct]->getRoomClientNbr()) + " ";
		}
    }
    return msg;
}

Room *Server::getRoomById(int id)
{
	for (unsigned int ct = 0; ct != _rooms.size(); ct ++) {
		if (_rooms[ct]->getRoomId() == id)
			return _rooms[ct];
	}
	return _mainRoom;
}

bool Server::getStatusFrom(Client *client)
{
    for (unsigned int ct = 0; ct != _rooms.size(); ct ++) {
        if (client->getWhichRoom() == _rooms[ct]->getRoomId())
            return _rooms[ct]->getStatusClients();
    }
    return false;
}

void Server::quit(Client *client, char *buffer, std::vector<std::string> arr)
{
    deleteClient(client);
    checkDeleteRoom();
    return;
}

void Server::log(Client *client, char *buffer, std::vector<std::string> arr)
{
    //A CHANGER !!!
    std::cout << "QUIT LOG\n";
    return;
}

void Server::chat(Client *client, char *buffer, std::vector<std::string> arr)
{
	std::string msg = ":";
	arr.erase(arr.begin());
	for (auto e : arr) {
		msg += " ";
		msg += e;
	}

    client->getRoom()->sendMessageAll("CHAT " + std::string(client->getUsername()) + msg);
    return;
}

void Server::action(Client *client, char *buffer, std::vector<std::string> arr)
{
	std::string msg;
	arr.erase(arr.begin());
	for (auto e : arr) {
		msg += " ";
		msg += e;
	}

//    client->getRoom()->sendMessageAll("ACTION " + std::to_string(client->_idingame)  + msg);
    client->getRoom()->sendMessageAll("ACTION " + std::to_string(client->_idingame)  + msg);
    return;
}

void Server::dead(Client *client, char *buffer, std::vector<std::string> arr)
{
    client->getRoom()->sendMessageAll("DEAD " + std::to_string(client->_idingame) + " " + arr[1]);
    return;
}

void Server::bonus(Client *client, char *buffer, std::vector<std::string> arr)
{
	std::string msg = std::string(buffer);
    client->getRoom()->sendMessageUser(msg, client);
    return;
}

void Server::room(Client *client, char *buffer, std::vector<std::string> arr)
{
    std::cout << "ROOM CMD\n";
    sendMsg(client->getFd(), getServerInfoRoom());
    return;
}

void Server::infoRoom(Client *client, char *buffer, std::vector<std::string> arr)
{
    std::cout << "INFOROOM CMD\n";
    if (arr.size() == 1) {
        sendMsg(client->getFd(), "INFOROOM -1");
        return;
    }
    for (std::string::const_iterator it = arr[1].begin(); it != arr[1].end(); it ++)
        if(std::isdigit(*it) == false) {
            sendMsg(client->getFd(), "INFOROOM -1");
            return;
        }
    for (unsigned int ct = 0; ct != _rooms.size(); ct ++) {
        if (atoi(arr[1].c_str()) == _rooms[ct]->getRoomId()) {
            sendMsg(client->getFd(), _rooms[ct]->getRoomInfo());
            return;
        }
    }
    sendMsg(client->getFd(), "INFOROOM -1");
    return;
}

void Server::seed(Client *client, char *buffer, std::vector<std::string> arr)
{
    sendMsg(client->getFd(), client->getRoom()->getSeed());
    return;
}

void Server::createRoom(Client *client, char *buffer, std::vector<std::string> arr)
{
    std::cout << "CREATEROOM CMD\n";
    addClientInRoom(client, addRoom());
    client->setChief(true);
    sendMsg(client->getFd(), "CREATEROOM " + std::to_string(client->getWhichRoom()));
	_mainRoom->sendMessageAll(getServerInfoRoom());
    return;
}

void Server::joinRoom(Client *client, char *buffer, std::vector<std::string> arr)
{
    std::cout << "JOINROOM CMD\n";
    if (arr.size() == 1) {
        sendMsg(client->getFd(), "JOINROOM -1");
        return;
    }
    for (std::string::const_iterator it = arr[1].begin(); it != arr[1].end(); it ++)
        if(std::isdigit(*it) == false) {
            sendMsg(client->getFd(), "JOINROOM -1 ERROR");
            return;
        }
    for (unsigned int ct = 0; ct != _rooms.size(); ct ++) {
        if (atoi(arr[1].c_str()) == _rooms[ct]->getRoomId()) {
			// client->getRoom()->clientLeave(client);
			sendMsg(client->getFd(), "JOINROOM OK");
            addClientInRoom(client, _rooms[ct]);
            // sendMsg(client->getFd(), _rooms[ct]->getRoomInfo());
			_mainRoom->sendMessageAll(getServerInfoRoom());
            return;
        }
    }
    sendMsg(client->getFd(), "JOINROOM -1");
}

void Server::leaveRoom(Client *client, char *buffer, std::vector<std::string> arr)
{
    std::cout << "LEAVEROOM CMD\n";
    if (client->getWhichRoom() != -1) {
        sendMsg(client->getFd(), "LEAVEROOM " + std::to_string(client->getWhichRoom()));
        deleteClientInRoom(client, client->getRoom());
	    client->setWhichRoom(_mainRoom);
		_mainRoom->clientJoin(client);
		_mainRoom->sendMessageAll(getServerInfoRoom());
        return;
    }
    sendMsg(client->getFd(), "JOINROOM -1");
	_mainRoom->sendMessageAll(getServerInfoRoom());
    return;
}

void Server::setUserName(Client *client, char *buffer, std::vector<std::string> arr)
{
    std::cout << "setUserName CMD\n";
    if (arr.size() >= 2)
        client->setWhichRoom(arr[1]);
    else
        sendMsg(client->getFd(), "SETUSERNAME -1");
}

void Server::play(Client *client, char *buffer, std::vector<std::string> arr)
{
    std::cout << "PLAY CMD\n";
    if (client->getWhichRoom() == -1)
        sendMsg(client->getFd(), "PLAY -1");
    else
        sendMsg(client->getFd(), "PLAY -1");
}

void Server::status(Client *client, char *buffer, std::vector<std::string> arr)
{
    std::cout << "STATUS CMD\n";
    if (arr.size() == 1) {
        sendMsg(client->getFd(), "STATUS -1");
        return;
    }
    if (arr[1] == "ready") {
        sendMsg(client->getFd(), "STATUS ready");
        if (client->getStatus() == true)
            return;
        client->setStatus(true);
		client->getRoom()->sendRoomInfo();
        if (client->getRoom()->getStatusClients() == true)
            client->getRoom()->GameLunch();
        return;
    }
    if (arr[1] == "unready") {
        client->setStatus(false);
        sendMsg(client->getFd(), "STATUS unready");
		client->getRoom()->sendRoomInfo();
        return;
    }
    sendMsg(client->getFd(), "STATUS -1");
}

void Server::promote(Client *client, char *buffer, std::vector<std::string> arr)
{
    std::cout << "PROMOTE CMD\n";
    if (arr.size() == 1) {
        sendMsg(client->getFd(), "PROMOTE -1");
        return;
    }
    if (client->getChief() == false) {
        sendMsg(client->getFd(), "PROMOTE you must be a chief to promote");
        return;
    }
    for (unsigned int ct = 0; ct != _clients.size(); ct ++) {
        if (_clients[ct]->getUsername() == arr[1] && _clients[ct]->getUsername() != client->getUsername()) {
            client->setChief(false);
            _clients[ct]->setChief(true);
            sendMsg(_clients[ct]->getFd(), "PROMOTE you have been promoted to chief in this room");
            sendMsg(client->getFd(), "PROMOTE you have been removed from chief of the room");
            return;
        }
    }
    sendMsg(client->getFd(), "PROMOTE -1");
}

void Server::sendMsg(int fdClient, std::string msg)
{
    dprintf(fdClient, "%s\n", msg.c_str());
}

void Server::setCharacter(Client *client, char *buffer, std::vector<std::string> arr)
{
	client->setCharacter(std::atoi(arr[1].c_str()));
	client->getRoom()->sendRoomInfo();
}

void Server::getCharacter(Client *client, char *buffer, std::vector<std::string> arr)
{
	client->getRoom()->sendCharacterIfAllOk(client);
}


void Server::pointerFct(Client *client, char *buffer)
{
    command_t const arr_cmd[] = {{"ACTION", &Server::action},
	{"DEAD", &Server::dead},
	{"BONUS", &Server::bonus},
	{"QUIT", &Server::quit},
	{"GETCHARACTER", &Server::getCharacter},
	{"LOG", &Server::log}, 
    {"CHAT", &Server::chat},
	{"ROOM", &Server::room},
	{"INFOROOM", &Server::infoRoom}, 
    {"CREATEROOM", &Server::createRoom},
	{"JOINROOM", &Server::joinRoom}, 
    {"LEAVEROOM", &Server::leaveRoom},
	{"SETUSERNAME", &Server::setUserName},
    {"PLAY", &Server::play},
	{"STATUS", &Server::status},
	{"PROMOTE", &Server::promote},
	{"SEED", &Server::seed}, 
	{"SETCHARACTER", &Server::setCharacter}};
    // char op[] = " \n\t\r";
    std::vector<std::string> arr;
	std::string str(buffer);
	boost::split(arr, str, boost::is_any_of(" \n"));

	for (auto e : arr_cmd) {
		if (arr[0] == e.cmd) {
            (this->*e.cmd_name)(client, buffer, arr);
            return;
        }
	}
    return;
}

bool Server::setSocket(void)
{
    _fdSocket = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;

    if (_fdSocket == -1) {
        fprintf(stderr, "Error opening socket.\n");
        return false;
    }
    if (bind(_fdSocket, (struct sockaddr *)&_addr, sizeof(struct sockaddr_in)) == -1) {
        fprintf(stderr, "Error binding socket.\n");
        return false;
    }
    setsockopt(_fdSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if (listen(_fdSocket, 1) < 0) {
        fprintf(stderr, "Listen faild.\n");
        return false;
    }
    return true;
}

int Server::run(void)
{
    int fd = 0;
    int newFd = 0;

	//_thread = std::thread([this]() {listenfd();});
    if (setSocket() == false)
        return 84;
    _mainRoom = addRoom();
    FD_ZERO(&_active_fd_set);
    FD_SET(_fdSocket, &_active_fd_set);
    while (1) {
        _read_fd_set = _active_fd_set;
        if (select (FD_SETSIZE, &_read_fd_set, NULL, NULL, NULL) < 0) {
            fprintf(stderr, "Select faild\n");
			_thread.join();
            return 84;
        }
        for (fd = FD_SETSIZE; fd > 0; -- fd) {
            if (FD_ISSET(fd, &_read_fd_set)) {
                if (fd == _fdSocket) {
                    if ((newFd = accept_client(_fdSocket, 0)) == -1) {
						_thread.join();
                        return 84;
					}
                    FD_SET(newFd, &_active_fd_set);
					dprintf(newFd, "CONNECTED\n");
                    addClient(newFd, "User");
                } else {
                     read_from_client(fd);
					//_stackfd.push_back(fd);
                }
            }
		}
    }
	_thread.join();
}

void Server::listenfd()
{
	while (1) {
		if (_stackfd.size() > 0) {
			for (auto e : _stackfd) {
				read_from_client(e);
			}
			_stackfd.clear();
		}
	}
}

int main(int ac, char **arg)
{
    int port = 7171;
    if (ac >= 2)
        port = atoi(arg[1]);
    srand(time(NULL));
    Server Server(port);

    Server.run();
}