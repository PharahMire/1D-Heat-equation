#ifndef RICHARDSON_H
#define RICHARDSON_H

#include "Method.h"

class Richardson : public Method {
public:
    Richardson(double dt, double dx, double L, double D, double T_sur, double Tin, double tmax);
    void compute() override;
private:
    double dt, dx, L, D, T_sur, Tin, tmax, r;
    int nSpaceNodes, nTimeNodes;
};

#endif
