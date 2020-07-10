/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** ScoreSaver
*/

#include "ScoreSaver.hpp"

Arcade::ScoreSaver::ScoreSaver(const std::string &filePath) : _filePath(filePath)
{
    std::ifstream file(_filePath);
    std::string currentSection;
    std::string line;
    int nLine = 0;

    if (file.fail())
        throw CoreError("ScoreSaver: Can't open '" + _filePath + "' file.");
    while (std::getline(file, line)) {
        if (line.empty() || isComment(line))
            continue;
        truncateComment(line);
        line.erase(line.find_last_not_of(" \n\r\t") + 1); // trim whitespaces
        if (!isGameSection(line) && !isScore(line)) {
            throw CoreError("ScoreSaver: Error at line ." + std::to_string(nLine) + "(/!\\ playerName must be composed of 3 letters)");
        }
        if (isGameSection(line)) {
            currentSection = line.substr(0, line.size() - 1);
            if (_mFile.find(currentSection) != _mFile.end())
                throw CoreError("ScoreSaver: Multiple gameSection at ." + std::to_string(nLine));
            _mFile.insert({currentSection, std::deque<std::pair<std::string, int>>()});
        }
        if (isScore(line)) {
            if (_mFile.at(currentSection).size() >= 10)
                throw CoreError("ScoreSaver: More than 10 scores saved in the '" + currentSection + "' section. (max: 10)");
            _mFile.at(currentSection).push_back(getPairFromLine(line));
        }
        nLine++;
    }
    file.close();
}

bool Arcade::ScoreSaver::saveScore(int score, const std::string &_playerName, const std::string &gameName)
{
    bool saved = false;
    std::string playerName = _playerName;

    std::for_each(playerName.begin(), playerName.end(), [](char &c){
        c = ::toupper(c);
    });
    if (playerName.size() != 3)
        throw CoreError("ScoreSaver: saveScore: Can't save a '" + playerName + "', more than 3 letters.");
    if (_mFile.find(gameName) == _mFile.end()) {
        std::deque<std::pair<std::string, int>> vScore;
        vScore.push_back(std::pair<std::string, int>(playerName, score));
        _mFile.insert({gameName, vScore});
        saved = true;
    } else {
        _mFile.at(gameName).push_back(std::pair<std::string, int>(playerName, score));
        std::sort(_mFile.at(gameName).begin(), _mFile.at(gameName).end(), [](auto &left, auto &right) {
            return (left.second > right.second);
        });
        if (_mFile.at(gameName).size() > 10)
            _mFile.at(gameName).pop_back();
        saved = true;
    }
    if (saved)
        rewriteScores();
    return (saved);
}

const std::deque<std::pair<std::string, int>> &Arcade::ScoreSaver::getScoresFrom(const std::string &gameNameSection)
{
    if (_mFile.find(gameNameSection) == _mFile.end()) {
        _mFile.insert({gameNameSection, std::deque<std::pair<std::string, int>>()});
        rewriteScores();
    }
    return (_mFile.at(gameNameSection));
}

void Arcade::ScoreSaver::rewriteScores()
{
    std::ofstream file(_filePath);

    if (file.fail())
        throw CoreError("ScoreSaver: Can't open '" + _filePath + "' file.");
    for (auto &vScores : _mFile) {
        file << vScores.first << ":\n";
        for (auto &scorePair : vScores.second)
            file << scorePair.first << ", " << scorePair.second << "\n";
    }
    file.close();
}

std::pair<std::string, int> Arcade::ScoreSaver::getPairFromLine(const std::string &line)
{
    std::smatch matchs;
    std::regex isScore("^(\\w{3}),[\t ]*([0-9]+)$");

    std::regex_search(line, matchs, isScore);
    return (std::pair<std::string, int>(matchs.str(1), std::stoi(matchs.str(2))));
}

void Arcade::ScoreSaver::truncateComment(std::string &line)
{
    if (line.find('#') != std::string::npos)
        line.erase(line.find('#'), std::string::npos);
}

bool Arcade::ScoreSaver::isComment(const std::string &line)
{
    std::smatch matchs;
    std::regex isGameSection("^\\w+:$");

    std::regex_search(line, matchs, isGameSection);
    if (matchs.str(1) == "")
        return (false);
    return (true);
}

bool Arcade::ScoreSaver::isGameSection(const std::string &line)
{
    std::smatch matchs;
    std::regex isGameSection("^\\w+:$");

    std::regex_search(line, matchs, isGameSection);
    if (matchs.empty())
        return (false);
    return (true);
}

bool Arcade::ScoreSaver::isScore(const std::string &line)
{
    std::smatch matchs;
    std::regex isScore("^(\\w{3}),[\t ]*([0-9]+)$");

    std::regex_search(line, matchs, isScore);
    if (matchs.empty())
        return (false);
    return (true);
}