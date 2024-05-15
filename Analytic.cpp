#include "Analytic.h"

Analytic::Analytic(double dx, double L, double D, double T_sur, double Tin) :
    dx(dx), L(L), D(D), T_sur(T_sur), Tin(Tin),
    nSpaceNodes(L / dx + 1)
{

}

void Analytic::compute() {
    const double PI = 4 * atan(1);
    int nPoints = L / dx + 1;

    vector<vector<double>> data;

    // compute analytic solution for t=0.1, 0.2, 0.3, 0.4 and 0.5
    for (int t = 1; t < 6; t++) {
        vector<double> results(nSpaceNodes);
        for (int i = 0; i < nPoints; i++) {
            double sum = 0;
            // 50 is the number above which the sum terms are negligible
            for (int j = 1; j < 51; j++) {
                sum += exp(-D * pow(j * PI / L, 2) * t * 0.1) * ((1 - pow(-1, j)) / (j * PI)) * sin(j * PI * i * dx / L);

            }
            results[i] = T_sur + 2 * (Tin - T_sur) * sum;
        }
        data.push_back(results);
    }
    print(data, "Analytic.csv", dx);
    
}