#include <iostream>
#include "Graph.h"

void displayResults(Graph * g) {
    if(g->minCost == -1){
        cout << "Algorytm nie zostal wykonany!" << endl;
        return;
    }
    cout << "Minimalny koszt: " << g->minCost << endl;
    cout << "Minimalna sciezka: ";
    for (int i = 0; i < g->minPath.size(); ++i) {
        cout << g->minPath[i] << " -> ";
    }
    cout << "0" << endl;
}

void setCooling(Graph * g) {
    char choice;
    cout << endl << endl;
    cout << "Schematy schladzania:" << endl
    << "[0] Pozostaw wartosc" << endl
    << "[1] 0.99" << endl
    << "[2] 0.95" << endl
    << "[3] 0.85" << endl;
    cout << "Aktualna wartosc: " << g->SA_a << endl;
    cout << "Wybierz nowa wartosc: ";
    cin >> choice;

    switch (choice) {
        case '0': return;
        case '1': {g->SA_a = 0.99; break;}
        case '2': {g->SA_a = 0.95; break;}
        case '3': {g->SA_a = 0.85; break;}
        default: cout << "Blad wyboru!" << endl;
    }
}

void readFromFile(Graph * g) {
    string name;
    cout << endl << endl;
    cout << "Prosze podac nazwe pliku:";
    cin >> name;
    if(!g->readGraphFromFile(name))
        cout << endl << "Blad odczytu pliku!" << endl;
    else
        cout << endl << "Plik wczytany prawidlowo!" << endl;
}

void setStop(Graph * g) {
    long long int stop;
    cout << endl << endl;
    cout << "Prosze podac kryterium stopu [s]:";
    cin >> stop;
    g->SA_stop = stop;
}

void setTemperature(Graph * g) {
    double temp;
    cout << endl << endl;
    cout << "Prosze podac temperature:";
    cin >> temp;
    g->SA_temperature = temp;
}

bool displayMenu() {
    auto *g = new Graph();
    char choice;

    cout << "============== Menu Glowne ==============" << endl;
    cout << "[0] Wyjscie z programu" << endl;
    cout << "[1] Wczytaj dane z pliku" << endl;
    cout << "[2] Wprowadz kryterium stopu" << endl;
    cout << "[3] SW - Ustawienie wspolczynnika temperatury" << endl;
    cout << "[4] SW - schematy schladzania" << endl;
    cout << "[5] SW - uruchom algorytm Symulowanego Wyzarzania" << endl;
    cout << "[6] Wyswietl wynik" << endl;

    cout << endl << "Wybierz opcje: ";
    cin >> choice;
    cout << endl;

    switch (choice) {
        case '0': return false;
        case '1': {readFromFile(g); break;}
        case '2': {setStop(g); break;}
        case '3': {setTemperature(g); break;}
        case '4': {setCooling(g); break;}
        case '5': {g->simulatedAnnealing(); break;}
        case '6': {displayResults(g); break;}
        default: cout << "Blad wyboru!" << endl;
    }
    return true;
}

using namespace std;
int main() {
    while(displayMenu());
    /*auto g = new Graph();
    g->readGraphFromFile("../rbg403.atsp");
    cout << endl << g->size << endl;
    g->SA_a = 0.9;
    g->SA_stop = 6*60;
    g->SA_temperature = g->size*g->size;
    g->simulatedAnnealing();
    displayResults(g);
     */

    return 0;
}
