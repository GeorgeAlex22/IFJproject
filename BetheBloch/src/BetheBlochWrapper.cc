#include "BetheBlochWrapper.h"

using namespace Dedx;

BetheBlochWrapper::BetheBlochWrapper(const std::vector<double>& parameters) : fBB()
{
    fBB.Set(parameters);
    return;
}

BetheBlochWrapper::BetheBlochWrapper() : BetheBlochWrapper(std::vector<double>{
                                                           -1.962, 3.639, 1.303, 4.080, 1.583,
                                                            0.510998902e-3,
                                                            139.57018e-3, 
                                                            493.677e-3, 
                                                            938.271998e-3, 
                                                            1875.612762e-3}) {}
                                                            
double BetheBlochWrapper::operator()(const int iParticle, const double p /* GeV */) const { return fBB(iParticle,p); }
