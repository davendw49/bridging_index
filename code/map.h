/***********************************************************************
 * Map Class
 *
 * struct illustration
 *    node: nodes in adjacency
 *    node2: node with F(e) weight
 *
 * data member
 * point: number of nodes
 * initMap: weighted graph
 * ks : k-shell
 * iter: iter
 * deg: degree
 *
 * functions
 * 1.exe ———— main execute function
 * 2.creatMap_edge ———— edge input
 * 3.creatDeg ———— node degree
 * 4.creatKsAndIter ———— calculate ks & iter
 * 5.clear ———— release memory
 ***********************************************************************/

#ifndef CODE_MAP_H
#define CODE_MAP_H

#include <iostream>
#include <fstream>
#include <stack>
#include <cmath>
#include <random>
#include <ctime>

using namespace std;

struct node
{
    int point = 0;      // node
    int edge = 0;       // edge weight
    int country = 0;    // xor on country
    int discipline = 0; // xor on discipline
    int institute = 0;  // xor on institute
    node *next = nullptr;

    explicit node(int p = 0, int e = 0, int c = 0, int d = 0, int i = 0, node *n = nullptr)
    {
        point = p;
        edge = e;
        next = n;
        country = c;
        discipline = d;
        institute = i;
    }
};

struct node2
{
    int point = 0;
    double Fe = 0;
    int country = 0;
    int discipline = 0;
    int institute = 0;
    node2 *next = nullptr;

    explicit node2(int p = 0, double e = 0, int c = 0, int d = 0, int i = 0, node2 *n = nullptr)
    {
        point = p;
        Fe = e;
        next = n;
        country = c;
        discipline = d;
        institute = i;
    }
};

class Map
{
public:
    int point;
    node *initMap;
    int *ks, *iter, *deg;

public:
    Map();
    void exe(const string &g_data);

    void creatMap_edge(const string &g_data);
    void creatDeg();
    void creatKsAndIter();

    void clear() const;
};

#endif // CODE_MAP_H
