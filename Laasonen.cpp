#include "Laasonen.h"

Laasonen::Laasonen(double dt, double dx, double L, double D, double T_sur, double Tin, double tmax) :
    dt(dt), dx(dx), L(L), D(D), T_sur(T_sur), Tin(Tin), tmax(tmax),
    nSpaceNodes(L / dx + 1),
    nTimeNodes(tmax / dt + 1),
    r(D* dt / (dx * dx))
{

}

void Laasonen::compute() {
    // Vector used in Thomas Algorithme
    vector<double> A(nSpaceNodes - 2);
    vector<double> B(nSpaceNodes - 2);
    vector<double> C(nSpaceNodes - 2);
    vector<double> X(nSpaceNodes - 2);
    vector<double> D(nSpaceNodes - 2);

    // Data will store the solution at 0.1, 0.2, 0.3, 0.4 and 0.5
    vector<vector<double>> data;

    // Vector initialization 
    for (int i = 0; i < nSpaceNodes - 2; i++) {
        A[i] = -r;
        B[i] = 2 * r + 1;
        C[i] = -r;
        D[i] = Tin;
        X[i] = 0;
    }

    A[0] = 0;
    C[nSpaceNodes - 3] = 0;
 
    for (int t = 1; t < nTimeNodes; t++) {
        // Add boundary condition to the first and last value in D
        D[0] = D[0] + r * T_sur;
        D[nSpaceNodes - 3] = D[nSpaceNodes - 3] + r * T_sur;

        // Compute Thomas algorithme for Laasonen
        for (int k = 1; k < nSpaceNodes - 2; k++) {
            double m = A[k] / B[k - 1];
            B[k] = B[k] - m * C[k - 1];
            D[k] = D[k] - m * D[k - 1];
        }

        X[nSpaceNodes - 3] = D[nSpaceNodes - 3] / B[nSpaceNodes - 3];



        for (int k = nSpaceNodes - 4; k >= 0; k--) {
            X[k] = (D[k] - C[k] * X[k + 1]) / B[k];
        }

        D = X;

        for (int i = 0; i < nSpaceNodes - 2; i++) {
            if (t != nTimeNodes - 1) {
                X[i] = 0; // Reset X
            }
            B[i] = 2 * r + 1; // Reset B
        }

        // This function is called at 5 time step no matter the number of time iteration
        if (t % ((nTimeNodes - 1)/5) == 0) {

            vector<double> results(nSpaceNodes);
            results[0] = T_sur;
            results[nSpaceNodes - 1] = T_sur;
            
            for (int i = 0; i < D.size(); i++) results[i + 1] = D[i];

            data.push_back(results);
        }
    }
    print(data, "Laasonen" + to_string(dt) + ".csv", dx);
}