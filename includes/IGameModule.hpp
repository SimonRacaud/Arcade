/*
** EPITECH PROJECT, 2021
** OOP_arcade_Interface
** File description:
** IGameModule
*/

#ifndef IGAME_MODULE_HPP_
#define IGAME_MODULE_HPP_

#include "IDisplayModule.hpp"
#include <string>

namespace arcade
{
    class IDisplayModule;

    class IGameModule {
      public:
        virtual ~IGameModule(){};

        virtual void refresh() = 0;

        virtual void reset() = 0;

        virtual size_t getScore() const = 0;

        virtual void setUsername(std::string const &username) = 0;

        virtual const IDisplayModule &getDisplayModule() const = 0;
        virtual void setDisplayModule(const IDisplayModule &displayModule) = 0;
    };
} // namespace arcade

#endif /* !IGAMEMODULE_HPP_ */
