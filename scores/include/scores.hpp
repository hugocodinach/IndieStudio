#ifndef SCORES_HPP_
#define SCORES_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <thread>

class Scores
{
    public:
        Scores();
        ~Scores();
        std::string getPathScores(void);
        std::vector<std::pair<std::string, int>> getScores(void);
        void loadScores(void);
        void saveScores(void);
        void addNewScore(std::string, int);
        void scoresQuickSort(void);
        void reset(void);
    private:
        std::vector<std::pair<std::string, int>> _playerScore;
        std::string _pathScores;
};

#endif