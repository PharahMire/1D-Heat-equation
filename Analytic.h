#ifndef ANALYTIC_H
#define ANALYTIC_H

#include "Method.h"

class Analytic : public Method {
public:
    Analytic(double dx, double L, double D, double T_sur, double Tin);
    void compute() override;
private:
    double dx, L, D, T_sur, Tin;
    int nSpaceNodes;
};

#endif
