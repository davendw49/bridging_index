#include "dateConverse.h"

// transfer string in to IDs
int char2num(char c)
{
    // char2num change here based on the alphabet in original IDs
    // Currently, support lower only and capital only
    // 1.if(c2n > 10) c2n = c - 'A' + 11;
    // 2.if(c2n > 10) c2n = c - 'a' + 11;
    // e.g. in our case use 1. for country, and the rest 2.
    int c2n = c - '0';
    // for '.'
    if (c2n < 0)
        c2n = 10;
    // for 'a-z|A-Z'
    if (c2n > 10)
        c2n = c - 'a' + 11;
    return c2n;
}

// Query the existency of p1 in hash map
bool exist(node3 *(&point)[37], string p1)
{
    // ID exist
    if (p1.empty())
        return true;

    int c2n = char2num(p1[0]);
    // ID not exist
    if (point[c2n] == NULL)
        return false;
    // continue query
    p1.erase(p1.begin());
    return exist(point[c2n]->next, p1);
}

// return new ID from original ID
int idx(node3 *(&point)[37], string p1)
{
    int c2n = char2num(p1[0]);

    if (p1.size() == 1)
        return point[c2n]->num;
    p1.erase(p1.begin());
    return idx(point[c2n]->next, p1);
}

// add to hash map
void add(node3 *(&point)[37], string p1, int num)
{
    int c2n = char2num(p1[0]);

    if (p1.size() == 1)
    {
        point[c2n] = new node3(num);
        return;
    }

    if (point[c2n] == nullptr)
        point[c2n] = new node3;
    p1.erase(p1.begin());
    add(point[c2n]->next, p1, num);
}

// free memory
void clear(node3 *point)
{
    if (point == nullptr)
        return;
    for (auto &i : point->next)
        if (i != nullptr)
            clear(i);
    delete point;
}

void converse()
{
    //---------data file folder------------
    string type = "/sample";
    //-------------------------------------

    // input all the files in folder 'type'
    getFileName(type);
    vector<string> fileName;
    ifstream inFileName("filename.txt");
    string name;
    while (inFileName >> name)
        fileName.push_back(name);
    inFileName.close();

    // mkdir converse & compare
    string path = getPath(); // get current path
    string pathCompare = path + type + "_compare";
    string pathConverse = path + type + "_converse";
    mkdir(pathCompare.c_str(), 0755);
    mkdir(pathConverse.c_str(), 0755);

    cout << "[CONVERSATION PROCESSING: ] finished: " << endl;
    for (auto i : fileName)
    {
        // create outstream
        string time(i, i.size() - 19, 19);
        string marker = time.substr(0, 10);
        cout << marker << ", ";
        string outConverse = pathConverse + type + "_converse_" + time;
        string outCompare = pathCompare + type + "_compare_" + time;
        ifstream in(i);
        ofstream out1(outConverse);
        ofstream out2(outCompare);

        string point1, point2;
        int weight, nation, discipline, institute, count = 0;
        vector<int> res;
        node3 *point[37];

        // init hash map
        for (auto &j : point)
            j = nullptr;

        while (in >> point1)
        {
            in >> point2 >> weight >> institute >> discipline >> nation;

            // cp string p1, p2
            string p1(point1, 0);
            string p2(point2, 0);

            // if not exist then create it
            if (!exist(point, p1))
            {
                add(point, p1, ++count);
                out2 << count << " " << point1 << "\n";
            }
            if (!exist(point, p2))
            {
                add(point, p2, ++count);
                out2 << count << " " << point2 << "\n";
            }

            res.push_back(idx(point, p1));
            res.push_back(idx(point, p2));
            res.push_back(weight);
            res.push_back(institute);
            res.push_back(discipline);
            res.push_back(nation);
        }
        res.push_back(count);

        // save the result using the outstream
        out1 << res[res.size() - 1] << "\n";
        for (int j = 0; j < (res.size() - 1) / 6; j++)
            out1 << res[6 * j] << " " << res[6 * j + 1] << " " << res[6 * j + 2] << " " << res[6 * j + 3] << " "
                 << res[6 * j + 4] << " " << res[6 * j + 5] << "\n";

        // release memory
        for (auto j : point)
            clear(j);

        in.close();
        out1.close();
        out2.close();
    }
    cout << endl;
}