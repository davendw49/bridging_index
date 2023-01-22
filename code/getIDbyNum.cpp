#include "getIDbyNum.h"

void getIDbyNum()
{
    //---------data file folder------------
    string type = "/sample";
    //-------------------------------------

    // read the file name
    string BIFile = type + "_bi";
    string ricciFile = type + "_ricci";
    string compareFile = type + "_compare";

    getFileName(BIFile);
    vector<string> fileName_BI;
    ifstream inFileName("filename.txt");
    string name;
    while (inFileName >> name)
        fileName_BI.push_back(name);
    inFileName.close();

    getFileName(ricciFile);
    vector<string> fileName_ricci;
    inFileName.open("filename.txt");
    while (inFileName >> name)
        fileName_ricci.push_back(name);
    inFileName.close();

    getFileName(compareFile);
    vector<string> fileName_compare;
    inFileName.open("filename.txt");
    while (inFileName >> name)
        fileName_compare.push_back(name);
    inFileName.close();

    // mkdir bi_result & ricci_result
    string path = getPath(); // get current path
    string path_bi = path + type + "_bi_result";
    string path_ricci = path + type + "_ricci_result";
    mkdir(path_bi.c_str(), 0755);
    mkdir(path_ricci.c_str(), 0755);

    for (int i = 0; i < fileName_BI.size(); i++)
    {
        string time(fileName_BI[i], fileName_BI[i].size() - 19, 19);
        string out_bi_name = path_bi + type + "_bi_" + time;
        string out_ricci_name = path_ricci + type + "_ricci_" + time;

        ifstream in_BI(fileName_BI[i]);
        ifstream in_ricci(fileName_ricci[i]);
        ifstream in_comapre(fileName_compare[i]);
        ofstream out_bi(out_bi_name);
        ofstream out_ricci(out_ricci_name);

        int num;
        string id;
        double res;
        vector<string> compare_table;

        // create mapping
        while (in_comapre >> num)
        {
            in_comapre >> id;
            compare_table.push_back(id);
        }

        // change back to original IDs
        while (in_BI >> num)
        {
            in_BI >> res;
            out_bi << compare_table[num - 1] << " " << res << "\n";
        }
        while (in_ricci >> num)
        {
            in_ricci >> res;
            out_ricci << compare_table[num - 1] << " " << res << "\n";
        }

        in_BI.close();
        in_ricci.close();
        in_comapre.close();
        out_bi.close();
        out_ricci.close();
    }
}