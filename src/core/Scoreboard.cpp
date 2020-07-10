/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Scoreboard
*/

#include "Scoreboard.hpp"

Arcade::Scoreboard::Scoreboard(ScoreSaver &scoreSaver) :
    _scoreSaver(scoreSaver),
    _textNumber(),
    _scoreLineTexts(),
    _noScore()
{
}

Arcade::Scoreboard::Scoreboard(ScoreSaver &scoreSaver, const std::string &gameTitle) :
    _scoreSaver(scoreSaver),
    _textNumber(),
    _scoreLineTexts(),
    _noScore()
{
    setScoreGameToDisplay(gameTitle);
}

Arcade::Scoreboard::~Scoreboard()
{
}

void Arcade::Scoreboard::drawWith(ILibGFX *lib)
{
    if (_textNumber.size() == 0 || _scoreLineTexts.size() == 0) {
        lib->drawText(_noScore);
    } else {
        for (auto &nbText : _textNumber)
            lib->drawText(nbText);
        for (auto &scoreLine : _scoreLineTexts) {
            lib->drawText(scoreLine.first);
            lib->drawText(scoreLine.second);
        }
        lib->drawRect(_line1);
        lib->drawRect(_line2);
        lib->drawRect(_line3);
        lib->drawText(_scoreText);
        lib->drawText(_nameText);
        lib->drawText(_nbText);
    }
}

void Arcade::Scoreboard::setScoreGameToDisplay(const std::string &gameTitle)
{
    int n = 1;
    const std::deque<std::pair<std::string, int>> scoresInfo = _scoreSaver.getScoresFrom(gameTitle);

    _line1.setDimension(3, 310);
    _line2.setDimension(3, 310);
    _line1.setPosition(300, 210);
    _line2.setPosition(470, 210);
    _line3.setDimension(400, 3);
    _line3.setPosition(180, 210);

    _nbText.setText("Rank:");
    _nbText.setPathFont("./assets/fonts/test.ttf");
    _nbText.setTextSize(25);
    _nbText.setPosition(205, 180);
    _nameText.setText("Name:");
    _nameText.setPathFont("./assets/fonts/test.ttf");
    _nameText.setTextSize(25);
    _nameText.setPosition(355, 180);
    _scoreText.setText("Score:");
    _scoreText.setPathFont("./assets/fonts/test.ttf");
    _scoreText.setTextSize(25);
    _scoreText.setPosition(490, 180);

    _textNumber.clear();
    _scoreLineTexts.clear();
    _noScore.setPosition(220, 280);
    _noScore.setText("No  Score  saved");
    _noScore.setTextSize(50);
    _noScore.setPathFont("./assets/fonts/ArcadeClassic.ttf");
    for (auto &info : scoresInfo) {
        Arcade::Text nbText(std::to_string(n));
        nbText.setPathFont("./assets/fonts/ArcadeClassic.ttf");
        nbText.setPosition(220, (30 * (n + 1)) + 150);
        _textNumber.push_back(nbText);

        Arcade::Text playerNameText(info.first);
        playerNameText.setPathFont("./assets/fonts/ArcadeClassic.ttf");
        playerNameText.setPosition(360, (30 * (n + 1)) + 150);

        Arcade::Text scoreText(std::to_string(info.second));
        scoreText.setPathFont("./assets/fonts/ArcadeClassic.ttf");
        scoreText.setPosition(510, (30 * (n + 1)) + 150);

        _scoreLineTexts.push_back(std::pair<Arcade::Text, Arcade::Text>(playerNameText, scoreText));
        n++;
    }
}