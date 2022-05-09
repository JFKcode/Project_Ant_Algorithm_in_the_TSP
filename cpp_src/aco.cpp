#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

#include "Graph.hpp"
#include "Ant.hpp"

using namespace std;

int n;

int ant_number;
int iteration_number;
double pheromone_evaporation;
double Q;
double pheromone_start_value;
double pheromone_influence;
double length_influence;

vector <int> best_solution;
double best_solution_cost = 0;

void generate_solutions(Graph* g, Ant* ant) {
    for(int i = 0; i < ant_number; i++) {
        ant[i].update(g->matrix);
    }
}

void compare_solution(Graph* g, Ant* ant) {
    if(best_solution.size() == 0) {
        best_solution = ant[0].solution;
        best_solution_cost = ant[0].solution_cost;
    }
    double cost;
    for(int i = 0; i < ant_number; i++) {
        cost = ant[i].solution_cost;
        if(cost < best_solution_cost) {
            best_solution_cost = cost;
            best_solution = ant[i].solution;
        }
    }
}

void pheromone_update(Graph* g, Ant* ant) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            g->matrix[i][j].pheromone = g->matrix[j][i].pheromone = (1 - pheromone_evaporation) * g->matrix[i][j].pheromone;
        }
    }
    int j;
    for(int k = 0; k < ant_number; k++) {
        for(int i = 0; i < ant[k].solution.size(); i++) {
            j = (i+1) % ant[k].solution.size();
            g->matrix[ant[k].solution[i]][ant[k].solution[j]].pheromone += Q / ant[k].solution_cost;
            g->matrix[ant[k].solution[j]][ant[k].solution[i]].pheromone += Q / ant[k].solution_cost;
        }
    }
}

int main() {
    srand( time( NULL ) );

    string temp;
    ifstream config("aco_config.txt");
    config >> temp >> ant_number;
    config >> temp >> iteration_number;
    config >> temp >> pheromone_start_value;
    config >> temp >> pheromone_evaporation;
    config >> temp >> pheromone_influence;
    config >> temp >> length_influence;
    config >> temp >> Q;
    config.close();

    cin >> n;
    City* cities = new City[n];
    for(int i = 0; i < n; i++)
        cin >> temp >> cities[i].x  >> cities[i].y;

    clock_t start = clock();
    Graph* g = new Graph(cities);
    Ant* ant = new Ant[ant_number];
    for(int i = 0; i < iteration_number; i++) {
        generate_solutions(g, ant);
        compare_solution(g, ant);
        pheromone_update(g, ant);
    }

    cout << "Czas: " << (clock() - start) / (double)CLOCKS_PER_SEC << endl;
    cout << "Wynik: " << (best_solution_cost * g->max_length) / 100.0 << endl;
    cout << "Rozwiazanie: ";
    for(auto x : best_solution)
        cout << x << ' ';
    cout << endl;

    delete g;
    delete[] cities;
    delete[] ant;
    return 0;
}
