#ifndef _CLVector_h_
#define _CLVector_h_

#include <TVector3.h>
#include "boostCM.h"
#include <functional>

class CLVector: public LVector {
public:
    // Constructor from LVector
    CLVector(const LVector& t) : LVector(t) {}
    // Named constructors
    static CLVector MPxPyPz(double m = 0, double px = 0, double py = 0, double pz = 0);
    static CLVector MPz(double m, double pz);
    static CLVector MPxPyY(double m, double px, double py, double y);
    static CLVector MPtYPhi(double m, double pt, double y, double phi = 0.);
    // methods
    inline double  Sx()  const { return Px() / Pxz(); }
    inline double  Sy()  const { return Py() / Pxz(); }
    inline double RhoT() const { return 1.0  / Pxz(); }
    inline double Qinv(const CLVector& t) const { return 0.5 * sqrt( -((*this)-t).mag2() ); }
    inline double DeltaPt(const CLVector& t) const {
        return ( TVector3(Px(), Py(), 0.) -
                 TVector3(t.Px(),t.Py(),0.) ).Perp();
    }
private:
    // methods
    inline double Pxz() const { return TVector3(Px(),0.,Pz()).Mag(); }    
    // private constructor
    CLVector(double px, double py, double pz, double mass);
};

inline CLVector::CLVector(double px, double py, double pz, double mass) : LVector(px,py,pz,mass) {}

inline CLVector CLVector::MPxPyPz(double m, double px, double py, double pz) { return CLVector(px,py,pz,m); }

inline CLVector CLVector::MPz(double m, double pz) { return CLVector(0, 0, pz,m); }

inline CLVector CLVector::MPxPyY(double m, double px, double py, double y) {
    const double mt = sqrt(px * px + py * py + m * m);
    return CLVector(px, py, mt * sinh(y), m);
}

inline CLVector CLVector::MPtYPhi(double m, double pt, double y, double phi) {
    const double mt = sqrt(pt * pt + m * m);
    return CLVector(pt * cos(phi), pt * sin(phi), mt * sinh(y), m);
}

/* lift ( LVector -> LVector )  -> ( CLVector -> CLVector ) */
typedef std::function<LVector (const LVector&)> LVectorFunc;
auto liftV = [](LVectorFunc func) { return [func](const CLVector& t){ return CLVector(func((LVector)t));  }; };
// inline CLVector CLBoosted(const LBoost& boost, const CLVector& t) { return CLVector( boost( (LVector)t ) ); }

#endif // #ifndef _CLVector_h_
