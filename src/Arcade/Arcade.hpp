/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Arcade.hpp.h
*/

#ifndef ARCADE_HPP_
#define ARCADE_HPP_

#include "../Timer/Timer.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "LibLoadingException.hpp"
#include "LibNotFoundException.hpp"
#include "lib/DLManager/DLManager.hpp"

#include <deque>
#include <string>

#ifndef EXIT_ERROR
    #define EXIT_ERROR 84
#endif

#define CORE_TIMER 200

namespace arcade
{
    typedef IDisplayModule::KeyList Key;

    class Arcade {
      public:
        enum class ExitStatus {
            SUCCESS = EXIT_SUCCESS,
            ERROR = EXIT_ERROR,
            LOOP = 8
        };

        Arcade(std::string const &defGraphicFile);

        virtual ~Arcade();

        void loop();

        void resetGame();

        void setUsername(std::string const &username);

        std::string const &getUsername() const;

        void selectGame(std::string const &name);
        void selectGraphic(std::string const &name);
        ExitStatus getStatus() const;

        void eventManager();

      protected:
        void gotoMainMenu();
        void rotateGraphLib(bool rev);
        void rotateGameLib(bool rev);

        static const std::deque<std::string> GAME_LIB_NAMES;
        static const std::deque<std::string> GRAPHIC_LIB_NAMES;

      private:
        std::string _username;
        ExitStatus _status;
        IGameModule *_selectedGame;
        IDisplayModule *_selectedGraphic;
        std::string _selectedGameName;
        std::string _selectedGraphicName;
        DL::DLManager<IDisplayModule> _graphLibManager;
        DL::DLManager<IGameModule> _gameLibManager;
        Timer _timer;

        // MainMenu _mainMenu;
    };
} // namespace arcade

#endif // ARCADE_HPP_
