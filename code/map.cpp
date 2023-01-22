#include "map.h"

Map::Map()
{
    point = 0;
    initMap = nullptr;
    ks = iter = deg = nullptr;
}

void Map::exe(const string &g_data)
{
    creatMap_edge(g_data); // read data
    creatDeg();            // calculate degree
    creatKsAndIter();      // calculate k-shell & iter
}

// create graph
void Map::creatMap_edge(const string &g_data)
{
    ifstream in_g(g_data);
    in_g >> point;

    initMap = new node[point];

    int point1, point2, edge;
    string p1, p2;
    int country, discipline, institute;
    while (in_g >> point1)
    {
        country = discipline = institute = 0;
        in_g >> point2 >> edge >> institute >> discipline >> country;
        point1--;
        point2--;
        // cooperation lower bound = 5
        edge -= 4;
        initMap[point1].next = new node(point2, edge, country, discipline, institute, initMap[point1].next);
        initMap[point2].next = new node(point1, edge, country, discipline, institute, initMap[point2].next);
    }

    in_g.close();
}

// calculate degree
void Map::creatDeg()
{
    deg = new int[point];

    for (int i = 0; i < point; i++)
    {
        int curDeg = 0;
        for (node *j = initMap[i].next; j != nullptr; j = j->next)
            curDeg++;
        deg[i] = curDeg;
    }
}

// calculate ks and iter
void Map::creatKsAndIter()
{
    ks = new int[point];
    iter = new int[point];

    node *tmpMap = new node[point]; // tmp graph
    for (int i = 0; i < point; i++)
    {
        node *tmp = initMap[i].next;
        while (tmp != nullptr)
        {
            // tmp graph set the properties into 0
            tmpMap[i].next = new node(tmp->point, tmp->edge, 0, 0, 0, tmpMap[i].next);
            tmp = tmp->next;
        }
    }

    double *tmpDeg = new double[point]; // tmp nodes' degree
    for (int i = 0; i < point; i++)
        tmpDeg[i] = deg[i];

    int curKs = 1, curIter = 1, leftPoint = point;
    while (leftPoint > 0)
    {
        bool sym = false;
        stack<int> delPoint;
        for (int i = 0; i < point; i++)
        {
            if (tmpMap[i].point == -1)
                continue;
            if (tmpDeg[i] <= curKs)
            {
                delPoint.push(i);
                leftPoint--;
                ks[i] = curKs;
                iter[i] = curIter;
                sym = true;
            }
        }
        if (!sym)
            curKs++;
        else
            curIter++;

        while (!delPoint.empty())
        {
            int tmp = delPoint.top();
            for (node *m = tmpMap[tmp].next; m != nullptr; m = m->next)
            { 
                node *p = &tmpMap[m->point];
                while (p->next->point != tmp)
                    p = p->next;
                node *del = p->next;
                p->next = p->next->next;
                delete del;
                tmpDeg[m->point]--;
            }

            for (node *m = tmpMap[tmp].next; m != nullptr; m = m->next)
            { 
                node *p = m->next;
                delete m;
                m = p;
                if (m == nullptr)
                    break;
            }

            tmpMap[tmp].next = nullptr;
            tmpMap[tmp].point = -1;
            delPoint.pop();
        }
    }

    // release memory
    delete[] tmpDeg;
    for (int i = 0; i < point; i++)
    {
        node *tmp = tmpMap[i].next;
        while (tmp != nullptr)
        {
            node *tmp2 = tmp->next;
            delete tmp;
            tmp = tmp2;
        }
    }
    delete[] tmpMap;
}

void Map::clear() const
{
    for (int i = 0; i < point; i++)
    {
        node *tmp = initMap[i].next;
        while (tmp != nullptr)
        {
            node *tmp2 = tmp->next;
            delete tmp;
            tmp = tmp2;
        }
    }
    delete[] initMap;

    delete[] ks;
    delete[] iter;
    delete[] deg;
}