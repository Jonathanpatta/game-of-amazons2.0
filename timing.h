#pragma once
#include<iostream>
#include<chrono>


class Timer
{
    private:
    std::chrono::time_point<std::chrono::high_resolution_clock> starttime,endtime;
    public:
        Timer()
        {
            starttime = std::chrono::high_resolution_clock::now();
        }
        ~Timer()
        {
            stop();
        }
        void stop()
        {
            endtime = std::chrono::high_resolution_clock::now();
            auto start = std::chrono::time_point_cast<std::chrono::microseconds>(starttime).time_since_epoch().count();
            auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endtime).time_since_epoch().count();
            auto duration = end-start;
            std::cout<<duration<<" ";
        }
    
};