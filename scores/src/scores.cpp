#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "scores.hpp"

Scores::Scores()
{
    _pathScores = "./scores/data/scores.txt";
    loadScores();
}

Scores::~Scores()
{
}

std::string Scores::getPathScores(void)
{
    return _pathScores;
}

std::vector<std::pair<std::string, int>> Scores::getScores(void)
{
    return _playerScore;
}


void Scores::addNewScore(std::string name, int score)
{
    std::pair<std::string, int> playerScores;

    playerScores.first = name;
    playerScores.second = score;
    _playerScore.push_back(playerScores);
    scoresQuickSort();
}

void Scores::loadScores(void)
{
    std::ifstream myFile;
    std::ios_base::openmode mode = std::ios_base::in;
    std::string str;
    std::string fileScores = getPathScores();
    int status = 0;
    std::pair<std::string, int> playerScores;

    myFile.open(fileScores, mode);
    while (getline(myFile, str)) {
        if (str.find(" ") == std::string::npos)
            status = 1;
        for (unsigned int ct = str.find(" ") + 1; str[ct] != '\0'; ct ++)
            if (isdigit(str[ct]) == 0)
                status = 1;
        if (status == 0) {
            playerScores.first = str.substr(0, str.find(" "));
            playerScores.second = stoi(str.substr(str.find(" ") + 1));
            _playerScore.push_back(playerScores);
        }
        status = 0;
    }
    myFile.close();
}

void Scores::saveScores(void)
{
    std::ofstream ofile(getPathScores());

    for (unsigned int ct = 0; ct != _playerScore.size(); ct ++) {
        ofile << _playerScore[ct].first + " " + std::to_string(_playerScore[ct].second) + "\n";
    }
    ofile.close();
}

void Scores::scoresQuickSort(void)
{
    for (unsigned int ct = 0; (ct + 1) != _playerScore.size(); ct ++)
        if (_playerScore[ct].second < _playerScore[ct + 1].second) {
            swap(_playerScore[ct], _playerScore[ct + 1]);
            ct = -1;
        }
}

void Scores::reset(void)
{
    _playerScore.clear();
    loadScores();
}

//EXEMPLE    g++  scores.cpp  -std=gnu++11

// int main()
// {
//     Scores Scores;
//     Scores.addNewScore("TEST", 20);
//     Scores.saveScores();
// }