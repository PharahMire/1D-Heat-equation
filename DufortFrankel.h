#ifndef DUFORT_FRANKEL_H
#define DUFORT_FRANKEL_H

#include "Method.h"

class DufortFrankel : public Method {
public:
    DufortFrankel(double dt, double dx, double L, double D, double T_sur, double Tin, double tmax);
    void compute() override;
private:
    double dt, dx, L, D, T_sur, Tin, tmax, r;
    int nSpaceNodes, nTimeNodes;
};

#endif