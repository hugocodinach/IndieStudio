/*
** EPITECH PROJECT, 2018
** ActionHandler.cpp
** File description:
** src/musicPlayer/musicPlayer.cpp
*/

#include "musicPlayer.hpp"

MusicPlayer::MusicPlayer()
{
	if (MUSIC == 1) {

    _musicList = loadPlaylist("./ressources/audio/musicList.txt");
    _soundList = loadPlaylist("./ressources/audio/soundList.txt");
    for (unsigned int ct = 0; ct != _musicList.size(); ct ++) {
        _musicPlaylist[_musicList[ct].first] = new Music();
        if (_musicPlaylist[_musicList[ct].first]->setMusicName(_musicList[ct].second) == false)
            _musicPlaylist.erase(_musicList[ct].first);
    }
    for (unsigned int ct = 0; ct != _soundList.size(); ct ++) {
        _soundPlaylist[_soundList[ct].first] = new Sound(_soundList[ct].second);
    }
	}
}

MusicPlayer::~MusicPlayer()
{
	if (MUSIC == 1) {

    std::map<std::string, Sound *>::iterator itSound;
    std::map<std::string, Music *>::iterator itMusic;

    for (itSound = _soundPlaylist.begin(); itSound != _soundPlaylist.end(); itSound++) {
        delete itSound->second;
    }
    for (itMusic = _musicPlaylist.begin(); itMusic != _musicPlaylist.end(); itMusic++) {
        delete itMusic->second;
    }
	}
}

std::vector<std::pair<std::string, std::string>> MusicPlayer::loadPlaylist(std::string soundPlaylistPath)
{
    std::ifstream myFile;
    std::ios_base::openmode mode = std::ios_base::in;
    std::string str;
    int status = 0;
    std::pair<std::string, std::string> soundList;
    std::vector<std::pair<std::string, std::string>> musicList;
    struct stat info;

	if (MUSIC == 1) {
    myFile.open(soundPlaylistPath, mode);
    if (!myFile) {
        myFile.close();
        return musicList;
    }
    while (std::getline(myFile, str)) {
        // std::cout << str << std::endl;
        if (str.find(" ") == std::string::npos)
            status = 1;
        if (status == 0) {
            soundList.first = str.substr(0, str.find(" "));
            soundList.second = str.substr(str.find(" ") + 1);
            musicList.push_back(soundList);
        }
        status = 0;
    }
    myFile.close();
	}
    return musicList;
}

void MusicPlayer::setNewMusic(std::string musicName, std::string musicPath)
{
    _musicPlaylist[musicName] = new Music();
    if (_musicPlaylist[musicName]->setMusicName(musicPath) == false)
        _musicPlaylist.erase(musicName);
}

void MusicPlayer::playSoundPlayer(std::string musicName)
{
	if (MUSIC == 1)
	{	// std::cout << musicName << std::endl;
		if (_soundPlaylist.find(musicName) == _soundPlaylist.end())
			return;
		_soundPlaylist[musicName]->playSound();
	}
}

void MusicPlayer::playMusicPlayer(std::string musicName)
{
    // std::cout << musicName << std::endl;
    if (_musicPlaylist.find(musicName) == _musicPlaylist.end())
        return;
    _musicPlaylist[musicName]->playMusic();
}

void MusicPlayer::pauseMusicPlayer(std::string musicName)
{
    if (_musicPlaylist.find(musicName) == _musicPlaylist.end())
        return;
    _musicPlaylist[musicName]->pauseMusic();
}

void MusicPlayer::stopMusicPlayer(std::string musicName)
{
    if (_musicPlaylist.find(musicName) == _musicPlaylist.end())
        return;
    _musicPlaylist[musicName]->stopMusic();
}

void MusicPlayer::setLoopMusicPlayer(std::string musicName, bool value)
{
    if (_musicPlaylist.find(musicName) == _musicPlaylist.end())
        return;
    _musicPlaylist[musicName]->setLoopMusic(value);
}

void MusicPlayer::setVolumeMusicPlayer(std::string musicName, int value)
{
    if (_musicPlaylist.find(musicName) == _musicPlaylist.end())
        return;
    _musicPlaylist[musicName]->setVolumeMusic(value);
}

void MusicPlayer::setVolumeAllMusic(int volume)
{
    for (int i = 0; i < _musicList.size(); i += 1) {
        setVolumeMusicPlayer(_musicList[i].first, volume);
    }
}

void MusicPlayer::setVolumeAllSound(int volume)
{
    for (int i = 0; i < _soundList.size(); i += 1) {
        _soundPlaylist[_soundList[i].first]->setVolume(volume);
    }
}


std::string MusicPlayer::getMusicPlayerPath(std::string musicName)
{
    if (_musicPlaylist.find(musicName) == _musicPlaylist.end())
        return NULL;
    return _musicPlaylist[musicName]->getMusicPath();
}