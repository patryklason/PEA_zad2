//
// Created by patry on 20.12.2022.
//
#include "chrono"

#ifndef PEA_ZAD2_TIMECOUNTER_H
#define PEA_ZAD2_TIMECOUNTER_H

using namespace std;

class TimeCounter {
public:
    chrono::system_clock::time_point startTime;
    chrono::system_clock::time_point endTime;

    void start();
    void stop();
    long long int elapsedSeconds();
    long long int elapsedMiliSeconds();
};


#endif //PEA_ZAD2_TIMECOUNTER_H
