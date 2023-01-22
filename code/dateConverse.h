/*********************************************
 * date_converse illustration
 *
 * IDs transformation
 *
 * input: node 1, node 2, edge weight, edge properties
 * output: converse:
 *        first line: number of nodes
 *        rest line: new ID of node 1, new ID of node 2, edge weight, edge properties
 *        compare: mapping file
 *********************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sys/stat.h>
#include "getFileName.h"

using namespace std;

// node struct in hash map
struct node3
{
    long num;
    node3 *next[37];

    node3(long n = 0)
    {
        num = n;
        for (auto &i : next)
            i = nullptr;
    }
};

int char2num(char c);

bool exist(node3 *(&point)[37], string p1);

int idx(node3 *(&point)[37], string p1);

void add(node3 *(&point)[37], string p1, int num);

void converse();
