#include "DufortFrankel.h"
#include "Richardson.h"
#include "Laasonen.h"
#include "CranckNicholson.h"
#include "Analytic.h"
using namespace std;

int main() {
    const double dt = 0.01;
    const double dx = 0.05;
    const double L = 31.0;
    const double D = 93.0;
    const double T_sur = 149;
    const double Tin = 38;
    const double tmax = 0.5;
    clock_t start, end;

    DufortFrankel df(dt, dx, L, D, T_sur, Tin, tmax);
    df.compute();

    Richardson richardson(dt, dx, L, D, T_sur, Tin, tmax);
    richardson.compute();

    Laasonen laasonen(dt, dx, L, D, T_sur, Tin, tmax);
    start = clock();
    laasonen.compute();
    end = clock();
    cout << "Compute time for dt = 0.01 is " << end - start << "ms\n";

    Laasonen laasonen0025(0.025, dx, L, D, T_sur, Tin, tmax);
    start = clock();
    laasonen0025.compute();
    end = clock();
    cout << "Compute time for dt = 0.025 is " << end - start << "ms\n";

    Laasonen laasonen005(0.05, dx, L, D, T_sur, Tin, tmax);
    start = clock();
    laasonen005.compute();
    end = clock();
    cout << "Compute time for dt = 0.05 is " << end - start << "ms\n";

    Laasonen laasonen01(0.1, dx, L, D, T_sur, Tin, tmax);
    start = clock();
    laasonen01.compute();
    end = clock();
    cout << "Compute time for dt = 0.1 is " << end - start << "ms\n";

    Analytic analytic(dx, L, D, T_sur, Tin);
    analytic.compute();

    CranckNicholson cn(dt, dx, L, D, T_sur, Tin, tmax);
    cn.compute();
  
    return 0;
}