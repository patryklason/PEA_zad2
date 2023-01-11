//
// Created by patry on 19.12.2022.
//
#include <string>
#include <fstream>
#include <vector>

#ifndef PEA_ZAD2_GRAPH_H
#define PEA_ZAD2_GRAPH_H

using namespace std;

/**
 * Wczytuje graf z pliku i przeprowadza na nim algorytmy
 *
 * --- Zmienne ogolne ---
 *
 * @param size - ilosc wierzcholkow
 * @param matrix - reprezentacja grafu
 * @param firstIndex - indeks wierzcholka poczatkowego
 * @param minCost - minimalny koszt uzyskany przez algorytm
 * @param minPath - najkrotsza sciezka uzyskana przez algorytm
 *
 * --- Zmienne dla Symulowanego Wyzarzania ---
 *
 * @param SA_stop - kryterium stopu dla SW
 * @param SA_temperature - wartosc temperatury dla SW
 * @param SA_minTemperature - minimalna wartosc temperatury dla SW
 * @param SA_a - wspolczynnik schladzania dla SW
 */
class Graph {
public:
    int size;
    int minCost;
    vector<int> minPath;
    int globalMinCost;
    vector<int> globalMinPath;

    long long int SA_stop;
    double SA_temperature;
    double SA_a;


    Graph() {
        this->globalMinCost = INT_MAX;
        this->size = -1;
        this->firstIndex = 0;
        this->SA_stop = 0;
        this->SA_temperature = 500;
        this->SA_minTemperature = 0.000001;
        this->SA_a = 0.99;
        minCost = -1;
    }

    bool readGraphFromFile(string filename);
    void simulatedAnnealing();
    void printMatrix();
    long long int read_QPC();
//private:

    vector<vector<int>> matrix;
    int firstIndex;




    double SA_minTemperature;


    int calculateCost(vector<int> &path);
    int SA_greedyAlgorithm();
    void insert(int toBeInsetedIndex, int whereToInsertIndex, vector<int> &path);
    bool probabilityCondition(int localMin);
};


#endif //PEA_ZAD2_GRAPH_H
