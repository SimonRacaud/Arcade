/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** ScoreLogger.hpp.h
*/

#ifndef SCORELOGGER_HPP_
#define SCORELOGGER_HPP_

#include <fstream>
#include <streambuf>
#include <string>
#include "IGameModule.hpp"
#include "ScoreException.hpp"
#include "lib/DLManager/DLManager.hpp"

namespace arcade
{
    struct GameScore {
        std::string name;
        std::string player;
        size_t score;
        size_t highScore;
    };

    #define ARCADE_DEF_SCORE_FILE "scores.log"

    class ScoreLogger {
      public:
        ScoreLogger(std::string const &filename = ARCADE_DEF_SCORE_FILE);
        ~ScoreLogger();

        void loadScores(std::string const &filename = ARCADE_DEF_SCORE_FILE);
        void saveScores(DL::DLManager<IGameModule> &gameDLManager,
            const std::string &playerName,
            std::string const &filename = ARCADE_DEF_SCORE_FILE);

        std::deque<std::shared_ptr<GameScore>> const &getGameScores() const;

      private:
        std::deque<std::shared_ptr<GameScore>> readParseFile(
            std::string const &filename);
        std::shared_ptr<GameScore> parseFileLine(std::string const &line);

        GameScore getGameScore(std::string const &libName,
            std::shared_ptr<IGameModule> const &gameModule,
            std::deque<std::shared_ptr<GameScore>> const &log,
            const std::string &name);

        std::deque<std::shared_ptr<GameScore>> _data;
    };
} // namespace arcade

#endif // SCORELOGGER_HPP_
