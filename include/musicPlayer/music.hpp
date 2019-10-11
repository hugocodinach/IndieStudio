/*
** EPITECH PROJECT, 2018
** ActionHandler.cpp
** File description:
** include/musicPlayer/music.cpp
*/

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

class Music
{
    public:
        Music();
        ~Music();
        void playMusic(void);
        void pauseMusic(void);
        void setVolumeMusic(int volume);
        void setLoopMusic(bool);
        void stopMusic(void);
        std::string getMusicPath(void);
        bool setMusicName(std::string);
    private:
        std::string _musicName;
        sf::Music _music;
};

#endif