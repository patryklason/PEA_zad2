//
// Created by patry on 11.01.2023.
//

#include "TimeTest.h"

#include <ntdef.h>
#include <profileapi.h>
#include "iostream"
#include "iomanip"
#include "Graph.h"

using namespace std;

/**
 * Funkcja przeprowadza testy czasu wykonywania wybranego algorytmu
 * @param iterations - ilosc przeprowadzonych powtorzen
 * @param size - ilosc wierzcholkow
 * @param algorithm - 0: Brute Force, 1: Dynamic Programming
 */
void TimeTest::runTest(int iterations, int size, int algorithm) {
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    long long int totalTime = 0;

    Graph g;
    if(algorithm == 0) {
        for (int i = 0; i < iterations; ++i) {


            start = read_QPC();

            elapsed = read_QPC() - start;

            totalTime += elapsed;
        }
    }
    else if(algorithm == 1){

        for (int i = 0; i < iterations; ++i) {


            start = read_QPC();

            elapsed = read_QPC() - start;

            totalTime += elapsed;
        }
    }
    /*start = read_QPC();
     // kod ktorego czas wykonania mierzymy
    elapsed = read_QPC() - start;*/



    cout << "Avg Time [s] = " << fixed << setprecision(3) << ((float)totalTime / (float)iterations)/ (float)frequency << endl;
    cout << "Avg Time [ms] = " << setprecision(3) << (1000.0 * (float)totalTime / iterations) / (float)frequency << endl;
    cout << "Avg Time [us] = " << setprecision(3) << (1000000.0 * (float)totalTime / iterations) / (float)frequency << endl << endl;
}

long long int TimeTest::read_QPC() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}