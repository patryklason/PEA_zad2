//
// Created by patry on 20.12.2022.
//

#include "TimeCounter.h"

void TimeCounter::start() {
    startTime = chrono::system_clock::now();
}

void TimeCounter::stop() {
    endTime = chrono::system_clock::now();
}

long long int TimeCounter::elapsedSeconds() {
    return chrono::duration_cast<chrono::seconds>(chrono::system_clock::now() - startTime).count();
}

long long int TimeCounter::elapsedMiliSeconds() {
    return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - startTime).count();
}
