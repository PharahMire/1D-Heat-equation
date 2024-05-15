#include "CranckNicholson.h"

CranckNicholson::CranckNicholson(double dt, double dx, double L, double D, double T_sur, double Tin, double tmax) :
    dt(dt), dx(dx), L(L), D(D), T_sur(T_sur), Tin(Tin), tmax(tmax),
    nSpaceNodes(L / dx + 1),
    nTimeNodes(tmax / dt + 1),
    r(D* dt / (2 *(dx * dx)))
{

}

void CranckNicholson::compute() {
    vector<double> A(nSpaceNodes - 2);
    vector<double> B(nSpaceNodes - 2);
    vector<double> C(nSpaceNodes - 2);
    vector<double> X(nSpaceNodes - 2);
    vector<double> FirstIteration(nSpaceNodes - 2);
    vector<double> D(nSpaceNodes - 2);

    // Data will store the solution at 0.1, 0.2, 0.3, 0.4 and 0.5
    vector<vector<double>> data;

    // Vector initialization
    for (int i = 0; i < nSpaceNodes - 2; i++) {
        A[i] = -r;
        B[i] = 1 + 2 * r;
        C[i] = -r;
        FirstIteration[i] = Tin;
        X[i] = 0;
    }

    A[0] = 0;
    C[nSpaceNodes - 3] = 0;

    for (int t = 1; t < nTimeNodes; t++) {

        // Set the boundary condition
        D[0] = r * T_sur + (1 - 2 * r) * FirstIteration[0] + r * FirstIteration[1] + r * T_sur;
        D[nSpaceNodes - 3] = r * FirstIteration[nSpaceNodes - 4] + (1 - 2 * r) * FirstIteration[nSpaceNodes - 3] + r * T_sur + r * T_sur;

        // Fill the rest of D
        for (int i = 1; i < nSpaceNodes - 3; i++) {
            D[i] = r * FirstIteration[i - 1] + (1 - 2 * r) * FirstIteration[i] + r * FirstIteration[i + 1];
        }

        for (int k = 1; k < nSpaceNodes - 2; k++) {
            double m = A[k] / B[k - 1];
            B[k] = B[k] - m * C[k - 1];
            D[k] = D[k] - m * D[k - 1];
        }

        X[nSpaceNodes - 3] = D[nSpaceNodes - 3] / B[nSpaceNodes - 3];

        for (int k = nSpaceNodes - 4; k >= 0; k--) {
            X[k] = (D[k] - C[k] * X[k + 1]) / B[k];
        }
        FirstIteration = X;

        // This function is called at 5 time step no matter the number of time iteration
        if (t % ((nTimeNodes - 1) / 5) == 0) {

            vector<double> results(nSpaceNodes);
            results[0] = T_sur;
            results[nSpaceNodes - 1] = T_sur;

            for (int i = 0; i < X.size(); i++) results[i + 1] = X[i]; 

            data.push_back(results);
        }

        for (int i = 0; i < nSpaceNodes - 2; i++) {
            if (t != nTimeNodes - 1) {
                X[i] = 0;  // Reset X and D
                D[i] = 0;
            }
            B[i] = 2 * r + 1; // Reset B
        }
        
    }
    print(data, "Cranck-Nicholson.csv", dx);
    
    
}