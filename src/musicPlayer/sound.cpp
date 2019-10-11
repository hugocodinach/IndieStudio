/*
** EPITECH PROJECT, 2018
** ActionHandler.cpp
** File description:
** src/musicPlayer/sound.cpp
*/

#include <musicPlayer.hpp>

Sound::Sound(std::string soundPath)
{
    sf::Sound sound;
    if (MUSIC == 1) {


    if (!_soundBuffer.loadFromFile(soundPath)) {
        return;
    }
    _soundName = soundPath;
    sound.setBuffer(_soundBuffer);
    for (unsigned int ct = 0; ct != 15; ct ++) {
        _sounds.push_back(sound);
    }
    }
}

Sound::~Sound()
{
    if (MUSIC == 1) {

    if (_sounds.size() == 0)
        return;
    for (unsigned int ct = 0; ct != 15; ct ++) {
        _sounds[ct].stop();
    }
    _sounds.clear();
    }
}

void Sound::playSound(void)
{
    if (_sounds.size() == 0) {
        return;
    }
    for (unsigned int ct = 0; ct != 15; ct ++) {
        if (_sounds[ct].getStatus() != 2) {
            _sounds[ct].play();
            return;
        }
    }
}

void Sound::setVolume(int value)
{
    for (unsigned int ct = 0; ct != 15 && ct < _sounds.size(); ct ++) {
        _sounds[ct].setVolume(value);
    }
}