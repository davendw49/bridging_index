#include "calculate.h"

Calculate::Calculate()
{
    pi = pa = na = p = nullptr;
    h1 = h2 = 0;
    Fe = nullptr;
    BI = PR = nullptr;
}

void Calculate::exe()
{
    //---------data file folder------------
    string type = "/sample";
    //-------------------------------------

    // read file from _converse
    string converseFile = type + "_converse";
    getFileName(converseFile);
    vector<string> fileName;
    ifstream inFileName("filename.txt");
    string name;
    while (inFileName >> name)
        fileName.push_back(name);
    inFileName.close();

    // default only bi & ricci
    // mkdir bi & ricci
    string path = getPath();
    string pathBI = path + type + "_bi";
    string pathPR = path + type + "_ricci";
    mkdir(pathBI.c_str(), 0755);
    mkdir(pathPR.c_str(), 0755);

    cout << "[CALCULATION PROCESSING: ] finished: " << endl;
    // calculate bi & ricci
    for (const auto &i : fileName)
    {
        string infile_graph = i;
        string time(i, i.size() - 19, 19);
        string marker = time.substr(0, 10);
        // cout<<marker<<", ";
        printf("%s\n", marker.c_str());
        string outfile_BI = pathBI + type + "_bi_" + time;
        string outfile_ricci = pathPR + type + "_ricci_" + time;

        map.exe(infile_graph);

        calPi();    // calculate PI(i)
        calPa();    // calculate PA(i)
        calNa();    // calculate NA(i)
        calH1();    // calculate H1
        calH2();    // calculate H2
        calP();     // calculate P(i)
        calFe();    // calculate Fe
        calBI();    // calculate BI
        calRicci(); // calculate ricci

        saveBI(outfile_BI);
        saveRicci(outfile_ricci);
        clear();
    }
    cout << endl;
}

void Calculate::calPi()
{
    pi = new double[map.point];

    for (int i = 0; i < map.point; i++)
        pi[i] = 3 / (4 * (1 + exp(-sqrt(map.iter[i]))));
}

void Calculate::calPa()
{
    pa = new double[map.point];

    for (int i = 0; i < map.point; i++)
    {
        double sumNeiPi = 0;
        for (node *j = map.initMap[i].next; j != nullptr; j = j->next)
            sumNeiPi += pi[j->point];
        pa[i] = map.ks[i] + sumNeiPi;
    }
}

void Calculate::calNa()
{
    na = new double[map.point];

    double *sumDeg = new double[map.point];
    for (int i = 0; i < map.point; i++)
    { // get neighbour and sum up the degree
        double sumNeiDeg = 0;
        for (node *j = map.initMap[i].next; j != nullptr; j = j->next)
            sumNeiDeg += map.deg[j->point];
        sumDeg[i] = sumNeiDeg;
    }
    for (int i = 0; i < map.point; i++)
    { // get NA
        double curNa = 0;
        for (node *j = map.initMap[i].next; j != nullptr; j = j->next)
            curNa += sumDeg[j->point];
        na[i] = curNa - map.deg[i] * (map.deg[i] - 1); // minor the repeat part
    }

    delete[] sumDeg;
}

void Calculate::calH1()
{
    double sum_r_lnr = 0, sum_a = 0;
    for (int i = 0; i < map.point; i++)
        sum_a += pa[i];

    for (int i = 0; i < map.point; i++)
        sum_r_lnr += pa[i] / sum_a * log(pa[i] / sum_a);
    h1 = -1 / log(map.point) * sum_r_lnr;
}

void Calculate::calH2()
{
    double sum_r_lnr = 0, sum_a = 0;
    for (int i = 0; i < map.point; i++)
        sum_a += na[i];

    for (int i = 0; i < map.point; i++)
        sum_r_lnr += na[i] / sum_a * log(na[i] / sum_a);
    h2 = -1 / log(map.point) * sum_r_lnr;
}

void Calculate::calP()
{
    p = new double[map.point];

    double w1, w2;
    w1 = (1 - h1) / (2 - h1 - h2);
    w2 = (1 - h2) / (2 - h1 - h2);
    for (int i = 0; i < map.point; i++)
        p[i] = w1 * pa[i] + w2 * na[i];
}

void Calculate::calFe()
{
    Fe = new node2[map.point];

    for (int i = 0; i < map.point; i++)
    {
        node2 *tmp = &Fe[i];
        for (node *j = map.initMap[i].next; j != nullptr; j = j->next)
        {
            double tmpFe;
            tmpFe = -(p[i] * (1 - map.deg[i] * sqrt(j->edge)) +
                      p[j->point] * (1 - map.deg[j->point] * sqrt(j->edge)));
            tmp->next = new node2(j->point, tmpFe, j->country, j->discipline, j->institute, tmp->next);
        }
    }
}

void Calculate::calBI()
{
    BI = new double[map.point];

    for (int i = 0; i < map.point; i++)
    {
        double sum = 0;
        for (node2 *j = Fe[i].next; j != nullptr; j = j->next)
        {
            sum += j->Fe * (j->country + j->discipline + j->institute + 1);
        }
        BI[i] = sum;
    }
}

void Calculate::calRicci()
{
    formanFe = new node2[map.point];
    ricci = new double[map.point];

    // calculate forman F(e)
    for (int i = 0; i < map.point; i++)
    {
        node2 *tmp = &formanFe[i];
        for (node *j = map.initMap[i].next; j != nullptr; j = j->next)
        {
            double tmpFe;
            tmpFe = 4 - map.deg[i] - map.deg[j->point];
            tmp->next = new node2(j->point, tmpFe, j->country, j->discipline, j->institute, tmp->next);
        }
    }

    // calculate forman ricci
    for (int i = 0; i < map.point; i++)
    {
        double sum = 0;
        for (node2 *j = formanFe[i].next; j != nullptr; j = j->next)
        {
            sum += j->Fe;
        }
        ricci[i] = sum;
    }
}

// calculate pagerank
void Calculate::calPR()
{
    PR = new double[map.point];

    // random init
    default_random_engine e;
    uniform_real_distribution<double> u(0, 1);
    e.seed(time(nullptr));
    for (int i = 0; i < map.point; i++)
        PR[i] = u(e);

    // iteration setup
    bool stop = false;
    while (!stop)
    {
        stop = true;
        for (int i = 0; i < map.point; i++)
        {
            double curPR = 0;
            for (node *j = map.initMap[i].next; j != nullptr; j = j->next)
                curPR += PR[j->point] / map.deg[j->point];
            // early stop
            curPR = curPR * 0.5 + 0.5 / map.point;
            if ((PR[i] - curPR) / PR[i] > 0.01 || (PR[i] - curPR) / PR[i] < -0.01)
                stop = false;
            PR[i] = curPR;
        }
    }
}

// save pi, pa, na, p
void Calculate::saveAll(const string &fileName) const
{
    ofstream out(fileName);

    for (int i = 0; i < map.point; i++)
        out << i + 1 << " " << pi[i] << " " << pa[i] << " " << na[i] << " " << p[i] << endl;

    out.close();
}

void Calculate::saveBI(const string &fileName) const
{
    ofstream out(fileName);

    for (int i = 0; i < map.point; i++)
        out << i + 1 << " " << BI[i] << endl;

    out.close();
}

// save degree
void Calculate::saveDeg(const string &fileName) const
{
    ofstream out(fileName);

    for (int i = 0; i < map.point; i++)
        out << i + 1 << " " << map.deg[i] << endl;

    out.close();
}

// pagerank
void Calculate::savePR(const string &fileName) const
{
    ofstream out(fileName);

    double sum = 0;
    for (int i = 0; i < map.point; i++)
        sum += PR[i];
    sum /= map.point;
    out << "average pagerank: " << sum << endl;

    for (int i = 0; i < map.point; i++)
        out << i + 1 << " " << PR[i] << endl;

    out.close();
}

void Calculate::saveRicci(const string &fileName) const
{
    ofstream out(fileName);

    for (int i = 0; i < map.point; i++)
        out << i + 1 << " " << ricci[i] << endl;

    out.close();
}

void Calculate::clear() const
{
    for (int i = 0; i < map.point; i++)
    {
        node2 *tmp = Fe[i].next;
        while (tmp != nullptr)
        {
            node2 *tmp2 = tmp->next;
            delete tmp;
            tmp = tmp2;
        }
    }
    delete[] Fe;

    for (int i = 0; i < map.point; i++)
    {
        node2 *tmp = formanFe[i].next;
        while (tmp != nullptr)
        {
            node2 *tmp2 = tmp->next;
            delete tmp;
            tmp = tmp2;
        }
    }
    delete[] formanFe;

    delete[] BI;
    delete[] PR;
    delete[] ricci;

    delete[] pi;
    delete[] pa;
    delete[] na;
    delete[] p;

    map.clear();
}