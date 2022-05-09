#ifndef ANT_HPP
#define ANT_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "Graph.hpp"

extern int n;
extern double pheromone_influence;
extern double length_influence;

class Ant {
private:
    int actual_city;
    bool* is_visited;
    int select_next_city(Road** matrix);
    double calculate_solution_cost(Road** matrix);
    void clear();
public:
    Ant();
    ~Ant();
    std::vector <int> solution;
    double solution_cost;
    void update(Road** matrix);
};
#endif
