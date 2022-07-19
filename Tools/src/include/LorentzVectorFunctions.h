#ifndef LorentzVectorFunctions_h
#define LorentzVectorFunctions_h

#include <TVector3.h>
#include "boostCM.h"

inline LVector MakeFromMPtYPhi(const double m, const double pt, const double y, const double phi = 0.0) {
    const double mt = sqrt(pt * pt + m * m);
    return LVector(pt * cos(phi), pt * sin(phi), mt * sinh(y), m);
}

inline LVector MakeFromMPxPyY(const double m, const double px, const double py, const double y) {
    const double mt = sqrt(px * px + py * py + m * m);
    return LVector(px, py, mt * sinh(y), m);
}

inline LVector MakeFromMPz(const double m, const double pz) {
    return LVector(0, 0, pz, m);
}

inline double DeltaPt(const LVector& t1, const LVector& t2) {
    const TVector3 v1(t1.Px(),t1.Py(),0.);
    const TVector3 v2(t2.Px(),t2.Py(),0.);
    
    return (v1-v2).Perp();
}


inline double qInv(const LVector& t1, const LVector& t2) {
    return 0.5 * sqrt( -(t1-t2).mag2() );
}

inline double pxy(const LVector& t) { return TVector3(t.Px(),0.,t.Pz()).Mag(); }
inline double  sx(const LVector& t) { return t.Px() / pxy(t); }
inline double  sy(const LVector& t) { return t.Py() / pxy(t); }
inline double rho(const LVector& t) { return 1.0    / pxy(t); }

#endif //  #ifndef LorentzVectorFunctions_h

