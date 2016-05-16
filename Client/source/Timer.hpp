#ifndef TIMER_HPP
#define TIMER_HPP

#include "global.hpp"

class Timer
{
    private:
        double expirationTime;

    public:
        inline void setDuration(double duration)
        {
            expirationTime = globalTime+duration;
        }

        bool hasPassed()
        {
            return globalTime >= expirationTime;
        }

        Timer()
            :   expirationTime(0.0)
        {
        }
};

#endif
