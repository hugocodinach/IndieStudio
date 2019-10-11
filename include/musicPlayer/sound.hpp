/*
** EPITECH PROJECT, 2018
** ActionHandler.cpp
** File description:
** include/musicPlayer/sound.cpp
*/

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

#ifndef SOUND_HPP_
#define SOUND_HPP_

class Sound
{
    public:
        Sound(std::string);
        ~Sound();
        void playSound(void);
        void setVolume(int value);

    private:
        std::string _soundName;
        std::vector<sf::Sound> _sounds;
        sf::SoundBuffer _soundBuffer;
};

#endif