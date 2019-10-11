/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** src/NetworkCommunication.cpp
*/

#include "NetworkClient.hpp"

NetworkClient::NetworkClient()
{
	_is_running = false;
	_tcpStream = nullptr;
}

void NetworkClient::listen(void)
{
    std::string str;

    while (std::getline(*_tcpStream, str)) {
		// std::cout << "msg : " << str << std::endl;
		_action.push_back(str);
    }
	// std::cout << "STOP" << std::endl;
}

bool NetworkClient::run(std::string ip, std::string port)
{
	if (_is_running == false) {
    	_tcpStream = new boost::asio::ip::tcp::tcp::iostream(ip, port);
		std::string str;
		std::getline(*_tcpStream, str);
		// std::cout  << str << std::endl;
		if (str == "") {
			// std::cout << "ERROR CONNECTION" << std::endl;
			return false;
		}
        // std::cout << "CONNECTED" << std::endl;
		_ip = ip;
		_port = port;
		_thread = std::thread([this]() {listen();});
		_name = "user";
		room();
		_is_running = true;
	}
	return true;
}

void NetworkClient::createRoom()
{
	*_tcpStream << "CREATEROOM" << std::endl;
}

void NetworkClient::joinRoom(int id)
{
	*_tcpStream << "JOINROOM " << id << std::endl;
}

void NetworkClient::room()
{
	*_tcpStream << "ROOM" << std::endl;
}

void NetworkClient::infoRoom(int id)
{
	*_tcpStream << "INFOROOM " << id << std::endl;
}

void NetworkClient::leaveRoom()
{
	*_tcpStream << "LEAVEROOM" << std::endl;
}

void NetworkClient::getSeed()
{
	*_tcpStream << "SEED" << std::endl;
}

void NetworkClient::dead()
{
	// std::cout << "onéla" << std::endl;
	// *_tcpStream << "DEAD" << std::endl;
	
	*_tcpStream << "ACTION BITE" << std::endl;
	// std::cout << "onéal" << std::endl;
}

void NetworkClient::ready()
{
	*_tcpStream << "STATUS ready" << std::endl;
}

void NetworkClient::setCharacter(int character)
{
	*_tcpStream << "SETCHARACTER " << character << std::endl;
}

void NetworkClient::bonus(int type, int x, int y)
{
	*_tcpStream << "BONUS " << type << " " << x << " " << y << std::endl;
}

void NetworkClient::action(std::string msg)
{
	if (msg.compare("DEAD") == 0) {
		*_tcpStream << "DEAD" << std::endl;
	}
	*_tcpStream << "ACTION " << msg << std::endl;
}

void NetworkClient::chat(std::string msg)
{
	*_tcpStream << "CHAT " << msg << std::endl;
}

void NetworkClient::getCharacter()
{
	*_tcpStream << "GETCHARACTER" << std::endl;
}

void NetworkClient::setUsername(std::string name)
{
	_name = name;
	*_tcpStream << "SETUSERNAME " << name << std::endl;
}

void NetworkClient::setStatus(bool status)
{
	std::string tmp;

	if (status)
		tmp = "ready";
	else
		tmp = "unready";
	*_tcpStream << "STATUS " << tmp << std::endl;
}

void NetworkClient::quit()
{
	if (_tcpStream != nullptr)
		*_tcpStream << "QUIT" << std::endl;
	if (_is_running == true)
		_thread.join();
	_is_running = false;
}

std::string NetworkClient::getMyIp()
{
	std::string s = "0.0.0.0";
	return (s);
}

NetworkClient::~NetworkClient()
{
}