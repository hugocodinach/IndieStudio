/*
** EPITECH PROJECT, 2018
** RessourcesInfo.hpp
** File description:
** include/RessourcesInfo.hpp
*/

#ifndef RESSOURCES_INFO
#define RESSOURCES_INFO

enum Mode {
    NORMAL,
    EPITECH,
};

class RessourcesInfo {
    public:
        RessourcesInfo();
        ~RessourcesInfo();

        void changeMode(Mode);

    private:
};

#endif