#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <string>
#include <vector>
#include <iostream>

#include "room.hpp"

class Room;

class Client
{
    public:
        Client(int, std::string, Room *);
        ~Client();
        int getFd(void);
        std::string getUsername(void);
        int getWhichRoom(void);
        void setWhichRoom(Room *);
		void setCharacter(int character);
		int getCharacter();
		Room* getRoom();
        // void setWhichRoom(int);
        void setWhichRoom(std::string);
        void setStatus(bool);
        bool getStatus(void);
        void setChief(bool);
        bool getChief(void);
		void setPosition(int x, int y);
		std::string getPosition();

		int _idingame;
    private:
        std::string _username;
        int _fd;
        int _whichRoom;
		Room * _room;
        bool _ready;
        bool _chief;
		int _character;
		int _x;
		int _y;
};


#endif