/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** CoreConfig
*/

#ifndef CORECONFIG_HPP_
#define CORECONFIG_HPP_

#include <deque>
#include <string>
#include <algorithm>
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "LibNotFoundException.hpp"
#include "Score/ScoreLogger/ScoreLogger.hpp"

#include "lib/DLManager/DLManager.hpp"

#ifndef EXIT_ERROR
    #define EXIT_ERROR 84
#endif

namespace arcade
{
    class CoreConfig {
        public:
            enum class ExitStatus {
                SUCCESS = EXIT_SUCCESS,
                ERROR = EXIT_ERROR,
                LOOP = 8
            };

            CoreConfig(std::string const &defGraphicFile);
            virtual ~CoreConfig();

            void resetGame();
            void reloadLib();

            void setUsername(std::string const &username);
            std::string const &getUsername() const;

            void selectGame(std::string const &name);
            void selectGraphic(std::string const &name);

            ExitStatus getStatus() const;
            void setStatus(ExitStatus const status);

            std::shared_ptr<IGameModule> getSelectedGame();
            std::shared_ptr<IDisplayModule> getSelectedGraphic();
            void rotateGraphLib(bool rev);
            void rotateGameLib(bool rev);
            void gotoMainMenu();

            std::deque<std::string> getGameNames();
            std::deque<std::string> getGraphicNames();

        protected:
            static const std::deque<std::string> GAME_LIB_NAMES;
            static const std::deque<std::string> GRAPHIC_LIB_NAMES;
        private:
            std::string _username;
            ExitStatus _status;
            std::shared_ptr<IGameModule> _selectedGame;
            std::shared_ptr<IDisplayModule> _selectedGraphic;
            DL::DLManager<IDisplayModule> _graphLibManager;
            DL::DLManager<IGameModule> _gameLibManager;
            std::string _selectedGameName;
            std::string _selectedGraphicName;
            ScoreLogger _scoreLogger;
    };

}

#endif /* !CORECONFIG_HPP_ */
