/*
** EPITECH PROJECT, 2021
** B-OOP-400-REN-4-1-arcade-aurelien.joncour
** File description:
** Timer.hpp.h
*/

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <ctime>

class Timer {
  private:
    clock_t _time;
    clock_t _period;

  public:
    Timer(clock_t period);
    Timer();
    virtual ~Timer() = default;

    bool shouldRefresh();

    void setTimeout(clock_t duration);
    bool isTimeout();

    clock_t getPeriod() const;
    void setPeriod(clock_t period);
};

#endif // TIMER_HPP_
