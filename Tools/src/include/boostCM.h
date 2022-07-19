#ifndef boostCM_h
#define boostCM_h

#include <cmath>
#include <Math/LorentzVector.h>
#include <Math/Vector4D.h>
#include <Math/Vector4Dfwd.h>
#include <Math/Boost.h>
#include "constants.h"

typedef ROOT::Math::PxPyPzMVector LVector;
typedef ROOT::Math::Boost LBoost;

inline LBoost boostToCM(int beamMomentum) {
    const LVector beam(0.,0.,(double)beamMomentum,constants::nucleon_mass), 
                  target(0.,0.,0.,constants::nucleon_mass);
    const LVector vecCM = beam + target;
    return LBoost( vecCM.BoostToCM()  );
}

inline LBoost boostFromCM(int beamMomentum) {
    return boostToCM(beamMomentum).Inverse();
}

#endif // #ifndef boostCM_h
