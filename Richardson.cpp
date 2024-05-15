#include "Richardson.h"

Richardson::Richardson(double dt, double dx, double L, double D, double T_sur, double Tin, double tmax) :
    dt(dt), dx(dx), L(L), D(D), T_sur(T_sur), Tin(Tin), tmax(tmax),
    nSpaceNodes(L / dx + 1),
    nTimeNodes(tmax / dt + 1),
    r(D* dt / (dx * dx)) {}

void Richardson::compute() {
    // Compute for initial condition at t0  
    vector<double> fp;

    fp.push_back(149);
    for (int i = 1; i < nSpaceNodes - 1; i++) {
        fp.push_back(38);
    }
    fp.push_back(149);

    // Compute for initial condition at t1 with Forward Center scheme
    vector<double> fp1(nSpaceNodes);
    for (int i = 1; i < nSpaceNodes - 1; i++) {
        fp1[i] = r * fp[i - 1] + (1 - 2 * r) * fp[i] + r * fp[i + 1];
    }
    fp1[0] = 149;
    fp1[nSpaceNodes - 1] = 149;

    // Vector that will store n + 1 values
    vector<double> fp2(nSpaceNodes);
    vector<vector<double>> data;

    // Compute Richardson algorithme method
    for (int j = 2; j < nTimeNodes; j++) {
        for (int i = 1; i < nSpaceNodes - 1; i++) {
            fp2[i] = fp[i] + r * (fp1[i + 1] - 2 * fp1[i] + fp1[i - 1]);
        }
        fp = fp1;

        fp2[0] = T_sur;
        fp2[nSpaceNodes - 1] = T_sur;
        fp1 = fp2;

        // Store in data values at 0.1, 0.2, 0.3, 0.4 and 0.5;
        if (j % 10 == 0) data.push_back(fp2);
    }

    print(data, "Richardson.csv", dx);
    return;
}