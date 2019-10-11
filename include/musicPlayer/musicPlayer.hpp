/*
** EPITECH PROJECT, 2018
** ActionHandler.cpp
** File description:
** include/musicPlayer/musicPlayer.cpp
*/

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include "music.hpp"
#include "sound.hpp"


#ifndef MUSICPLAYER_HPP_
#define MUSICPLAYER_HPP_
extern int MUSIC;

class MusicPlayer
{
    public:
        MusicPlayer();
        ~MusicPlayer();
        void playMusicPlayer(std::string);
        void pauseMusicPlayer(std::string);
        void setVolumeMusicPlayer(std::string, int volume);
        void setLoopMusicPlayer(std::string, bool);
        void stopMusicPlayer(std::string);
        std::string getMusicPlayerPath(std::string);
        bool setMusicPlayerName(std::string);
        std::vector<std::pair<std::string, std::string>> loadPlaylist(std::string);
        void setNewMusic(std::string, std::string);
        void setVolumeAllMusic(int);
        void setVolumeAllSound(int);

        void playSoundPlayer(std::string);

    private:
        std::map<std::string, Music *> _musicPlaylist;
        std::map<std::string, Sound *> _soundPlaylist;
        std::vector<std::pair<std::string, std::string>> _musicList;
        std::vector<std::pair<std::string, std::string>> _soundList;
};

#endif