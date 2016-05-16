#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <ctime>

class BenchmarkClass
{
    public:
        int timer[10];
        int current_timer;
        time_t start_time;
        void ClearTimers()
        {
            for(int i=0; i<10; ++i) {
                timer[i]=0;
            }
        }
        void StartTimer(int index)
        {
            if(current_timer >= 0 && current_timer < 10) {
                timer[current_timer] += clock() - start_time;
            }
            current_timer = index;
            start_time = clock();
        }
        
        BenchmarkClass()
            :   current_timer(-1) {
                ClearTimers();
        }
};

#endif
