/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Timer.cpp.cc
*/

#include "Timer.hpp"

#include <iostream>

static const size_t SECOND_TO_MILLI = 1000;

Timer::Timer(clock_t period) : _time(clock()), _period(period)
{
}


Timer::Timer() : _time(0), _period(0)
{
}

bool Timer::shouldRefresh()
{
    if ((((double) (clock() - _time) / CLOCKS_PER_SEC) * SECOND_TO_MILLI)
        >= _period) {
        _time = clock();
        return true;
    }
    return false;
}

clock_t Timer::getPeriod() const
{
    return _period;
}

void Timer::setPeriod(clock_t period)
{
    _period = period;
}

void Timer::setTimeout(clock_t duration)
{
    _period = duration;
    _time = clock();
}

bool Timer::isTimeout()
{
    if (_period != 0
        && (((double) (clock() - _time) / CLOCKS_PER_SEC) * SECOND_TO_MILLI)
            >= _period) {
        _period = 0;
        return true;
    }
    return false;
}
