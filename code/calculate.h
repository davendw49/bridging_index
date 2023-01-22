/*********************************************
 * Calculate class
 *
 * data member
 * map : Map instance
 * pi : PI(i) position index
 * pa : PA(i) position attribute
 * na : NA(i) neighbour attribute
 * h1、h2 : H1、H2 (for calculating w1、w2)
 * p : P(i) node attribute
 * Fe : F(e)
 * BI : BI
 * PR : pagerank
 * formanFe : forman Fe
 * ricci : ricci-curvature
 *
 * 函数：
 * 1.exe ———— execute function
 * 2.cal + data_member ———— calculate related data
 * 3.save ———— save to file 
 * 4.clear ———— free memory
 *********************************************/

#ifndef MAIN_CPP_CALCULATE_H
#define MAIN_CPP_CALCULATE_H

#include "sys/stat.h"
#include "map.h"
#include "getFileName.h"

class Calculate
{
private:
    Map map;

    double *pi, *pa, *na, *p;
    double h1, h2;
    node2 *Fe, *formanFe;
    double *BI, *PR, *ricci;

public:
    Calculate();

    void exe();

    void calPi();

    void calPa();

    void calNa();

    void calH1();

    void calH2();

    void calP();

    void calFe();

    void calBI();

    void calRicci();

    void calPR();

    void saveAll(const string &fileName) const;

    void saveBI(const string &fileName) const;

    void saveDeg(const string &fileName) const;


    void savePR(const string &fileName) const;

    void saveRicci(const string &fileName) const;

    void clear() const;
};

#endif // MAIN_CPP_CALCULATE_H
