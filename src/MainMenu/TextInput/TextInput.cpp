/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** TextInput
*/

#include "TextInput.hpp"

using namespace arcade;

const std::map<IDisplayModule::KeyList, char> TextInput::_key = {
    {IDisplayModule::KeyList::KEY_A, 'A'},
    {IDisplayModule::KeyList::KEY_B, 'B'},
    {IDisplayModule::KeyList::KEY_C, 'C'},
    {IDisplayModule::KeyList::KEY_D, 'D'},
    {IDisplayModule::KeyList::KEY_E, 'E'},
    {IDisplayModule::KeyList::KEY_F, 'F'},
    {IDisplayModule::KeyList::KEY_G, 'G'},
    {IDisplayModule::KeyList::KEY_H, 'H'},
    {IDisplayModule::KeyList::KEY_I, 'I'},
    {IDisplayModule::KeyList::KEY_J, 'J'},
    {IDisplayModule::KeyList::KEY_K, 'K'},
    {IDisplayModule::KeyList::KEY_L, 'L'},
    {IDisplayModule::KeyList::KEY_M, 'M'},
    {IDisplayModule::KeyList::KEY_N, 'N'},
    {IDisplayModule::KeyList::KEY_O, 'O'},
    {IDisplayModule::KeyList::KEY_P, 'P'},
    {IDisplayModule::KeyList::KEY_Q, 'Q'},
    {IDisplayModule::KeyList::KEY_R, 'R'},
    {IDisplayModule::KeyList::KEY_S, 'S'},
    {IDisplayModule::KeyList::KEY_T, 'T'},
    {IDisplayModule::KeyList::KEY_U, 'U'},
    {IDisplayModule::KeyList::KEY_V, 'V'},
    {IDisplayModule::KeyList::KEY_W, 'W'},
    {IDisplayModule::KeyList::KEY_X, 'X'},
    {IDisplayModule::KeyList::KEY_Y, 'Y'},
    {IDisplayModule::KeyList::KEY_Z, 'Z'},
    {IDisplayModule::KeyList::KEY_1, '1'},
    {IDisplayModule::KeyList::KEY_2, '2'},
    {IDisplayModule::KeyList::KEY_3, '3'},
    {IDisplayModule::KeyList::KEY_4, '4'},
    {IDisplayModule::KeyList::KEY_5, '5'},
    {IDisplayModule::KeyList::KEY_6, '6'},
    {IDisplayModule::KeyList::KEY_7, '7'},
    {IDisplayModule::KeyList::KEY_8, '8'},
    {IDisplayModule::KeyList::KEY_9, '9'},
    {IDisplayModule::KeyList::KEY_0, '0'},
};

TextInput::TextInput(const std::string input) :
    _input(std::string(input))
{
}

TextInput::~TextInput()
{
}

void TextInput::refresh(IDisplayModule &display)
{
    for (auto const &key : _key) {
        if (display.isKeyPress(key.first)) {
            _input.push_back(key.second);
        }
    }
    if (display.isKeyPress(IDisplayModule::KeyList::BACK_SPACE)) {
        if (!_input.empty()) {
            _input.pop_back();
        }
    }
}

std::string TextInput::getInputText() const
{
    return _input;
}