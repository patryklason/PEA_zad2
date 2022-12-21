//
// Created by patry on 19.12.2022.
//

#include <iostream>
#include <limits>
#include <iomanip>
#include <cmath>
#include "Graph.h"
#include "TimeCounter.h"
using namespace std;
/**
 * Wczytuje graf z pliku do programu
 *
 * @param filename - sciezka do pliku (nazwa pliku)
 *
 * @return
 *          true - plik otwarty prawidlowo
 *          false - blad otwarcia pliku
 */
bool Graph::readGraphFromFile(string filename) {
    fstream file(filename, ios_base::in);
    if(!file.is_open())
        return false;
    string line;
    int x;
    // pominiecie 3 pierwszych linii
    for (int i = 0; i < 3; ++i) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // pobranie linii z liczba wierzcholkow
    getline(file, line);
    // wyciecie "DIMENSION: " tak aby zostala sama liczba
    line = line.substr(11, line.length() - 11);
    // konwersja ze strina do inta
    x = stoi(line);
    this->size = x;

    // pominiecie 3 kolejnych linii
    for (int i = 0; i < 3; ++i) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // zarezerwowanie przestrzeni w vectorze
    this->matrix.resize(size);
    for (int i = 0; i < this->size; i++) {
        this->matrix[i].resize(size);
    }

    // wczytanie po kolei liczb do macierzy
    for (int i = 0; i < this->size; ++i) {
        for (int j = 0; j < this->size; ++j) {
            file >> x;
            this->matrix[i][j] = x;
        }
    }

    // zamiana kosztow miast do samych siebie na wartosc -1
    for (int i = 0; i < this->size; ++i) {
        for (int j = 0; j < this->size; ++j) {
            if(i == j)
                this->matrix[i][j] = -1;
        }
    }

    return true;
}

/**
 * Przeprowadza algorytm Symulowanego Wyzarzania
 */
void Graph::simulatedAnnealing() {
    TimeCounter timeCounter;
    srand(time(NULL));
    timeCounter.start();

    // czas odnalezienia rozwiazania
    int foundTime = 0;

    // na poczatku wykonaj algorytm zachlanny
    minCost = SA_greedyAlgorithm();

    // powtarzaj dopoki nie przekroczy czasu lub temperatura spadnie ponizej wartosci minimalnej
    while (timeCounter.elapsedSeconds() < SA_stop && SA_temperature > SA_minTemperature) {
        // przechowuje koszt najnizszej lokalnie sciezki
        int localMin = INT_MAX;
        // przechowuje lokalna sciezke
        vector<int> localPath;

        int i = 0;
        do {
            localPath = minPath;

            // losujemy indeks wierzcholka ktory bedziemy wstawiac
            int indexI = rand() % (size - 1) + 1;

            // losujemy indeks wierzcholka w miejsce ktorego bedziemy wstawiac
            int indexJ = rand() % (size - 1) + 1;

            // jezeli indeksy sa takie same, wylosuj nowy indeks w miejsce ktorego bedziemy wstawiac
            while (indexI == indexJ)
                indexJ = rand() % (size - 1) + 1;

            // wstaw indexI w miejsce indexJ
            insert(indexI, indexJ, localPath);

            // oblicz nowy koszt po wstawieniu
            localMin = calculateCost(localPath);

            i++;
            // wykonaj petle 100 razy chyba ze znaleziona zostanie krotsza sciezka
        } while (minCost < localMin && i < 100);

        // jezeli (lokalne rozwiazanie jest lepsze niz dotychczasowe) lub (wieksze ale spelniono warunek prawdopodobienstwa),
        //      to przypisz najlepsze_rozwiazanie <= lokalne rozwiazanie
        if (localMin < minCost || probabilityCondition(localMin)) {
            minCost = localMin;
            minPath = localPath;
            foundTime = timeCounter.elapsedSeconds();
        }
        // zmien temperature, zgodnie ze wzorem T(i + 1) = a * T(i)
        SA_temperature *= SA_a;
    }

    cout << "Besto found in [s]: " << foundTime << endl;
    cout << "Total time [s]: " << timeCounter.elapsedSeconds() << endl << setprecision(20) << fixed << SA_temperature << endl;
}

/**
 * Oblicza koszt na podstawie sciezki
 */
int Graph::calculateCost(vector<int> &path) {
    int cost = 0;
    int end;
    for (int i = 1; i < size; ++i) {
        cost += matrix[path[i - 1]][path[i]];
        end = i;
    }
    cost += matrix[path[end]][path[firstIndex]];
    return cost;
}

/**
 * Algorytm zachlanny - potrzebny do wykonania pierwszej iteracji
 *
 * @return najmniejszy uzyskany koszt po przejsciu
 */
int Graph::SA_greedyAlgorithm() {
    // wyczysc wynik po porzednim wyknaniu
    minPath.clear();
    //minPath.resize(size);

    // poczatkowo ustaw wierzcholki w sciezce po kolei
    for (int i = 0; i < size; ++i) {
        minPath.push_back(i);
    }

    // ilosc iteracji dla wszystkich wierzcholkow poza ostatnim, z ktorego idziemy do [0]
    for (int i = 0; i < size - 1; ++i) {
        // lokalny najmniejszy koszt
        int localMin = INT_MAX;
        // indeks wyszukanego miasta o najmniejszym koszcie dojscia z miasta [i]
        int nearestIndex = i + 1;

        // ilosc iteracji dla liczby pozostalych wierzcholkow
        for (int j = i + 1; j < size; ++j) {
            // jesli koszt z path[i] do path[j] jest < lokalne minimum
            if (matrix[minPath[i]][minPath[j]] < localMin) {
                // indeks sasiada o najmniejszym koszcie, ktorego jeszcze nie rozpatrywalismy
                nearestIndex = j;
                // koszt dojscia do najblizszego sasiada
                localMin = matrix[minPath[i]][minPath[j]];
            }
        }

        // podmien path[i+1] z path[nearestIndex]
        int x = minPath[i + 1];
        minPath[i + 1] = minPath[nearestIndex];
        minPath[nearestIndex] = x;
    }

    return calculateCost(minPath);
}

/**
 * Wyswietla reprezentacje macierzy w oknie konsoli
 */
void Graph::printMatrix() {
    for(int i = 0; i < this->size; i++){
        for(int j = 0; j < this->size; j++){
            cout << setw(3) << this->matrix[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * Wykonuje operacja insert(i, j), a wiec usuwa i ze sciezki i przenosi ja w miejsce j (j jest o miejsce dalej)
 *
 * @param toBeInsetedIndex - indeks, z ktorego usuniemy wartosc
 * @param whereToInsertIndex - indeks, w ktory wkleimy usunieta wartosc
 * @param path - sciezka, na ktorej dzialamy
 */
void Graph::insert(int toBeInsetedIndex, int whereToInsertIndex, vector<int> &path) {

    int node = path[toBeInsetedIndex];
    path.erase(path.begin() + toBeInsetedIndex);
    path.insert(path.begin() + whereToInsertIndex, node);
}
/**
 * Warunek prawdopodobienstwa przyjecia gorszego rozwiazania
 *
 * jesli p [0,1) < e^((g(y) - g(x)) / T) -> akceptujemy gorsze rozwiazanie
 * gdzie
 *      p jest generowane losowo [0, 1)
 *      g(x) - najkrotsza sciezka dotychczas
 *      g(y) - lokalny koszt sciezki
 *
 * @param localMin - rozpatrywane lokalne minimum
 * @return
 *          true - gorsze rozwiazanie zostalo zaakceptowane
 *          false - gorsze rozwiazanie NIE zostalo zaakceptowane
 */
bool Graph::probabilityCondition(int localMin) {
    return (localMin > minCost && exp((double(minCost - localMin) / SA_temperature)) > (double(rand()) / (double(RAND_MAX) + 1.0)));
}
