#include "Ant.hpp"
using namespace std;

Ant::Ant() {
    is_visited = new bool[n];
}

Ant::~Ant() {
    delete[] is_visited;
}

void Ant::update(Road** matrix) {
    clear();
    for(int i = 0; i < n-1; i++) {
        actual_city = select_next_city(matrix);
        is_visited[actual_city] = true;
        solution.push_back(actual_city);
    }
    solution_cost = calculate_solution_cost(matrix);
}

int Ant::select_next_city(Road** matrix) {
    vector <double> probability;
    vector <double> candidate;
    double temp,sum = 0;
    for(int i = 0; i < n; i++) {
        if(!is_visited[i]) {
            candidate.push_back(i);
            temp = pow(matrix[actual_city][i].pheromone,pheromone_influence) * pow(1/matrix[actual_city][i].length,length_influence);
            sum += temp;
            probability.push_back(temp);
        }
    }

    for(int i = 0; i < probability.size(); i++)
        probability[i] /= sum;

    temp = 0;
    double random = (double)rand()/RAND_MAX;
    for(int i = 0; i < probability.size(); i++){
        temp += probability[i];
        if(random <= temp)
            return candidate[i];
    }
    return candidate[candidate.size()-1];
}

double Ant::calculate_solution_cost(Road** matrix) {
    double result = 0;
    int j;
    for(int i = 0; i < n; i++) {
        j = (i+1) % n;
        result += matrix[solution[i]][solution[j]].length;
    }
    return result;
}

void Ant::clear() {
    actual_city = rand() % n;
    for(int i = 0; i < n; i++)
        is_visited[i] = false;
    solution.clear();
    is_visited[actual_city] = true;
    solution.push_back(actual_city);
}
