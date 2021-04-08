/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** MainMenu
*/

#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include "../Timer/Timer.hpp"
#include "../CoreConfig/CoreConfig.hpp"
#include <string>
#include <unistd.h>
#include <vector>
#include <deque>

namespace arcade
{
    class MainMenu {
        public:
            MainMenu(CoreConfig &coreConfig);
            virtual ~MainMenu();

            void refresh();

            protected:
            private:
                std::string rotate(const std::deque<std::string> &listName, std::string selected, bool rev);

                void movePanelEvent(IDisplayModule &selectedGraphic);
                void eventHandler();

                void displayFirstPanel(IDisplayModule &selectedGraphic);
                void displaySecondPanel(IDisplayModule &selectedGraphic);
                void displayThirdPanel(IDisplayModule &selectedGraphic);

                void displayMenu(IDisplayModule &selectedGraphic);
                void displayLoading(IDisplayModule &selectedGraphic);

                static const std::vector<std::string> _title;
                static const std::vector<std::string> _menuTitle;
                static const std::deque<std::string> CATEGORIE_NAMES;
                static const std::deque<std::string> _helpText;
                static const std::deque<std::string> _settings;

                CoreConfig &_coreConfig;
                std::string _selectedCategorie;
                std::string _selectedGame;
                std::string _selectedGraphic;
                std::string _selectedSetting;
                size_t _selectedPanel;
                bool _isLoading;
                Timer _animationTimer;
                bool _pressStart;
    };
} // namespace arcade

#endif /* !MENU_HPP_ */
