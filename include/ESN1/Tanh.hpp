#ifndef TANH
#define TANH

#include "Activation.hpp"

class TanH : public Activation{
    public:
    TanH();
    VectorXd compute(VectorXd);
};


#endif