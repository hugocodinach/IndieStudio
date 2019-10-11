/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/Client.hpp
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <string>
#include <iostream>

class Client {
	public:
		Client(int ssock){
			sock = ssock;
		};

		~Client(){};


		int sock;
//		int cfd;
		struct sockaddr_in peer_addr;
	    socklen_t peer_addr_size;
	private:
		
};

#endif