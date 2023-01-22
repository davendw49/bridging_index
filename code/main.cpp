#include "calculate.h"
#include "dateConverse.h"
#include "getIDbyNum.h"

using namespace std;

int main()
{
    cout<<"[MAIN PROCESSING: ] Starting conversation ... "<<endl;
    converse();
    cout << "[MAIN PROCESSING: ] Starting calculation ... " << endl;
    Calculate calculate;
    calculate.exe();
    cout << "[MAIN PROCESSING: ] Starting IDs recovery ... " << endl;
    getIDbyNum();
}
