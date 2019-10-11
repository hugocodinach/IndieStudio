/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** include/NetworkCommunication/NetworkClient.hpp
*/

#ifndef NETWORK_CLIENT
    #define NETWORK_CLIENT

    #include <iostream>
    #include <string>
    #include <boost/asio.hpp>

    class NetworkClient {
        public:
            NetworkClient();
            ~NetworkClient();

            void listen(void);
            bool run(std::string ip, std::string port);
			void createRoom();
			void joinRoom(int id);
			void room();
			void infoRoom(int id);
			void leaveRoom();
			void setUsername(std::string name);
			void setStatus(bool status);
			void quit();
			void getSeed();
			void setCharacter(int character);
			void action(std::string msg);
			void chat(std::string msg);
			void ready();
			void dead();
			void bonus(int type, int x, int y);
			void getCharacter();

			std::string getMyIp();

			std::vector<std::string> _action;
        private:
            std::string _ip;
            std::string _port;
            boost::asio::ip::tcp::tcp::iostream *_tcpStream;
            std::thread _thread;
			std::string _name;
			bool _is_running;
    };
#endif