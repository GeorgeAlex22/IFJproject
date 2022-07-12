#ifndef _BetheBloch_h_
#define _BetheBloch_h_

#include <cmath>
#include <vector>
#include <stdexcept>

namespace Dedx {

  class BetheBlochParametric {
  public:
    BetheBlochParametric()
      : fAlpha(0), fX0(0), fX1(0), fE0(0), fB(0), fM(0), fXA(0), fA(0)
    {}

    void
    Set(const std::vector<double>& parameters)
    {
      if (parameters.size() != 10)
        throw std::runtime_error("exactly 10 parameters needed for Bethe-Bloch formula");

      Set(parameters[0],
          parameters[1],
          parameters[2],
          parameters[3],
          parameters[4],
          parameters[5],
          parameters[6],
          parameters[7],
          parameters[8],
          parameters[9]);
    }

    double
    operator()(const int iParticle, const double p /* GeV */)
      const
    {
      static const double kLn10 = std::log(10);

      const double bg = p / fMass[iParticle];

      const double beta = bg / std::sqrt(1.0 + bg*bg);
      const double gamma = 1.0/std::sqrt(1.0 - beta*beta);
      const double x = std::log10(bg);

      double delta = 0.0;
      if (fX0 < x) {
        delta = 2.0 * kLn10 * (x - fXA);
        if (x < fX1)
          delta += + fA * std::pow(fX1 - x, fM);
      }

      return fE0 * std::pow(beta, fAlpha) * (fB + 2.0 * std::log(gamma) - beta*beta - delta);
    }

  private:
    void
    Set(const double alpha, const double mu,
        const double x0, const double x1, const double s,
        const double mElectron = 511.e-6,
        const double mPion = 0.13957,
        const double mKaon = 0.49367,
        const double mProton = 0.93827,
        const double mDeuteron = 1.8756)
    {
      static const double kLn10 = std::log(10);

      fMass[0] = mElectron;
      fMass[1] = mPion;
      fMass[2] = mKaon;
      fMass[3] = mProton;
      fMass[4] = mDeuteron;

      fAlpha = alpha;
      fX0 = x0;
      fX1 = x1;

      const double betaMin = mu/std::sqrt(1.0 + std::pow(mu,2));
      const double betaMin2 = betaMin*betaMin;

      fE0 = -alpha/2.0*(1.0 - betaMin2)/std::pow(betaMin, alpha + 4.0);
      fB = std::pow(mu, 2) * (1.0 - betaMin2*(1.0 + 2.0/alpha)) + std::log(1.0 - betaMin2);
      fM = (x1 - x0) / ( (s/fE0 - fB + 1.0) / (2.0*kLn10) - x0 );
      fXA = x0 - (x0 - x1)/fM;
      fA = 2.0 * kLn10 / fM * std::pow(x1 - x0, 1.0 - fM);
    }


    double fAlpha;
    double fX0;
    double fX1;
    double fE0;
    double fB;
    double fM;
    double fXA;
    double fA;
    double fMass[5];
  };


  double BetheBlochTabulated(const unsigned int iParticle, const double p);


  // typedef BetheBlochParametric BetheBloch;

  // Wrapper to be able to choose between parametric and tabulated
  class BetheBloch {
  public:
    BetheBloch() :
      fParametric(false),
      fInitialized(false)
    { }

    void
    Set(const std::vector<double>& parameters)
    {
      if (parameters.size() > 1) {
        fParametric = true;
        fParametricBB.Set(parameters);
      }
      fInitialized = true;
    }

    double
    operator()(const int iParticle, const double p /* GeV */)
      const
    {
      if (!fInitialized)
        throw std::runtime_error("Set the BetheBloch before using");

      if (fParametric)
        return fParametricBB(iParticle, p);

      return BetheBlochTabulated(iParticle, p);
    }

  private:
    bool fParametric;
    bool fInitialized;
    BetheBlochParametric fParametricBB;
  };


} // NS Dedx

#endif
