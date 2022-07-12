#ifndef _BetheBlochWrapper_h_
#define _BetheBlochWrapper_h_

#include "BetheBloch.h"

namespace Dedx
{
    class BetheBlochWrapper
    {
    public:
        BetheBlochWrapper();
        BetheBlochWrapper(const std::vector<double> &parameters);
        /*
                                  const double alpha, const double mu,
                                  const double x0, const double x1, const double s,
                                  const double mElectron,
                                  const double mPion,
                                  const double mKaon,
                                  const double mProton,
                                  const double mDeuteron);
        */
        double operator()(const int iParticle, const double p /* GeV */) const;

    private:
        Dedx::BetheBlochParametric fBB;
    };
}

#endif // #ifndef _BetheBlochWrapper_h_
