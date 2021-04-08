/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** TextInput
*/

#ifndef TEXTINPUT_HPP_
#define TEXTINPUT_HPP_

#include <string>
#include <map>
#include "IDisplayModule.hpp"

namespace arcade
{

    class TextInput {
        public:
            TextInput(const std::string input = "");
            ~TextInput();

            void refresh(IDisplayModule &display);
            std::string getInputText() const;

        protected:
        private:
            std::string _input;
            static const std::map<IDisplayModule::KeyList, char> _key;
    };
}

#endif /* !TEXTINPUT_HPP_ */
