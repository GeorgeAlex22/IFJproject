#ifndef Event_h
#define Event_h

#include <Rtypes.h>
#include <vector>

namespace EventClass {

/* TrackCore Class */

struct TrackCoreBind {
    double &px, &py, &pz;
    double &dEdx;
    double &probElectron, &probPion, &probKaon, &probProton, &probDeuteron;
    unsigned int &clustersAll;
    
    TrackCoreBind(double &px, double &py, double &pz,
                  double &dEdx,
                  double &probElectron, double &probPion,
                  double &probKaon, double &probProton,
                  double &probDeuteron,
                  unsigned int &clustersAll) :
                  px(px), py(py), pz(pz),
                  dEdx(dEdx),
                  probElectron(probElectron),
                  probPion(probPion),
                  probKaon(probKaon), 
                  probProton(probProton),
                  probDeuteron(probDeuteron),
                  clustersAll(clustersAll)
    {}
};


class TrackCore
{
public:
    TrackCore();
    TrackCore(TrackCoreBind trackCoreBind);
    
    double px, py, pz;
    double dEdx;
    double probElectron, probPion, probKaon, probProton, probDeuteron;
    unsigned int clustersAll;

    ClassDefNV(TrackCore,4);
};


/* Track Class */

struct TrackBind {
    double &bx, &by;
    double &NPratio;
    unsigned int &clustersVTPC1, &clustersVTPC2, 
                 &clustersGTPC, 
                 &clustersdEdx, &clustersPotentialAll;
    TrackCoreBind &trackCoreBind;
    
    TrackBind(TrackCoreBind &trackCoreBind,
              double &bx, double &by,
              double &NPratio,
              unsigned int &clustersVTPC1, 
              unsigned int &clustersVTPC2, 
              unsigned int &clustersGTPC, 
              unsigned int &clustersdEdx,
              unsigned int &clustersPotentialAll) :
              trackCoreBind(trackCoreBind),
              bx(bx), by(by),
              NPratio(NPratio),
              clustersVTPC1(clustersVTPC1), 
              clustersVTPC2(clustersVTPC2), 
              clustersGTPC(clustersGTPC), 
              clustersdEdx(clustersdEdx),
              clustersPotentialAll(clustersPotentialAll)
    {}
};


class Track : public TrackCore
{
public:
    Track();
    Track(const TrackCore& tc);
    Track(TrackBind trackBind);

    double bx, by;
    double NPratio;
    unsigned int clustersVTPC1, clustersVTPC2, 
                 clustersGTPC, 
                 clustersdEdx, clustersPotentialAll;

    ClassDefNV(Track,5);
};


/* Event Class */

struct EventBind {
    unsigned int &run_number, &event_id;
    unsigned int &cBin;
    unsigned int &nTracksFit, &nTracksAll;
    double &VertexZ;
    double &energySpectatorModules, &energyAllPSDModules;
    
    EventBind(unsigned int &run_number, unsigned int &event_id,
              unsigned int &cBin,
              unsigned int &nTracksFit, unsigned int &nTracksAll,
              double &VertexZ,
              double &energySpectatorModules, double &energyAllPSDModules) :
              run_number(run_number), event_id(event_id),
              cBin(cBin),
              nTracksFit(nTracksFit), nTracksAll(nTracksAll),
              VertexZ(VertexZ),
              energySpectatorModules(energySpectatorModules), energyAllPSDModules(energyAllPSDModules)
    {}
};


class Event
{
public:
    Event();
    Event(EventBind eventBind);
    
    unsigned int run_number, event_id;
    unsigned int cBin;
    unsigned int nTracksFit, nTracksAll;
    double VertexZ;
    double energySpectatorModules, energyAllPSDModules;
    std::vector<Track> tracks;

    
    ClassDefNV(Event,4);
};

}

#endif // #ifndef Event_h
