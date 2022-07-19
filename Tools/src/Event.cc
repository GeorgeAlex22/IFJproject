#include "Event.h"

using namespace EventClass;

ClassImp(TrackCore);
ClassImp(Track);
ClassImp(Event);

TrackCore::TrackCore()
     : px(0), py(0), pz(0),
       dEdx(0),
       probElectron(0), probPion(0), probKaon(0), probProton(0), probDeuteron(0),
       clustersAll(0)
    {}
    
TrackCore::TrackCore(TrackCoreBind trackCoreBind)
     : px(trackCoreBind.px),
       py(trackCoreBind.py), 
       pz(trackCoreBind.pz),
       dEdx(trackCoreBind.dEdx),
       probElectron(trackCoreBind.probElectron), 
       probPion(trackCoreBind.probPion), 
       probKaon(trackCoreBind.probKaon), 
       probProton(trackCoreBind.probProton), 
       probDeuteron(trackCoreBind.probDeuteron),
       clustersAll(trackCoreBind.clustersAll)
    {}

Track::Track()
     : bx(0), by(0), NPratio(0),
       clustersVTPC1(0), clustersVTPC2(0),
       clustersGTPC(0), clustersdEdx(0), clustersPotentialAll(0)
    {}

Track::Track(const TrackCore& tc)
     : bx(0), by(0), NPratio(0),
       clustersVTPC1(0), clustersVTPC2(0),
       clustersGTPC(0), clustersdEdx(0), clustersPotentialAll(0),
       TrackCore(tc)
    {}

Track::Track(TrackBind trackBind)
     : bx(trackBind.bx), 
       by(trackBind.by), 
       NPratio(trackBind.NPratio),
       clustersVTPC1(trackBind.clustersVTPC1), 
       clustersVTPC2(trackBind.clustersVTPC2),
       clustersGTPC(trackBind.clustersGTPC), 
       clustersdEdx(trackBind.clustersdEdx), 
       clustersPotentialAll(trackBind.clustersPotentialAll),
       TrackCore(trackBind.trackCoreBind)
    {}

Event::Event()
     : run_number(0), event_id(0), cBin(0),
       nTracksFit(0), nTracksAll(0), VertexZ(0),
       energySpectatorModules(0), energyAllPSDModules(0)
     {}

Event::Event(EventBind eventBind)
     : run_number(eventBind.run_number), 
       event_id(eventBind.event_id), 
       cBin(eventBind.cBin),
       nTracksFit(eventBind.nTracksFit), 
       nTracksAll(eventBind.nTracksAll), 
       VertexZ(eventBind.VertexZ),
       energySpectatorModules(eventBind.energySpectatorModules), 
       energyAllPSDModules(eventBind.energyAllPSDModules)
     {}
