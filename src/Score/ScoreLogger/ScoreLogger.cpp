/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** ScoreLogger.cpp.cc
*/

#include "ScoreLogger.hpp"

using namespace arcade;

static const size_t MAX_BLOCK_SIZE = 30;
static const size_t COLUMNS = 3;

ScoreLogger::ScoreLogger(const std::string &filename)
{
    this->loadScores(filename);
}

ScoreLogger::~ScoreLogger()
{
}

void ScoreLogger::loadScores(const std::string &filename)
{
    this->_data.clear();
    try {
        this->_data = this->readParseFile(filename);
    } catch (ScoreException const &e) {
        this->_data.clear();
        std::cerr << "Warning: Score log loading fail" << std::endl;
    }
}

void ScoreLogger::saveScores(
    DL::DLManager<IGameModule> &gameDLManager, const std::string &filename)
{
    std::deque<std::string> const &libs = gameDLManager.getAvailableLibs();
    std::ofstream file(filename);

    if (file.is_open() == false) {
        throw ScoreException("Fail to save scores");
    }
    for (std::string const &libName : libs) {
        try {
            auto const &gameModule = gameDLManager.getModule(libName);
            file << libName << "," << gameModule->getScore() << ","
                 << gameModule->getScoreHigh() << "\n";
        } catch (BaseException const &e) {
            std::cerr << "ScoreLogger::saveScores : " << e.what() << std::endl;
        }
    }
    file.close();
}

std::deque<std::shared_ptr<GameScore>> const &ScoreLogger::getGameScores() const
{
    return _data;
}

/* Private */

std::deque<std::shared_ptr<GameScore>> ScoreLogger::readParseFile(
    const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;
    std::deque<std::shared_ptr<GameScore>> result;

    if (file.is_open() == false) {
        throw ScoreException("Score file not found or unavailable");
    }
    while (std::getline(file, line)) {
        result.push_back(this->parseFileLine(line));
    }
    file.close();
    return result;
}

std::shared_ptr<GameScore> arcade::ScoreLogger::parseFileLine(
    const std::string &line)
{
    std::stringstream sbuf(line);
    std::deque<std::string> splitLine;
    std::shared_ptr<GameScore> parsedLine = std::make_shared<GameScore>();

    for (size_t i = 0; sbuf.good() && i < (COLUMNS + 1); i++) {
        std::string substr;
        getline(sbuf, substr, ',');
        if (substr.size() > MAX_BLOCK_SIZE) {
            throw ScoreException("Score log load : too much score cases");
        }
        splitLine.push_back(substr);
    }
    if (splitLine.size() != COLUMNS) {
        throw ScoreException("Score log load : invalid columns size");
    }
    parsedLine->name = splitLine[0];
    try {
        parsedLine->score = std::stoul(splitLine[1]);
        parsedLine->highScore = std::stoul(splitLine[2]);
    } catch (std::invalid_argument const &e) {
        throw ScoreException("Score log load : invalid score values");
    }
    return parsedLine;
}
