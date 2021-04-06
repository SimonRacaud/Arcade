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
    class ScoreLogger {
      public:
        ScoreLogger(std::string const &filename = "scores.log");
        ~ScoreLogger();

        void loadScores(std::string const &filename);
        void saveScores(DL::DLManager<IGameModule> &gameDLManager,
            std::string const &filename = "scores.log");

        std::deque<std::string> const &getGameScores() const;

      private:
        std::deque<std::string> const readParseFile(
            std::string const &filename);
        std::string parseFileLine(std::string const &line);

        std::deque<std::string> _data;
    };
} // namespace arcade

#endif // SCORELOGGER_HPP_
