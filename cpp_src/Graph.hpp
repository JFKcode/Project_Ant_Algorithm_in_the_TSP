#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <math.h>
#include <vector>

extern int n;
extern double pheromone_start_value;
extern double pheromone_influence;
extern double length_influence;

struct City {
    double x;
    double y;
};

struct Road {
    double pheromone;
    double length;
};

class Graph {
public:
    double max_length;
    Road** matrix;
    Graph(City* cities);
    ~Graph();
    void normalize();
};
#endif
