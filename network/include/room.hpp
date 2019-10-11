#ifndef ROOM_HPP_
#define ROOM_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <thread>

#include "client.hpp"

class Client;

class Room
{
    public:
        Room(int);
        ~Room();
        void clientJoin(Client *);
        void clientLeave(Client *);
        void sendMessageAll(std::string);
        void sendMessageUser(std::string, Client *);
        std::string getRoomInfo(void);
        unsigned int getRoomClientNbr(void);
        void setRoomId(int);
        int getRoomId(void);
        bool getStatusClients(void);
        int getRoomGameStatus(void);
        void setRoomGameStatus(int);
        void GameLunch(void);
        void GameStart(void);
        void GameEnd(void);
		void CompteurStart(void);
		void setClientsRoomStatus(bool status);
        void generateChief(void);
		void sendCharacterIfAllOk(Client * client);
		void setPosition();
		std::string getSeed(void);
		void sendRoomInfo();


    private:
        std::string adress;
        int _roomId;
        std::vector<Client *> _clients;
        int _roomGameStatus;//-1 no game, 0 en attente in bound,  game en cours
		int _testthread;
		std::string _seed;
		std::thread _thread;
};

#endif