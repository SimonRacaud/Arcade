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
        this->_data.push_back("no scores.");
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
            auto const& gameModule = gameDLManager.getModule(libName);
            file << libName << "," << gameModule->getScore() << ","
                 << gameModule->getScoreHigh() << "\n";
        } catch (BaseException const &e) {
            std::cerr << "ScoreLogger::saveScores : " << e.what() << std::endl;
        }
    }
    file.close();
}

std::deque<std::string> const &ScoreLogger::getGameScores() const
{
    return _data;
}

/* Private */

const std::deque<std::string> ScoreLogger::readParseFile(
    const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;
    std::deque<std::string> result;

    if (file.is_open() == false) {
        throw ScoreException("Score file not found or unavailable");
    }
    while (std::getline(file, line)) {
        result.push_back(this->parseFileLine(line));
    }
    file.close();
    return result;
}

std::string arcade::ScoreLogger::parseFileLine(const std::string &line)
{
    std::stringstream sbuf(line);
    std::deque<std::string> splitLine;

    for (size_t i = 0; sbuf.good() && i < (COLUMNS + 1); i++) {
        std::string substr;
        getline(sbuf, substr, ',');
        if (substr.size() > MAX_BLOCK_SIZE) {
            throw ScoreException("too long score case");
        }
        splitLine.push_back(substr);
    }
    if (splitLine.size() != COLUMNS) {
        throw ScoreException("invalid columns size");
    }
    return splitLine[0] + ": Score " + splitLine[1] + ", HScore "
        + splitLine[2];
}
