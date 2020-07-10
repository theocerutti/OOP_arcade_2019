/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ScoreSaver2
*/

#ifndef SCORESAVER_HPP_
#define SCORESAVER_HPP_

#include <iostream>
#include <fstream>
#include <map>
#include <deque>
#include <regex>
#include "../errors/CoreError.hpp"

namespace Arcade {
    class ScoreSaver {
        public:
            ScoreSaver(const std::string &scoreFile);
            // save score
            // returns true if in top 10 else false
            bool saveScore(int score, const std::string &playerName, const std::string &gameName);
            const std::deque<std::pair<std::string, int>> &getScoresFrom(const std::string &gameName);
        private:
            void rewriteScores();
            void truncateComment(std::string &line);
            bool isComment(const std::string &line);
            bool isGameSection(const std::string &line);
            bool isScore(const std::string &line);
            std::pair<std::string, int> getPairFromLine(const std::string &line);
        private:
            std::string _filePath;
            std::map<std::string, std::deque<std::pair<std::string, int>>> _mFile;
    };
}

#endif /* !SCORESAVER_HPP_ */
