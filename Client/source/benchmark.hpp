#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <ctime>
#include "global.hpp"

class BenchmarkClass
{
    public:
        double timer[10];
        int current_timer;
        sf::Time startTime;
        void clearTimers()
        {
            for(int i=0; i<10; ++i) {
                timer[i] = 0.0;
            }
        }
        void startTimer(int index)
        {
            if(current_timer >= 0 && current_timer < 10) {
                sf::Time time = globalClock.getElapsedTime();
                timer[current_timer] += (time.asMicroseconds() - startTime.asMicroseconds()) / 1000.0;
            }
            current_timer = index;
            startTime = globalClock.getElapsedTime();
        }

        BenchmarkClass()
            :   current_timer(-1) {
                clearTimers();
        }
};

#endif
