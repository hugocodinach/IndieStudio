/*
** EPITECH PROJECT, 2018
** ActionHandler.cpp
** File description:
** src/musicPlayer/music.cpp
*/

#include <musicPlayer.hpp>

Music::Music()
{
}

Music::~Music()
{
    _music.stop();
}

std::string Music::getMusicPath(void)
{
    return _musicName;
}

bool Music::setMusicName(std::string musicName)
{
    if (!_music.openFromFile(musicName)) {
        return false;
    }
    _musicName = musicName;
    return true;
}

void Music::playMusic(void)
{
    _music.play();
}

void Music::pauseMusic(void)
{
    _music.pause();
}

void Music::stopMusic(void)
{
    _music.stop();
}

void Music::setLoopMusic(bool value)
{
    _music.setLoop(value);
}

void Music::setVolumeMusic(int value)
{
    _music.setVolume(value);
}